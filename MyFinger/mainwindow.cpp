#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"
#include "login.h"
#include "mysqldb.h"
#define serverIP "127.0.0.1"
#define serverPort 8888

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("主界面"));
    ui->pushButton_login->setShortcut(tr("return"));
    initTCP();
    connectServer();

    qDebug()<<"客户端socket状态1："<<tcpSocket->state();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initTCP()
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void MainWindow::connectServer()
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(serverIP,serverPort);


    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));

}




void MainWindow::readMessages(){

}



void MainWindow::on_pushButton_register_clicked()
{
    Register *registerdlg = new Register(this);
    registerdlg->exec();
}

void MainWindow::on_pushButton_login_clicked()
{
    Login *logindlg = new Login(tcpSocket);
    this ->close();
    logindlg->show();
}

void MainWindow::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}
