#include "QueryApi.h"

QueryApi::QueryApi(QObject *parent)
    : QObject{parent}
{

}

CData QueryApi::api(CData data)
{
    CData re;
    re.iAciton = data.iAciton;
    re.iState =ACT_RECALL;
    re.bOk=false;
    re.dData=QVariantMap();

    QString sData="";

    if(m_sql==nullptr)
    {
        qDebug()<<"api msql is nullptr";
        return re;
    }
    int iAction  = data.iAciton;


    if(iAction == ADP_API::RATE)
    {

        re.bOk = getRate(re.dData);


    }

    else if(iAction == ADP_API::GAME_LIST)
    {

        re.bOk = getGameList(re.dData);



    }

    else if(iAction == ADP_API::GAME_ITEM)
    {

        re.bOk = getGameItemFromGame(data.dData["Sid"].toString(),re.dData);


    }

    else if(iAction == ADP_API::CUS_DATA)
    {

        re.bOk = getCusFromLineId(data.dData["Line"].toString(),re.dData);



    }
    else  if(iAction == ADP_API::CUS_HISTORY)
    {

        re.bOk = getCusHistory(data.dData["Sid"].toString(),re.dData);



    }

    else  if(iAction == ADP_API::CUS_GAME)
    {

        re.bOk = getCusGame(data.dData["Sid"].toString(),re.dData);


    }

    else  if(iAction == ADP_API::ADD_VALUE_TYPE)
    {

        re.bOk = getPayType(re.dData);



    }

    else  if(iAction == ADP_API::ORDER)
    {

        re.bOk = doOrder(data.dData,re.dData);



    }





    return re;
}

bool QueryApi::getRate(QVariantMap &data)
{
    QVariantList listData;
    QString sError;
    QVariantMap in;
    in["LIMIT"]="5";

    bool bOk = m_sql->queryTb(SQL_TABLE::ExchangeRate(),in,listData,sError);



    if(bOk && listData.length()>0)
    {

        data["data"] = COMMON.listToJson(listData);
    }
    else
    {
         data["data"] = notFound();
    }


    return bOk;
}


bool QueryApi::getGameList(QVariantMap &data)
{
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::GameList(),listData,sError);


    if(bOk)
    {
        data["data"] = COMMON.listToJson(listData);
    }
    else
    {

        data["data"] = notFound();
    }



    return bOk;
}

bool QueryApi::getGameItemFromGame(QString sSid, QVariantMap &data)
{

    QVariantMap in;
    in["GameSid"]=sSid;
    in["ASC"]="Sort";
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::GameItem(),in,listData,sError);

    if(bOk && listData.length()>0)
    {
        QStringList listKey;
        listKey<<"Sid"<<"GameSid"<<"Name"<<"Bouns"<<"OrderNTD"<<"Enable"<<"AddValueTypeSid"<<"Bonus"<<"UpdateTime";
        data["data"] = COMMON.listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data["data"] = notFound();
    }


    return bOk;
}





bool QueryApi::getCusFromLineId(QString sLine, QVariantMap &data)
{
    QVariantMap in;
    in["Line"]=sLine;
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::CustomerData(),in,listData,sError);



    if(bOk && listData.length()>0)
    {
        QVariantMap cusData = listData.first().toMap();
        in.clear();
        listData.clear();
        in["Sid"]=cusData["Sid"];
        bOk = m_sql->queryTb(SQL_TABLE::CustomerMoney(),in,listData,sError);

        if(bOk&&listData.length()>0)
        {
            cusData["CurrentMoney"]=listData.first().toMap()["Money"].toString();
        }


        QStringList listKey;
        listKey<<"Sid"<<"Id"<<"Vip"<<"Name"<<"Currency"<<"Num5"<<"Note1"<<"CurrentMoney"<<"UpdateTime";
        data["data"] = COMMON.mapToJson(cusData,QStringList()<<listKey);
    }
    else
    {
        data["data"] = notFound();
    }


    return bOk;
}

bool QueryApi::getCusHistory(QString sSid, QVariantMap &data)
{
    QVariantMap in;
    in["CustomerSid"]=sSid;
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::CustomerCost(),in,listData,sError);

    if(bOk)
    {
        QStringList listKey;
        // listKey<<"Sid"<<"GameSid"<<"Name"<<"Bouns"<<"OrderNTD"<<"Enable"<<"UpdateTime";
        data["data"] = COMMON.listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data["data"] = notFound();
    }


    return bOk;
}

bool QueryApi::getCusGame(QString sSid, QVariantMap &data)
{
    QVariantMap in;
    in["CustomerSid"]=sSid;
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::CustomerGameInfo(),in,listData,sError);

    if(bOk)
    {
        QStringList listKey;
        // listKey<<"Sid"<<"GameSid"<<"Name"<<"Bouns"<<"OrderNTD"<<"Enable"<<"UpdateTime";
        data["data"] = COMMON.listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data["data"] = notFound();
    }


    return bOk;
}

bool QueryApi::getPayType(QVariantMap &data)
{
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::PayType(),listData,sError);

    if(bOk)
    {
        data["data"] = COMMON.listToJson(listData);
    }
    else
    {
        data["data"] = notFound();
    }


    return bOk;
}

bool QueryApi::doOrder(QVariantMap input, QVariantMap &data)
{

    OrderData reOrder;

    qDebug()<<"do order : "<<input;

    QString sUserId=input["UserId"].toString();
    QString sPassword=input["Password"].toString();
    QStringList listItem=input["Item"].toString().split(",");
    QStringList listCount=input["Count"].toString().split(",");
    QString sCusSid = input["Customer"].toString();
    QString sGameAccount = input["GameAccount"].toString();


    if(!checkLogin(sUserId,sPassword))
    {
        qDebug()<<"Login error";


        data["data"]=COMMON.toJsonString("error","login error");
        return false;
    }

    QVariantMap in;
    in["Sid"]=sCusSid;
    QVariantList listData;
    QString sError;
    bool bOk;
    bOk= m_sql->queryTb(SQL_TABLE::CustomerData(),in,listData,sError);

    CustomerData cus;
    if(bOk && listData.length()>0)
    {
        cus.setData(listData.first().toMap());
    }
    else
    {
        qDebug()<<"not found customer";


        data["data"]=notFound("customer");
        return false;
    }

    //------------------
    in.clear();
    in["Sid"]=sGameAccount;

    bOk= m_sql->queryTb(SQL_TABLE::CustomerGameInfo(),in,listData,sError);

    if(!bOk || listData.length()<1)
    {
        data["data"]=notFound("customer game account");
        return false;
    }
    CustomerGameInfo gameInfo(listData.first().toMap());


    //--------------------


    in.clear();
    in["Sid"]= gameInfo.GameSid;
    bOk= m_sql->queryTb(SQL_TABLE::GameList(),in,listData,sError);
    if(!bOk || listData.length()<1)
    {
        data["data"]=notFound(" game");
        return false;
    }

    DataGameList game(listData.first().toMap());


    QString sGameName= game.Name;
    reOrder.GameSid=gameInfo.GameSid;

    reOrder.GameRate= QString::number(game.GameRate);
    //-------------------

    QStringList listItemInfo;
    listItemInfo.append(sGameName);
    listItemInfo.append(gameInfo.LoginType);
    listItemInfo.append(gameInfo.LoginAccount);
    listItemInfo.append(gameInfo.LoginPassword);
    listItemInfo.append(gameInfo.ServerName);
    listItemInfo.append(gameInfo.Characters);
    reOrder.ItemInfo = listItemInfo;



    QString sMsg;
    QStringList listCanType;
    bool bCheck = checkGameItem(listItem,listCount,sMsg,listCanType);

    qDebug()<<"check : "<<bCheck;


    if(!bCheck)
    {
        data["data"] = COMMON.toJsonString("error",sMsg);
        return false;
    }



    auto items = [=]()
    {
        QStringList listRe;
        for(int i=0;i<listItem.length();i++)
        {
            QString st = listItem.at(i)+",,"+listCount.at(i);

            listRe.append(st);
        }

        return listRe.join(";;");
    };



    reOrder.CustomerSid=cus.Sid;
    reOrder.CustomerName=cus.Name;
    reOrder.Currency=cus.Currency;

    reOrder.CanSelectPayType=listCanType.join(";;");

    reOrder.OrderDate=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("yyyyMMdd");
    reOrder.Owner="未分配";
    reOrder.OrderTime=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("hhmmss");
    reOrder.Step="1";
    reOrder.Item = items();

    qDebug()<<"send signalDoOrder";


    emit signalDoOrder(reOrder.data());

    in.clear();
    in["CustomerSid"]=reOrder.CustomerSid;
    in["Owner"] = reOrder.Owner;


   bOk= m_sql->queryTb(SQL_TABLE::OrderData(),in,listData,sError);
    if(!bOk || listData.length()<1)
    {
        data["data"] = COMMON.toJsonString("error","write fail");
        return false;
    }

    OrderData rechek(listData.last().toMap());


    QVariantMap d;
    d["Status"]="1";
    d["OrderId"]=rechek.Id;

    data["data"]=COMMON.mapToJson(d);

    return true;
}

//bool QueryApi::doOrder(QString sCusSid, QStringList listItem, QStringList listCount, QString &data)
//{

//    QVariantMap in;
//    in["Sid"]=sCusSid;
//    QVariantList listData;
//    QString sError;
//    bool bOk;
//    bOk= m_sql->queryTb(SQL_TABLE::CustomerData(),in,listData,sError);

//    CustomerData cus;
//    if(bOk && listData.length()>0)
//    {
//        cus.setData(listData.first().toMap());
//    }
//    else
//    {
//        data="not found customer";
//        return false;
//    }

//    QString sMsg;
//    QStringList listCanType;
//    bool bCheck = checkGameItem(listItem,listCount,sMsg,listCanType);

//    if(!bCheck)
//    {
//        data = sMsg;
//        return false;
//    }


//    auto items = [=]()
//    {
//        QStringList listRe;
//        for(int i=0;i<listItem.length();i++)
//        {
//            QString st = listItem.at(i)+",,"+listCount.at(i);

//            listRe.append(st);
//        }

//        return listRe.join(";;");
//    };


//    OrderData order;
//    order.CustomerSid=cus.Sid;
//    order.CustomerName=cus.Name;
//    order.Currency=cus.Currency;
//    order.GameSid = sMsg; // it is game sid or error msg
//    order.CanSelectPayType=listCanType.join(";;");

//    order.OrderDate=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("yyyyMMdd");

//    order.OrderTime=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("hhmmss");
//    order.Step=2;
//    order.Item = items();

//}






bool QueryApi::checkGameItem(QStringList listItem, QStringList listCount, QString &sGameSid,QStringList &listCanType)
{

    QStringList listReCanType;

    auto getAddValueTypeList=[=](QString  sAddValueType)
    {
        QStringList listRe;

        QStringList listTmp;
        listTmp = sAddValueType.split(";;");

        foreach(QString v,listTmp)
        {
            listRe.append(v.split(",,").first());
        }

        return listRe;
    };

    auto getItemFromSid=[=](QString sSid,DataGameItem &gameItem)
    {

        QVariantMap in;
        in["Sid"]=sSid;
        in["ASC"]="Sort";
        QVariantList listData;
        QString sError;
        bool bOk = m_sql->queryTb(SQL_TABLE::GameItem(),in,listData,sError);


        if(!bOk || listData.length()<1)
        {
            return false;
        }
        else
        {
            DataGameItem item(listData.first().toMap());
            gameItem =item;
            return true;
        }
    };



    if(listItem.length()!=listCount.length())
    {
        sGameSid="item length no mapping count lenght";
        return false;
    }

    QString sTmpGameSid="";

    for(int i=0;i<listItem.length();i++)
    {


        DataGameItem item;
        bool b=  getItemFromSid(listItem.at(i),item);
        if(!b)
        {
            sGameSid = "not found GameItem Sid:"+listItem.at(i);
            return false;
        }

        QStringList listPayType =getAddValueTypeList(item.AddValueTypeSid);



        if(i==0)
        {
            listReCanType = listPayType;
            sTmpGameSid =item.GameSid;
        }
        else
        {
            if(sTmpGameSid!=item.GameSid)
            {
                sGameSid = "Game Sid no mapping :"+listItem.at(i);
                return false;
            }

            QSet<QString> setA=listReCanType.toSet();
            QSet<QString> setB=listPayType.toSet();

            QSet<QString> commonElements = setA.intersect(setB);

            listReCanType=commonElements.toList();

            if(listReCanType.length()<1)
            {
                sGameSid = "Items AddValueType no mapping :"+listItem.at(i);
                return false;
            }


        }



    }

    sGameSid = sTmpGameSid;

    listCanType=listReCanType;
    return true;
}

bool QueryApi::checkLogin(QString sUser, QString sPassword)
{
    QVariantMap in;
    QString sError;
    in["Id"]=sUser;
    in["Password"]=sPassword;
    QVariantList out;
    m_sql->queryTb(SQL_TABLE::UserData(),in,out,sError);

    return out.length()>0;
}

QString QueryApi::notFound(QString sOtherMsg)
{


    return COMMON.toJsonString("error","not found "+sOtherMsg);
}
