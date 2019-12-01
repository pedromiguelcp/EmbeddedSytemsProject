#include "devicewatcher.h"
#include <signal.h>
#include <syslog.h>

char volatile WaitingSignal = 1;

using namespace std;

void sig_handler(int sig){

    //Come;ar uma musica
    if(sig == SIGUSR2){
        WaitingSignal = 0;
    }


}


int main(){


    DeviceWatcher myDeviceWatcher;

        //in case of a signal calls the handler
        //signal(SIGUSR2, sig_handler);

        //myDeviceWatcher.DeamonizeMyProcess();

       // myDeviceWatcher.giveMyPID();

       // while(WaitingSignal == 1);

        //gets the main process pid and can start running normaly
       // myDeviceWatcher.getMainProcessPID();


        myDeviceWatcher.ShowPluggedInDevices();

        myDeviceWatcher.WatchNewPluggedDevices();

        syslog (LOG_NOTICE, "First daemon terminated.");
        closelog();

     return EXIT_SUCCESS;

}
