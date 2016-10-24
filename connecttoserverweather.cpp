#include "connecttoserverweather.h"


ConnectToServerWeather::ConnectToServerWeather() : connect("api.openweathermap.org")
{

}

std::string ConnectToServerWeather::getWeather(const std::string &city)
{
    string message =    "GET /data/2.5/weather/?q=" + city +
                    "&units=metric&APPID=f35aabad9d11c1c2f787fad11e074b89 HTTP/1.1\r\n"\
                    "Host: api.openweathermap.org\r\n\r\n";
    return connect.getMessage(message);
}


void ConnectToServerWeather::saveIconFile(const std::string &fileNameOnServer)
{
    string messageToServer = "GET /img/w/" + fileNameOnServer + " HTTP/1.0\r\n"\
                     "Host: api.openweathermap.org\r\n\r\n";
    string fileName = "icon.png";
    connect.saveFile(fileName, messageToServer);
}
