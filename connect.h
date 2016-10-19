#ifndef CONNECT_H
#define CONNECT_H
#include <string>

using std::string;

class Connect
{
public:
    Connect();
    Connect(const string& host);

    std::string getWeather(const string & city);
    void saveFile(const string & fileName);
private:
    int mSockfd;
    string mHost;

    bool isConectServer();
};

#endif // CONNECT_H
