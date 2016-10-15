#include "connect.h"
#include <unistd.h> // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>

using std::string;

Connect::Connect() :    mHost("api.openweathermap.org"),
                        mSockfd(-1)
{
}

Connect::Connect(const string &host) :   mHost(host),
                                         mSockfd(-1)
{
}

bool Connect::mConectServer()
{
    bool isConnected = false;
    struct addrinfo *servinfo;
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    int status = getaddrinfo(mHost.c_str(), "http", &hints, &servinfo);

    if(status == 0)
    {
        mSockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
        if(mSockfd != -1)
        {
            if(connect(mSockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
                close(mSockfd);
            else
                isConnected = true;
        }
    }
    return isConnected;
}

std::string Connect::getWeather(const std::string & city)
{
    string weather;
    if(mConectServer())
    {
        string message =    "GET /data/2.5/weather/?q=" + city +
                "&units=metric&APPID=f35aabad9d11c1c2f787fad11e074b89 HTTP/1.1\r\n"\
                "Host: api.openweathermap.org\r\n\r\n";
        int len = message.length();
        int bytes_sent = send(mSockfd, message.c_str(), len, 0);
        char buf[1000];

        if((bytes_sent = recv(mSockfd, buf, 999, 0)) != -1)
            weather.assign(buf, bytes_sent);

        close(mSockfd);
    }
    return weather;
}

void Connect::saveFile(const std::string & fileName)
{
    if(mConectServer() && !fileName.empty())
    {
        const int SIZEBUF = 4096;
        char buf[SIZEBUF];
        bool headerIsGone = false;
        int len = 0;
        std::ofstream file("icon.png", std::ios::binary);

        string message = "GET /img/w/" + fileName + " HTTP/1.0\r\n"\
                         "Host: api.openweathermap.org\r\n\r\n";
        send(mSockfd, message.c_str(), message.length(), 0);

        while((len = recv(mSockfd, buf, SIZEBUF-1, 0)) > 0)
           {
            if (headerIsGone) {
                file.write(buf, len);
            } else {
                char* ptr;
                buf[len] = '\0';
                ptr = strstr(buf, "\r\n\r\n");
                if (ptr != NULL) {
                    ptr += 4;
                    file.write(ptr, len - (ptr - buf));
                    headerIsGone = true;
                }
            }
        }
        file.close();
        close(mSockfd);
    }
}
