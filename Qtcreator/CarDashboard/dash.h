#ifndef DASH_H
#define DASH_H
#include "ledstripinterface.h"
#include "carinterface.h"
#include "daemonsinterface.h"
#include "musicplayer.h"
#include "networkinterface.h"
#include <QObject>
#include <QSerialPort>
#include <QByteArray>

#define TIMERSAMPLE 1//timer trigger in TIMERSAMPLE sec
#define TEMPERATURESAMPLE 10//SAMPLE INTERVALS IN TEMPERATURESAMPLE x TIMERSAMPLE sec
#define BRIGHTNESSSAMPLE 8
#define NETWORKSAMPLE 90
#define CARINFOSAMPLE 1


class Dash : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int distancetoobjects READ distancetoobjects NOTIFY refresh_distancetoobjects)
    Q_PROPERTY(int car_speed READ car_speed NOTIFY refresh_speed)
    Q_PROPERTY(int car_rpm READ car_rpm NOTIFY refresh_rpm)
    Q_PROPERTY(int car_enginetemp READ car_enginetemp NOTIFY refresh_enginetemp)
    Q_PROPERTY(int car_temp READ car_temp NOTIFY refresh_cartemp)
    Q_PROPERTY(int car_bright READ car_bright NOTIFY refresh_carbright)

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
    Q_INVOKABLE void nextSong();
    Q_INVOKABLE void previousSong();

    /*************************Camera**********************/
    Q_INVOKABLE void openCamera();
    Q_INVOKABLE void closeCamera();

    /*************************Touchscreen**********************/
    Q_INVOKABLE void adjustDashBright(int command);
    Q_INVOKABLE void brightmode(bool autom);
    Q_INVOKABLE bool brightstate();


    /*************************News**********************/
    Q_INVOKABLE QString getNews(int index);
    Q_INVOKABLE QString getWeather(int parameter);
    Q_INVOKABLE void newNetworkConfig(QString SSID, QString PSW);

    int distancetoobjects() const;
    int car_speed() const;
    int car_rpm() const;
    int car_enginetemp() const;
    int car_temp() const;
    int car_bright() const;
    Q_INVOKABLE QString getCarProblems() const;


signals:
    void askfornetworkinfo();
    void askforbrightness();
    void askfortemperature();
    void timersignal();
    void refresh_distancetoobjects();
    void refresh_speed();
    void refresh_rpm();
    void refresh_enginetemp();
    void refresh_cartemp();
    void refresh_carbright();

private:
    LedStripInterface *LedStrip;
    DaemonsInterface *MyDaemon;
    CarInterface *STMUART;
    NetworkInterface *NetworkInfo;
    MusicPlayer *MyMusicPlayer;

    static void *USBMonitorThread(void *);
    static void *TimerThread(void *);
    static void *CarInfoThread(void *);
    static void signalsHandler(int sig);
    static void doWork(int signo);


    QString getUSBDaemonData();
    void setNewDevice(QString Devicepath);
    void initProgram();

    pthread_t USBMonitor_thread, Timer_thread, CarInfo_thread;
    pthread_attr_t USBMonitor_attr, Timer_attr, CarInfo_attr;
    sched_param USBMonitor_param, Timer_param, CarInfo_param;
    pthread_mutex_t USBMonitor_mutex, Timer_mutex, CarInfo_mutex;

    pthread_mutex_t carinfo_condition_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t carinfo_condition_cond = PTHREAD_COND_INITIALIZER;
};

#endif // DASH_H
