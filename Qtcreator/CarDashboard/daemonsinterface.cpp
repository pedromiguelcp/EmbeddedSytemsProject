#include "daemonsinterface.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <QDebug>
#include <QString>

DaemonsInterface::DaemonsInterface(): USBDaemonPid(0), MusicDaemonPid(0), DashDaemonPid(0)
{
    initDaemons();
}

pid_t DaemonsInterface::getmusicpid()
{
    return this->MusicDaemonPid;
}

void DaemonsInterface::initDaemons()
{
    this->readMusicDaemonPid();

    this->readUSBDaemonPid();

    this->writeDashPid();

    if(this->USBDaemonPid > 0)
        kill(this->USBDaemonPid,SIGUSR2);
}

void DaemonsInterface::readUSBDaemonPid()
{
   key_t key = ftok("/Daemons/USBDaemon", 65);
   if (key == (key_t) -1) {
                  qDebug() << "Function ftok failed with errno = " << strerror(errno);
              }

   //shmget returns an identifier in shmid
   int shmid = shmget(key,1024,0666|IPC_CREAT);

   //shmat to attach to shared memory
   char *str = (char*) shmat(shmid,nullptr,0);

   this->USBDaemonPid = atoi(str);
   qDebug() << "USB Daemon Pid:" << this->USBDaemonPid;

   //detach from shared memory
   shmdt(str);

   //destroy the shared memory
   shmctl(shmid,IPC_RMID,nullptr);
}

void DaemonsInterface::readMusicDaemonPid()
{
   //ftok to generate unique key
   key_t key = ftok("/Daemons/MusicDaemon",65);
   if(key == -1) {
         qDebug() << "Function ftok failed with errno = " << strerror(errno);
       }

   //shmget returns an identifier in shmid
   int shmid = shmget(key,1024,0666|IPC_CREAT);

   //shmat to attach to shared memory
   char *str = (char*) shmat(shmid,nullptr,0);

   this->MusicDaemonPid = atoi(str);
   qDebug() << "Music Daemon Pid:" << this->MusicDaemonPid;

   //detach from shared memory
   shmdt(str);

   //destroy the shared memory
   shmctl(shmid,IPC_RMID,nullptr);
}

void DaemonsInterface::writeDashPid()
{
    DashDaemonPid = getpid();

    // ftok to generate unique key
    key_t   key = ftok("/Daemons/MainProcess",65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char* str = (char*) shmat(shmid,nullptr,0);

    //Write to the shared memory the process ID
    sprintf(str, "%d", DashDaemonPid);
    qDebug() << "Dash Pid:" << DashDaemonPid;

    //detach from shared memory
    shmdt(str);
}

QString DaemonsInterface::readUSBDaemonData()
{
    //cleans the flag
    //WaitingSignal = 1;
    this->USBDaemonData = "";

    //ftok to generate unique key
    key_t key = ftok("usb",65);

    //shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    //shmat to attach to shared memory
    char *str = (char*) shmat(shmid,nullptr,0);

    this->USBDaemonData.append(str);
    //myMusic->setNewstorageDevie(str);

    //detach from shared memory
    shmdt(str);

    //destroy the shared memory
    shmctl(shmid,IPC_RMID,nullptr);

    return this->USBDaemonData;
}

