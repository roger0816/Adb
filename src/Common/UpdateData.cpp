#include "UpdateData.h"

DataProvider::DataProvider(QObject *parent)
    : QObject{parent}
{

}

QString DataProvider::setData(QVariantList data)
{
    if(data.length()<1)
    {
        return m_lastUpdate;
    }

    m_bOnSync = true;
    QVariantMap d;
    QVariant v =d["data"];

    foreach(QVariant v ,data)
    {
        m_oriData[v.toMap()["Sid"].toInt()]=v;
    }


    QList<int> keys=m_oriData.keys();
    // 使用 Qt 的 qSort 函數進行排序
      qSort(keys.begin(), keys.end());

      m_list.clear();

      for(int i=0;i<keys.length();i++)
      {
        QVariant d =m_oriData[keys[i]];
        QString sUpdateTime = d.toMap()["UpdateTime"].toString();
        m_list.append(d);
        if(sUpdateTime>m_lastUpdate)
            m_lastUpdate=sUpdateTime;
      }


    changeData();

    m_bOnSync = false;

    return m_lastUpdate;
}



UpdateData::UpdateData(QObject *parent)
{
    connect(&RPKCORE.network,&Network::singalLongConnect,this,&UpdateData::slotRead);
    m_timer.connect(&m_timer,&QTimer::timeout,this,&UpdateData::slotTimer);
    m_timer.start(3000);
}

int UpdateData::connectIp(QString sIp, QString sPort)
{
    int iRe = RPKCORE.network.openConnect(sIp,sPort);
    qDebug()<<"connect update port "<<iRe;
    return iRe;
}

void UpdateData::setRun(bool b)
{
    m_bRun=b;
}

void UpdateData::sendData(QByteArray arrInput)
{
    qDebug()<<"update port send data len : "<<arrInput;
    RPKCORE.network.sendData("",arrInput);
}

void UpdateData::runUpdate()
{
    QVariantMap in;
    QVariantList out;

    in["OrderDate"]=queryDateTime.Order;

    //in["OrderDate"]="19990101000000";
    //in["ASC"]="OrderTime";  //不能改顺序，依sid排，因为報價/下單要用
    QString sError;

    CData input;

    input.iAciton = ACT::UPDATE_DATA;

    input.dData = in;

     qDebug()<<"update port send data : "<<in;
    bool bOk = RPKCORE.network.sendData("",input.enCodeJson());
    qDebug()<<"send data is :"<<bOk;
    if(!bOk)
        m_bRun=true;


}



void UpdateData::slotRead(QString sConnect, QString sId, QByteArray data, int Error)
{
    qDebug()<<"connect : "<<sConnect<<" , sId : "<<sId;
    qDebug()<<"data len : "<<data.length();

    CData tmp;
    tmp.deCodeJson(data);
    QVariantMap reData = tmp.dData;
    qDebug()<< reData.keys();
    if(reData.contains("OrderData"))
    {
        queryDateTime.Order=order.setData(reData["OrderData"].toList());
        qDebug()<<"orderData len : "<<reData["OrderData"].toList().length();
    }
    QTimer::singleShot(3000,[=]{
        m_bRun = true;
    });

}

void UpdateData::slotTimer()
{
    if(m_bRun && !order.m_bOnSync)
    {
        m_bRun= false;
        runUpdate();

    }
    else
    {
        qDebug()<<"run is : "<<m_bRun<<" , sync : "<<order.m_bOnSync;
    }
}
