#include <QCoreApplication>
#include <QDebug>
#include "RpkCore.h"


void fnRunTcpServer()
{

    RPKCORE.network.runTcpServer("6000");
}

void fnTcpClient()
{

    QByteArray arr1,arr2;

    arr1.append("test");

    RPKCORE.network.connectHost("127.0.0.1","6000",arr1,arr2);
    qDebug()<<"send";
    qDebug()<<arr2;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RPKCORE;




    return a.exec();
}
