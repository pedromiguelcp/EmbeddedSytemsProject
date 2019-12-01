#ifndef FetchMe_H
#define FetchMe_H

#include <QObject>

#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <iostream>

using namespace std;

typedef struct weather{
    char * description;
    double temp;
    int pressure;
    int humidity;
    char * country;
    int id;
    char * name;
}weather;


typedef  struct news{
    char * author; //"Jason Hanna, Ray Sanchez, Flora Charner and Christina Maxouris, CNN"
    char * source;
    char * title; //"Venezuela's opposition leader warns of another massive rally as Maduro blames US for protests - CNN"
    char * description;
    char * url;
    char * content;
}news;

struct mystring {
    char *ptr;
    size_t len;
};

class FetchMe
{

public:

    FetchMe(){

    }
    Q_INVOKABLE  QString sayHello() const;
    Q_INVOKABLE  int printMe() const;

    void IncrementMe();

    //weather API functions
    void printWeather(weather * weather_file);
    void fillWeather(cJSON * json_file,weather * weather_file);


    //news API functions
    void printNews(news * news_file);
    void fillNews(cJSON * json_file,news * news_file, int news_index);

    void getNews();
    void getWeather();

    // friend void weather_function(FetchMe *obj);
    //friend void news_function(FetchMe *obj);

    virtual Q_INVOKABLE  QString getDescription(void) const = 0;
    virtual Q_INVOKABLE  double getTemp(void) const = 0;
    virtual Q_INVOKABLE  int getPressure(void) const = 0;
    virtual Q_INVOKABLE  int getHumidity(void) const = 0;
    virtual Q_INVOKABLE  QString getCountry(void) const = 0;
    virtual Q_INVOKABLE  QString getName(void) const = 0;//City name
    virtual Q_INVOKABLE  QString getTitle(int index) const = 0;//City name

protected:
    int m_inc;
    weather weather1;
    news news1[10];
    uint8_t m_color;

    static void init_string(struct mystring *s);
    static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct mystring *s);
};

#endif // FetchMe_H
