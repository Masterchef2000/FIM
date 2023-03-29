#include "serverthread.h"

ServerThread::ServerThread(int sockDesc, QObject *parent) :
    QThread(parent),
    m_sockDesc(sockDesc)
{
    //qDebug()<<"thread id:"<<sockDesc;
}

ServerThread::~ServerThread()
{
    //m_socket->close();
}

void ServerThread::run(void)
{

    /*
    m_socket = new MySocket(m_sockDesc);
    //m_socket->waitForBytesWritten();
    if (!m_socket->setSocketDescriptor(m_sockDesc))
        return ;
    threadMain();
    */
   //emit(startservice());
   this->exec();//让该线程进入事件循环。
}


/*
void ServerThread::threadMain()
{
    //qDebug()<<"服务端socket连接对象："<<m_socket->peerPort();
    initSQL();


    connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void ServerThread::disconnectToHost(void)
{
    //emit disconnectTCP(m_sockDesc);
    m_socket->disconnectFromHost();
    this->quit();
}

void ServerThread::initSQL()
{
    MySQLdb *mysql = new MySQLdb();
    //连接数据库
    if(mysql->initSql())
    {
        qDebug("server %d: connect to DB",m_sockDesc);
    }
}


void ServerThread::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<m_socket->errorString();
    m_socket->close();
}


void ServerThread::receiveData()
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

void ServerThread::sendData(MessageType type)
{
    //发送通话请求
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<(MessageType)NewCall<<"123"; //通话请求+本机名
    m_socket->write(block);

    switch (type) {
        case AcceptVerify:{
            out<<(MessageType)type;
            break;
         }
    default:
        qDebug()<<"unknown type!";

    }
}
*/
