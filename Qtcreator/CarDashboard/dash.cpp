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
#include <unistd.h>
#include <sys/time.h>

static volatile char USBSignal;
static volatile char TimerSignal;


Dash::Dash()
{
    signal(SIGUSR2, this->signalsHandler);
    signal(SIGALRM, this->doWork);

    MyDaemon = new DaemonsInterface ();

    MyMusicPlayer = new MusicPlayer (MyDaemon->getmusicpid());

    LedStrip = new LedStripInterface ();

    STMUART = new CarInterface ();

    NetworkInfo = new NetworkInterface ();

    connect(this, &Dash::askfornetworkinfo, NetworkInfo, &NetworkInterface::requestNetworkinfo);
    connect(this, &Dash::askforbrightness, STMUART, &CarInterface::requestBrightness);
    connect(this, &Dash::askfortemperature, STMUART, &CarInterface::requestTemperature);

    initProgram();

    /*STMUART->processCarInfo("v96r2692e123\r");
    STMUART->processCarInfo("b70\r");
    STMUART->processCarInfo("t20\r");*/
}



/*******************************program timer**********************************/
void Dash::initProgram()
{
    adjustDashBright(255);

    system("v4l2-ctl --set-fmt-overlay=top=0,left=50,width=690,height=600");

    USBSignal = 1;
    TimerSignal = 1;

    struct itimerval itv;

    itv.it_interval.tv_sec = TIMERSAMPLE; //tv_sec -> time in seconds;tv_usec -> time in useconds; total time in useconds = tv_usec + tv_sec*1000000
    itv.it_interval.tv_usec = 0; //it_interval -> period between successive timer interrupts, if 0 it will only be sent once.
    itv.it_value.tv_sec = TIMERSAMPLE;
    itv.it_value.tv_usec = 0; //it_value -> period between now and the first interrupt, if 0 it is disabled
    setitimer(ITIMER_REAL, &itv, nullptr); //ITIMER_REAL,ITIMER_VIRTUAL ITIMER_PROF -> types of interval timers available per process

    STMUART->UpdateCarInfo();
    //STMUART->sendCommandSTM("Start collect car information");
    /*meter a regular o brilho
      meter a dar display dos erros*/
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
    USBMonitor_param.sched_priority = 2;
    pthread_attr_setdetachstate(&USBMonitor_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&USBMonitor_attr,&USBMonitor_param);
    pthread_attr_init(&USBMonitor_attr);
    pthread_create(&USBMonitor_thread, &USBMonitor_attr, USBMonitorThread, this);

    Timer_param.sched_priority = 4;
    pthread_attr_setdetachstate(&Timer_attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setschedparam(&Timer_attr,&Timer_param);
    pthread_attr_init(&Timer_attr);
    pthread_create(&Timer_thread, &Timer_attr, TimerThread, this);

    CarInfo_param.sched_priority = 5;
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
                timerMonitor->STMUART->processCarInfo("b50\r\r");
            }
            if(brightcount == BRIGHTNESSSAMPLE)
            {
                timerMonitor->STMUART->UpdateCarInfo();
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
        //carinfoMonitor->STMUART->UpdateCarInfo();//so para ver updates
        emit carinfoMonitor->refresh_distancetoobjects();
        emit carinfoMonitor->refresh_speed();
        emit carinfoMonitor->refresh_rpm();
        emit carinfoMonitor->refresh_enginetemp();
        emit carinfoMonitor->refresh_cartemp();
        emit carinfoMonitor->refresh_carbright();
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
    MyMusicPlayer->setNewstorageDevie(Devicepath);
}

void Dash::selectSong(QString song)
{
    MyMusicPlayer->setnewSong(song);
}

QString Dash::getDeviceSongs()
{
    return MyMusicPlayer->getSongs();
}

QString Dash::currentSong()
{
    return MyMusicPlayer->getcurrentSong();
}

void Dash::pauseSong()
{
    MyMusicPlayer->pauseCurrentSong();
}

void Dash::resumeSong()
{
    MyMusicPlayer->resumeCurrentSong();
}

int Dash::getMusicVolume()
{
    return MyMusicPlayer->getMusicVolume();
}

void Dash::controlMusicVolume(int volume)
{
    MyMusicPlayer->changeMusicVolume(volume);
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
    STMUART->setnewbright(command);
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

void Dash::newNetworkConfig(QString SSID, QString PSW)
{
    std::string newconnection = "wpa_passphrase " + SSID.toStdString() + " " + PSW.toStdString() + " > /etc/wpa_supplicant.conf";

    system(newconnection.c_str());
    system("/etc/init.d/S40network restart");
}

