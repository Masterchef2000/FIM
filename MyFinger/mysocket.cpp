#include "mysocket.h"

MySocket::MySocket(QObject *parent):
    QTcpSocket(parent)
{

}

MySocket::MySocket(int sockDesc, QObject *parent) :
    QTcpSocket(parent),
    m_sockDesc(sockDesc)
{
    //qDebug()<<"socket id:"<<sockDesc;

    //connect(this,SIGNAL(disconnected()),this, SLOT(on_discon()));
    //connect(this,SIGNAL(readyRead()),this,SLOT(rece()));

}

void MySocket::on_discon()
{
    qDebug()<<"server:有一个连接已断开";
}
void MySocket::rece()
{
    qDebug()<<"get";
}





