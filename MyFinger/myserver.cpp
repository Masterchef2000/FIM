#include "myserver.h"

MyServer::MyServer(QWidget *parent) : QTcpServer(parent)
{
    //qDebug()<<"server initing";


}

void MyServer::incomingConnection(int sockDesc)
{
    //qDebug()<<"提示：有新连接";
    qDebug("收到新连接%d",sockDesc);

    work = new ServerWork(sockDesc);
    new_thread = new ServerThread(sockDesc);
    work->moveToThread(new_thread);
    //connect(new_thread, SIGNAL(startservice()),work,SLOT(init_server()),Qt::QueuedConnection);
    connect(new_thread, &QThread::started, work, &ServerWork::init_server);
    //connect(new_thread, &QThread::finished, work, &QObject::deleteLater);

    m_socketList.append(sockDesc);

    //ServerThread *thread = new ServerThread(sockDesc);
    // thread->start();
    new_thread->start();
}
