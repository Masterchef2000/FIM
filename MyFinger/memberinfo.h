#ifndef MEMBERINFO_H
#define MEMBERINFO_H

#include <QDialog>
#include <QDebug>
#include <QString>

enum MessageType{Verify, AcceptVerify, RejectVerify, NewCall, AcceptCall, RejectCall, FileName, Refuse};


class MemberInfo
{
public:
    MemberInfo();

    QString account;
    QString password;

    QString ip;
    quint16 port;


    void ClearInfo();
};

#endif // MEMBERINFO_H
