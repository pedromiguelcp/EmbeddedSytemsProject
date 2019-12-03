#include "music.h"
#include <QDebug>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Music::Music(pid_t musicDaemonPID){
    usbpath.setPath("/media1/");
    this->musicDaemonPID = musicDaemonPID;
    changeMusicVolume(70);
}

void Music::setNewstorageDevie(QString newDevice)
{
    usbpath.setPath(newDevice);
}

void Music::setnewSong(QString song)
{
    QString musicPath(usbpath.path());

    musicPath.append("/");
    musicPath.append(song);

    //Resumes the daemon if it was paused
    //this->continueMusic();

    usleep(100);

    this->currentsong = musicPath;

    qDebug() << this->currentsong;

    //ftok to generate unique key
    key_t key = ftok("musicnames",65);

    //shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    //shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    //Write to the shared memory the process ID

    strcpy(str, currentsong.toStdString().c_str());

    //detach from shared memory
    shmdt(str);

    kill(this->musicDaemonPID, SIGUSR1);
}

QString Music::getSongs()
{
    return usbpath.path();
}

QString Music::getcurrentSong()
{
    return this->currentsong;
}

void Music::pauseCurrentSong()
{
    kill(this->musicDaemonPID, SIGSTOP);
}

void Music::resumeCurrentSong()
{
    kill(this->musicDaemonPID, SIGCONT);
}

void Music::changeMusicVolume(int volume)
{
    this->musicVolume = volume;

    std::string control = "amixer -M set PCM ";
    control += std::to_string(volume);
    control += "%";
    system(control.c_str());
}

int Music::getMusicVolume()
{
    return this->musicVolume;
}
