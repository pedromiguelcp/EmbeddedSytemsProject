#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H

#include <string.h>
#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h> //mkdir also
#include <fcntl.h>
#include <sys/mount.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

using namespace std;

class DeviceWatcher
{
public:
    DeviceWatcher();
    void ShowPluggedInDevices();
    int WatchNewPluggedDevices();
    void DeamonizeMyProcess();
    void getMainProcessPID();
    void giveMyPID();
    void sendNewestDir();
    void WriteOnMyLog(const char *message);

private:
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices;
    struct udev_device *dev;

    int fd_udev;
    struct epoll_event ep_udev;

    struct udev_monitor *mon;
    int fd_ep = -1;

    int  NUM_OF_EVENTS;

    string action;
    string partition;
    string devicesubsystem;
    string devicenode;

    //Directories / Mounting Points
    //used to check if the dir exists
    DIR *dir;
    //base mountingfolder
    string MountingFolder;
    //name of the folder
    vector <string> folders;
    //index for the vector
    char currentmountedFolder;

    sem_t * semaphore;

    pid_t myPid;
    pid_t mainProcessPid;

    pid_t pid, sid;
	int len, fd;
	

};

#endif // DEVICEWATCHER_H