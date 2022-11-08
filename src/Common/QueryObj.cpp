#include "QueryObj.h"




QueryObj::QueryObj(QObject *parent)
    : QObject{parent}
{
    //  connect(&m_sql,&CSqlClass::tbUpdate,this,&QueryObj::updateTrigger);




}

void QueryObj::linkage(int iApi, QList<int> listApi)
{

    QString sApi =QString::number(iApi);

    QStringList list;

    foreach(int i,listApi)
    {
        list.append(QString::number(i));
    }

    m_dLinkage[sApi]=list;

}

void QueryObj::linkage(int iApi, int iBindApi)
{
    QList<int> list;

    list.append(iBindApi);

    return linkage(iApi,list);
}



void QueryObj::setDataBase(bool bMysql, QString sIp, QString sPort)
{
    if(m_sql.openDb(bMysql,sIp,sPort,"adp"))
        m_dTrigger = m_sql.readTrigger();
}

CData QueryObj::queryData(CData data)
{

    CData re;

    if(data.iAciton==1)  //heartbeat (Trigger)
    {

        re.iAciton = data.iAciton;
        re.iState=ACT_RECALL;

        QString st(heartBeat());
        re.dData["trigger"]=st;

        re.bOk = true;

        return re;
    }




    re = implementRecall(data);

    if(re.bOk)
    {
        re.sTrigger = checkUpdate(data.iAciton);
    }
    else
    {
        re.sTrigger="0";
    }

    qDebug()<<"recall api "<<data.iAciton<<", trigger : "<<re.sTrigger;

    return re;
}


QByteArray QueryObj::heartBeat()
{
    QStringList list;

    foreach(QString sKey,m_dTrigger.keys())
    {
        list.append(sKey+"="+m_dTrigger.value(sKey));
    }

    QByteArray bRe;

    bRe.append(list.join(",").toUtf8());

    return bRe;
}

bool QueryObj::isQueryApi(int iApi)
{
    QString sApi =QString::number(iApi);

    return sApi.length()>=4 && sApi.mid(2,1)=="3";

}



QString QueryObj::checkUpdate(int iApi)
{
    QString sTrigger="0";

    QString sTmp = QString::number(iApi);

    while(sTmp.length()<4)
        sTmp="0"+sTmp;

    QString sGroup = sTmp.left(2);


    if(isQueryApi(iApi))
    {
        if(!m_dTrigger.keys().contains(sGroup))
        {
            m_dTrigger[sGroup] ="1";
        }
        else{}

    }
    else
    {
        QString sUpdateTime = QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmss");

        m_dTrigger[sGroup] = sUpdateTime;

        m_sql.saveTrigger(sGroup,sUpdateTime);
    }

    sTrigger = m_dTrigger[sGroup];


    return sTrigger;
}






