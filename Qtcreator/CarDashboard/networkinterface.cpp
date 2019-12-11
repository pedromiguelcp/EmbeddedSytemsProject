#include "networkinterface.h"

NetworkInterface::NetworkInterface()
{
    connect(&weather_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshWeather()));
    connect(&news_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshNews()));
    //requestNews();
    //requestWeather();

}


// Makes the http request to the API
void NetworkInterface::requestWeather()
{
    QUrl url("http://api.openweathermap.org/data/2.5/weather?id=2738752&APPID=f1d822f5687e5b77896e45a48ed02ef1");
    QNetworkRequest request;
    request.setUrl(url);
    currentReplyWeather = weather_networkManager.get(request);
    qDebug() << "Weather requested!";
}

void NetworkInterface::requestNews()
{
    QUrl url("http://webhose.io/filterWebContent?token=cdf0ac25-0d32-4ac2-8e7f-9dba8adb09cd&format=json&ts=1548848178768&sort=relevancy&q=language%3Aenglish%20site_type%3Anews%20thread.country%3APT");
    //QUrl url("http://webhose.io/filterWebContent?token=ebb54250-6b79-4a85-ba03-5a5a9f9719a3&format=json&ts=1548848178768&sort=social.facebook.likes&q=language%3Aenglish%20site_type%3Anews%20thread.country%3APT");
    QNetworkRequest request;
    request.setUrl(url);
    currentReplyNews = news_networkManager.get(request);
    qDebug() << "News requested!";
}

void NetworkInterface::requestNetworkinfo()
{
    requestWeather();

    requestNews();
}



// Parses the json response from the API
void NetworkInterface::refreshWeather()
{
    QByteArray response;

    /* Checks if the reply has no erros */
    if(currentReplyWeather->error() == QNetworkReply::NoError) {
        response = currentReplyWeather->readAll();
    }

    else {
        qDebug() << "Error reading: "<< currentReplyWeather->errorString();
    }


    QJsonParseError jsonError;
    QJsonDocument loadDoc = QJsonDocument::fromJson(response, &jsonError); // Parse and capture the error flag

    if(jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error weather: " << jsonError.errorString();
    }

    /* Parses the json and fills the weather variable */
    QJsonObject rootObject = loadDoc.object();
    QJsonObject mainObject = rootObject["main"].toObject();
    QJsonObject locationObject = rootObject["sys"].toObject();
    QJsonArray weatherArray = rootObject["weather"].toArray();

    weather.temperature = static_cast<int> (mainObject["temp"].toDouble()) - 273;
    weather.max_temp = static_cast<int> (mainObject["temp_max"].toDouble()) - 273;
    weather.min_temp = static_cast<int> (mainObject["temp_min"].toDouble()) - 273;
    weather.location = rootObject["name"].toString();
    //weather.city = weatherArray[0].toObject()["icon"].toString();
    weather.country = locationObject["country"].toString();

    //printweather();
    //emit readyweather(weather); // Debug purposes
}

void NetworkInterface::refreshNews()
{
    QByteArray response;

    /* Checks if the reply has no erros */
    if(currentReplyNews->error() == QNetworkReply::NoError) {
        response = currentReplyNews->readAll();
    }

    else {
        qDebug() << "Error reading: "<< currentReplyNews->errorString();
    }


    QJsonParseError jsonError;
    QJsonDocument loadDoc = QJsonDocument::fromJson(response, &jsonError); // Parse and capture the error flag

    if(jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error news: " << jsonError.errorString();
    }

    /* Parses the json and fills the weather variable */
    QJsonObject rootObject = loadDoc.object();
    QJsonArray newsArray = rootObject["posts"].toArray();

    for(int i=0; i < 5; i++)
    {
        news[i].author = newsArray[i].toObject()["author"].toString();
        news[i].title = newsArray[i].toObject()["title"].toString();
        news[i].content = newsArray[i].toObject()["text"].toString();
    }

    //printnews();
    //emit readynews(news); // Debug purposes
}



// Returns the weather struct
weather_t NetworkInterface::getWeather() const
{
    return this->weather;
}

news_t *NetworkInterface::getNews()
{
    return this->news;
}






/* ================================ TEST FUNCTIONS ================================== */

void NetworkInterface::printweather()
{
    qDebug() << "Temperature:" << getTemperature();
    qDebug() << "Min:" << getMinTemperature();
    qDebug() << "Max:" << getMaxTemperature();
    qDebug() << "Location:" << getLocation();
    qDebug() << "Country:" << getCountry() << "\n\n";
}

void NetworkInterface::printnews()
{
    for(int i=0; i < 5; i++)
    {
        qDebug() << "Title:" << getTitle(i);
        qDebug() << "Author:" << getAuthor(i);
        qDebug() << "Content:" << getContent(i) << "\n\n";
    }
}



int NetworkInterface::getTemperature() const
{
    return this->weather.temperature;
}

int NetworkInterface::getMaxTemperature() const
{
    return this->weather.max_temp;
}

int NetworkInterface::getMinTemperature() const
{
    return this->weather.min_temp;
}

QString NetworkInterface::getCountry() const
{
    return this->weather.country;
}

QString NetworkInterface::getLocation() const
{
    return this->weather.location;
}



QString NetworkInterface::getTitle(int index) const
{
    return this->news[index].title;
}

QString NetworkInterface::getAuthor(int index) const
{
    return this->news[index].author;
}

QString NetworkInterface::getContent(int index) const
{
    return this->news[index].content;
}

