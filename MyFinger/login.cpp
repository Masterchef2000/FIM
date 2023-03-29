#include "login.h"
#include "ui_Login.h"
#include "friendlist.h"



Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::Login(QTcpSocket *socket,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->accountEdit->setFocus();
    this->setWindowTitle(QObject::tr("登陆"));
    ui->pwdEdit->setEchoMode(QLineEdit::Password);

    clientSocket = socket; //用指针传递socket
    //qDebug()<<"客户端socket所用端口："<<clientSocket->localPort();
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

Login::~Login()
{
    delete ui;
}
/*
bool Login::createConnection()
{
    //添加数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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
*/


bool Login::verify(MemberInfo member)
{

    //发送验证请求
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    //out<<(quint16) 0;
    out<<(MessageType)Verify<<member_local.account<<member_local.password;
   // out.device()->seek(0);
    //out<<(quint16) (block.size() - sizeof(quint16));
    //qDebug()<<"客户端socket 发送时状态："<<clientSocket->state();

    qDebug()<<"发送"<<block;
    if(!clientSocket->write(block)){
        qDebug()<<"发送失败";
    }
    clientSocket->flush();
    clientSocket->waitForReadyRead();





    QSqlQuery query;
    query.exec(QString("select * from user where account = '%1' and password = '%2'").arg(member.account, member.password));


    if(query.next()){
        member_local.ip = query.value(2).toString();
        member_local.port = query.value(3).toInt();
        return true;
    }
    return false;
}

void Login::receiveData()
{
    //qDebug("receive");
    QByteArray block = clientSocket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_6);
    qDebug()<<"login接收到报文："<<block;
    int MessageType;
    in>>MessageType;
    switch (MessageType) {
        case AcceptVerify:{
            qDebug("登陆成功！");
            break;
        }

        default:
            qDebug()<<"login：收到无效报文！";
    }
}



void Login::on_pushButton_clicked()
{
    if( ui->accountEdit->text().isEmpty() | ui->pwdEdit->text().isEmpty()){
        QMessageBox::information(NULL,"请检查输入","请检查输入", QMessageBox::Ok);
        return;
    }

    member_local.account =  ui->accountEdit->text();
    member_local.password = ui->pwdEdit->text();
    if(verify(member_local)){
        Friendlist *friendlist = new Friendlist(member_local);
        this ->close();
        friendlist->exec();
    }
    else{
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle(QObject::tr("提示"));
        dialog->resize(250,50);
        dialog->setModal(true);
        QLabel *label = new QLabel(dialog);
        label->setText(QObject::tr("用户名或密码错误\n"));
        dialog->show();
        ui->accountEdit->clear();
        //ui->pwdEdit->clear();
    }
}
