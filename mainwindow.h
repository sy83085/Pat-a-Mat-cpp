#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "wtcpclient.h"
#include "receivethread.h"
#include "response.h"


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
    ReceiveThread * receiveThread;

private slots:

//    void readCapture();

    void disconnectServer();
    void chatMessageAppend(ResText * resText);
    void MessageAppend();

};
#endif // MAINWINDOW_H
