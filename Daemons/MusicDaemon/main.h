#ifndef MAIN_H
#define MAIN_H

#include <alsa/asoundlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <string.h>
#include <ao/ao.h>
#include <mpg123.h>


typedef struct myMusic{

    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

}Music;


#endif // MAIN_H
