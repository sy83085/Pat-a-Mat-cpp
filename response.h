#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <vector>
#include <Qstring>

class Response
{
public:
    enum Type{Message = 0};
    enum Data{String = 0};
    Response(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList);
    ~Response();

    void initDataBytesList();

protected:
    char ** dataBytesList;
    std::vector<int> dataLengthList;

    int dataSize;
    std::vector<int> dataTypeList;
};


class ResText : public Response
{
public:
    ResText(const char * headerBytes, const char * const * dataBytesList, int headSize, std::vector<int> & dataLengthList);

    const std::string &msg();

private:
    std::string _msg;


};




#endif // RESPONSE_H
