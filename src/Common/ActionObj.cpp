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

  //m_timer.start(1000);
}




bool ActionObj::action(ACT::_KEY act, QVariantList listData, QString &sError)
{
    QVariantList out;

    return action(act,listData,out,sError);

}

bool ActionObj::action(ACT::_KEY act, QVariantMap data, QString &sError)
{
    CData input;

    input.iAciton = ACT::_KEY(act);

    input.dData = data;

    CData re;

    re = query(input);

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(ACT::_KEY act, QVariantMap data, QVariantMap &out, QString &sError)
{
    CData input;

    input.iAciton = ACT::_KEY(act);

    input.dData = data;

    CData re;

    re = query(input);

    out = re.dData;

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(ACT::_KEY act, QVariantMap data,QVariantList &listOut, QString &sError)
{
    CData input;

    input.iAciton = ACT::_KEY(act);

    input.dData = data;

    CData re;

    re = query(input);

    listOut = re.listData;

    sError =re.sMsg;

    return re.bOk;
}

bool ActionObj::action(ACT::_KEY act, QVariantList listData, QVariantList &listOut, QString &sError)
{
    CData data;

    data.iAciton = ACT::_KEY(act);

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
        return callServer(data);
    else
        return m_queryObj.queryData(data);
}



CData ActionObj::callServer(CData data)
{

    emit lockLoading(true);

    CData re;

    QByteArray out;

    qDebug()<<"call server : "<<data.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<data.enCodeJson();
    RPKCORE.network.connectHost(m_ip,m_port,data.enCodeJson(),out);

    re.deCodeJson(out);

    qDebug()<<"server return : "<<re.iAciton<<" , "<<QTime::currentTime().toString("hh:mm:ss:zzzz");
    qDebug()<<out;
    emit lockLoading(false);

    return re;
}

void ActionObj::updateIndx(QString sId, QByteArray data, int Error)
{
    qDebug()<<"heart bee get : "<<data;
}
