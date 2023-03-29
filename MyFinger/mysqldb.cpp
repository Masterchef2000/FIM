#include "mysqldb.h"

MySQLdb::MySQLdb(QObject *parent) : QObject(parent)
{

}

bool MySQLdb::initSql()
{
    //添加数据库驱动
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

    //设置数据库名称
    db.setDatabaseName("memory.db");
    //打开数据库
    if(!db.open())
    {
        qDebug()<<QObject::tr("打开数据库失败");
        return false;
    }
    return true;
}

void MySQLdb::creatTable()
{
    qDebug()<<"this is mysql";
    QSqlQuery query;
    //新建user表，account设置为主键，还有一个password项
    query.exec("create table user (account varchar(8) primary key,password varchar(8),ip varchar(16),port int)");
    //向表中插入记录
    query.exec("insert into user values('admin','admin','127.0.0.1',8000)");
    query.exec("insert into user values('1001','1001','127.0.0.1',8001)");
    query.exec("insert into user values('1002','1002','127.0.0.1',8002)");
}

void MySQLdb::selectTable()
{
    QStringList accountList;
    QSqlQuery query;
    //删除user表
    //query.exec("drop table user");
    //查找user表中的记录的account项和password项的值


    //query.next()指向查找到的第一条记录，然后每次后移一条记录
    query.exec("select account,password,ip,port from user");
    qDebug() << "account" << "password" << "ip" << "port";
    while(query.next())
    {
        QString value0 = query.value(0).toString();
        QString value1 = query.value(1).toString();
        QString value2 = query.value(2).toString();
        int value3 = query.value(3).toInt();

        accountList << value0;
        //显示查找记录
        qDebug() << value0 << value1 << value2 << value3;
    }
}

bool MySQLdb::userSignup(QString account, QString password)
{
    QSqlQuery query;
    QString str=QString("select * from user where name='%1").arg(account);
    query.exec(str);

    if(!query.next())
        //QMessageBox::warning(this,"错误","该用户已存在",QMessageBox::Yes);
        return false;
    str=QString("insert into user value('%1','%2')").arg(account).arg(password);
    bool ret=query.exec(str);
    return ret;

}

bool MySQLdb::userLogin(QString account, QString password)
{
    QSqlQuery query;
    QString str = QString("select * from user where account = '%1' and password = '%2'").arg(account, password);
    query.exec(str);
    if(query.next()){
        return true;
    }
    return false;
}
