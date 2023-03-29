#pragma once


#include "ui_qwaiting.h"
#include <QDialog>
#include<QMovie>
class QWaiting : public QDialog
{
    Q_OBJECT

public:
    QWaiting(QWidget *parent = Q_NULLPTR);
    ~QWaiting();

private:
    Ui::QWaiting ui;

    QMovie * m_Move;

private slots:
    void slot_changestate(QString);
};
