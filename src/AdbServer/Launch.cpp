#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{
    act.m_queryObj.openDb(true);

    act.setDataFromServer(false);



    RPKCORE.network.runTcpServer("6000");

    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));




}

void Launch::getData(QByteArray dData, uintptr_t handleId)
{
    qDebug()<<"server get Data: "<<dData.toStdString().c_str()<<"\n";



    CData data;

    data.deCodeJson(dData);

    CData reData = act.query(data);

    QByteArray re = reData.enCodeJson();
    qDebug()<<"server return data : "<<re.toStdString().c_str()<<" \n";

    RPKCORE.network.recallClient(re,handleId);
}
