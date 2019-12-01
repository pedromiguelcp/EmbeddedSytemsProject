#include "devicewatcher.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
using namespace std; 


DeviceWatcher::DeviceWatcher()
{
    this->fd_udev = -1;
    this->ep_udev = { 0 };
    this->fd_ep = -1;

    this->udev = udev_new();
    if (!this->udev) 
    {
        printf("Can't create udev\n");
        exit(1);
    }
    this->NUM_OF_EVENTS = 5;

    //this->folders.push_back("fpen");
    //this->folders.push_back("spen");
    //this->folders.push_back("tpen");
    //this->folders.push_back("ftpen");
    this->MountingFolder = "/media1/";
    this->currentmountedFolder = 0;
}


void DeviceWatcher::DeamonizeMyProcess()
{
    /* Fork off the parent process */
    myPid = fork();
    if (myPid < 0)// on error exit 
    { 
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}
    /* Success: Let the parent terminate */
    if (myPid > 0)
    {
        WriteOnMyLog((std::string("\nUSB DAEMON PID = ") + std::to_string(myPid) + "\n").c_str());
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


void DeviceWatcher::giveMyPID()
{
    myPid = getpid();

    // ftok to generate unique key
    key_t key = ftok("/Daemons/USBDaemon",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024, 0666 | IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    // shmat to attach to shared memory
    char* str = (char*) shmat(shmid,(void*)0,0);

    if (str == (void *) -1)
    {
        perror("shmat");
        exit(1);
    }

    //Write to the shared memory the process ID
    sprintf(str, "%d", myPid);

    //detach from shared memory
    shmdt(str);
}


void DeviceWatcher::getMainProcessPID()
{
    // ftok to generate unique key
    key_t key = ftok("/Daemons/MainProcess",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    mainProcessPid = atoi(str);

    //detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
    WriteOnMyLog((std::string("MAIN PROCESS PID = ") + std::to_string(mainProcessPid) + "\n").c_str());
}


void DeviceWatcher::ShowPluggedInDevices()
{
    enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    /// enumerate through any that are installed
    udev_list_entry_foreach(entry, devices)
    {

        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *scsi = udev_device_new_from_syspath(udev, path);

        struct udev_device *usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

        if (usb) 
        {
            WriteOnMyLog((std::string("USB = ") + 
            std::string(udev_device_get_sysattr_value(usb, "idVendor")) +
            std::string(":") + 
            std::string(udev_device_get_sysattr_value(usb, "idProduct")) +
            std::string(", SCSI = ") + 
            std::string(udev_device_get_sysattr_value(scsi, "vendor")) +
             "\n").c_str());

            kill(this->mainProcessPid, SIGUSR2);
            /*printf("usb = %s:%s, scsi = %s\n",
            udev_device_get_sysattr_value(usb, "idVendor"),
            udev_device_get_sysattr_value(usb, "idProduct"),
            udev_device_get_sysattr_value(scsi, "vendor"));*/
        }

        udev_device_unref(scsi);
    }

    udev_enumerate_unref(enumerate);
}


int DeviceWatcher::WatchNewPluggedDevices()
{
    string aux;
    // Begin active polling for USB input and output

    //Create a udev monitor object(eturns a pointer to the allocated udev monitor)
    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
    udev_monitor_enable_receiving(mon);

    // Setup epoll
    fd_ep = epoll_create1(0);
    if (fd_ep < 0) 
    {
        fprintf(stderr, "error creating epoll\n");
        return 1;
    }

    fd_udev = udev_monitor_get_fd(mon);
    ep_udev.events = EPOLLIN;
    ep_udev.data.fd = fd_udev;
    if (epoll_ctl(fd_ep, EPOLL_CTL_ADD, fd_udev, &ep_udev) < 0) 
    {
        fprintf(stderr, "fail to add fd to epoll\n");
        return 2;
    }

    // Polling loop for devices
    while (1) 
    {
        int fdcount;
        struct epoll_event ev[this->NUM_OF_EVENTS];
        int i = 0;

        fdcount = epoll_wait(fd_ep, ev, this->NUM_OF_EVENTS, -1);
        if (fdcount < 0) 
        {
            if (errno != EINTR)
                fprintf(stderr, "error receiving uevent message: %m\n");
            continue;
        }

        for (i = 0; i < fdcount; i++) 
        {
            if (ev[i].data.fd == fd_udev && ev[i].events & EPOLLIN) 
            {

                dev = udev_monitor_receive_device(mon);
                if (dev == NULL)
                    continue;

                this->action = udev_device_get_action(dev);
                this->devicenode = udev_device_get_devnode(dev);
                this->devicesubsystem = udev_device_get_subsystem(dev);
                this->partition = udev_device_get_devtype(dev);

                WriteOnMyLog(("\nAction: " + this->action + "\n" +
                              "Node: " + this->devicenode + "\n" +
                              "Partition: " + this->partition + "\n" +
                              "Subsystem: " + this->devicesubsystem + "\n").c_str());

                if(!this->action.compare("remove") && !partition.compare("partition"))
                {
                    aux = this->MountingFolder;// + this->folders[this->currentmountedFolder];
                    WriteOnMyLog(("\nUmountingFolder: " + aux + "\n").c_str());

                    this->dir = opendir(aux.c_str());
                    if(dir)
                    {
                        umount(aux.c_str());
                        rmdir(aux.c_str());

                        if(this->currentmountedFolder != 0)
                            this->currentmountedFolder--;
                        else
                            this->currentmountedFolder = 0;
                    }
                }
                else if(!this->action.compare("add") && !partition.compare("partition"))
                {
                    aux = this->MountingFolder;// + this->folders[this->currentmountedFolder];
                    WriteOnMyLog(("\nMountingFolder: " + aux + "\n").c_str());

                    this->dir = opendir(aux.c_str());
                    if(!dir)
                        mkdir(aux.c_str(),777);

                    mount(this->devicenode.c_str(), aux.c_str(), "vfat", MS_NOATIME, NULL);
                    this->currentmountedFolder++;
                    this->currentmountedFolder &= 0x03;

                    // ftok to generate unique key
                    key_t key = ftok("usb",65);

                    // shmget returns an identifier in shmid
                    int shmid = shmget(key,1024,0666|IPC_CREAT);

                    // shmat to attach to shared memory
                    char *str = (char*) shmat(shmid,(void*)0,0);

                    //write on the share memory the usb folder
                    strcpy(str, aux.c_str());

                    //detach from shared memory
                    shmdt(str);

                    kill(this->mainProcessPid, SIGUSR2);
                }
                WriteOnMyLog(("\nTeste: " + aux + "\n").c_str());
                udev_unref(udev);
            }
        }
    }
}



void DeviceWatcher::WriteOnMyLog(const char *message)
{
    int len = strlen(message);
	char *buf = (char *)malloc(sizeof(char) + len + 1);
	if (buf == NULL) 
    {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if ((fd = open("/var/log/firstdaemon.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) 
    {
		perror("open");
		exit(EXIT_FAILURE);
	}

	strncpy(buf, message, len + 1);
	write(fd, buf, len + 1);
	close(fd);
}