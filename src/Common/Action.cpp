#include "Action.h"

Action::Action(QObject *parent)
    : QObject{parent}
{
    setDataFromServer(false);



}

void Action::setDataFromServer(bool b)
{
    m_bDataFromServer = b;
}

bool Action::action(ACT::_KEY act, QVariantList listData, QString &sError)
{
    QVariantList out;

    return action(act,listData,out,sError);

}

bool Action::action(ACT::_KEY act, QVariantMap data, QString &sError)
{
    CData input;

    input.iAciton = ACT::_KEY(act);

    input.dData = data;

    CData re;

    re = query(input);

    sError =re.sMsg;

    return re.bOk;
}

bool Action::action(ACT::_KEY act, QVariantMap data, QVariantMap &out, QString &sError)
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

bool Action::action(ACT::_KEY act, QVariantMap data,QVariantList &listOut, QString &sError)
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

bool Action::action(ACT::_KEY act, QVariantList listData, QVariantList &listOut, QString &sError)
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

bool Action::checkLogin(QString sUser, QString sPass, QString &sError)
{

    CData data;

    data.iAciton = ACT::LOGIN;

    data.listData<<sUser<<sPass;

    CData dRe = query(data);

    bool bOk = dRe.bOk;

    sError = dRe.sMsg;

    if(bOk)
    {
        m_currentUser.setData(dRe.dData);

    }

    return bOk;


//    m_sCurrentLoginUser.clear();

//    int iRe = -1;

//    if(bOk && data.listData.length()>0)
//    {


//        m_sCurrentLoginUser = data.sUser;

//        iRe = dRe.listData.first().toInt();

//        if(m_sCurrentLoginUser=="root")
//            iRe =99;
//    }

//    m_iUserLv = iRe;

//    return iRe;


}

bool Action::addUser(QString sUser, QString sPass,QString sCid, QString sName,int iLv,QDate startDate, QString &sError)
{
    CData data;

    data.iAciton = ACT::ADD_USER;

    data.listData<<sUser<<sPass<<sCid<<sName<<QString::number(iLv)<<startDate.toString("yyyyMMdd");

    CData dRe = query(data);

    sError = dRe.sMsg;


    return dRe.bOk;
}



bool Action::editUser(QVariantMap userData, QString &sError)
{

    CData data;

    data.iAciton = ACT::EDIT_USER;

    data.listData.append(userData);

    CData dRe = query(data);

    sError = dRe.sMsg;
    return dRe.bOk;

}

bool Action::delUser(QString sUser,QString &sError)
{
    CData data;

    data.iAciton = ACT::DEL_USER;

    data.listData<<sUser;

    CData dRe = query(data);

    sError = dRe.sMsg;

    return dRe.bOk;
}

QList<UserData> Action::queryUser(QString sId)
{
    CData data;

    if(sId!="")
        data.dData["Sid"]= sId;

    data.iAciton = ACT::QUERY_USER;

    CData dRe = query(data);

    QList<UserData> listRe;

    foreach(QVariant v,dRe.listData)
    {
        UserData user;

        user.setData(v.toMap());

        listRe.append(user);
    }

    return listRe;
}

bool Action::setKeyValue(QString key, QString value, bool inLocal)
{
    bool bRe= false;


    if(inLocal)
    {

        bRe = RPKCORE.database.insertKeyPair(key,value,1);

        return bRe;
    }



    CData data;

    data.iAciton=ACT::SET_VALUE;

    data.listData.append(key);
    data.listData.append(value);

    CData re = query(data);

    return re.bOk;
}

QString Action::getKeyValue(QString key, bool inLocal)
{
    QString sRe="";

    if(inLocal)
    {

        sRe = RPKCORE.database.getKeyPair(key,1);

        return sRe;
    }

    CData data;

    data.iAciton=ACT::GET_VALUE;

    data.listData.append(key);

    CData re = query(data);

    return re.listData.first().toString();

}


CData Action::query(CData data)
{
//    qDebug()<<"query : " <<data.iAciton;
//    qDebug()<<"listData : "<<data.listData;
    data.sUser = m_currentUser.Id;

    if(m_bDataFromServer)
        return callServer(data);
    else
        return m_queryObj.queryData(data);
}

CData Action::callServer(CData data)
{
    CData re;

    QByteArray out;

    RPKCORE.network.connectHost("127.0.0.1","6000",data.enCodeJson(),out);

    re.deCodeJson(out);

    return re;
}

