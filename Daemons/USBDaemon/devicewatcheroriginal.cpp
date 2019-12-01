#include "devicewatcher.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <syslog.h>


//char SEM_NAME[] = "semaphore_name";



DeviceWatcher::DeviceWatcher()
{
    this->fd_udev = -1;
    this->ep_udev = { 0 };
    this->fd_ep = -1;

    this->udev = udev_new();
    if (!this->udev) {
            printf("Can't create udev\n");
            exit(1);
    }
    this->NUM_OF_EVENTS = 5;

    //this->folders.push_back("fpen");
    //this->folders.push_back("spen");
    //this->folders.push_back("tpen");
    //this->folders.push_back("ftpen");
    this->MountingFolder = "/media/";
    this->currentmountedFolder =0;
}

void DeviceWatcher::getMainProcessPID()
{
    // ftok to generate unique key
    key_t key = ftok("mainprocess",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Main Process PID: %s\n",str);

        mainProcessPid = atoi(str);

       //detach from shared memory
       shmdt(str);

       // destroy the shared memory
       shmctl(shmid,IPC_RMID,NULL);
}

void DeviceWatcher::giveMyPID()
{
     myPid = getpid();


     // ftok to generate unique key
       key_t   key = ftok("udev",65);

         // shmget returns an identifier in shmid
        int shmid = shmget(key,1024,0666|IPC_CREAT);

        // shmat to attach to shared memory
        char* str = (char*) shmat(shmid,(void*)0,0);

        //Write to the shared memory the process ID
       sprintf(str, "%d", myPid);

        printf("Daemon PID: %s\n",str);

       //detach from shared memory
        shmdt(str);

}

void DeviceWatcher::DeamonizeMyProcess(){

    /* Fork off the parent process */
    myPid = fork();

    /* An error occurred */
    if (myPid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (myPid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    myPid = fork();

    /* An error occurred */
    if (myPid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (myPid > 0)
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
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);

}

void DeviceWatcher::ShowPluggedInDevices(){

    enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, "scsi");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
    udev_enumerate_scan_devices(enumerate);

    devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    /// enumerate through any that are installed
    udev_list_entry_foreach(entry, devices) {

            const char *path = udev_list_entry_get_name(entry);
            struct udev_device *scsi = udev_device_new_from_syspath(udev, path);

            struct udev_device *usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

            if (usb) {
                    printf("usb = %s:%s, scsi = %s\n",
                           udev_device_get_sysattr_value(usb, "idVendor"),
                           udev_device_get_sysattr_value(usb, "idProduct"),
                           udev_device_get_sysattr_value(scsi, "vendor"));
            }

            udev_device_unref(scsi);
    }

    udev_enumerate_unref(enumerate);


}

int DeviceWatcher::WatchNewPluggedDevices(){

    string aux;
        /// Begin active polling for USB input and output

        mon = udev_monitor_new_from_netlink(udev, "udev");
        udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
        udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
        udev_monitor_enable_receiving(mon);

        /// Setup epoll
        fd_ep = epoll_create1(0);
        if (fd_ep < 0) {
                fprintf(stderr, "error creating epoll\n");
                return 1;
        }

        fd_udev = udev_monitor_get_fd(mon);
        ep_udev.events = EPOLLIN;
        ep_udev.data.fd = fd_udev;
        if (epoll_ctl(fd_ep, EPOLL_CTL_ADD, fd_udev, &ep_udev) < 0) {
                fprintf(stderr, "fail to add fd to epoll\n");
                return 2;
        }

        /// Polling loop for devices
        while (1) {
                int fdcount;
                struct epoll_event ev[this->NUM_OF_EVENTS];
                int i = 0;

                fdcount = epoll_wait(fd_ep, ev, this->NUM_OF_EVENTS, -1);
                if (fdcount < 0) {
                        if (errno != EINTR)
                                fprintf(stderr, "error receiving uevent message: %m\n");
                        continue;
                }

                for (i = 0; i < fdcount; i++) {
                        if (ev[i].data.fd == fd_udev && ev[i].events & EPOLLIN) {

                                dev = udev_monitor_receive_device(mon);
                                if (dev == NULL)
                                        continue;

                            this->action = udev_device_get_action(dev);
                            this->devicenode = udev_device_get_devnode(dev);
                            this->devicesubsystem = udev_device_get_subsystem(dev);
                            this->partition = udev_device_get_devtype(dev);


                                    if(!partition.compare("partition")){
                                       aux = this->MountingFolder ; //+ this->folders[this->currentmountedFolder];
                                       this->dir = opendir(aux.c_str());
                                       //if(!dir){
                                            //    mkdir(aux.c_str(),777);
                                        //}
                                        //mkdir("/home/test/", 777);//create a folder
                                        mount(this->devicenode.c_str(), "media", "vfat", MS_NOATIME, NULL);
                                        //this->currentmountedFolder++;
                                      //  this->currentmountedFolder &= 0x03;

                                    //}
                                //}

                                udev_unref(udev);
                        }
                }
        }
    }
