#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include "main.h"

#define BITS 8

static volatile char waitingSignal = 1;


static char* GetMusicName(void);
static void DaemonizeMyProcess(pid_t pid);
static void GiveProcessID(void);
static void initializeM3(Music *MusicDaemon);




void sig_handler(int sig){

    if(sig == SIGSTOP){
        printf("Received a SIGSTOP");
    }
    if(sig == SIGCONT){
        printf("Received a SIGSCONT");
    }
    //Come;ar uma musica
    if(sig == SIGUSR1){
        waitingSignal = 0;
        printf("signal received");
    }
}

//Note - i can use signals like interrupts to stop or start the music and change music

int main(int argc, char *argv[])
{
    char *str, musicname[100];
    Music MusicDaemon;
    pid_t pid;
    int volatile musicOver = 0;


    DaemonizeMyProcess(pid);
    //Tells the other process what is his ID
    GiveProcessID();

    //calls sig_handler when one of the signals is received
    signal(SIGSTOP, sig_handler) ;
    signal(SIGCONT, sig_handler) ;
    signal(SIGUSR1, sig_handler);

    initializeM3(&MusicDaemon);

    //Runs until the program ends
    while(1)
    {
        //wait for something in the shared memory
        while(waitingSignal);
        waitingSignal = 1;

        //Gets the music name and location
        str = GetMusicName();

        //saves it to a string
        strcpy(musicname, str);

        printf("%music name : s", str);

        //Detach from memory
        shmdt(str);

        /* open the file and get the decoding format */
        mpg123_open_64(MusicDaemon.mh, musicname);
        mpg123_getformat(MusicDaemon.mh, &MusicDaemon.rate, &MusicDaemon.channels, &MusicDaemon.encoding);

        /* set the output format and open the output device */
        MusicDaemon.format.bits = mpg123_encsize(MusicDaemon.encoding) * BITS;
        MusicDaemon.format.rate = MusicDaemon.rate;
        MusicDaemon.format.channels = MusicDaemon.channels;
        MusicDaemon.format.byte_format = AO_FMT_NATIVE;
        MusicDaemon.format.matrix = 0;
        MusicDaemon.dev = ao_open_live(MusicDaemon.driver, &MusicDaemon.format, NULL);

        /* decode and play */
        while ((musicOver = mpg123_read(MusicDaemon.mh, MusicDaemon.buffer, MusicDaemon.buffer_size, &MusicDaemon.done)) == MPG123_OK & waitingSignal == 1)
        {
            //Play a block of audio data to an open device
            ao_play(MusicDaemon.dev, MusicDaemon.buffer, (char *)MusicDaemon.done);
            if(waitingSignal == 0)
                break;
        }
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
    int shmid; //used for shared memory
    char *str;

    // ftok to generate unique key
    key_t key = ftok("musicnames",65);

    // shmget returns an identifier in shmid
    shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    str = (char*) shmat(shmid,(void*)0,0);

    printf("Data read from memory: %s\n",str);

    return str;
}


void DaemonizeMyProcess(pid_t pid)
{
    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("mp3deamon", LOG_PID, LOG_DAEMON);
}


void GiveProcessID(void)
{
    int shmid; //used for shared memory
    char *str;

    // ftok to generate unique key
    key_t key = ftok("daemonpid",65);

    // shmget returns an identifier in shmid
    shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    str = (char*) shmat(shmid,(void*)0,0);

    //Write to the shared memory the process ID
    sprintf(str, "%d", getpid());

    printf("Data written in memory: %s\n",str);

    //detach from shared memory
    shmdt(str);
}


void initializeM3(Music *MusicDaemon)
{
    /* initializations */
    ao_initialize();
    MusicDaemon->driver = ao_default_driver_id();
    mpg123_init();
    MusicDaemon->mh = mpg123_new(NULL, MusicDaemon->err);
    MusicDaemon->buffer_size = mpg123_outblock(MusicDaemon->mh);
    MusicDaemon->buffer = (unsigned char*) malloc((MusicDaemon->buffer_size) * sizeof(unsigned char));
}
