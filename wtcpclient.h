#ifndef WTCPCLIENT_H
#define WTCPCLIENT_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <opencv2/opencv.hpp>
#include "request.h"
//#include <QString>

class WTCPClient
{
private:
    WSADATA wsaData;
    SOCKADDR_IN servAddr;
    SOCKET cSock;

public:
    WTCPClient();
    ~WTCPClient();
    bool connectServer(std::string serverIp = "127.0.0.1", short serverPort = 2500);

//    bool sendReqImage(const cv::Mat & img);

    bool sendReqImage(const cv::Mat & img);
    bool sendRequest(Request * request);
    bool sendByteData(const char * data, const int dataSize);//실질적으로 데이터를 보내는 것
    bool sendText(QString msg);
    int receive(char ** headerBytes, char *** dataBytesList, std::vector<int> & dataLengthList);
    int receiveByteData(char ** data);//실질적으로 데이터를 받는 것
};



//class wtcpclient
//{
//public:
//    wtcpclient();
//};

#endif // WTCPCLIENT_H
