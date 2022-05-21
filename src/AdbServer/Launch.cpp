#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{
    RPKCORE.network.runTcpServer("6000");

    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray)),this,SLOT(getData(QByteArray)));




}

void Launch::getData(QByteArray dData)
{
    qDebug()<<"server get Data: "<<dData;

    CData reData;

    reData.deCodeJson(dData);

    RPKCORE.network.recallClient(reData.enCodeJson());
}
