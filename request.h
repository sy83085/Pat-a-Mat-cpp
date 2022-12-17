#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <vector>
#include <QString>
#include <string>


class Request
{
public:
    enum Type{TextMessage = 0};
    enum Data{String = 0};
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

class ReqText : public Request
{
public:
    ReqText(QString);
};


#endif // REQUEST_H
