#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new WTCPClient)
    , receiveThread(new ReceiveThread(this->client))

{
    ui->setupUi(this);

    this->timer = new QTimer(this);
    this->label = new OpenCVImageLabel(this);

    if (this->client->connectServer())
    {
        qDebug() << "connected";
        connect(this->timer, SIGNAL(timeout()), this, SLOT(readCapture()));
        connect(this->receiveThread, SIGNAL(disconnectServerSignal()), this, SLOT(disconnectServer()));
        connect(this->receiveThread, SIGNAL(resImageSignal(ResImage*)), this, SLOT(responseImage(ResImage*)), Qt::BlockingQueuedConnection);
        connect(ui->videoStart, SIGNAL(clicked(bool)), this, SLOT(showVideo()));
        connect(ui->textSend, SIGNAL(clicked(bool)), this, SLOT(chatMessageAppend()));
        connect(ui->videoSend, SIGNAL(clicked(bool)), this, SLOT(stopVideo()));
        this->receiveThread->start();

//        this->client->sendReqRoomList();
    }
    else
    {
        this->disconnectServer();
    }
}

MainWindow::~MainWindow()
{
    delete timer;
    delete label;
    delete client;
    this->cap.release();
    delete ui;
}


// slots
void MainWindow::showVideo()
{
    this->timer->start(33);
}

void MainWindow::stopVideo()
{
    this->timer->stop();
    ui->video->clear();
}

void MainWindow::readCapture()
{
    if (this->cap.isOpened())
    {   // 라벨에 영상 띄우는 부분
        this->cap.read(img);
        cv::resize(img, img, cv::Size(320, 240));
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        QImage qtImage((const unsigned char *) (img.data), img.cols, img.rows, QImage::Format_RGB888);
        ui->video->setPixmap(QPixmap::fromImage(qtImage));
    }
    else
    {
        this->cap.open(0);
        this->cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
        this->cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    }
}

void MainWindow::disconnectServer()
{
    QMessageBox msgBox;
    msgBox.setText("서버와의 접속을 유지할 수 없습니다.");
    msgBox.exec();
    this->deleteLater();
}

void MainWindow::responseImage(ResImage * resImage)
{
    QLabel * current = NULL;

    switch(resImage->number())
    {
//    case 0:
//        current = ui->lb_proImage;
//        break;
//    case 1:
//        current = ui->lb_stuImage1;
//        break;
//    case 2:
//        current = ui->lb_stuImage2;
//        break;
//    case 3:
//        current = ui->lb_stuImage3;
//        break;
//    case 4:
//        current = ui->lb_stuImage4;
//        break;
    }

    if (current != NULL)
    {
        QImage qtImage((const unsigned char *) (resImage->img().data), resImage->img().cols, resImage->img().rows, QImage::Format_RGB888);
        current->setPixmap(QPixmap::fromImage(qtImage));
    }
}

void MainWindow::chatMessageAppend()
{
    ui->textBrowser->append(ui->lineEdit->text());
//    std::string msg = ui->lineEdit->text();
    this->client->sendText(ui->lineEdit->text());
    ui->lineEdit->clear();
}


