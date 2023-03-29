#include "friendlist.h"
#include "ui_friendlist.h"
#include "userwidget.h"
#include "login.h"
#include "chatwindow.h"
#include "memberinfo.h"

Friendlist::Friendlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Friendlist)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/img/logo1.png"));
    this->loadStyleSheet(":/qss/aqua.qss");
}

Friendlist::Friendlist(MemberInfo member_input,  QWidget *parent):
    QDialog(parent),
    ui(new Ui::Friendlist)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("好友列表"));
    member_local = member_input;

    setWindowIcon(QIcon(":/img/img/logo1.png"));
    this->loadStyleSheet(":/qss/aqua.qss");
    //qDebug() << QString("打开好友列表：%1").arg(member_local.account);
    ui->label_title->setText(QObject::tr("account:%1").arg(member_local.account));
    this->show();
    vertical_layout = new QVBoxLayout(ui->page_friend);
    matchUserFriend();
    waitForCall();
    MemberInfo man;

    pQwait = new QWaiting(this);
    connect(this,SIGNAL(signal_changestate(QString)),pQwait,SLOT(slot_changestate(QString)));


}

Friendlist::~Friendlist()
{
    delete ui;
}


bool Friendlist::createConnection()
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

void Friendlist::matchUserFriend()
{
    QSqlQuery query;
    QString str = QString("select account,password,ip,port from user where account = %1").arg(member_local.account);
    //qDebug() << QString("-- 用户好友列表：");
    query.exec(str);
    while(query.next()){
        member_widget.account = query.value(0).toString(); //account
        member_widget.ip = query.value(2).toString();      //ip
        member_widget.port = query.value(3).toInt();           //port
        if(member_widget.account == member_local.account)continue;
        Userwidget *user = new Userwidget(member_widget);
        vertical_layout->addWidget(user);
        connect(user,SIGNAL(signal_initConnect(MemberInfo)),
                this,SLOT(initConnect(MemberInfo)));
    }

    query.exec("select account,password,ip,port from user");
    while(query.next())
    {
        member_widget.account = query.value(0).toString(); //account
        member_widget.ip = query.value(2).toString();      //ip
        member_widget.port = query.value(3).toInt();           //port

        if(member_widget.account == member_local.account)continue;
        Userwidget *user = new Userwidget(member_widget);
        vertical_layout->addWidget(user);

        //动态数组？


        connect(user,SIGNAL(signal_initConnect(MemberInfo)),
                this,SLOT(initConnect(MemberInfo)));
    }
    vertical_layout->addStretch(1);
}




/*************接听方的连接*************/
void Friendlist::waitForCall()
{
    tcpServer = new QTcpServer(this);
    QHostAddress hostip =  QHostAddress(member_local.ip);
    if(!tcpServer->listen(hostip,member_local.port))
    {  //监听本地主机的IP和端口，如果出错就输出错误信息，并关闭
        qDebug() << tcpServer->errorString();
        close();
    }

    //连接信号和相应槽函数
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(getCall()));
}

//收到来电
void Friendlist::getCall()
{
    //qDebug()<<QObject::tr("%1 ：收到通话请求").arg(member_local.account);

    //获取客户端连接
    recvSocket = tcpServer->nextPendingConnection();
    connect(recvSocket,SIGNAL(readyRead()),this,SLOT(readData_rec()));
}

void Friendlist::readData_rec()
{

    QDataStream in(recvSocket);
    int MessageType;
    in>>MessageType;

    switch (MessageType) {
    case NewCall:
            in>>member_source.account;
            callChioce();
            break;
    }
}


//选择是否接听
void Friendlist::callChioce()
{
    //获取来电方的地址和端口
    member_source.ip = recvSocket->peerAddress().toString();
    member_source.port = recvSocket->peerPort();

    QString dlgTitle="通话请求";
    QString strInfo= QString("收到来自用户%1的拨号请求(地址%2:%3)，是否接听？").arg(member_source.account).arg(member_source.ip).arg(member_source.ip);
    QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
    QMessageBox::StandardButton result;//返回选择的按钮
    result=QMessageBox::question(this, dlgTitle, strInfo,
                      QMessageBox::Yes|QMessageBox::No,
                      defaultBtn);


    QByteArray callresult; //结果--接听or拒绝
    QDataStream out(&callresult, QIODevice::WriteOnly);

    if (result==QMessageBox::Yes){
        //qDebug()<<"yes";
        //给发起方返回允许接听的信息
        out<<(MessageType)AcceptCall;
        //显示聊天窗口
/*
        emit(signal_changestate("正在查询对方公钥.."));
        pQwait->show();
        for (int i = 0; i < 500000; i++)
        {
            qDebug()<<"loading";
            QCoreApplication::processEvents();
        }
*/

        ChatWindow *chat = new ChatWindow(member_local, member_source);
        chat->show();

    }
    else if(result==QMessageBox::No){
        qDebug()<<"no";
        out<<(MessageType)RejectCall;
    }
    recvSocket->write(callresult);
}










/*************拨号方的连接*************/
void Friendlist::initConnect(MemberInfo member_init)
{
    member_target =  member_init; //设置为目标通话对象
    //qDebug()<<QObject::tr("initing Connection with %1...").arg(member_target.account);

    sendSocket = new QTcpSocket(this);
    connect(sendSocket, SIGNAL(readyRead()),
            this,SLOT(readData()));


    sendSocket->abort(); //取消已有的连接
    sendSocket->bind(member_local.port);
    //连接到主机，这里从界面获取主机地址和端口号
    sendSocket->connectToHost(member_target.ip, member_target.port);
    //等待连接成功
    if(!sendSocket->waitForConnected(30000))
    {
        qDebug() << "Connection failed!";
        return;
    }

    //发送通话请求
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<(MessageType)NewCall<<member_local.account; //通话请求+本机名
    sendSocket->write(block);

    //设置一个box提示等待中
    QMessageBox *box_wait_for_reply = new QMessageBox(QMessageBox::Information, "提示",  "正在等待对方响应... ",QMessageBox::Close,this);
    box_wait_for_reply->show();
    connect(sendSocket, SIGNAL(readyRead()),box_wait_for_reply,SLOT(close()));


}

void Friendlist::readData()
{

    QByteArray block = sendSocket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);
    int MessageType;
    in>>MessageType;

    switch (MessageType) {
        case AcceptCall:{

            ChatWindow *chat = new ChatWindow(member_local, member_target);
            chat->show();
         break;
        }
        case RejectCall:{
            QString rejectinfo = QString("你向%1发起的通话请求被拒绝！").arg(member_target.account);
            QMessageBox::information(this,"通话请求被拒绝！",rejectinfo,QMessageBox::Yes);
         break;
        }

    }
}

void Friendlist::loadStyleSheet(const QString &styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());//读取样式表文件
        this->setStyleSheet(styleSheet);//把文件内容传参
        file.close();
    }
    else
    {
        QMessageBox::information(this,"tip","cannot find qss file");
    }
}

