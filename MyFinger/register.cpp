#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("注册界面"));
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_register_clicked()
{
    QString account = ui->accountEdit->text();
    QString password = ui->pwdEdit->text();
    QString port = ui->portEdit->text();

    qDebug()<<QObject::tr("-- 键入内容");
    qDebug()<<QObject::tr("用户名：%1").arg(account);
    qDebug()<<QObject::tr("密码：%1").arg(password);
    qDebug()<<QObject::tr("端口：%1").arg(port);


    userRegister(account,password,port);
    /*
    //QString procname = "notepad";
    QString procname = "D:\\CODE\\Qt\\MyFinger\\finger\\FP_In_C(5).exe";
    //QString procname = "../finger/FP_In_C.exe";
    QString procarg = QString("D:\\CODE\\Qt\\MyFinger\\finger\\%1.tif").arg(account);
    QStringList list;
    //list<<"-r"<<procarg;
    list << procarg;
    qDebug()<<list;
    //QProcess *myproc = new QProcess();
    myproc = new QProcess();
    connect(myproc,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(statechange(QProcess::ProcessState)));
    connect(myproc, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError (QProcess::ProcessError)));    //myproc->setWorkingDirectory("D:/CODE/Qt/MyFinger/finger");
    connect(myproc, SIGNAL(finished(int)),this,SLOT(Result(int)));
    //myproc->setNativeArguments("temp.png");
    myproc->start(procname,list);
    //myproc->startDetached(procname,list);


    if(!myproc->waitForStarted())
    {
        qDebug()<<"failure!";
    }else
    {
        qDebug()<<"succ!";
    }

*/
}

void Register::Result(int a)
    {
        if (0 == a)
        {
            QByteArray res = myproc->readAllStandardOutput(); //获取标准输出
           // ui.Txt->appendPlainText(QString::fromLocal8Bit(res)); //打印出来
            QString str =  QString::fromLocal8Bit(res);
            qDebug()<<str;
        }
        myproc->close();
    }

void Register::statechange(QProcess::ProcessState newstate){
    qDebug()<<"new state is:"<<newstate;
}

void Register::processError(QProcess::ProcessError error)
{
    qDebug()<<error;
}



void Register::userRegister(const QString &strAccount, const QString &strPwd, const QString &strPort)
{
    QSqlQuery query;
    //query.exec(QString("select * from user where account = '%1' and password = '%2'").arg(strAccount, strPwd));
    query.exec(QString("insert into user values('%1','%2','127.0.0.1','%3')").arg(strAccount, strPwd, strPort));
    qDebug()<<QObject::tr("-- 注册成功！");
    selectTable();
}

void Register::selectTable()
{
    QStringList accountList;
    QSqlQuery query;
    //删除user表
    //query.exec("drop table user");
    //查找user表中的记录的account项和password项的值
    query.exec("select account,password,ip,port from user");
    //query.next()指向查找到的第一条记录，然后每次后移一条记录
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

