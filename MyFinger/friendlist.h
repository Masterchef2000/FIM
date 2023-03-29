#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include <QtNetwork>
#include <QMessageBox>
#include "qwaiting.h"
#include "memberinfo.h"
#include "call.h"
namespace Ui {
class Friendlist;
}

//enum MessageType{Verify, AcceptVerify, RejectVerify, NewCall, AcceptCall, RejectCall, FileName, Refuse};

class Friendlist : public QDialog
{
    Q_OBJECT

public:
    explicit Friendlist(QWidget *parent = nullptr);
    explicit Friendlist(MemberInfo, QWidget *parent = 0);
    ~Friendlist();

public:



private:
    Ui::Friendlist *ui;

    MemberInfo member_local;
    MemberInfo member_target;
    MemberInfo member_source;
    MemberInfo member_widget;


    void loadStyleSheet(const QString &styleSheetFile);


    //quint16 user_port;
    QVBoxLayout *vertical_layout;

    QTcpServer *tcpServer;//监听套接字
    QTcpSocket *recvSocket;//接收方的socket
    QTcpSocket *sendSocket;//拨号方的socket

    QString message;  //存放从服务器接收到的字符串
    quint16 blockSize; //存放文件的大小信息

    QWaiting *pQwait;

    bool createConnection();
    void matchUserFriend();
    void callChioce();

private slots:
    void initConnect(MemberInfo);
    void readData();

    void getCall();
    void waitForCall();
    void readData_rec();
signals:
    void signal_changestate(QString);

};

#endif // FRIENDLIST_H
