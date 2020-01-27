#include "musicplayer.h"
#include <QDebug>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

MusicPlayer::MusicPlayer(pid_t musicDaemonPID){
    usbpath.setPath("/media1/");
    this->musicDaemonPID = musicDaemonPID;
    changeMusicVolume(70);
    musicindex=0;
}

void MusicPlayer::setNewstorageDevie(QString newDevice)
{
    usbpath.setPath(newDevice);
}

void MusicPlayer::setnewSong(QString song)
{
    QString musicPath(usbpath.path());

    musicPath.append("/");
    musicPath.append(song);

    //Resumes the daemon if it was paused
    //this->continueMusic();

    usleep(100);

    this->currentsong = song;

    qDebug() << this->currentsong;

    //ftok to generate unique key
    key_t key = ftok("musicnames",65);

    //shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    //shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);

    //Write to the shared memory the process ID

    strcpy(str, musicPath.toStdString().c_str());

    //detach from shared memory
    shmdt(str);

    kill(this->musicDaemonPID, SIGUSR1);

    musicindex = 0;
    foreach(QString filename, musicslist) {
        if(song == filename)
            break;
        else musicindex++;
    }
    qDebug() << "index:" << musicindex;
}

QString MusicPlayer::getSongs()
{
    QDir directory("/media1");
    musicslist.clear();
    musicslist = directory.entryList(QStringList() << "*.mp3", QDir::Files);
    qDebug() << usbpath.path();

    return usbpath.path();
}

QString MusicPlayer::getcurrentSong()
{
    return this->currentsong.replace(".mp3","");
}

void MusicPlayer::pauseCurrentSong()
{
    kill(this->musicDaemonPID, SIGUSR2);
}

void MusicPlayer::resumeCurrentSong()
{
    kill(this->musicDaemonPID, SIGCONT);
}

void MusicPlayer::changeMusicVolume(int volume)
{
    this->musicVolume = volume;

    std::string control = "amixer -M set PCM ";
    control += std::to_string(volume);
    control += "%";
    system(control.c_str());
}

int MusicPlayer::getMusicVolume()
{
    return this->musicVolume;
}

void MusicPlayer::nextSong()
{
    if(musicindex == (musicslist.length() - 1))
        musicindex = 0;
    else musicindex ++;

    setnewSong(musicslist.at(musicindex));
}

void MusicPlayer::previousSong()
{
    if(musicindex == 0)
        musicindex = 0;
    else musicindex --;

    setnewSong(musicslist.at(musicindex));
}
