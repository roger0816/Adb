#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{

    //QString sIp="206.189.185.20";
   //  QString sIp="178.128.62.72";
      QString sIp="167.172.87.35";

   // QString sLocal="127.0.0.1";

    queryObj.setDataBase(true,sIp);


    RPKCORE.network.runTcpServer("6000");

    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));



}

void Launch::getData(QByteArray dData, uintptr_t handleId)
{



    CData data;

    data.deCodeJson(dData);

    if(data.iAciton==1)
    {
        RPKCORE.network.recallClient(queryObj.heartBeat(),handleId);

        return;
    }




    CData reData = queryObj.queryData(data);

    QByteArray re = reData.enCodeJson();

    RPKCORE.network.recallClient(re,handleId);



  //  qDebug()<<"server recal: "<<reData.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss.zzz");

}
