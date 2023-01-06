#include "Launch.h"

Launch::Launch(QObject *parent)
    : QObject{parent}
{



   // 167.172.87.35  server
    //167.99.66.45 test server
   // QString sIp="127.0.0.1";



    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));



}

void Launch::startServer(QString sIp)
{
    qDebug()<<"version : "<<ADP_VER;

  queryObj.setDataBase(true,sIp);


  RPKCORE.network.runTcpServer("6000");
}

void Launch::getData(QByteArray dData, uintptr_t handleId)
{



    CData data;

    data.deCodeJson(dData);


    CData reData = queryObj.queryData(data);

    QByteArray re = reData.enCodeJson();

    RPKCORE.network.recallClient(re,handleId);



  //  qDebug()<<"server recal: "<<reData.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss.zzz");

}
