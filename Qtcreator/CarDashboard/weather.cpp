#include "weather.h"


Weather::Weather()
{
//    QUrl url("http://api.openweathermap.org/data/2.5/weather?id=2738752&APPID=f1d822f5687e5b77896e45a48ed02ef1");
//    QNetworkRequest request;
//    request.setUrl(url);

//    currentReply = networkManager.get(request);

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshWeather()));
}


// Makes the http request to the API
void Weather::requestWeather()
{
    QUrl url("http://api.openweathermap.org/data/2.5/weather?id=2738752&APPID=f1d822f5687e5b77896e45a48ed02ef1");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager.get(request);
}


// Parses the json response from the API
void Weather::refreshWeather()
{
    QByteArray response;

    /* Checks if the reply has no erros */
    if(currentReply->error() == QNetworkReply::NoError) {
        response = currentReply->readAll();
    }

    else {
        qDebug() << "Error reading: "<< currentReply->errorString();
    }


    QJsonParseError jsonError;
    QJsonDocument loadDoc = QJsonDocument::fromJson(response, &jsonError); // Parse and capture the error flag

    if(jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error weather: " << jsonError.errorString();
    }

    /* Parses the json and fills the weather variable */
    QJsonObject rootObject = loadDoc.object();
    QJsonObject mainObject = rootObject["main"].toObject();
    QJsonArray weatherArray = rootObject["weather"].toArray();

    weather.temperature = static_cast<int> (mainObject["temp"].toDouble()) - 273;
    weather.max_temp = static_cast<int> (mainObject["temp_max"].toDouble()) - 273;
    weather.min_temp = static_cast<int> (mainObject["temp_min"].toDouble()) - 273;
    weather.icon = weatherArray[0].toObject()["icon"].toString();

    emit ready(weather); // Debug purposes
}


// Returns the weather struct
weather_t Weather::getWeather() const
{
    return this->weather;
}


/* ================================ TEST FUNCTIONS ================================== */

void Weather::print()
{
    qDebug() << "Temperature:" << getTemperature();
    qDebug() << "Min:" << getMinTemperature();
    qDebug() << "Max:" << getMaxTemperature();
    qDebug() << "Icon:" << getIcon();
}


int Weather::getTemperature() const
{
    return this->weather.temperature;
}


int Weather::getMaxTemperature() const
{
    return this->weather.max_temp;
}


int Weather::getMinTemperature() const
{
    return this->weather.min_temp;
}


QString Weather::getIcon() const
{
    return this->weather.icon;
}
