#include "DataSync.h"

DataSync::DataSync(QObject *parent)
    : QObject{parent}
{

    connect(&m_timer,&QTimer::timeout,this,&DataSync::slotTimer);

    m_timer.start(500);

    connect(&RPKCORE.network,&Network::replyFromServer,this,&DataSync::slotServerRecv);

}

void DataSync::setServer(bool b, QString sIp, QString sPort)
{
    m_sIp = sIp;

    m_sPort = sPort;

    m_act.setServer(b,sIp,sPort);
}

void DataSync::slotTimer()
{
    return;
   CData data;

   QVariantMap in;

   QDate tDate=QDate::currentDate().addDays(-1);

   in["OrderDate >="]=tDate.toString("yyyyMMdd");


   data.iAciton=ACT::QUERY_ORDER;

   data.dData = in;

   m_actId=QDateTime::currentDateTimeUtc().toString("yyMMddhhmmsszzz");

   RPKCORE.network.connectHost(m_actId,m_sIp,m_sPort,data.enCodeJson());

}

void DataSync::slotServerRecv(QString sId, QByteArray data, int error)
{
    if(sId==m_actId)
    {
        qDebug()<<data;


    }


}


