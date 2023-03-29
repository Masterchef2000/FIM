#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include "mysocket.h"
#include "serverthread.h"
#include "serverwork.h"
#include "serverwork.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QWidget *parent = nullptr);

private:
     void incomingConnection(qintptr sockDesc) override;

     ServerWork *work;
     //QThread *new_thread;
     ServerThread *new_thread;


     QList<int> m_socketList;




};

#endif // MYSERVER_H
