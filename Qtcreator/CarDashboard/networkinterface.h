#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include <QtNetwork>
#include <QObject>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

struct weather_t {
    int max_temp;
    int min_temp;
    QString country;
    QString location;
    int temperature;
};

struct news_t{
    QString author;
    QString source;
    QString title;
    QString description;
    QString url;
    QString content;
};
#define SIZE_OF_ARRAY (5)

class NetworkInterface : public QObject
{
    Q_OBJECT
public:
    NetworkInterface();
    weather_t getWeather() const; // Returns the weather struct
    news_t *getNews(); // Returns the news struct

    void requestWeather(); // Makes the http request to the API
    void requestNews(); // Makes the http request to the API
    void requestNetworkinfo();

    QString getTitle(int index) const;
    QString getLocation() const;
    QString getCountry() const;
    int getTemperature() const;

public slots:
    void refreshWeather(); // Parses the json response from the API
    void refreshNews(); // Parses the json response from the API
    void printweather(); // Debug purposes
    void printnews(); // Debug purposes

signals:
    void readyweather(weather_t weatherValues); // Debug purposes
    void readynews(news_t newsValues[]); // Debug purposes
    //void readynews(); // Debug purposes

private:
    weather_t weather;
    news_t news[5];
    QNetworkAccessManager news_networkManager;
    QNetworkAccessManager weather_networkManager;
    QNetworkReply* currentReplyWeather;
    QNetworkReply* currentReplyNews;

    int getMaxTemperature() const;
    int getMinTemperature() const;

    QString getAuthor(int index) const;
    QString getContent(int index) const;
};

#endif // NETWORKINTERFACE_H
