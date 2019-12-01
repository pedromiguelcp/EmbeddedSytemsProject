#ifndef NETWORK_H
#define NETWORK_H
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
    QString icon;
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

class Network : public QObject
{
    Q_OBJECT
public:
    Network();
    weather_t getWeather() const; // Returns the weather struct
    news_t *getNews(); // Returns the news struct
    void requestWeather(); // Makes the http request to the API
    void requestNews(); // Makes the http request to the API

public slots:
    void refreshWeather(); // Parses the json response from the API
    void refreshNews(); // Parses the json response from the API
    void printweather(); // Debug purposes
    void printnews(); // Debug purposes

signals:
    void readyweather(weather_t weatherValues); // Debug purposes
    void readynews(news_t newsValues[]); // Debug purposes

private:
    weather_t weather;
    news_t news[5];
    QNetworkAccessManager networkManager;
    QNetworkReply* currentReplyWeather;
    QNetworkReply* currentReplyNews;

    /* Debug purposes */
    int getTemperature() const;
    int getMaxTemperature() const;
    int getMinTemperature() const;
    QString getIcon() const;
    QString getLocation() const;

    QString getTitle(int index) const;
    QString getAuthor(int index) const;
    QString getContent(int index) const;
};

#endif // NETWORK_H
