#ifndef CONNECTTOSERVERWEATHER_H
#define CONNECTTOSERVERWEATHER_H

#include <string>
#include "connect.h"

class ConnectToServerWeather
{
public:
    ConnectToServerWeather();
    std::string getWeather(const std::string &city);
    void saveIconFile(const std::string &fileNameOnServer);
private:
   // void connect(const std::string &city);
    Connect connect;
};

#endif // CONNECTTOSERVERWEATHER_H
