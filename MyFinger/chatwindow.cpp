#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("聊天界面"));
    setWindowIcon(QIcon(":/img/img/logo1.png"));
    this->loadStyleSheet(":/qss/aqua.qss");
    ui->textEdit_2->hide();
    this->setFixedSize(400,410);

    receiver = new QUdpSocket(this);
    receiver->bind(member_local.port, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &ChatWindow::processPendingDatagram);

    sender = new QUdpSocket(this);
}

ChatWindow::ChatWindow(MemberInfo local, MemberInfo target,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("聊天界面"));
    setWindowIcon(QIcon(":/img/img/logo1.png"));
    this->loadStyleSheet(":/qss/aqua.qss");
    ui->textEdit_2->hide();
    this->setFixedSize(400,410);

    member_local = local;
    member_target = target;

    receiver = new QUdpSocket(this);

    receiver->bind(member_local.port, QUdpSocket::ShareAddress);
    connect(receiver, &QUdpSocket::readyRead, this, &ChatWindow::processPendingDatagram);

    sender = new QUdpSocket(this);

    ui->label_name->setText(QObject::tr(" %1 -> %2  %3:%4").arg(member_local.account).arg(member_target.account).arg(member_target.ip).arg(member_target.port));
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            qDebug()<< QObject::tr("-- Qt 事件机制,键盘事件(Ctrl + Enter)");
            qDebug()<< QObject::tr("press: Ctrl + Enter");
            if(event->isAutoRepeat()) return;
            on_pushButton_send_clicked();
        }
    }
}

void ChatWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            qDebug()<< QObject::tr("release: Ctrl + Enter");
            if(event->isAutoRepeat()) return;
        }
    }
}

void ChatWindow::processPendingDatagram()
{
    // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;

        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());

        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());
        //QListWidgetItem *item2=new QListWidgetItem(datagram);
        //item2->setForeground (Qt::red);//前景色(文字颜色)
        ui->listWidget->addItem(datagram);


        QDir userDir(QDir::currentPath());
        userDir.mkdir("userDir");
        userDir.cd("userDir");
        QFile file(userDir.absolutePath() + QString("/%1.txt").arg(member_target.account));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
            qDebug() << file.errorString();
        file.write(datagram);
        file.close();
    }
}

void ChatWindow::on_pushButton_send_clicked()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString strData = currentTime.toString("%1  yyyy-MM-dd hh:mm:ss\n").arg(member_local.account);

    QByteArray datagram = strData.toUtf8();

    datagram += ui->textEdit->toPlainText().toUtf8();
    datagram += "\n";
    ui->listWidget->addItem(datagram);
    if(sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress(member_target.ip), member_target.port)){
        qDebug()<<"发送一条信息！";
    }


    QDir userDir(QDir::currentPath());
    userDir.mkdir("userDir");
    userDir.cd("userDir");
    QFile file(userDir.absolutePath() + QString("/%1.txt").arg(member_target.account));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        qDebug() << file.errorString();
    file.write(datagram);
    file.close();
    ui->textEdit->setText("");
}

void ChatWindow::on_pushButton_close_clicked()
{
    close();
}

void ChatWindow::on_pushButton_chatdata_toggled(bool checked)
{
    ui->textEdit_2->setVisible(checked);
    if(checked)
    {
        ui->pushButton_chatdata->setText(tr("隐藏记录"));
        this->setFixedSize(668,410);
        QDir userDir(QDir::currentPath());
        userDir.mkdir("userDir");
        userDir.cd("userDir");
        QFile file(userDir.absolutePath() + QObject::tr("/%1.txt").arg(member_target.account));
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
          qDebug() << file.errorString();

        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QByteArray line = file.readAll();
        QString temp = "-- 聊天记录：\n\n";
        temp += codec->toUnicode(line);

        qDebug() << QObject::tr("聊天记录：") << endl << temp;
        ui->textEdit_2->setText(temp);
        file.close();
    }
    else{
        ui->pushButton_chatdata->setText(tr("聊天记录"));
        this->setFixedSize(400,410);
    }
}

void ChatWindow::loadStyleSheet(const QString &styleSheetFile)
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
