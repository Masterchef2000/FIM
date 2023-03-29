#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#include <QWidget>
#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QHostAddress>
#include "memberinfo.h"

namespace Ui {
class Userwidget;
}

class Userwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Userwidget(QWidget *parent = 0);
    //explicit Userwidget(quint16 receive_port,QString send_ip ,quint16 send_port,QString send_account,QWidget *parent = 0);
    explicit Userwidget(MemberInfo ,QWidget *parent = 0);
    ~Userwidget();


protected:
    void mouseDoubleClickEvent(QMouseEvent *event);


private:
    Ui::Userwidget *ui;

    MemberInfo member_widget;
    void loadStyleSheet(const QString &styleSheetFile);



signals:
    void signal_initConnect(MemberInfo);

private slots:





};

#endif // USERWIDGET_H
