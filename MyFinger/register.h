#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QCompleter>
#include <QProcess>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_register_clicked();
    void statechange(QProcess::ProcessState);
    void processError(QProcess::ProcessError error);
    void Result(int);
private:
    Ui::Register *ui;
    QProcess *myproc;

    void userRegister(const QString &strAccount, const QString &strPwd, const QString &strPort);
    void selectTable();
};

#endif // REGISTER_H
