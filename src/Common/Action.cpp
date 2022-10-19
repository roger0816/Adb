#include "Action.h"

Action::Action(QObject *parent)
    : ActionObj{parent}
{


}

 Action::~Action()
{
    qDebug()<<"un Action";
}


void Action::setServer(bool b, QString sIp, QString sPort)
{
    //b = false  is no use server
    qDebug()<<"sIp: "<<sIp<<" ,port :  "<<sPort;
    m_ip = sIp;

    m_port = sPort;

    m_bDataFromServer = b;

}



bool Action::checkLogin(QString sUser, QString sPass, QString &sError)
{
qDebug()<<"check login : "<<sUser<<" , "<<sPass<<" , error : "<<sError;
    CData data;

    data.iAciton = ACT::LOGIN;

    data.listData<<sUser<<sPass;


    CData dRe = query(data);

    bool bOk = dRe.bOk;
    qDebug()<<"re ok : "<<dRe.bOk;
    sError = dRe.sMsg;

    if(bOk)
    {
        m_currentUser.setData(dRe.dData);
        m_sCurrentUserId = m_currentUser.Sid;
        m_sCurrentUserName = m_currentUser.Name;
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


    qDebug()<<"query user "<<sId;

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

    qDebug()<<"setKeyValue : "<<key<<" , value :"<<value;
    if(inLocal)
    {

        bRe = RPKCORE.database.insertKeyPair(key,value,0);

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

        sRe = RPKCORE.database.getKeyPair(key,0);

        return sRe;
    }

    CData data;

    data.iAciton=ACT::GET_VALUE;

    data.listData.append(key);

    CData re = query(data);

    return re.listData.first().toString();

}

bool Action::addGroupData(int iType, GroupData data, QString &sError)
{
    QVariantMap d = data.data();
    d["Type"]= QString::number(iType);

    bool b = action(ACT::ADD_GROUP, d, sError);

    return b;
}

bool Action::delGroupData(int iType, QString sSid,QString &sError)
{
    QVariantMap d ;
    d["Type"]= QString::number(iType);
    d["Sid"] =sSid;

    bool b = action(ACT::DEL_GROUP, d, sError);

    return b;
}

bool Action::editGroupData(int iType, GroupData data,QString &sError)
{
    QVariantMap d = data.data();


    bool b = action(ACT::EDIT_GROUP, d, sError);

    return b;
}

QList<GroupData> Action::getGroupData(int iType,QString &sError)
{
    QVariantList in,out;

    bool b = action(ACT::QUERY_GROUP, in,out, sError);

    QList<GroupData> list;

    for(int i=0;i<in.length();i++)
    {
        GroupData v(list.at(i));


    }


    return list;
}






void Action::reQuerty()
{
    getUser(true);

    getGameList(true);

    getCustomerClass(true);

  //  rate("",true);
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

    return m_listGameItem;
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

void Action::updateGameItemPrice(QString sGameSid, double iGameRate)
{


    QList<DataGameItem> list = getGameItem(sGameSid,true);

    QVariantList listSend;

    for(int i=0;i<list.length();i++)
    {


        DataGameItem v = list.at(i);
        v.NTD = QString::number(v.Bonus.toDouble()*iGameRate);


        listSend.append(v.data());
    }


    QString sError;

    qDebug()<<"lll0"<<listSend.length();

    action(ACT::EDIT_GAME_ITEM,listSend,sError);

}

DataGameItem Action::getGameItemFromSid(QString sSid, bool bQuery)
{
    DataGameItem re;

    QList<DataGameItem> list = getGameItem(bQuery);

    foreach(DataGameItem v, list)
    {
        if(v.Sid==sSid)
        {
           re =v;

           break;
        }
    }

    return re;
}

QString Action::getGameName(QString sId)
{
    QString sRe="";

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sId==m_listGameList.at(i).Sid)
        {

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


//DataExchange::Rate Action::rate(QString sSid, bool bRequest)
//{
//    /**
//    if(!bRequest)
//        return m_rate;
//    QVariantList input,listRate;

//    QString sError;

//    bool bRateOk =true;

//    bRateOk= action(ACT::READ_EXCHANGE,input,listRate,sError);

//    if(bRateOk)
//    {
//        DataExchange tmp(listRate);

//        m_rate = tmp.rate(sSid);

//    }
//    */
//    DataExchange::Rate re;

//    if(bRequest)
//    {
//        primeRate("",true,true);
//    }
//    if(m_exRate.length()>0)
//    {
//        re.fromPrime(m_exRate.last().toMap());
//    }

//    return re;
//}

bool Action::addRate(QVariantMap data,QString &sError,bool bExchangeType)
{

    QVariantList out;

    bool bRe=false;

    if(!bExchangeType)
        bRe=action(ACT::ADD_PRIMERATE,data,out,sError);
    else
        bRe=action(ACT::ADD_EXCHANGE,data,out,sError);

    return bRe;

}

QList<DataRate> Action::listRate(QString sSid, bool bRequest,bool bExchangeType)
{
    QList<DataRate> re  ;

    if(bRequest || (m_primeRate.length()<1 || m_primeRate.length()<1))
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

      qDebug()<<"m_exRate len : "<<m_exRate.length();
    qDebug()<<"target rate len : "<<target.length();

    if(sSid=="")
    {


        for(int i=0;i<target.length();i++)
        {
            DataRate data;

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
                DataRate data;

                data.setData(target.at(i).toMap());

                re.append(data);
            }
        }
    }

    if(re.length()<1)
        re.append(DataRate());


    return re;
}

QList<DataUserBonus> Action::listBouns(QString sUserSid)
{
    QList<DataUserBonus> listRe;

    QVariantList out;

    QVariantMap in;

    QString sError;

    in["UserSid"] = sUserSid;

    action(ACT::QUERY_BOUNS,in,out,sError);

    for(int i=0;i<out.length();i++)
    {
        DataUserBonus data;

        data.setData(out.at(i).toMap());

        listRe.append(data);
    }

    if(listRe.length()<1)
        listRe.append(DataUserBonus());

    return listRe;
}


CListPair Action::getAddValueType(bool bRequest)
{
    if(!bRequest && m_listAddValueType.length()>0)
        return m_listAddValueType;

    CListPair listRe;

    QVariantMap in;
    QVariantList list;
    QString sError;
    action(ACT::QUERY_PAY_TYPE,in,list,sError);

    for(int i=0;i<list.length();i++)
    {
        QVariantMap data = list.at(i).toMap();
        QPair<QString,QString> v;
        v.first=data["Sid"].toString();
        v.second=data["Name"].toString();
        listRe.append(v);
    }

    m_listAddValueType = listRe;

    return listRe;
}

QString Action::getAddValueName(QString sSid)
{
    if(m_listAddValueType.length()<1)
        getAddValueType(true);

    QString sRe="";

    foreach(CPair v, m_listAddValueType)
    {
        if(v.first==sSid)
            sRe = v.second;
    }

    return sRe;
}

double Action::payTypeToNTD(QString payTypeSid, DataRate rate)
{
    double re=1.00;

    QVariantMap input;
    QVariantList in,rawData;
    QString sError;

    input["Sid"] = payTypeSid;
    action(ACT::QUERY_PAY_TYPE,input,rawData,sError);

    if(rawData.length()<1)
        return 0;

    QStringList listValue = rawData.first().toMap()["Value"].toString().split(";");


    while(listValue.length()<9)
        listValue.push_front("1");

    double r = rate.listData.findValue(listValue.last()).toDouble();

    re=1.00*r;

    for(int i=0;i<7;i++)
    {
        double d = listValue.at(i).toDouble();

        if(i==2)
            re/=d;
        else
            re*=d;

    }


    return re;
}

