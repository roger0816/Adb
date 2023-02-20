#include "QueryObj.h"




QueryObj::QueryObj(QObject *parent)
    : QObject{parent}
{
    //  connect(&m_sql,&CSqlClass::tbUpdate,this,&QueryObj::updateTrigger);

    m_timer.connect(&m_timer,&QTimer::timeout,[=]()
    {
        QStringList listKey = m_dLogingUser.keys();

        QStringList listRmKey;

        for(int i=0;i<listKey.length();i++)
        {
            int iCount = m_dLogingUser[listKey.at(i)].toMap()["Count"].toInt();

            if(iCount>0)
                m_dLogingUser[listKey.at(i)].toMap()["Count"]=iCount-1;
            else
                listRmKey.append(listKey.at(i));
        }


        foreach(QString s,listRmKey)
        {
            m_dLogingUser.remove(s);
        }

    });

    m_timer.start(1000);


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

void QueryObj::setKeyValue(QString sKey, QVariant value)
{
    QVariantMap d;
    d["skey"]=sKey;
    d["svalue"]=value;

    QString sError;
     m_sql.insertTb("Settings",d,sError,true);
}

QVariant QueryObj::keyValue(QString sKey)
{
    QVariant re;
    QVariantMap d;
    d["skey"]=sKey;
    QVariantList out;
    QString sError;
    m_sql.queryTb("Settings",d,out,sError);

    if(out.length()>0)
    {
        re = out.first().toMap()["svalue"];
    }
    return re;
}



void QueryObj::setDataBase(bool bMysql, QString sIp, QString sPort)
{
    qDebug()<<"database ip :"<<sIp;

    if(m_sql.openDb(bMysql,sIp,sPort,"adp"))
        m_dTrigger = m_sql.readTrigger();
}

CData QueryObj::queryData(CData data)
{

    CData re;

    QString sMsg;

    re.iAciton = data.iAciton;

    re.iState = ACT_RECALL;


    if(data.iAciton==1)  //heartbeat (Trigger)
    {

        re.iAciton = data.iAciton;
        re.iState=ACT_RECALL;

        QString st(heartBeat());
        re.dData["trigger"]=st;

        re.sHeartBeat=st;
        QString sUserSid = data.dData["UserSid"].toString();

        QString sSession = data.dData["Session"].toString();

        QVariantMap d;

        re.bOk =checkSesison(sUserSid,sSession);

        return re;

    }


    if(data.iAciton==1000)
    {
        int iRe=-1;

        bool bOk=false;

        if(!checkAppVersion(data.sMsg))
        {
            bOk=false;
            sMsg="版本無法使用，請更新版本";
        }

        else
        {
            QString sUserId;

            if(data.listData.length()>=2)
            {

                bOk = m_sql.checkLogin(data.listData.first().toString(),data.listData.last().toString(),re.dData,sMsg);

                sUserId =re.dData["Sid"].toString();
                re.listData.append(iRe);


            }
            if(bOk)
            {
                sMsg ="登入成功";

                QString str=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmss");

                QByteArray s=QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);

                QString sSession(s.toHex());

                re.dData["Session"]=sSession;

                QVariantMap d;
                d["Session"]=sSession;
                d["Count"]=5;

                m_dLogingUser[sUserId] = d;
            }
            else
                sMsg="帳密錯誤";
        }

        re.sMsg = sMsg;

        re.bOk = bOk;

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


    re.sHeartBeat=QString(heartBeat());

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

bool QueryObj::checkAppVersion(QString sVersion)
{
    bool bRe = false;

    QStringList listTmp = sVersion.split(".");

    if(listTmp.length()<3)
        return false;

    //ex :   v1.01.1115_2

    int iVersion = listTmp.at(1).toInt();
    int iDate=listTmp.at(2).mid(0,4).toInt();
    if(iVersion>=10)
    {
        if(iVersion==10)
        {
            QString sT="0220";
            if(iDate<sT.toInt())
                return false;
        }
        return true;
    }

    /*
    if(listTmp.at(1).toInt()>=1)
    {

        if(listTmp.at(2).split("_").first().toInt()>1129)
            bRe =true;
    }
    */




    return bRe;
}

bool QueryObj::checkSesison(QString sUserSid, QString sSession)
{

    if(!m_dLogingUser.keys().contains(sUserSid))
        return false;


    if(m_dLogingUser[sUserSid].toMap()["Session"].toString()!=sSession)
        return false;

    QVariantMap d= m_dLogingUser[sUserSid].toMap();

    d["Count"]=5;

    m_dLogingUser[sUserSid] =d;

    return true;
}






