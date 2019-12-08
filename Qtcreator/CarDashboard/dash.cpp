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

    MyDaemon = new DaemonsInterface ();

    MusicPlayer = new Music (MyDaemon->getmusicpid());

    LedStrip = new DDriver ();

    STMUART = new UartSTM ();

    NetworkInfo = new Network ();

    connect(this, &Dash::askfornetworkinfo, NetworkInfo, &Network::requestNetworkinfo);
    connect(this, &Dash::askforbrightness, STMUART, &UartSTM::requestBrightness);
    connect(this, &Dash::askfortemperature, STMUART, &UartSTM::requestTemperature);

    initProgram();
}



/*******************************program timer**********************************/
void Dash::initProgram()
{
    adjustDashBright(244);

    system("v4l2-ctl --set-fmt-overlay=top=0,left=50,width=690,height=600");

    USBSignal = 1;
    TimerSignal = 1;

    struct itimerval itv;

    itv.it_interval.tv_sec = TIMERSAMPLE; //tv_sec -> time in seconds;tv_usec -> time in useconds; total time in useconds = tv_usec + tv_sec*1000000
    itv.it_interval.tv_usec = 0; //it_interval -> period between successive timer interrupts, if 0 it will only be sent once.
    itv.it_value.tv_sec = TIMERSAMPLE;
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

    Timer_param.sched_priority = 4;
    pthread_attr_setdetachstate(&Timer_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&Timer_attr,&Timer_param);
    pthread_attr_init(&Timer_attr);
    pthread_create(&Timer_thread, &Timer_attr, TimerThread, this);

    CarInfo_param.sched_priority = 4;
    pthread_attr_setdetachstate(&CarInfo_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&CarInfo_attr,&CarInfo_param);
    pthread_attr_init(&CarInfo_attr);
    pthread_create(&CarInfo_thread, &CarInfo_attr, CarInfoThread, this);
}

void Dash::JoinPthreads()
{
    pthread_join(USBMonitor_thread, nullptr);
    pthread_join(CarInfo_thread, nullptr);
    pthread_join(Timer_thread, nullptr);
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

void *Dash::TimerThread(void *myDash)
{
    Dash * timerMonitor = static_cast<Dash *>(myDash);
    static int temperaturecount = 0, brightcount = 0, networkcount = 0, carinfocount = 0;

    while(1)
    {
        if(!TimerSignal)
        {
            if(carinfocount == CARINFOSAMPLE)
            {
                pthread_mutex_lock(&timerMonitor->carinfo_condition_mutex);
                pthread_cond_signal(&timerMonitor->carinfo_condition_cond);
                pthread_mutex_unlock(&timerMonitor->carinfo_condition_mutex);

                carinfocount = 0;
            }
            if(temperaturecount == TEMPERATURESAMPLE)
            {
                emit timerMonitor->askfortemperature();
                temperaturecount = 0;
            }
            if(brightcount == BRIGHTNESSSAMPLE)
            {
                emit timerMonitor->askforbrightness();
                brightcount = 0;
            }
            if(networkcount == NETWORKSAMPLE)
            {
                emit timerMonitor->askfornetworkinfo();
                networkcount = 0;
            }

            temperaturecount ++;
            brightcount ++;
            networkcount ++;
            carinfocount ++;
            TimerSignal = 1;
        }
    }
}

void *Dash::CarInfoThread(void *myDash)
{
    Dash * carinfoMonitor = static_cast<Dash *>(myDash);

    while(1)
    {
        pthread_mutex_lock(&carinfoMonitor->carinfo_condition_mutex);
        pthread_cond_wait(&carinfoMonitor->carinfo_condition_cond, &carinfoMonitor->carinfo_condition_mutex);
        pthread_mutex_unlock(&carinfoMonitor->carinfo_condition_mutex);

        //carinfoMonitor->setVal(1);
        /*carinfoMonitor->STMUART->UpdateCarInfo();//so para ver updates
        emit carinfoMonitor->refresh_distancetoobjects();
        emit carinfoMonitor->refresh_speed();
        emit carinfoMonitor->refresh_rpm();
        emit carinfoMonitor->refresh_enginetemp();
        emit carinfoMonitor->refresh_cartemp();
        emit carinfoMonitor->refresh_carbright();*/
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

QString Dash::getWeather(int parameter)
{
    if(parameter == 1)
        return NetworkInfo->getCountry();
    else if(parameter == 2)
        return NetworkInfo->getLocation();
    else return QString::number(NetworkInfo->getTemperature());
}



/*****************************car info********************************/
/*void Dash::setVal(const int &v)
{
    //esta funçao apenas tem de dar emit, quando recebo pela porta serie os dados
     // do carro dou update nas propriedades da classe CarInfo, depois quando der
     // emit aqui (periodicamente) a funçao val será chamada para ir buscar os
     // dados á classe CarInfo e dar refresh no qml
    STMUART->UpdateCarInfo();
    emit valChanged(v);
}*/


