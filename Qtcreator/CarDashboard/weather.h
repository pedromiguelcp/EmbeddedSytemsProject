#ifndef MYURL_H
#define MYURL_H

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
    int temperature;
};


class Weather : public QObject
{
    Q_OBJECT

public:
    Weather();
    weather_t getWeather() const; // Returns the weather struct
    void requestWeather(); // Makes the http request to the API

public slots:
    void refreshWeather(); // Parses the json response from the API
    void print(); // Debug purposes

signals:
    void ready(weather_t weatherValues); // Debug purposes

private:
    weather_t weather;
    QNetworkAccessManager networkManager;
    QNetworkReply* currentReply;
    QNetworkReply* currentReplynews;

    /* Debug purposes */
    int getTemperature() const;
    int getMaxTemperature() const;
    int getMinTemperature() const;
    QString getIcon() const;
};

#endif // MYURL_H
