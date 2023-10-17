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
    in["DESC"]="Sid";

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
    in["ForApi"] =1;
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
    QStringList inItem=input["Item"].toString().split(",");
    QStringList inCount=input["Count"].toString().split(",");
    QString sCusSid = input["Customer"].toString();
    QString sGameAccount = input["GameAccount"].toString();
    //
    DataRate rate,primeRate;
    QString sMsg;
    DataGameList game;
    CustomerGameInfo gameInfo;
    CustomerData cus;

    if(inItem.length()<1 || inCount.length()<1 ||
            inItem.length()!=inCount.length())
    {
        qDebug()<<"item or count error";


        data["data"]=COMMON.toJsonString("error","item or count error");
        return false;
    }


    if(!checkLogin(sUserId,sPassword))
    {
        qDebug()<<"Login error";


        data["data"]=COMMON.toJsonString("error","login error");
        return false;
    }

    if(!checkGameInfo(sCusSid,sGameAccount,gameInfo))
    {
        qDebug()<<"GameAccount error";

        data["data"]=COMMON.toJsonString("error","GameAccount error");
        return false;
    }


    if(!checkRate(rate,primeRate))
    {
        qDebug()<<"rate error";

        data["data"]=COMMON.toJsonString("error","rate error");
        return false;
    }




    QVariantMap in;
    in["Sid"]=sCusSid;
    QVariantList listData;
    QString sError;
    bool bOk;

    //--------- get customer data

    bOk= m_sql->queryTb(SQL_TABLE::CustomerData(),in,listData,sError);

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

    //--------------get gamelist

    in.clear();
    in["Sid"]= gameInfo.GameSid;
    bOk= m_sql->queryTb(SQL_TABLE::GameList(),in,listData,sError);
    if(!bOk || listData.length()<1)
    {
        data["data"]=notFound(" game");
        return false;
    }

    game.setData(listData.first().toMap());

    //-----------------------


    if(!checkGameItem(inItem,inCount,gameInfo.GameSid,reOrder,sMsg))
    {
        data["data"] = COMMON.toJsonString("error",sMsg);
        return false;
    }


    auto items = [=]()
    {
        QStringList listRe;
        for(int i=0;i<inItem.length();i++)
        {
            QString st = inItem.at(i)+",,"+inCount.at(i);

            listRe.append(st);
        }

        return listRe.join(";;");
    };



    reOrder.CustomerSid=cus.Sid;
    reOrder.CustomerName=cus.Name;
    reOrder.Currency=cus.Currency;

    reOrder.GameSid=gameInfo.GameSid;
    reOrder.GameRate= QString::number(game.GameRate);

    reOrder.ExRateSid=rate.Sid;
    reOrder.PrimeRateSid=primeRate.Sid;

    reOrder.UiRecord="0,0,0,0";
    reOrder.OrderDate=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("yyyyMMdd");
    reOrder.Owner="未分配";
    reOrder.OrderTime=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("hhmmss");
    reOrder.Step="1";
    reOrder.Item = items();

    QStringList listItemInfo;
    listItemInfo.append(game.Name);
    listItemInfo.append(gameInfo.LoginType);
    listItemInfo.append(gameInfo.LoginAccount);
    listItemInfo.append(gameInfo.LoginPassword);
    listItemInfo.append(gameInfo.ServerName);
    listItemInfo.append(gameInfo.Characters);
    reOrder.ItemInfo = listItemInfo;

    checkOrderCost(cus,game,rate,reOrder);

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






bool QueryApi::checkGameItem(QStringList listItem, QStringList listCount,QString sInfoGameSid, OrderData &order,QString &sMsg)
{
    QStringList listReCanType,listCanType;
   // QList<DataGameItem> listGameItem;

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
        sMsg="item length no mapping count lenght";
        return false;
    }

    QString sGameSid="";

    QStringList sItem;

    double iTotalBonus=0.00;
    QStringList listBonus;

   // listGameItem.clear();
    for(int i=0;i<listItem.length();i++)
    {
        QString sCount =listCount.at(i);

        sItem.append(listItem.at(i)+",,"+sCount);

        DataGameItem item;
        bool b=  getItemFromSid(listItem.at(i),item);
        if(!b)
        {
            sMsg = "not found GameItem Sid:"+listItem.at(i);
            return false;
        }


        if(item.GameSid != sInfoGameSid)
        {
            sMsg = "GameAccount 、Item GameSid no mapping";
            return false;
        }

      //  listGameItem.append(item);

        iTotalBonus+= item.Bonus.toDouble();
        listBonus.append(item.Bonus+"*"+sCount);

        QStringList listPayType =getAddValueTypeList(item.AddValueTypeSid);



        if(i==0)
        {
            listReCanType = listPayType;
            sGameSid =item.GameSid;
        }
        else
        {
            if(sGameSid!=item.GameSid)
            {
                sMsg = "Game Sid no mapping :"+listItem.at(i);
                return false;
            }

            QSet<QString> setA=listReCanType.toSet();
            QSet<QString> setB=listPayType.toSet();

            QSet<QString> commonElements = setA.intersect(setB);

            listReCanType=commonElements.toList();

            if(listReCanType.length()<1)
            {
                sMsg = "Items AddValueType no mapping :"+listItem.at(i);
                return false;
            }


        }



    }


    order.Item=sItem.join(";;");
    order.CanSelectPayType=listReCanType.join(";;");
    order.Bouns=QString::number(iTotalBonus);
    order.ListBouns=listBonus;

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

bool QueryApi::checkGameInfo(QString sCusSid, QString sGameInfoSid, CustomerGameInfo &gameAccount)
{
    QVariantMap in;
    QString sError;
    in["CustomerSid"]=sCusSid;
    in["Sid"]=sGameInfoSid;
    QVariantList out;
    bool bOk =m_sql->queryTb(SQL_TABLE::CustomerGameInfo(),in,out,sError);

    if(out.length()>0)
    {
        gameAccount.setData(out.first().toMap());
    }


    return bOk && out.length()>0 ;
}

bool QueryApi::checkRate(DataRate &exRate, DataRate &primeRate)
{
    QVariantMap in;
    QVariantList out;
    QString sError;
    in["DESC"]="Sid";
    in["LIMIT"]="1";

    bool bOk = false;

    bOk = m_sql->queryTb(SQL_TABLE::ExchangeRate(),in,out,sError);

    if(bOk && out.length()>0)
    {
        exRate.setData(out.first().toMap());
    }
    else
    {
        return false;
    }

    out.clear();
    bOk = m_sql->queryTb(SQL_TABLE::PrimeCostRate(),in,out,sError);

    if(bOk && out.length()>0)
    {
        primeRate.setData(out.first().toMap());
    }
    else
    {
        return false;
    }

    return true;
}

bool QueryApi::checkOrderCost(CustomerData cus, DataGameList game, DataRate exRate, OrderData &order)
{
    QString sCurrency=cus.Currency;

    double iRate = 1.0;

    double iGameRate = game.GameRate;

    if(!sCurrency.toUpper().contains("NTD"))
        iRate= exRate.findValue(sCurrency);


    auto into=[=](double d)
    {

        int roundedNumber = static_cast<int>(std::ceil(d));

        return roundedNumber;
    };

    int iTotalNtd=0;
    int iTotalCost=0;
    QStringList listCost;

    foreach(QString s,order.ListBouns)
    {
        QStringList tmp = s.split("*");

        if(tmp.length()<2)
            continue;

        double iBonus=tmp.first().toDouble();
        int iCount = tmp.last().toInt();

        int iNtd=into(iBonus*iGameRate);

        int iCost = into((iBonus*iGameRate)/iRate);

        iTotalNtd+=iNtd*iCount;

        iTotalCost+=iCost*iCount;

        listCost.append(QString::number(iCost));
    }

    order.Money[0] =QString::number(iTotalNtd);
    order.Cost=QString::number(iTotalCost);
    order.ListCost = listCost;

    return true;
}

QString QueryApi::notFound(QString sOtherMsg)
{


    return COMMON.toJsonString("error","not found "+sOtherMsg);
}
