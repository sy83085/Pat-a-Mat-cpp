#include "receivethread.h"
#include "response.h"


ReceiveThread::ReceiveThread(
        WTCPClient * client,
        QObject *parent
    )
    : QThread{parent}
    , isRunning(false)
    , client(client)
    , headerBytes(NULL)
    , dataBytesList(NULL)
    , headSize(0)
    , responseType(0)
    , resText(NULL)

{
    this->dataLengthList.resize(0);
}

ReceiveThread::~ReceiveThread()
{
    initHeaderBytes();
    initDataBytesList();
}

void ReceiveThread::initHeaderBytes()
{
    if (this->headerBytes != NULL)
    {
        delete [] this->headerBytes;
        this->headerBytes = NULL;
    }
}

void ReceiveThread::initDataBytesList()
{
    if (this->dataBytesList != NULL && this->dataLengthList.size() != 0)
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

void ReceiveThread::run()
{
    while (this->isRunning)
    {
        initHeaderBytes();
        initDataBytesList();

        this->headSize = this->client->receive(&this->headerBytes, &this->dataBytesList, dataLengthList);
        if (this->headSize == -1)
        {
            this->isRunning = false;
            emit disconnectServerSignal();
            break;
        }

        memcpy(&this->responseType, this->headerBytes + sizeof(int) * 1, sizeof(int));

        if (resText != NULL)
            delete resText;
        resText = new ResText(this->headerBytes, this->dataBytesList, this->headSize, this->dataLengthList);
        emit resTextSignal(resText);
    }
}

void ReceiveThread::start()
{
    isRunning = true;
    QThread::start();
}
