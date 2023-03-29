#include "mainwindow.h"
#include "myserver.h"
#define serverIP "127.0.0.1"
#define serverPort 8888


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w1;
    w1.show();


    MainWindow w2;
    w2.show();

    //TcpServer w3;
    MyServer *server = new MyServer();
    server->listen(QHostAddress(serverIP),serverPort);

    return a.exec();
}
