#ifndef DASH_H
#define DASH_H
#include "ddriver.h"
#include "uartstm.h"
#include "daemon.h"
#include "music.h"
#include "network.h"
#include <QObject>
#include <QSerialPort>
#include <QByteArray>

#define TIMERSAMPLE 1//timer trigger in TIMERSAMPLE sec
#define TEMPERATURESAMPLE 10//SAMPLE INTERVALS IN TEMPERATURESAMPLE x TIMERSAMPLE sec
#define BRIGHTNESSSAMPLE 8
#define NETWORKSAMPLE 15
#define CARINFOSAMPLE 2

class Dash : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int val READ val WRITE setVal NOTIFY valChanged)

public:
    Dash();

    void SetPthreads();
    void JoinPthreads();

    void SetMutexes();
    void DestroyMutexes();

    /********************* UART STM ******************/
    Q_INVOKABLE void sendCommand(QString command);

    /********************* Device driver *************/
    Q_INVOKABLE void setColor(QString id_color);

    /***************** MusicPlayer *************************/
    Q_INVOKABLE QString getDeviceSongs(void);
    Q_INVOKABLE void selectSong(QString song);
    Q_INVOKABLE QString currentSong();
    Q_INVOKABLE void pauseSong();
    Q_INVOKABLE void resumeSong();
    Q_INVOKABLE void controlMusicVolume(int volume);
    Q_INVOKABLE int getMusicVolume();

    /*************************Camera**********************/
    Q_INVOKABLE void openCamera();
    Q_INVOKABLE void closeCamera();

    /*************************Touchscreen**********************/
    Q_INVOKABLE void adjustDashBright(int command);
    Q_INVOKABLE int getDashBright();

     /*************************News**********************/
    Q_INVOKABLE QString getNews(int index);
    Q_INVOKABLE QString getWeatherCity();
    Q_INVOKABLE QString getWeatherCountry();
    Q_INVOKABLE int getWeatherTemperature();

    int val() const;
    void setVal(const int &v);

signals:
    void askfornews();
    void askforweather();
    void askforbrightness();
    void askfortemperature();
    void askforcarinfo();
    void timersignal();
    void valChanged(int);

private:


    DDriver *LedStrip;
    Music *MusicPlayer;
    Daemon *MyDaemon;
    UartSTM *STMUART;
    Network *NetworkInfo;

    int bright;
    int temperature_count;

    static void *USBMonitorThread(void *);
    static void *NetworkInfoThread(void *);
    static void *DashBrightThread(void *);
    static void *TemperatueThread(void *);
    static void *TimerThread(void *);
    static void *CarInfoThread(void *);
    static void signalsHandler(int sig);
    static void doWork(int signo);


    QString getUSBDaemonData();
    void setNewDevice(QString Devicepath);
    void initTimer();

    pthread_t USBMonitor_thread, NetworkInfo_thread, DashBright_thread, Temperatue_thread, Timer_thread, CarInfo_thread;
    pthread_attr_t USBMonitor_attr, NetworkInfo_attr, DashBright_attr, Temperatue_attr, Timer_attr, CarInfo_attr;
    sched_param USBMonitor_param, NetworkInfo_param, DashBright_param, Temperatue_param, Timer_param, CarInfo_param;
    pthread_mutex_t USBMonitor_mutex, NetworkInfo_mutex, DashBright_mutex, Temperatue_mutex, Timer_mutex, CarInfo_mutex;

    pthread_mutex_t temperature_condition_mutex = PTHREAD_MUTEX_INITIALIZER, bright_condition_mutex = PTHREAD_MUTEX_INITIALIZER, networkinfo_condition_mutex = PTHREAD_MUTEX_INITIALIZER, carinfo_condition_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t temperature_condition_cond = PTHREAD_COND_INITIALIZER, bright_condition_cond = PTHREAD_COND_INITIALIZER, networkinfo_condition_cond = PTHREAD_COND_INITIALIZER, carinfo_condition_cond = PTHREAD_COND_INITIALIZER;
};

#endif // DASH_H
