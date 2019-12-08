#ifndef DAEMONSINTERFACE_H
#define DAEMONSINTERFACE_H

#include <sys/types.h>
#include <iostream>
#include <QString>

using namespace std;

class DaemonsInterface
{
public:
    DaemonsInterface();
    ~DaemonsInterface();

    void initDaemons();
    void readUSBDaemonPid();
    void readMusicDaemonPid();
    void writeDashPid();
    pid_t getmusicpid();
    QString readUSBDaemonData();

private:
    pid_t USBDaemonPid;
    pid_t MusicDaemonPid;
    pid_t DashDaemonPid;
    QString USBDaemonData;
};

#endif // DAEMONSINTERFACE_H
