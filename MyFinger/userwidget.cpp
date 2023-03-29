#include "userwidget.h"
#include "ui_userwidget.h"
#include "chatwindow.h"
#include "call.h"

Userwidget::Userwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userwidget)
{
    ui->setupUi(this);
}

Userwidget::Userwidget(MemberInfo member_input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Userwidget)
{
    ui->setupUi(this);
    member_widget = member_input;
    setWindowIcon(QIcon(":/img/img/logo1.png"));
    this->loadStyleSheet(":/qss/aqua.qss");
    /*
    udp_receive_port = receive_port;
    udp_send_ip = send_ip;
    udp_send_port = send_port;
    udp_send_account = send_account;
    */
    ui->label_pic->setPixmap(QPixmap(QString(":/img/userPic/%1.jpg").arg(member_widget.account)));
    ui->label_name->setText(QObject::tr("%1").arg(member_widget.account));
    ui->label_diy->setText(QObject::tr("%1:%2").arg(member_widget.ip).arg(member_widget.port));


}

Userwidget::~Userwidget()
{
    delete ui;
}


void Userwidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        //qDebug()<<QObject::tr("发起对%1的通话请求").arg(member_widget.account);
        emit signal_initConnect(member_widget);//传递目标用户的信息给主机

    }

}
void Userwidget::loadStyleSheet(const QString &styleSheetFile)
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

