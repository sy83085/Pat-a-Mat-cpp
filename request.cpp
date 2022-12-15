#include "request.h"

Request::Request()
    : _headerBytes(NULL)
    , _dataBytesList(NULL)
    , _headerSize(0)
{

}

Request::~Request()
{
    this->initHeaderBytes();
    this->initDataBytesList();
}

const char *Request::headerBytes()
{
    return this->_headerBytes;
}

const char * const *Request::dataBytesList()
{
    return this->_dataBytesList;
}

const int Request::headerSize()
{
    return this->_headerSize;
}

const std::vector<int> &Request::dataLengthList()
{
    return this->_dataLengthList;
}

void Request::initHeaderBytes()
{
    if (this->_headerBytes != NULL)
    {
        delete [] this->_headerBytes;
        this->_headerBytes = NULL;
    }
}

void Request::initDataBytesList()
{
    if (this->_dataBytesList != NULL && this->_dataLengthList.size() > 0)
    {
        for (int i = 0; i < this->_dataLengthList.size(); i++)
        {
            if (this->_dataBytesList[i] != NULL)
                delete [] this->_dataBytesList[i];
        }
        delete [] this->_dataBytesList;
        this->_dataBytesList = NULL;
        this->_dataLengthList.resize(0);
    }
}

ReqText::ReqText(QString msg)
    : Request()
{
    this->_headerSize = sizeof(int) * 4;
    int receiveCount = 1;
    int requestType = Request::TextMessage;
    int dataSize = 1;
    int firstDataType = Request::String;

    this->_headerBytes = new char[this->_headerSize];
    memcpy(this->_headerBytes + sizeof(int) * 0, &receiveCount, sizeof(int)); // dataCount
    memcpy(this->_headerBytes + sizeof(int) * 1, &requestType, sizeof(int)); // requestType
    memcpy(this->_headerBytes + sizeof(int) * 2, &dataSize, sizeof(int)); // attrSize;
    memcpy(this->_headerBytes + sizeof(int) * 3, &firstDataType, sizeof(int));

    this->_dataLengthList.resize(1);
    this->_dataBytesList = new char * [1]();
    this->_dataBytesList[0] = new char[msg.toStdString().size() + 1];
    memcpy(this->_dataBytesList[0], msg.toStdString().c_str(), msg.toStdString().size() + 1);
    this->_dataLengthList[0] = msg.toStdString().size() + 1;

}

ReqImage::ReqImage(const cv::Mat &img)
    : Request()
{
    /*
     * reqImage header
     * datacount : 1 <32bit, 4byte, int>
     * requestType : 1(image) (32bite, 4byte, int)
     * dataSize : 1 <32bit, 4byte, int>
     * dataType:
     *     2 : OpenCVImage
     */

    this->_headerSize = sizeof(int) * 4;
    int receiveCount = 0;
    int requestType = Request::RoomList;
    int dataSize = 0;
    int firstDataType = Request::OpenCVImage;

    this->_headerBytes = new char[this->_headerSize];
    memcpy(this->_headerBytes + sizeof(int) * 0, &receiveCount, sizeof(int)); // dataCount
    memcpy(this->_headerBytes + sizeof(int) * 1, &requestType, sizeof(int)); // requestType
    memcpy(this->_headerBytes + sizeof(int) * 2, &dataSize, sizeof(int)); // attrSize;
    memcpy(this->_headerBytes + sizeof(int) * 3, &firstDataType, sizeof(int));

    this->_dataLengthList.resize(1);
    this->_dataBytesList = new char * [1]();
    this->_dataBytesList[0] = new char[img.total() * img.channels()];
    memcpy(this->_dataBytesList[0], (char *) img.data, img.total() * img.channels());
    this->_dataLengthList[0] = img.total() * img.channels();
}


