#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include "opencvimagelabel.h"
#include "wtcpclient.h"
#include "receivethread.h"
#include "response.h"
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    WTCPClient * client;
//    LTCPClient * client;

    ReceiveThread * receiveThread;

    cv::VideoCapture cap;
    cv::Mat img;

    QTimer * timer;
    OpenCVImageLabel * label;

    // roomList
    std::vector<std::string> ipList;
    std::vector<int> portList;
    std::vector<std::string> roomNameList;
    std::vector<int> roomMemberCountList;

private slots:

    void readCapture();

    void disconnectServer();
    void responseImage(ResImage * resImage);
    void chatMessageAppend();
    void showVideo();
    void stopVideo();


//    void on_chatButton_clicked();

signals:
    void setOpenCVImageSignal(cv::Mat);
};
#endif // MAINWINDOW_H
