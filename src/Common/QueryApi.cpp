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

        re.bOk = getRate(sData);

        re.dData["data"]=sData.toUtf8();

    }

    else if(iAction == ADP_API::GAME_LIST)
    {

        re.bOk = getGameList(sData);

        re.dData["data"]=sData.toUtf8();

    }

    else if(iAction == ADP_API::GAME_ITEM)
    {

        re.bOk = getGameItemFromGame(data.dData["Sid"].toString(),sData);

        re.dData["data"]=sData.toUtf8();

    }

    else if(iAction == ADP_API::CUS_DATA)
    {

        re.bOk = getCusFromLineId(data.dData["Line"].toString(),sData);

        re.dData["data"]=sData.toUtf8();

    }
    else  if(iAction == ADP_API::CUS_HISTORY)
    {

        re.bOk = getCusHistory(data.dData["Sid"].toString(),sData);

        re.dData["data"]=sData.toUtf8();

    }

    else  if(iAction == ADP_API::CUS_GAME)
    {

        re.bOk = getCusGame(data.dData["Sid"].toString(),sData);

        re.dData["data"]=sData.toUtf8();

    }

    else  if(iAction == ADP_API::ADD_VALUE_TYPE)
    {

        re.bOk = getPayType(sData);

        re.dData["data"]=sData.toUtf8();

    }

    else  if(iAction == ADP_API::ORDER)
    {

        re.bOk = doOrder(data.dData,sData);

        re.dData["data"]=sData.toUtf8();

    }





    return re;
}

bool QueryApi::getRate(QString &data)
{
    QVariantList listData;
    QString sError;
    QVariantMap in;
    in["LIMIT"]="5";

    bool bOk = m_sql->queryTb(SQL_TABLE::ExchangeRate(),in,listData,sError);



    if(bOk && listData.length()>0)
    {

        data = listToJson(listData);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getGameList(QString &data)
{

    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::GameList(),listData,sError);

    if(bOk)
    {
        data = listToJson(listData);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getGameItemFromGame(QString sSid, QString &data)
{
    QVariantMap in;
    in["GameSid"]=sSid;
    in["ASC"]="Sort";
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::GameItem(),in,listData,sError);

    if(bOk)
    {
        QStringList listKey;
        listKey<<"Sid"<<"GameSid"<<"Name"<<"Bouns"<<"OrderNTD"<<"Enable"<<"AddValueTypeSid"<<"Bonus"<<"UpdateTime";
        data = listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getCusFromLineId(QString sLine, QString &data)
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
        data = mapToJson(cusData,QStringList()<<listKey);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getCusHistory(QString sSid, QString &data)
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
        data = listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getCusGame(QString sSid, QString &data)
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
        data = listToJson(listData,QStringList()<<listKey);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::getPayType(QString &data)
{
    QVariantList listData;
    QString sError;
    bool bOk = m_sql->queryTb(SQL_TABLE::PayType(),listData,sError);

    if(bOk)
    {
        data = listToJson(listData);
    }
    else
    {
        data = sError;
    }


    return bOk;
}

bool QueryApi::doOrder(QVariantMap input, QString &data)
{

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

        data="Login error";
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
        qDebug()<<"no found customer";

        data="no found customer";
        return false;
    }


    QString sMsg;
    QStringList listCanType;
    bool bCheck = checkGameItem(listItem,listCount,sMsg,listCanType);

    qDebug()<<"check : "<<bCheck;


    if(!bCheck)
    {
        data = sMsg;
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


    OrderData order;
    order.CustomerSid=cus.Sid;
    order.CustomerName=cus.Name;
    order.Currency=cus.Currency;
    order.GameSid = sMsg; // it is game sid or error msg
    order.CanSelectPayType=listCanType.join(";;");

    order.OrderDate=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("yyyyMMdd");

    order.OrderTime=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("hhmmss");
    order.Step="0";
    order.Item = items();

    qDebug()<<"send signalDoOrder";


    emit signalDoOrder(order.data());



    data="send ok";
    return true;
}

bool QueryApi::doOrder(QString sCusSid, QStringList listItem, QStringList listCount, QString &data)
{

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
        data="no found customer";
        return false;
    }

    QString sMsg;
    QStringList listCanType;
    bool bCheck = checkGameItem(listItem,listCount,sMsg,listCanType);

    if(!bCheck)
    {
        data = sMsg;
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


    OrderData order;
    order.CustomerSid=cus.Sid;
    order.CustomerName=cus.Name;
    order.Currency=cus.Currency;
    order.GameSid = sMsg; // it is game sid or error msg
    order.CanSelectPayType=listCanType.join(";;");

    order.OrderDate=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("yyyyMMdd");

    order.OrderTime=QDateTime::currentDateTimeUtc().addSecs(8 * 3600).toString("hhmmss");
    order.Step=2;
    order.Item = items();

}



QString QueryApi::listToJson(QVariantList list,QStringList listKey)
{

    // Convert QVariantList to QJsonArray
    QJsonArray jsonArray;
    for (const QVariant& variant : list)
    {

        QVariant target;

        if(listKey.length()>0)
        {
            QVariantMap d=variant.toMap();

            QStringList listTmp = d.keys();

            QVariantMap dR;

            foreach(QString v,listTmp)
            {
                if(listKey.contains(v))
                    dR[v]=d[v];
            }

            target = dR;

        }
        else
        {
            target = variant;
        }

        jsonArray.append(QJsonValue::fromVariant(target));
    }

    // Convert QJsonArray to QJsonDocument
    QJsonDocument jsonDocument(jsonArray);

    // Convert QJsonDocument to JSON string
    // QString jsonString = jsonDocument.toJson(QJsonDocument::Compact);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    return jsonString;
}

QVariantList jsonToList(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        // 若轉換失敗或不是 JSON Array，返回空的 QVariantList
        return QVariantList();
    }

    QJsonArray jsonArray = jsonDoc.array();
    QVariantList list;
    for (const QJsonValue& jsonValue : jsonArray) {
        list.append(jsonValue.toVariant());
    }

    return list;
}

QString QueryApi::mapToJson(QVariantMap map, QStringList listKey)
{

    QVariantMap variantMap;

    if(listKey.length()<1)
    {
        variantMap = map;
    }
    else
    {
        QStringList listTmp = map.keys();
        foreach(QString v,listTmp)
        {
            if(listKey.contains(v))
            {
                variantMap[v]=map[v];
            }
        }

    }


    // 將 QVariantMap 轉換為 QJsonObject
    QJsonObject jsonObject = QJsonObject::fromVariantMap(variantMap);

    // 使用 QJsonDocument 來創建 JSON 格式的 QByteArray
    QJsonDocument jsonDoc(jsonObject);

    // 使用 toJson 函數將 QJsonDocument 轉換為格式化的 JSON 字串
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // 將 QByteArray 轉換為 QString
    QString jsonString(jsonData);

    return jsonString;
}

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


        if(bOk || listData.length()<1)
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
            sGameSid = "no found GameItem Sid:"+listItem.at(i);
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
    qDebug()<<"DDD "<<out;
    return out.length()>0;
}
