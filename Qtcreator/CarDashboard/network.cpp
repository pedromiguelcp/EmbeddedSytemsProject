#include "network.h"

Network::Network()
{
    //connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshWeather()));
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(refreshNews()));
}


// Makes the http request to the API
void Network::requestWeather()
{
    QUrl url("http://api.openweathermap.org/data/2.5/weather?id=2738752&APPID=f1d822f5687e5b77896e45a48ed02ef1");
    QNetworkRequest request;
    request.setUrl(url);
    currentReplyWeather = networkManager.get(request);
}

void Network::requestNews()
{
    QUrl url("http://webhose.io/filterWebContent?token=ebb54250-6b79-4a85-ba03-5a5a9f9719a3&format=json&ts=1548848178768&sort=social.facebook.likes&q=language%3Aenglish%20site_type%3Anews%20thread.country%3APT");
    QNetworkRequest request;
    request.setUrl(url);
    currentReplyNews = networkManager.get(request);
}



// Parses the json response from the API
void Network::refreshWeather()
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
    QJsonArray weatherArray = rootObject["weather"].toArray();

    weather.temperature = static_cast<int> (mainObject["temp"].toDouble()) - 273;
    weather.max_temp = static_cast<int> (mainObject["temp_max"].toDouble()) - 273;
    weather.min_temp = static_cast<int> (mainObject["temp_min"].toDouble()) - 273;
    weather.location = rootObject["name"].toString();
    weather.icon = weatherArray[0].toObject()["icon"].toString();

    emit readyweather(weather); // Debug purposes
}

void Network::refreshNews()
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


    emit readynews(news); // Debug purposes
}



// Returns the weather struct
weather_t Network::getWeather() const
{
    return this->weather;
}

// Returns the news struct array
news_t *Network::getNews()
{
    return this->news;
}


/* ================================ TEST FUNCTIONS ================================== */

void Network::printweather()
{
    qDebug() << "Temperature:" << getTemperature();
    qDebug() << "Min:" << getMinTemperature();
    qDebug() << "Max:" << getMaxTemperature();
    qDebug() << "Location:" << getLocation();
    qDebug() << "Icon:" << getIcon() << "\n\n";
}

void Network::printnews()
{
    for(int i=0; i < 5; i++)
    {
        qDebug() << "Title:" << getTitle(i);
        qDebug() << "Author:" << getAuthor(i);
        qDebug() << "Content:" << getContent(i) << "\n\n";
    }
}



int Network::getTemperature() const
{
    return this->weather.temperature;
}

int Network::getMaxTemperature() const
{
    return this->weather.max_temp;
}

int Network::getMinTemperature() const
{
    return this->weather.min_temp;
}

QString Network::getIcon() const
{
    return this->weather.icon;
}

QString Network::getLocation() const
{
    return this->weather.location;
}



QString Network::getTitle(int index) const
{
    return this->news[index].title;
}

QString Network::getAuthor(int index) const
{
    return this->news[index].author;
}

QString Network::getContent(int index) const
{
    return this->news[index].content;
}
