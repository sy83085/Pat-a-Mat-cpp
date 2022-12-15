#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QString>
#include <string>


class Request
{
public:
    enum Type{Image = 1, TextMessage = 2, RoomList, MakeRoom, EnterRoom, LeaveRoom};
    enum Data{String = 0, Int, OpenCVImage};
    Request();
    ~Request();

    const char * headerBytes();
    const char * const * dataBytesList();
    const int headerSize();
    const std::vector<int> & dataLengthList();

    void initHeaderBytes();
    void initDataBytesList();

protected:
    char * _headerBytes;
    char ** _dataBytesList;
    int _headerSize;
    std::vector<int> _dataLengthList;
};

class ReqImage : public Request
{
public:
    ReqImage(const cv::Mat & img);
};

class ReqText : public Request
{
public:
    ReqText(QString);
};




//class request
//{
//public:
//    request();
//};

#endif // REQUEST_H
