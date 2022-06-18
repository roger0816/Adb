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

    data.dData["Id"]=sUser;

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


void Action::reQuerty()
{
    getUser(true);

    getGameList(true);

    getCustomerClass(true);

    rate("",true);
}

QList<UserData> Action::getUser(bool bQuery)
{
    if(bQuery)
        m_listUser = queryUser();

    return m_listUser;
}

UserData Action::getUser(QString sSid,bool bQuery)
{
    UserData re;
    getUser(bQuery);
    for(int i=0;i<m_listUser.length();i++)
    {
        if(sSid==m_listUser.at(i).Sid)
            re =m_listUser.at(i);
    }

    return re;
}

QList<DataCustomerClass> Action::getCustomerClass(bool bQuery)
{
    if(bQuery)
    {
        m_listCustomerClass.clear();

        QVariantList in,listClass;

        QString sError;

        action(ACT::QUERY_CUSTOM_CLASS,in,listClass,sError);

        foreach(QVariant v,listClass)
        {
            DataCustomerClass tmp;

            tmp.setData(v.toMap());

            m_listCustomerClass.append(tmp);
        }

    }
    return m_listCustomerClass;
}

DataCustomerClass Action::getCustomerClass(QString sSid, bool bQuery)
{
    getCustomerClass(bQuery);

    DataCustomerClass re;

    for(int i=0;i<m_listCustomerClass.length();i++)
    {
        if(sSid == m_listCustomerClass.at(i).Sid)
        {
            re = m_listCustomerClass.at(i);

            break;
        }
    }

    return re;
}

QList<DataFactory> Action::getFactoryClass(QString sSid, bool bQuery)
{
    if(bQuery)
    {
        m_listFactoryClass.clear();

        QVariantList in,list;

        QString sError;

        action(ACT::QUERY_FACTORY_CLASS,in,list,sError);

        foreach(QVariant v,list)
        {
            DataFactory tmp;

            tmp.setData(v.toMap());

            m_listFactoryClass.append(tmp);
        }

    }

    QList<DataFactory> listRe;

    if(sSid!="")
    {
        for(int i=0;i<m_listFactoryClass.length();i++)
        {
            if(m_listFactoryClass.at(i).Sid==sSid)
            {
                listRe.append(m_listFactoryClass.at(i));
            }
        }

    }
    else
    {
        listRe = m_listFactoryClass;
    }

    return listRe;
}




QList<DataGameList> Action::getGameList(bool bQuery)
{
    if(bQuery)
    {
        m_listGameList.clear();

        QVariantList in,list;

        QString sError;

        action(ACT::QUERY_GAME_LIST,in,list,sError);

        foreach(QVariant v,list)
        {
            DataGameList tmp;

            tmp.setData(v.toMap());

            m_listGameList.append(tmp);
        }

    }
    return m_listGameList;
}

DataGameList Action::getGameList(QString sSid, bool bQuery)
{
    getGameList(bQuery);

    DataGameList re;

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sSid == m_listGameList.at(i).Sid)
        {
            re = m_listGameList.at(i);

            break;
        }
    }

    return re;
}

QList<DataGameItem> Action::getGameItem(bool bQuery)
{
    if(!bQuery)
        return m_listGameItem;

    QList<DataGameItem> listRe;

    QVariantMap d;

    //    d["GameSid"] = sGameSid;

    QVariantList listOut;

    QString sError;

    action(ACT::QUERY_GAME_ITEM,d,listOut,sError);

    m_listGameItem.clear();

    for(int i=0;i<listOut.length();i++)
    {
        DataGameItem item(listOut.at(i).toMap());

        m_listGameItem.append(item);
    }

    return listRe;
}

QList<DataGameItem> Action::getGameItem(QString sGameSid, bool bQuery)
{
    getGameItem(bQuery);

    QList<DataGameItem> listRe;


    for(int i=0;i<m_listGameItem.length();i++)
    {
        DataGameItem data = m_listGameItem.at(i);
        if(data.GameSid == sGameSid)
        {
            listRe.append(data);
        }
    }

    return listRe;
}

QString Action::getGameName(QString sId)
{
    QString sRe="";
    qDebug()<<"BB0 : "<<m_listGameList.length();
    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sId==m_listGameList.at(i).Sid)
        {
              qDebug()<<"BB1 : "<<sId<<" ,BB2 :"<<m_listGameList.at(i).Sid;
            sRe =m_listGameList.at(i).Name;

            break;
        }
    }

    return sRe;

}

QString Action::getGameId(QString sName)
{
    QString sRe="";

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sName==m_listGameList.at(i).Name)
        {
            sRe =m_listGameList.at(i).Sid;

            break;
        }
    }

    return sRe;
}

QList<CustomerCost> Action::getCustomerCost(QString sCustomerSid, bool bQuery)
{

    if(bQuery)
    {
        QVariantMap in;

        QVariantList listOut;

        in["CustomerSid"] = sCustomerSid;

        QString sError;

        action(ACT::QUERY_CUSTOMER_COST,in,listOut,sError);

        m_listCustomerCost.clear();

        for(int i=0;i<listOut.length();i++)
        {
            CustomerCost d(listOut.at(i).toMap());
            m_listCustomerCost.append(d);
        }
    }
    return m_listCustomerCost;
}

bool Action::setCustomerCost(CustomerCost costData,QString &sError)
{
    bool bRe = false;

    QVariantMap out;

    bRe = action(ACT::ADD_CUSTOMER_COST,costData.data(),out,sError);

    return bRe;
}

QList<OrderData> Action::getOrder(bool bRequest)
{
    if(bRequest)
    {
        QVariantList in,out;

        QString sError;
        action(ACT::QUERY_ORDER,in,out,sError);

        m_listOrder.clear();

        for(int i=0;i<out.length();i++)
        {
            OrderData data(out.at(i).toMap());

            m_listOrder.append(data);
        }

    }

    return m_listOrder;
}

bool Action::replaceOrder(OrderData order, QString &sError)
{
    bool bRe = false;
    QVariantMap out;
    bRe = action(ACT::REPLACE_ORDER,order.data(),out,sError);
    return bRe;

}

OrderData Action::getOrder(QString sSid, bool bRequest)
{
    if(bRequest)
        getOrder(bRequest);

    OrderData re;

    for(int i=0;i<m_listOrder.length();i++)
    {
        if(m_listOrder.at(i).Sid==sSid)
            re = m_listOrder.at(i);
    }

    return re;
}

OrderData Action::getOrderByCustomerSid(QString sSid, bool bRequest)
{
    if(bRequest)
        getOrder(bRequest);

    OrderData re;

    for(int i=0;i<m_listOrder.length();i++)
    {
        if(m_listOrder.at(i).CustomerSid==sSid)
        {

            re = m_listOrder.at(i);


        }
    }

    return re;
}

QVariant Action::trKey(QVariantList list, QVariantMap info, QString sTargetKey)
{
    QVariant sRe="";
    for(int i=0;list.length();i++)
    {
        QVariantMap d = list.at(i).toMap();
        if(d[info.firstKey()] == info.first())
        {
            sRe = d[sTargetKey];
        }
    }

    return sRe;
}

QStringList Action::mapToList(QVariantList list, QString sKey)
{
    QStringList listRe;

    foreach(QVariant v ,list)
    {
        listRe.append(v.toMap()[sKey].toString());


    }

    return listRe;
}

int Action::mapping(QVariantList list, QString sKey, QString var)
{
    int iIdx=-1;

    for(int i=0;i<list.length();i++)
    {
        if(list.at(i).toMap()[sKey] == var)
        {
            iIdx=i;

            break;
        }
    }


    return iIdx;
}


DataExchange::Rate Action::rate(QString sSid, bool bRequest)
{
    /*
    if(!bRequest)
        return m_rate;
    QVariantList input,listRate;

    QString sError;

    bool bRateOk =true;

    bRateOk= action(ACT::READ_EXCHANGE,input,listRate,sError);

    if(bRateOk)
    {
        DataExchange tmp(listRate);

        m_rate = tmp.rate(sSid);

    }
    */
    DataExchange::Rate re;

    if(bRequest)
    {
        primeRate("",true,true);
    }
    if(m_exRate.length()>0)
    {
        re.fromPrime(m_exRate.last().toMap());
    }

    return re;
}

bool Action::addPrimeRate(QVariantMap data,QString &sError,bool bExchangeType)
{

    QVariantList out;

    bool bRe=false;

    if(!bExchangeType)
        bRe=action(ACT::ADD_PRIMERATE,data,out,sError);
    else
        bRe=action(ACT::ADD_EXCHANGE,data,out,sError);

    return bRe;

}

QList<PrimeRate> Action::primeRate(QString sSid, bool bRequest,bool bExchangeType)
{
    QList<PrimeRate> re  ;

    if(bRequest)
    {
        QVariantList out;

        QVariantMap in;

        QString sError;


        if(!bExchangeType)
        {
            action(ACT::QUERY_PRIMERATE,in,out,sError);

            m_primeRate = out;
        }
        else
        {
            action(ACT::QUERY_EXCHANGE,in,out,sError);

            m_exRate=out;
        }

    }

    QVariantList target = m_primeRate;

    if(bExchangeType)
        target=m_exRate;

    if(sSid=="")
    {


        for(int i=0;i<target.length();i++)
        {
            PrimeRate data;

            data.setData(target.at(i).toMap());

            re.append(data);
        }

    }
    else
    {
        for(int i=0;i<target.length();i++)
        {
            if(sSid==target.at(i).toMap()["Sid"])
            {
                PrimeRate data;

                data.setData(target.at(i).toMap());

                re.append(data);
            }
        }
    }

    return re;
}
