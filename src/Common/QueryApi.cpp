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

        re.bOk = getGameItem(data.dData["Sid"].toString(),sData);

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

bool QueryApi::getGameItem(QString sSid, QString &data)
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
        listKey<<"Sid"<<"GameSid"<<"Name"<<"Bouns"<<"OrderNTD"<<"Enable"<<"AddValueTypeSid"<<"UpdateTime";
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
