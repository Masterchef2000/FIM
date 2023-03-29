#ifndef MYSQLDB_H
#define MYSQLDB_H


#include <QWidget>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtNetwork>
#include <QMessageBox>

class MySQLdb : public QObject
{
    Q_OBJECT
public:
    explicit MySQLdb(QObject *parent = nullptr);

    bool initSql();
    void creatTable();
    void selectTable();

    bool userSignup(QString, QString);
    bool userLogin(QString, QString);


signals:

};

#endif // MYSQLDB_H
