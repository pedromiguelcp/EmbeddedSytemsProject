#include "dash.h"
#include <signal.h>
#include <QDebug>
#include <QTimer>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtAlgorithms>
#include <iostream>
#include <string>
#include <unistd.h>

volatile char USBSignal;

Dash::Dash()
{
    signal(SIGUSR2, this->signalsHandler);

    MyDaemon = new Daemon ();
    MyDaemon->initDaemons();

    MusicPlayer = new Music (MyDaemon->getmusicpid());

    LedStrip = new DDriver ();
    LedStrip->setLedStripColor("0");

    STMUART = new UartSTM ();

    NetworkInfo = new Network ();
    //NetworkInfo->requestWeather();
    NetworkInfo->requestNews();

    USBSignal = 1;
    DashBright_prctg = 100;
}

void Dash::setColor(QString id_color)
{
    LedStrip->setLedStripColor(id_color);
}



void Dash::sendCommand(QString command)
{
    STMUART->sendCommandSTM(command);
}



void Dash::SetPthreads()
{
    USBMonitor_param.sched_priority = 3;
    pthread_attr_setdetachstate(&USBMonitor_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&USBMonitor_attr,&USBMonitor_param);
    pthread_attr_init(&USBMonitor_attr);
    pthread_create(&USBMonitor_thread, &USBMonitor_attr, USBMonitorThread, this);
}

void Dash::JoinPthreads()
{
    pthread_join(USBMonitor_thread, nullptr);
}

void Dash::SetMutexes()
{
    pthread_mutex_init(&USBMonitor_mutex, nullptr);
}

void Dash::DestroyMutexes()
{
    pthread_mutex_destroy(&USBMonitor_mutex);
}



void *Dash::USBMonitorThread(void *usbaux)
{
    Dash * usbMonitor = (Dash *)usbaux;
    QString Devicepath;

    while(1)
    {
        if(!USBSignal)
        {
            Devicepath =  usbMonitor->getUSBDaemonData();

            //pthread_mutex_lock(&myDeviceWatcher->dwatchermutex);
            usbMonitor->setNewDevice(Devicepath);
            qDebug() << "USB device path:" << Devicepath;
            //pthread_mutex_unlock(&myDeviceWatcher->dwatchermutex);

            Devicepath.clear();
            USBSignal = 1;
            //signal(SIGUSR2, signalsHandler);

        }
        //pthread_yield();
    }

}


QString Dash::getUSBDaemonData()
{
    return MyDaemon->readUSBDaemonData();
}

void Dash::setNewDevice(QString Devicepath)
{
    MusicPlayer->setNewstorageDevie(Devicepath);
}



void Dash::signalsHandler(int signal)
{
    if(signal == SIGUSR2)
    {
        USBSignal = 0;
    }
}



void Dash::selectSong(QString song)
{
    MusicPlayer->setnewSong(song);
}

QString Dash::getDeviceSongs()
{
    return MusicPlayer->getSongs();
}

QString Dash::currentSong()
{
    return MusicPlayer->getcurrentSong();
}

void Dash::pauseSong()
{
    MusicPlayer->pauseCurrentSong();
}

void Dash::resumeSong()
{
    MusicPlayer->resumeCurrentSong();
}



void Dash::openCamera()
{
    /*qDebug() << "Open Camera";
    system("/OpenCamera.sh");*/
    //NetworkInfo->printweather();
    NetworkInfo->printnews();
}

void Dash::closeCamera()
{
    qDebug() << "Close Camera";
    system("/CloseCamera.sh");
}

void Dash::adjustDashBright(QString command)
{
    if(command == "+" && DashBright_prctg != 100)
    {
        DashBright_prctg += 10;
    }
    else if (command == "-" && DashBright_prctg != 0)
    {
        DashBright_prctg -= 10;
    }
    else
        return ;
    std::string adjust = "echo ";
    adjust += std::to_string(DashBright_prctg * 255 / 100);
    adjust += " > /sys/class/backlight/rpi_backlight/brightness";
    system(adjust.c_str());
}



