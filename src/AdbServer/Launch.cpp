#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{
    LIB.network()->runTcpServer("6000");

    connect(LIB.network(),SIGNAL(signalReadAll(QByteArray)),this,SLOT(getData(QByteArray)));

}

void Launch::getData(QByteArray dData)
{
    qDebug()<<"server get Data: "<<dData;

    LIB.network()->recallClient("AAAA");
}
