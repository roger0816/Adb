#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{

    QString sIp="206.189.185.20";

   // QString sLocal="127.0.0.1";

    act.setDataFromServer(false);

    act.setDataBase(true,sIp);




    RPKCORE.network.runTcpServer("6000");

    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));




}

void Launch::getData(QByteArray dData, uintptr_t handleId)
{

    CData data;

    data.deCodeJson(dData);

    qDebug()<<"server get Data: "<<data.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss.zzz");


    CData reData = act.query(data);

    QByteArray re = reData.enCodeJson();

    RPKCORE.network.recallClient(re,handleId);



    qDebug()<<"server recal: "<<reData.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss.zzz");

}
