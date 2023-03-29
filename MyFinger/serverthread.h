#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include "mysocket.h"

class Socket;

class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(int sockDesc, QObject *parent = nullptr);
    ~ServerThread();

private:
    void run(void);
    void disconnectToHost(void);

    int m_sockDesc;
    MySocket *m_socket;
    MySQLdb mysql;
    quint16 blockSize;

    /*
    void threadMain();
    void initSQL();
    void initTCP();
    void sendData(MessageType);



private slots:
    void displayError(QAbstractSocket::SocketError);
    //void acceptConnection();
    void receiveData();
    */
signals:

};

#endif // SERVERTHREAD_H
