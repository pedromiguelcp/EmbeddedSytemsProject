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

class Dash : public QObject
{
    Q_OBJECT

/*private slots:
    void readSerialUART();*/

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

    /*************************Camera**********************/
    Q_INVOKABLE void openCamera();
    Q_INVOKABLE void closeCamera();

    /*************************Touchscreen**********************/
    Q_INVOKABLE void adjustDashBright(QString command);


private:
    DDriver *LedStrip;
    Music *MusicPlayer;
    Daemon *MyDaemon;
    UartSTM *STMUART;
    Network *NetworkInfo;

    static void *USBMonitorThread(void *);
    static void signalsHandler(int sig);
    QString getUSBDaemonData();
    void setNewDevice(QString Devicepath);

    pthread_t USBMonitor_thread;
    pthread_attr_t USBMonitor_attr;
    sched_param USBMonitor_param;
    pthread_mutex_t USBMonitor_mutex;
    int DashBright_prctg;
};

#endif // DASH_H
