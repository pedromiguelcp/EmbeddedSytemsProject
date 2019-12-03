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
#include <sys/time.h>

static volatile char USBSignal;
static volatile char TimerSignal;


Dash::Dash()
{
    signal(SIGUSR2, this->signalsHandler);
    signal(SIGALRM, this->doWork);

    MyDaemon = new Daemon ();

    MusicPlayer = new Music (MyDaemon->getmusicpid());

    LedStrip = new DDriver ();

    STMUART = new UartSTM ();

    NetworkInfo = new Network ();

    connect(this, &Dash::askfornews, NetworkInfo, &Network::requestNews);
    connect(this, &Dash::askforweather, NetworkInfo, &Network::requestWeather);
    connect(this, &Dash::askforbrightness, STMUART, &UartSTM::requestBrightness);
    connect(this, &Dash::askfortemperature, STMUART, &UartSTM::requestTemperature);

    adjustDashBright(244);

    system("v4l2-ctl --set-fmt-overlay=top=0,left=50,width=690,height=600");

    USBSignal = 1;
    TimerSignal = 1;





    struct itimerval itv;

    itv.it_interval.tv_sec = 25; //tv_sec -> time in seconds;tv_usec -> time in useconds; total time in useconds = tv_usec + tv_sec*1000000
    itv.it_interval.tv_usec = 0; //it_interval -> period between successive timer interrupts, if 0 it will only be sent once.
    itv.it_value.tv_sec = 5;
    itv.it_value.tv_usec = 0; //it_value -> period between now and the first interrupt, if 0 it is disabled
    setitimer(ITIMER_REAL, &itv, nullptr); //ITIMER_REAL,ITIMER_VIRTUAL ITIMER_PROF -> types of interval timers available per process
}



/*******************************signals handler**********************************/
void Dash::signalsHandler(int signal)
{
    if(signal == SIGUSR2)
    {
        USBSignal = 0;
    }
}

void Dash::doWork(int signo)
{
    if(signo==SIGALRM)
    {
        TimerSignal = 0;
    }
}



/*******************************led strip**********************************/
void Dash::setColor(QString id_color)
{
    LedStrip->setLedStripColor(id_color);
}



/****************************uart communication******************************/
void Dash::sendCommand(QString command)
{
    STMUART->sendCommandSTM(command);
}



/****************************pthreads and mutexes***************************/
void Dash::SetPthreads()
{
    USBMonitor_param.sched_priority = 4;
    pthread_attr_setdetachstate(&USBMonitor_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&USBMonitor_attr,&USBMonitor_param);
    pthread_attr_init(&USBMonitor_attr);
    pthread_create(&USBMonitor_thread, &USBMonitor_attr, USBMonitorThread, this);

    NetworkInfo_param.sched_priority = 1;
    pthread_attr_setdetachstate(&NetworkInfo_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&NetworkInfo_attr,&NetworkInfo_param);
    pthread_attr_init(&NetworkInfo_attr);
    pthread_create(&NetworkInfo_thread, &NetworkInfo_attr, NetworkInfoThread, this);

    DashBright_param.sched_priority = 3;
    pthread_attr_setdetachstate(&DashBright_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&DashBright_attr,&DashBright_param);
    pthread_attr_init(&DashBright_attr);
    pthread_create(&DashBright_thread, &DashBright_attr, DashBrightThread, this);

    Temperatue_param.sched_priority = 2;
    pthread_attr_setdetachstate(&Temperatue_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&Temperatue_attr,&Temperatue_param);
    pthread_attr_init(&Temperatue_attr);
    pthread_create(&Temperatue_thread, &Temperatue_attr, TemperatueThread, this);

    Timer_param.sched_priority = 4;
    pthread_attr_setdetachstate(&Timer_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&Timer_attr,&Timer_param);
    pthread_attr_init(&Timer_attr);
    pthread_create(&Timer_thread, &Timer_attr, TimerThread, this);
}

void Dash::JoinPthreads()
{
    pthread_join(USBMonitor_thread, nullptr);
    pthread_join(NetworkInfo_thread, nullptr);
    pthread_join(DashBright_thread, nullptr);
    pthread_join(Temperatue_thread, nullptr);
}

void Dash::SetMutexes()
{
    pthread_mutex_init(&USBMonitor_mutex, nullptr);
}

void Dash::DestroyMutexes()
{
    pthread_mutex_destroy(&USBMonitor_mutex);
}



/*******************************threads**********************************/
void *Dash::USBMonitorThread(void *myDash)
{
    Dash * usbMonitor = static_cast<Dash *>(myDash);
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
        }
        //pthread_yield();
    }

}

void *Dash::NetworkInfoThread(void *myDash)
{
    Dash * newsMonitor = static_cast<Dash *>(myDash);

    while(1)
    {
        emit newsMonitor->askfornews();
        emit newsMonitor->askforweather();
        sleep(15);
    }
}

void *Dash::DashBrightThread(void *myDash)
{
    Dash * dashbrightMonitor = static_cast<Dash *>(myDash);

    while(1)
    {
        emit dashbrightMonitor->askforbrightness();
        sleep(15);
    }
}

void *Dash::TemperatueThread(void *myDash)
{
    Dash * newsMonitor = static_cast<Dash *>(myDash);

    while(1)
    {
        pthread_mutex_lock(&newsMonitor->condition_mutex);
        pthread_cond_wait(&newsMonitor->condition_cond, &newsMonitor->condition_mutex);

        emit newsMonitor->askfortemperature();

        pthread_mutex_unlock(&newsMonitor->condition_mutex);
        //emit newsMonitor->askfortemperature();
        //sleep(15);
    }
}

void *Dash::TimerThread(void *myDash)
{
    Dash * timerMonitor = static_cast<Dash *>(myDash);

    while(1)
    {
        if(!TimerSignal)
        {
            pthread_mutex_lock(&timerMonitor->condition_mutex);
            pthread_cond_signal(&timerMonitor->condition_cond);
            pthread_mutex_unlock(&timerMonitor->condition_mutex);

            TimerSignal = 1;
        }
    }
}



/*****************************Daemons********************************/
QString Dash::getUSBDaemonData()
{
    return MyDaemon->readUSBDaemonData();
}



/*****************************music player********************************/
void Dash::setNewDevice(QString Devicepath)
{
    MusicPlayer->setNewstorageDevie(Devicepath);
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

int Dash::getMusicVolume()
{
    return MusicPlayer->getMusicVolume();
}

void Dash::controlMusicVolume(int volume)
{
    MusicPlayer->changeMusicVolume(volume);
}



/********************************camera**********************************/
void Dash::openCamera()
{
    qDebug() << "Open Camera";
    system("v4l2-ctl --overlay=1");
}

void Dash::closeCamera()
{
    qDebug() << "Close Camera";
    system("v4l2-ctl --overlay=0");
}



/********************************bright**********************************/
void Dash::adjustDashBright(int command)
{
    this->bright = command;

    std::string adjust = "echo ";
    adjust += std::to_string(command);
    adjust += " > /sys/class/backlight/rpi_backlight/brightness";
    system(adjust.c_str());
}

int Dash::getDashBright()
{
    return this->bright;
}



/*****************************network info********************************/
QString Dash::getNews(int index)
{
    return NetworkInfo->getTitle(index);
}
