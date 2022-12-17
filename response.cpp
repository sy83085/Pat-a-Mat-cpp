#include "response.h"

Response::Response(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList)
    : dataLengthList(dataLengthList)
{
    memcpy(&this->dataSize, headerBytes + sizeof(int) * 2, sizeof(int));
    this->dataTypeList.resize(this->dataSize);
    for (int i = 0; i < this->dataTypeList.size(); i++)
        memcpy(&(this->dataTypeList[i]), headerBytes + sizeof(int) * (3 + i), sizeof(int));

    this->dataBytesList = new char * [this->dataLengthList.size()]();
    for (int i = 0; i < this->dataLengthList.size(); i++)
    {
        this->dataBytesList[i] = new char[this->dataLengthList[i]];
        memcpy(this->dataBytesList[i], dataBytesList[i], this->dataLengthList[i]);
    }
}

Response::~Response()
{
    initDataBytesList();
}

void Response::initDataBytesList()
{
    if (this->dataBytesList != NULL && this->dataLengthList.size() > 0)
    {
        for (int i = 0; i < this->dataLengthList.size(); i++)
        {
            if (this->dataBytesList[i] != NULL)
                delete [] this->dataBytesList[i];
        }
        delete [] this->dataBytesList;
        this->dataBytesList = NULL;
        this->dataLengthList.resize(0);
    }
}

ResText::ResText(const char *headerBytes, const char * const *dataBytesList, int headSize, std::vector<int> &dataLengthList)
    : Response(headerBytes, dataBytesList, headSize, dataLengthList)
{
    this->_msg = std::string(dataBytesList[0], dataLengthList[0]);
}

const std::string &ResText::msg()
{
    return this->_msg;
}

