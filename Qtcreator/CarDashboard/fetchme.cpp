#include "fetchme.h"
#include <unistd.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

/*FetchMe::FetchMe(QObject *parent) : QObject(parent)
{
    this->m_inc = 0;

}*/

QString FetchMe::sayHello() const
{
    return "Saying Hello from C++ Class";
}

void FetchMe::IncrementMe(){
    this->m_inc++;
}

QString FetchMe::getDescription() const
{
    return this->weather1.description;
}

double FetchMe::getTemp() const
{
    return this->weather1.temp;
}

int FetchMe::getPressure() const
{
    return this->weather1.pressure;
}

int FetchMe::getHumidity() const
{
    return this->weather1.humidity;
}

QString FetchMe::getCountry() const
{
    return this->weather1.country;
}

QString FetchMe::getName() const
{
    return this->weather1.name;
}

QString FetchMe::getTitle(int index) const
{
    return this->news1[index].title;
}



void FetchMe::init_string(mystring *s)
{
    s->len = 0;
    s->ptr =static_cast<char*>( malloc(s->len+1));
    if (s->ptr == nullptr) {
        fprintf(stderr, "malloc() failed\n");
        //exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t FetchMe::writefunc(void *ptr, size_t size, size_t nmemb, mystring *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = static_cast<char*>(realloc(s->ptr, new_len+1));
    if (s->ptr == nullptr) {
        fprintf(stderr, "realloc() failed\n");
        //exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

void FetchMe::printNews(news * news_file){
    //    printf("Print info of weather structure:\n");
    //    printf("Author: %s\n",news_file->author);
    // printf("Url: %s\n",news_file->url);
    printf("Title: %s\n",news_file->title);
    //    printf("Source: %s\n",news_file->source);
    //    printf("Content: %s\n",news_file->content);
    //    printf("Description: %s\n",news_file->description);
}

void FetchMe::fillNews(cJSON * json_file,news * news_file, int news_index){
    //so e necessario dar free do root no caso dos cJSON
    //criar cJSON mais pequenos para aceder a partes do cJSON maior, ir buscar os campos
    cJSON *description = cJSON_GetObjectItem(json_file,"posts");
    cJSON *thread1=cJSON_GetArrayItem(description,news_index);
    cJSON *url1 = cJSON_GetObjectItem(thread1,"url");
    cJSON *title1= cJSON_GetObjectItem(thread1,"title");

    //obter city name
    news_file->url = static_cast<char*>(malloc(strlen(url1->valuestring) + sizeof(""))); /* sizeof("") accounts for '\0' at the end */
    strcpy(news_file->url, url1->valuestring);

    //obter city name
    news_file->title =static_cast<char*>( malloc(strlen(title1->valuestring) + sizeof(""))); /* sizeof("") accounts for '\0' at the end */
    strcpy(news_file->title, title1->valuestring);
}

void FetchMe::getNews()
{
    CURL *curl;
    CURLcode res;
    char * out=nullptr;
    //parte 2: NEWS
    //deve ser chamada antes de todas as outras funçoes de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    //inicializa um objeto curl, primeira funçao que deve ser chamada, creaty an easy handle
    curl = curl_easy_init();
    if(curl) {
        struct mystring s;
        init_string(&s);
        //curl set options
        curl_easy_setopt(curl, CURLOPT_URL, "http://webhose.io/filterWebContent?token=ebb54250-6b79-4a85-ba03-5a5a9f9719a3&format=json&ts=1548848178768&sort=social.facebook.likes&q=language%3Aenglish%20site_type%3Anews%20thread.country%3APT");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &this->writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        //printf("res = %d\n",res);
        cJSON *json = cJSON_Parse(s.ptr);

        if (!json)
        {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }
        else
        {
            int i=0;
            for(i=0;i<10;i++){

                this->fillNews(json, &this->news1[i],i);
                this->printNews(&this->news1[i]);
                //obj->fillNews(json,&obj->news1[i],i);
                //obj->printNews(&obj->news1[i]);
            }

            cJSON_Delete(json);
            free(out);
        }
        //libertar memoria alocada pelas strings.
        free(s.ptr);

        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void FetchMe::getWeather()
{
    CURL *curl;
    CURLcode res;

    //inicio do comentario para o weather API -----------------------------------------------------------------------------------
    //deve ser chamada antes de todas as outras funçoes de curl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    //inicializa um objeto curl, primeira funçao que deve ser chamada, creaty an easy handle
    curl = curl_easy_init();
    if(curl) {
        struct mystring s;
        init_string(&s);

        //curl set options
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?id=2738752&APPID=f1d822f5687e5b77896e45a48ed02ef1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        //printf("String is %s\n", s.ptr);

        cJSON *json = cJSON_Parse(s.ptr);

        if (!json)
        {
            printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        }
        else
        {
            //out = cJSON_Print(json);

            this->fillWeather(json,&this->weather1);
            this->printWeather(&this->weather1);
            //obj->fillWeather(json,&obj->weather1);
            //obj->printWeather(&obj->weather1);
            //libertar memoria alocada ao criar os cJSON
            cJSON_Delete(json);

            //libertar memoria alocada pelas strings.

        }
        //procurar por
        //libertar memoria alocada pelas strings.
        free(s.ptr);

        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        //printf("String is  %s\n",curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

}




//print the current weather struct info
void FetchMe::printWeather(weather * weather_file){
    printf("Print info of weather structure:\n");
    printf("City: %s\n",weather_file->name);
    printf("Country: %s\n",weather_file->country);
    printf("Description: %s\n",weather_file->description);
    printf("ID: %d\n",weather_file->id);
    printf("Temp: %.02lf K %.02lf C\n",weather_file->temp,weather_file->temp-273.15);
    printf("Humidity: %d %%\n",weather_file->humidity);
    printf("Pressure: %d hpa\n",weather_file->pressure);
}


void FetchMe::fillWeather(cJSON * json_file,weather * weather_file){
    if (!json_file)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    //so e necessario dar free do root no caso dos cJSON
    //criar cJSON mais pequenos para aceder a partes do cJSON maior, ir buscar os campos
    cJSON *description = cJSON_GetArrayItem(cJSON_GetObjectItem(json_file, "weather"),0);
    cJSON *description2 = cJSON_GetObjectItem(description, "description");
    cJSON *name =  cJSON_GetObjectItem(json_file, "name");//BRAGA
    cJSON *sys =  cJSON_GetObjectItem(json_file, "sys");//sys
    cJSON *country =  cJSON_GetObjectItem(sys, "country");//PT, is inside sys
    cJSON *main_section= cJSON_GetObjectItem(json_file, "main");//main section, contains temp, pressure, humidity, visibility

    //obter city name
    weather_file->name = static_cast<char*>(malloc(strlen(name->valuestring) + sizeof(""))); /* sizeof("") accounts for '\0' at the end */
    strcpy(weather_file->name, name->valuestring);

    //obter o id da cidade
    weather_file->id= cJSON_GetObjectItem(json_file,"id")->valueint;//id

    //obter a sigla do pais
    weather_file->country= static_cast<char*>(malloc(strlen(country->valuestring) + sizeof(""))); /* sizeof("") accounts for '\0' at the end */
    strcpy(weather_file->country, country->valuestring);

    //obter temperatura da cidade
    weather_file->temp= cJSON_GetObjectItem(main_section, "temp")->valuedouble;

    //obter pressao da cidade
    weather_file->pressure= cJSON_GetObjectItem(main_section, "pressure")->valueint;

    //obter o id da cidade
    weather_file->humidity= cJSON_GetObjectItem(main_section,"humidity")->valueint;

    //obter a descricao do tempo
    weather_file->description=static_cast<char*>( malloc(strlen(description2->valuestring) + sizeof(""))); /* sizeof("") accounts for '\0' at the end */
    strcpy(weather_file->description, description2->valuestring);
}


int FetchMe::printMe() const{
    return this->m_inc;
}
