#ifndef WEATHER_H
#define WEATHER_H
#include <string>

using std::string;

class Weather
{
public:
    Weather();

    void connectWeather(const string &city);
    string getTemp();
    string getComment();
    string getCity();
private:
    string mTemp;
    string mComment;
    string mCity;
    string mIconName;

    void mJsonParser(const string &json);
};
#endif // WEATHER_H
