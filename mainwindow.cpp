#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new WTCPClient)
    , receiveThread(new ReceiveThread(this->client))

{
    ui->setupUi(this);

    if (this->client->connectServer())
    {
        qDebug() << "connected";
        connect(this->receiveThread, SIGNAL(disconnectServerSignal()), this, SLOT(disconnectServer()));
        connect(this->receiveThread, SIGNAL(resTextSignal(ResText*)), this, SLOT(chatMessageAppend(ResText*)));
        connect(ui->textSend, SIGNAL (clicked(bool)), this, SLOT(MessageAppend()));
        this->receiveThread->start();
    }
    else
    {
        this->disconnectServer();
    }
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::disconnectServer()
{
    QMessageBox msgBox;
    msgBox.setText("서버와의 접속을 유지할 수 없습니다.");
    msgBox.exec();
    this->deleteLater();
}

void MainWindow::chatMessageAppend(ResText * restext)
{

    ui->textBrowser->append("user 1 : " + QString::fromStdString(restext->msg()));
}


void MainWindow::MessageAppend()
{
    ui->textBrowser->append("user 2 : " + ui->lineEdit->text());
    this->client->sendText(ui->lineEdit->text());
    ui->lineEdit->clear();
}

