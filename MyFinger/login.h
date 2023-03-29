#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QCompleter>

#include <QTcpSocket>
#include "memberinfo.h"

namespace Ui {
class Login;
}

//enum MessageType{Verify, AcceptVerify, RejectVerify, NewCall, AcceptCall, RejectCall, FileName, Refuse};


class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    explicit Login(QTcpSocket* ,QWidget *parent = 0);
    ~Login();



private slots:
    void on_pushButton_clicked();
    void receiveData();

private:
    Ui::Login *ui;

    QTcpSocket *clientSocket;//指针传递socket

    MemberInfo member_local;
    //bool verify(const QString &strAccount, const QString &strPwd);
    bool verify(MemberInfo);

signals:
    void user_signal(QString value);
};



#endif // LOGIN_H
