#include "serverwork.h"

ServerWork::ServerWork(QObject *parent) : QObject(parent)
{

}

ServerWork::ServerWork(int sockDesc, QObject *parent) :
    QObject(parent),
    m_sockDesc(sockDesc)
{
    //qDebug()<<1;

}

void ServerWork::init_server()
{
    //qDebug()<<"serverwork's socketdesc:"<<m_sockDesc;
    //QTcpSocket *socket = new QTcpSocket();
    m_socket = new MySocket();
    if (!m_socket->setSocketDescriptor(m_sockDesc)){
        qDebug()<<"error";
        //return ;
    }
    //qDebug()<<"新建服务端socket状态："<<m_socket->state();

    initSQL();

    connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void ServerWork::initSQL()
{
    MySQLdb *mysql = new MySQLdb();
    //连接数据库
    if(mysql->initSql())
    {
        qDebug("server %d: connect to DB",m_sockDesc);
        mysql->selectTable();
    }
}


void ServerWork::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<m_socket->errorString();
    m_socket->close();
}


void ServerWork::receiveData()
{
    qDebug("receive");
    QByteArray block = m_socket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_6);


    qDebug()<<"接受："<<block;
    //qDebug()<<"size:"<<sizeof(block);
    int MessageType;
    in>>MessageType;
    //qDebug()<<"type:"<<MessageType;
    switch (MessageType) {
        case Verify:{
            QString account;
            QString password;
            in>>account>>password;
            qDebug()<<"server get"<<account<<password;
            if(mysql.userLogin(account,password)){
                //qDebug()<<"存在该用户";
                sendData(AcceptVerify);
            }
            break;
        }

        default:
            qDebug()<<"无效报文！";
    }
}

void ServerWork::sendData(MessageType type)
{
    //发送通话请求
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    //out<<(MessageType)NewCall<<"123"; //通话请求+本机名


    switch (type) {
        case AcceptVerify:{
            out<<(MessageType)type;
            break;
         }
    default:
        qDebug()<<"unknown type!";

    }
    qDebug()<<"Server发送:"<<block;
    m_socket->write(block);
}
