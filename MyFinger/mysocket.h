#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtNetwork>

#include "mysqldb.h"
#include "memberinfo.h"


class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = Q_NULLPTR);
    explicit MySocket(int sockDesc, QObject *parent = Q_NULLPTR);


private:
    int m_sockDesc;









private slots:
    void on_discon();
    void rece();


};

#endif // MYSOCKET_H
