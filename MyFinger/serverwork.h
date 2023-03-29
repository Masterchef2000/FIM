#ifndef SERVERWORK_H
#define SERVERWORK_H

#include <QObject>
#include "mysocket.h"
#include "mysqldb.h"
#include "memberinfo.h"

class ServerWork : public QObject
{
    Q_OBJECT
public:
    explicit ServerWork(QObject *parent = nullptr);
    explicit ServerWork(int, QObject *parent = nullptr);

private:
    int m_sockDesc;
    MySocket *m_socket;
    MySQLdb mysql;
    quint16 blockSize;

    void initSQL();

    void sendData(MessageType);
signals:


public slots:
    void init_server();
    void displayError(QAbstractSocket::SocketError);
    void receiveData();
};

#endif // SERVERWORK_H
