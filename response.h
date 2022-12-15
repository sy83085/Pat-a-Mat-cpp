#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Qstring>

class Response
{
public:
    enum Type{Image = 1, Message = 2};
    enum Data{String = 0, Int, OpenCVImage};
    Response(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList);
    ~Response();

    void initDataBytesList();

protected:
    char ** dataBytesList;
    std::vector<int> dataLengthList;

    int dataSize;
    std::vector<int> dataTypeList;
};

class ResImage : public Response
{
public:
    ResImage(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList);

    const cv::Mat & img();
    const int number();

private:
    cv::Mat _img;
    int _number;
};

// class 텍스트 부분 추가해주기
class ResText : public Response
{
public:
    ResText(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList);

};



#endif // RESPONSE_H
