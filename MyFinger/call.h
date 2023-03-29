#ifndef CALL_H
#define CALL_H

#include <QWidget>
#include <QString>
#include <QtNetwork>
#include <QMovie>

namespace Ui {
class Call;
}

class Call : public QWidget
{
    Q_OBJECT

public:
    explicit Call(QWidget *parent = 0);
   // explicit Call(quint16 receive_port, QString send_ip ,quint16 send_port,QString send_account,QWidget *parent = 0);
    ~Call();

private:
    Ui::Call *ui;

};

#endif // CALL_H
