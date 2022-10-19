#include "ActionObj.h"

ActionObj::ActionObj(QObject *parent)
    : QObject{parent}
{

    connect(&RPKCORE.network,SIGNAL(replyFromServer(QString,QByteArray,int))
            ,this,SLOT(updateIndx(QString,QByteArray,int)));

    m_timer.connect(&m_timer,&QTimer::timeout,this,[=]()
    {

        CData data;

        data.iAciton=1;

        RPKCORE.network.connectHost("getUpdate",m_ip,m_port,data.enCodeJson());

    });


}

ActionObj::~ActionObj()
{
    qDebug()<<"destroy ActionObj";

    m_timer.stop();
}

void ActionObj::setStartSyanc(bool b)
{

    if(b)
        m_timer.start(1000);
    else
        m_timer.stop();

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

    out = re.dData;

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
    CData re;

    QString sApi = QString::number(data.iAciton);
    while(sApi.length()<4)
        sApi="0"+sApi;

    QString sGroup = sApi.left(2);

    bool bIsQuery = isQueryApi(data.iAciton);

    bool bNeedFromeServer =isNeedFromServer(data.iAciton);

    if(!bNeedFromeServer)
    {
        re.deCodeJson(m_dKeepData[sApi].toByteArray());

        return re;
    }

    qDebug()<<"api : "<<sApi<<"is query api :"<< bIsQuery<<" , need frome server: "<<bNeedFromeServer;
    qDebug()<<"local trigger : "<<m_dLocalTrigger;
    qDebug()<<"update trigger : "<<m_dUpdateTrigger;


    emit lockLoading(true);


    QByteArray out;

    qDebug()<<"call server : "<<data.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<data.enCodeJson().toStdString().c_str();
    RPKCORE.network.connectHost(m_ip,m_port,data.enCodeJson(),out);

    re.deCodeJson(out);

    if(re.bOk &&bIsQuery)
    {
        if(isQueryApi(data.iAciton))
        {
            m_dLocalTrigger[sGroup] = re.sTrigger;
        }
        else
        {
            //如果上傳新資料，本地端該群資料需重取，只用heartbeat 會有時間差
            m_dLocalTrigger[sGroup] = "0";

        }

        m_dKeepData[sApi] = out;

    }



    qDebug()<<"server return : "<<re.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<out.toStdString().c_str();
    emit lockLoading(false);

    return re;
}



bool ActionObj::isQueryApi(int iApi)
{
    return m_queryObj.isQueryApi(iApi);
}

bool ActionObj::isNeedFromServer(int iApi)
{
    QString sApi=QString::number(iApi);

    while(sApi.length()<4)
        sApi="0"+sApi;

    QString sGroup = sApi.left(2);

    if(m_dLocalTrigger.keys().indexOf(sGroup)<0)
    {
        m_dLocalTrigger[sGroup]="0";
    }


    qDebug()<<"local trigger : "<<m_dLocalTrigger[sGroup];
    qDebug()<<"updater trigger: "<<m_dUpdateTrigger[sGroup];


    if(m_dLocalTrigger[sGroup]=="0")
        return true;

    if(m_dKeepData.keys().indexOf(sApi)<0)
        return true;


    return m_dLocalTrigger[sGroup] != m_dUpdateTrigger[sGroup];

}

void ActionObj::updateIndx(QString sId, QByteArray data, int )
{

    if(sId=="getUpdate")
    {

        QString sTrigger(data);

        QStringList listSt = sTrigger.split(",");

        QMap<QString,QString> d;

        foreach(QString st,listSt)
        {

            QStringList tmp = st.split("=");

            d[tmp.first()] = tmp.last();

        }

        m_dUpdateTrigger = d;

    }


}
