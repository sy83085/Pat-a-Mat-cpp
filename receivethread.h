#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QThread>
#include <QDebug>
#include "wtcpclient.h"
#include "response.h"


class ReceiveThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveThread(
        WTCPClient * client,
        QObject *parent = nullptr
    );
    ~ReceiveThread();

    void initHeaderBytes();
    void initDataBytesList();

    void run() override;


private:
    bool isRunning;

    WTCPClient * client;
//    LTCPClient * client;

    char * headerBytes;
    char ** dataBytesList;
    int headSize;
    std::vector<int> dataLengthList;
    int responseType;

    ResImage * resImage;



public slots:
    void start();

signals:
    void disconnectServerSignal();
    void resImageSignal(ResImage *);
};

#endif // RECEIVETHREAD_H








//class receivethread
//{
//public:
//    receivethread();
//};

//#endif // RECEIVETHREAD_H
