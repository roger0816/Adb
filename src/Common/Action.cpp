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



int Action::checkLogin(QString sUser, QString sPass, QString &sError)
{
    qDebug()<<"check login : "<<sUser<<" , "<<sPass<<" , error : "<<sError;
    CData data;

    data.iAciton = ACT::LOGIN;

    data.listData<<sUser<<sPass;


    CData dRe = query(data);

    bool bOk = dRe.bOk;

    sError = dRe.sMsg;

    int iRe = 0;

    if(bOk)
    {
        m_currentUser.setData(dRe.dData);
        m_sCurrentUserId = m_currentUser.Sid;
        m_sCurrentUserName = m_currentUser.Name;

        iRe =1;
    }
    else
    {
        if(dRe.iState==0)
            iRe = -1;
        else
            iRe = 0;
    }

    return iRe;

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

    costRate("",true);

    primeRate("",true);



    //一進入程式，首先的公告、公告圖、圖片資料做預載
    QString sError;
    QVariantMap in,out;
    in["DESC"]="Sid";
    action(ACT::QUERY_BULLETIN,in,sError);

    in.clear();
    in["Type"]=2;
    action(ACT::QUERY_BULLETIN,in,out,sError);

    in.clear();
    in["Md5"]=out["Content"].toString();
    action(ACT::QUERY_PIC,in,out,sError);
    //pre load make cache data
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

CustomerData Action::getCustomer(QString sSid,bool bQuery)
{
    CustomerData data;

    if(bQuery || m_listCustomer.length()<1)
    {
        QVariantMap in;
        QVariantList listOut;

        QString sError;
        if(action(ACT::QUERY_CUSTOMER,in,listOut,sError))
        {
            foreach(QVariant v,listOut)
                m_listCustomer.append(CustomerData(v.toMap()));
        }

    }


    foreach(CustomerData vData,m_listCustomer)
    {
        if(vData.Sid == sSid)
        {

            return vData;
        }
    }

    return data;

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
            DataFactory tmp(v.toMap());

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

QList<DataGameItem> Action::getGameItemFromGameSid(QString sGameSid, bool bQuery)
{
    QList<DataGameItem> re;

    QList<DataGameItem> list = getGameItem(bQuery);

    foreach(DataGameItem v, list)
    {
        if(v.GameSid==sGameSid)
        {
            re.append(v);
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


    bRe = action(ACT::ADD_CUSTOMER_COST,costData.data(),sError);

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

    bool bToUpdateMoney = false;


    int iStep =qBound(0,order.Step.toInt(),5);

    order.Step=QString::number(iStep);

    if(order.Step=="0")  //報價- 儲存匯率sid
    {
        order.ExRateSid=costRate("",true).Sid;
        order.PrimeRateSid= primeRate("",true).Sid;
    }
    else if(order.Step=="1")  //下單- 計算應收
    {
        setSellMoney(order);

    }
    else if(order.Step=="3") //儲值 - 計算成本
    {
        setPrimeMoney(order);
    }

    else if(order.Step=="4") //回報 - 更新用戶餘額
        bToUpdateMoney=true;

    // QVariantMap out;
    bRe = action(ACT::REPLACE_ORDER,order.data(),sError);

    if(!bRe)
    {
        return bRe;
    }

    if(bRe && bToUpdateMoney)
    {
        QVariantList listOut;
        QVariantMap in;
        in["CustomerSid"]=order.CustomerSid;
        in["DESC"]="Sid";

        double iCurrentTotal=0;

        bRe = action(ACT::QUERY_CUSTOMER_COST,in,listOut,sError);

        if(!bRe)
        {
            return bRe;
        }

        CustomerCost lastCost;
        if(listOut.length()>0)
        {
            lastCost.setData(listOut.first().toMap());

            iCurrentTotal=lastCost.Total.toDouble();
        }
        else
        {
            iCurrentTotal = 0;
        }
        //剛寫入的訂單沒產生sid
        QString sOrderSid =getOrderCustomerLast(order.CustomerSid).Sid;


        CustomerCost data;

        data.UserSid = m_currentUser.Sid;

        data.Rate = order.ExRateSid;

        data.CustomerSid=order.CustomerSid;

        data.IsAddCost=false;

        data.Currency =  getCustomer(data.CustomerSid).Currency;

        data.ChangeValue=QString::number(order.Cost.toDouble()*-1);

        double cost =iCurrentTotal+data.ChangeValue.toDouble();

        data.Total = QString::number(cost);

        data.OrderId = sOrderSid;

        QString sError;
        bool bOk =action(ACT::ADD_CUSTOMER_COST,data.data(),sError);


        if(bOk)
        {
            bRe = true;

            CustomerData customerData = getCustomer(order.CustomerSid);

            customerData.Money=data.Total;

            bOk = action(ACT::EDIT_CUSTOMER,customerData.data(),sError);


        }
        else
        {
            return bRe;
        }

    }
    else
    {
        bRe = true;
    }



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

OrderData Action::getOrderCustomerLast(QString sCustomerSid, bool bRequest)
{
    if(bRequest)
        getOrder(bRequest);

    OrderData re;
    re.Sid="";
    re.Id="";  //is no order

    for(int i=0;i<m_listOrder.length();i++)
    {
        if(m_listOrder.at(i).CustomerSid==sCustomerSid)
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

    if(bRequest || (m_primeRate.length()<1 || m_exRate.length()<1))
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

void Action::setSellMoney(OrderData &order)
{
    auto ntdToInt=[=](double iCost)
    {
        QStringList listTmp = QString::number(iCost).split(".");

        int cost = listTmp.first().toInt();

        if(listTmp.length()>1 && listTmp.last().toInt()>0)
        {
            cost+=1;
        }

        return cost;
    };

    //

    QStringList listMoney;

    DataRate rate=costRate(order.ExRateSid,false);

    //cost

    int idx =rate.listKey().indexOf(getCustomer(order.CustomerSid).Currency);

    if(idx<0)
        return;

    double iCost = order.Cost.toDouble()*rate.listValue().at(idx).toDouble(); //原幣應收
    order.Money[0]= QString::number(ntdToInt(iCost));


}

void Action::setPrimeMoney(OrderData &order)
{

    auto ntdToInt=[=](double iCost)
    {
        QStringList listTmp = QString::number(iCost).split(".");

        int cost = listTmp.first().toInt();

        if(listTmp.length()>1 && listTmp.last().toInt()>0)
        {
            cost+=1;
        }

        return cost;
    };

    qDebug()<<"XXXXXXXXXXXX : "<<order.PrimeRateSid;
    DataRate rate=primeRate(order.PrimeRateSid,true);

    CListPair listPay =getAddValueType();
    int idx = listPay.listFirst().indexOf(order.PayType);

    if(idx<0)
        return;

    CListPair listItem(order.Item);

    double prime=0.00;

    for(int i=0;i<listItem.length();i++)  //訂單裡的  GameItem
    {

        CPair p = listItem.at(i);

        QString sItemSid = p.first;

        int itemCount = p.second.toInt();

        DataGameItem target = getGameItemFromSid(sItemSid,true);   //用game item sid取得完整料結構

        CListPair payType(target.AddValueTypeSid);                // 支付方式sid 與 數量

        QString sValue = payType.findValue(order.PayType);

        double iOneItemPrice = payTypeToNTD(order.PayType,rate)*sValue.toDouble();

        prime =prime+(itemCount*iOneItemPrice);



    }


    order.Money[1] = QString::number(ntdToInt(prime));    //換成台幣的成本

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
    QVariantList rawData;
    QString sError;

    input["Sid"] = payTypeSid;
    action(ACT::QUERY_PAY_TYPE,input,rawData,sError);

    if(rawData.length()<1)
        return 0;



    DataPayType data(rawData.first().toMap());
    qDebug()<<"BBBBBBBBBBBB2: "<<data.Currency;

    qDebug()<<"list "<<rate.listKey()<<" , "<<rate.listValue();

    double r = rate.listData.findValue(data.Currency).toDouble();

    qDebug()<<"BBBBBBBBBBBBB3 : "<<r;


    re=r*data.Value[0].toDouble()*data.Value[1].toDouble()
            *data.Value[2].toDouble()*data.Value[3].toDouble()
            /data.SubValue.first().toDouble();


    return re;
}

bool Action::orderUpdateCount(QString sOrderSid, QString sUserSid,QString sOrderItem)
{
    bool bRe =true;

    CListPair list(sOrderItem);

    if(list.length()<1)
        return false;

    QString sError;

    for(int i=0;i<list.length();i++)
    {
        QVariantMap tmp,tmpOut;
        tmp["GameItemSid"] = list.at(i).first;
        tmp["DESC"] = "Sid";

        action(ACT::QUERY_ITEM_COUNT,tmp,tmpOut,sError);

        DataItemCount itemLast(tmpOut);


        DataItemCount item;

        item.OrderSid=sOrderSid;

        item.GameItemSid = list.at(i).first;

        item.ChangeValue = list.at(i).second.toInt()*-1;

        item.UserSid = sUserSid;

        item.TotalSell= itemLast.TotalSell+list.at(i).second.toInt();

        item.TotalCount = itemLast.TotalCount;


        bool bOk =action(ACT::ADD_ITEM_COUNT,item.data(),sError);

        if(!bOk)
            bRe =false;

    }

    clearCacheData(ACT::QUERY_ITEM_COUNT);

    qDebug()<<"clear cacheData ok";
    return bRe;
}

QPair<int,int> Action::getItemCount(QString sGameItemSid,bool bQuery)
{

    getItemCount(bQuery);

    QPair<int ,int > re={0,0};

    if(m_listItemCount.length()<=0)
        return re;

    foreach(DataItemCount v ,m_listItemCount)
    {
        if(v.GameItemSid == sGameItemSid)
        {
            re.first=v.TotalSell;

            re.second=v.TotalCount;
        }
    }

    return re;
}

QList<DataItemCount> Action::getItemCount(bool bQuery)
{
    QVariantMap tmp;
    QVariantList listTmp;
    QString sError;

    if(bQuery || m_listItemCount.length()<1)
    {
        action(ACT::QUERY_ITEM_COUNT,tmp,listTmp,sError);

        m_listItemCount.clear();

        foreach(QVariant v,listTmp)
        {
            m_listItemCount.append(DataItemCount(v.toMap()));
        }
    }


    return m_listItemCount;
}

QString Action::findGameSid(QString sGameItemSid,bool bQuery)
{
    //GameCount、orderData 沒寫入game sid
    getGameItem(bQuery);


    for(int i=0;i<m_listGameItem.length();i++)
    {
        DataGameItem v =m_listGameItem.at(i);

        if(v.Sid==sGameItemSid)
            return v.GameSid;
    }

    return "";

}

void Action::clearCacheData(int iApi)
{
    QString sApi =QString::number(iApi);

    if(sApi.length()<2)
        return;

    QString sKey = sApi.mid(0,2);

    QStringList listKey = m_dKeepData.keys();

    for(int i=0;i<listKey.length();i++)
    {
        QString sK = listKey.at(i);

        if(sK.length()>2 && sK.mid(0,2) == sKey)
        {
            qDebug()<<"clear cache : "<<sK;
            m_dKeepData[sK]="";

        }

    }

    return ;

}

