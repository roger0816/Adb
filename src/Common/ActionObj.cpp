#include "ActionObj.h"

ActionObj::ActionObj(QObject *parent)
    : QObject{parent}
{

    connect(&RPKCORE.network,SIGNAL(replyFromServer(QString,QByteArray,int))
            ,this,SLOT(serverTrigger(QString,QByteArray,int)));


    auto heartBeat =[=]()
    {
        CData data;

        data.iAciton=1;

        RPKCORE.network.connectHost("getTrigger",m_ip,m_port,data.enCodeJson());
    };

    m_timer.connect(&m_timer,&QTimer::timeout,heartBeat);



}

ActionObj::~ActionObj()
{
    qDebug()<<"destroy ActionObj";

    m_timer.stop();
}

void ActionObj::setStartSyanc(bool b)
{

    if(b)
    {

        m_timer.start(1000);
    }
    else
        m_timer.stop();

}

bool ActionObj::action(int act, QString sKey, QVariant sValue, QVariantMap &output)
{
    QVariantList list;

    QVariantMap in;
    in[sKey]=sValue;
    int iRet=action(act,in,list);

    if(list.length()>0)
        output=list.first().toMap();

    return iRet;
}

bool ActionObj::action(int act, QVariantMap input, QVariantList &output)
{
    QString sError;

    return action(act,input,output,sError);
}




bool ActionObj::action(int act, QVariantList listData, QString &sError)
{
    QVariantList out;

    return action(act,listData,out,sError);

}

bool ActionObj::action(int act, QVariantMap data, QString &sError)
{
    CData input;

    input.iAciton = act;

    input.dData = data;

    CData re;

    re = query(input);

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(int act, QVariantMap data, QVariantMap &out, QString &sError)
{
    CData input;

    input.iAciton = act;

    input.dData = data;

    CData re;

    re = query(input);

    // out = re.dData;
    if(re.listData.length()>0)
        out = re.listData.first().toMap();

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(int act, QVariantMap data, QVariantList &listOut, QString &sError)
{
    CData input;

    input.iAciton = act;

    input.dData = data;

    CData re;

    re = query(input);

    listOut = re.listData;

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(int act, QVariantList listData, QVariantList &listOut, QString &sError)
{
    CData data;

    data.iAciton = act;

    data.listData = listData;


    CData re;

    re = query(data);

    listOut =re.listData;

    sError = re.sMsg;

    return re.bOk;
}

CData ActionObj::query(CData data)
{

    // data.sUser = m_currentUser.Id;
    data.sUser = m_sCurrentUserId;

    if(m_bDataFromServer)
    {
        return callServer(data);
    }
    else
        return m_queryObj.queryData(data);
}



CData ActionObj::callServer(CData data)
{

    //    if(m_bIsLock)
    //    {
    //        QEventLoop *loop=new QEventLoop(this);

    //        loop->connect(this,&ActionObj::lockLoading,[=](bool)
    //        {
    //            if(!m_bIsLock)
    //                loop->quit();
    //        });

    //        delete loop;
    //    }



    CData re;

    QString sApi = QString::number(data.iAciton);

    QString sCacheKey = apiCacheKey(sApi,data.dData);

    while(sApi.length()<4)
        sApi="0"+sApi;

    QString sGroup = sApi.left(2);

    bool bIsQuery = isQueryApi(data.iAciton);

    bool bNeedFromeServer =isNeedFromServer(data.iAciton,data.dData);
    qDebug()<<"trigger local:"<<m_dLocalTrigger[sGroup]<<", update:"<<m_dUpdateTrigger[sGroup];
    qDebug()<<"call aip :"+sApi<<",data from server:"<<bNeedFromeServer<<",cacheKey:"<<sCacheKey<<"\n";

    if(!bNeedFromeServer)
    {
        re.deCodeJson(m_dKeepData[sCacheKey].toByteArray());

        return re;
    }


    m_bIsLock= true;

    emit lockLoading(m_bIsLock);


    QByteArray out;

    qDebug()<<"call server : "<<data.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<data.enCodeJson().toStdString().c_str();
    RPKCORE.network.connectHost(m_ip,m_port,data.enCodeJson(),out);


    re.deCodeJson(out);


    auto  clearGroupCache = [=](QString sGroup)
    {
        QStringList listKey = m_dKeepData.keys();
        foreach(QString v , listKey)
        {
            if(v.length()>2&&v.left(2) ==sGroup)
            {
                m_dKeepData[v]=QVariant();
            }
        }
    };



    if(re.bOk)
    {

        QString sCacheKey = apiCacheKey(sApi,data.dData);



        if(bIsQuery)
        {
            m_dLocalTrigger[sGroup] = re.sTrigger;

            m_dKeepData[sCacheKey] = out;
        }
        else
        {
            //如果上傳新資料，本地端該群資料需重取，只用heartbeat 會有時間差
            m_dLocalTrigger[sGroup] = "0";

            clearGroupCache(sGroup);

        }




    }



    qDebug()<<"server return : "<<re.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<out.toStdString().c_str();

    m_bIsLock= false;


    emit lockLoading(m_bIsLock);

    return re;
}



bool ActionObj::isQueryApi(int iApi)
{
    return m_queryObj.isQueryApi(iApi);
}

bool ActionObj::isNeedFromServer(int iApi, const QVariantMap conditions)
{

    QString sApi=QString::number(iApi);

    while(sApi.length()<4)
        sApi="0"+sApi;

    QString sGroup = sApi.left(2);

    if(m_dLocalTrigger.keys().indexOf(sGroup)<0)
    {
        m_dLocalTrigger[sGroup]="0";
    }


    if(m_dLocalTrigger[sGroup]=="0")
    {
        return true;
    }
    QString sCacheKey = apiCacheKey(sApi,conditions);

    // qDebug()<<m_dKeepData[sCacheKey].toString().toStdString().c_str();

    if(!m_dKeepData.keys().contains(sCacheKey)
            || m_dKeepData[sCacheKey].toString()=="")
    {
        qDebug()<<"\napi:"<<iApi<<"no cacheData";

        return true;
    }

    return m_dLocalTrigger[sGroup] != m_dUpdateTrigger[sGroup];

}

QString ActionObj::apiCacheKey(QString  sApi,QVariantMap conditions)
{

    QString sRe = sApi;

    QString sCondition="_";

    QStringList listTmp = conditions.keys();

    foreach(QString v, listTmp)
    {
        sCondition+=v+"="+conditions[v].toString();
    }

    if(listTmp.length()>0)
        sRe=sRe+sCondition;

    return sRe;
}

void ActionObj::serverTrigger(QString sId, QByteArray data, int )
{

    if(sId=="getTrigger")
    {

        CData re(data);

        if(re.iAciton==1 && re.iState==ACT_RECALL)
        {

            QString sTrigger(re.dData["trigger"].toString());

            QStringList listSt = sTrigger.split(",");

            QMap<QString,QString> d;

            foreach(QString st,listSt)
            {

                QStringList tmp = st.split("=");

                QString sApiGroup = tmp.first();

                QString sTrigger = tmp.last();

                d[sApiGroup] = sTrigger;

                if(m_dLocalTrigger[tmp.first()]!=""
                        && m_dLocalTrigger[tmp.first()]!="0" )
                {
                    if(m_dLocalTrigger[sApiGroup] !=sTrigger)

                        emit updateTrigger(sApiGroup);
                }


            }


            m_dUpdateTrigger = d;

            if(m_dLocalTrigger.keys().length()<1)
            {
                qDebug()<<m_dUpdateTrigger;
            }



        }
    }


}
