#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <mqueue.h>   /* mq_* functions */
#include "main.h"

#define BITS 8

static volatile char waitingSignal = 1;
static char strlog[255];

static char* GetMusicName(void);
static void DaemonizeMyProcess(pid_t pid);
static void GiveProcessID(void);
static void initializeM3(Music *MusicDaemon);
static void WriteOnMyLog(const char *message);


void sig_handler(int sig){

    if(sig == SIGSTOP){
        waitingSignal = 0;
    }
    else if(sig == SIGCONT){
    }
    //Come;ar uma musica
    else if(sig == SIGUSR1){
        waitingSignal = 0;
    }
}

//Note - i can use signals like interrupts to stop or start the music and change music

int main(int argc, char *argv[])
{
    char *str, musicname[100];
    char logaux[12];
    Music MusicDaemon;
    pid_t pid;
    int volatile musicOver = 0;
    int volatile format = 0;

    signal(SIGSTOP, sig_handler);
    signal(SIGCONT, sig_handler);
    signal(SIGUSR1, sig_handler);

    DaemonizeMyProcess(pid);

    //Tells the other process what is his ID
    GiveProcessID(); 

    initializeM3(&MusicDaemon);
    WriteOnMyLog("Initialization done, waiting for a signal!\n");

    //Runs until the program ends
    while(1)
    {
        //wait for something in the shared memory
        while(waitingSignal);
        waitingSignal = 1;
        WriteOnMyLog("Signal received!\n");

        //Gets the music name and location
        str = GetMusicName();

        //saves it to a string
        strcpy(musicname, str);

        //Detach from memory
        shmdt(str);

        /* open the file and get the decoding format */
        if(mpg123_open_64(MusicDaemon.mh, musicname) != MPG123_OK)
            WriteOnMyLog("Error on mpg123_open_fd!\n");

        if((format = mpg123_getformat(MusicDaemon.mh, &MusicDaemon.rate, &MusicDaemon.channels, &MusicDaemon.encoding)) != MPG123_OK)
            WriteOnMyLog("Error on mpg123_getformat!\n");
        
        /* set the output format and open the output device */
        MusicDaemon.format.bits = mpg123_encsize(MusicDaemon.encoding) * BITS;
        MusicDaemon.format.rate = MusicDaemon.rate;
        MusicDaemon.format.channels = MusicDaemon.channels;
        MusicDaemon.format.byte_format = AO_FMT_NATIVE;
        MusicDaemon.format.matrix = 0;
        MusicDaemon.dev = ao_open_live(MusicDaemon.driver, &MusicDaemon.format, NULL);

        /* decode and play */
        while ((musicOver = mpg123_read(MusicDaemon.mh, MusicDaemon.buffer, MusicDaemon.buffer_size, &MusicDaemon.done)) == MPG123_OK)
        {
            //Play a block of audio data to an open device
            ao_play(MusicDaemon.dev, MusicDaemon.buffer, (char *)MusicDaemon.done);
            if(waitingSignal == 0)
                break;
        }
        WriteOnMyLog("Music end!\n");
    }

    /* clean up */
    free(MusicDaemon.buffer);
    ao_close(MusicDaemon.dev);
    mpg123_close(MusicDaemon.mh);
    mpg123_delete(MusicDaemon.mh);
    mpg123_exit();
    ao_shutdown();

    //Deamon shutding down
    syslog (LOG_NOTICE, "Music Daemon close");
    closelog();

    return 0;
}


char* GetMusicName()
{
    // ftok to generate unique key
    key_t key = ftok("musicnames",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    memset(strlog, 0, sizeof strlog);
    strcpy(strlog, "Music selected: ");
    strcat(strlog, str);
    strcat(strlog, "\n");
    WriteOnMyLog(strlog);

    return str;
}


void DaemonizeMyProcess(pid_t pid)
{
    pid_t sid;
    char mypid[12];

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0)// on error exit 
    { 
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}
    /* Success: Let the parent terminate */
    if (pid > 0)
    {
        memset(strlog, 0, sizeof strlog);
        strcpy(strlog, "\nMusic DAEMON PID = ");  
        sprintf(mypid, "%d", pid);
        strcat(strlog, mypid);
        strcat(strlog, "\n");
        WriteOnMyLog(strlog);
        
        exit(EXIT_SUCCESS);
    }

    /* On success: The child process becomes session leader */
    sid = setsid(); // create a new session
	if (sid < 0)// on error exit
    { 
		syslog(LOG_ERR, "%s\n", "setsid");
		exit(EXIT_FAILURE);
	}

    // make '/' the root directory
	if (chdir("/") < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "chdir");
		exit(EXIT_FAILURE);
	}
    
	umask(0);

    close(STDIN_FILENO);  // close standard input file descriptor
	close(STDOUT_FILENO); // close standard output file descriptor
	close(STDERR_FILENO); // close standard error file descriptor
}


void GiveProcessID(void)
{
    /*mqd_t msgq_id;
    char msgcontent[50];
    unsigned int msgprio = 1;
    pid_t my_pid = getpid();
    // opening the queue using default attributes  --  mq_open() 
    msgq_id = mq_open("/myqueue", O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, NULL);
    if (msgq_id == (mqd_t)-1) {
        perror("In mq_open()");
        exit(1);
    }
    snprintf(msgcontent, 50, "%u", my_pid);
    // sending the message      --  mq_send() 
    mq_send(msgq_id, msgcontent, strlen(msgcontent)+1, msgprio);
    // closing the queue        -- mq_close() 
    mq_close(msgq_id);*/

    // ftok to generate unique key
    key_t key = ftok("/Daemons/MusicDaemon",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    if (str == (void *) -1)
    {
        perror("shmat");
        exit(1);
    }

    //Write to the shared memory the process ID
    sprintf(str, "%d", getpid());

    //detach from shared memory
    shmdt(str);
}


void initializeM3(Music *MusicDaemon)
{
    /* initializations */
    ao_initialize();
    MusicDaemon->driver = ao_default_driver_id();
    if(mpg123_init() != MPG123_OK)
        WriteOnMyLog("Error on mpg123_init\n");
    MusicDaemon->mh = mpg123_new(NULL, MusicDaemon->err);
    MusicDaemon->buffer_size = mpg123_outblock(MusicDaemon->mh);
    MusicDaemon->buffer = (unsigned char*) malloc((MusicDaemon->buffer_size) * sizeof(unsigned char));
}


void WriteOnMyLog(const char *message)
{
    int len = strlen(message);
    int fd;

	char *buf = (char *)malloc(sizeof(char) + len + 1);
	if (buf == NULL) 
    {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if ((fd = open("/var/log/musicdaemon.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) 
    {
		perror("open");
		exit(EXIT_FAILURE);
	}

	strncpy(buf, message, len + 1);
	write(fd, buf, len + 1);
	close(fd);
}
