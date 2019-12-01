#ifndef DAEMON_H
#define DAEMON_H

#include <sys/types.h>
#include <iostream>
#include <QString>

using namespace std;

class Daemon
{
public:
    Daemon();
    ~Daemon(){}

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

#endif // DAEMON_H
