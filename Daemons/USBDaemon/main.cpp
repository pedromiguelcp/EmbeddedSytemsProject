#include "devicewatcher.h"
#include <signal.h>
#include <syslog.h>

char volatile WaitingSignal = 1;

using namespace std;

void sig_handler(int sig)
{
    if(sig == SIGUSR2)
    {
        WaitingSignal = 0;
    }
    else
    {
        DeviceWatcher dummy;
        dummy.WriteOnMyLog("ANOTHER SIGNAL RECEIVED\n");
    }
}


int main()
{
    DeviceWatcher myDeviceWatcher;

    signal(SIGUSR2, sig_handler);
    signal(SIGHUP, sig_handler);
    signal(SIGCONT, sig_handler);

    myDeviceWatcher.DeamonizeMyProcess();

    myDeviceWatcher.giveMyPID();

    //printf("Waitting for signal");
    myDeviceWatcher.WriteOnMyLog("WAITTING FOR SIGNAL\n");
    while(WaitingSignal == 1);
    myDeviceWatcher.WriteOnMyLog("SIGNAL RECEIVED\n");

    //gets the main process pid and can start running normaly
    myDeviceWatcher.getMainProcessPID();


    myDeviceWatcher.ShowPluggedInDevices();
    myDeviceWatcher.WriteOnMyLog("PLUGGED IN DEVICES SHOWN\n");

    myDeviceWatcher.WatchNewPluggedDevices();

    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}