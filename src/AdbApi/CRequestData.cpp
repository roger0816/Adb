#include "CRequestData.h"

CRequestData::CRequestData(QObject *parent)
    : QObject{parent}
{

}

void CRequestData::setServer(QString sIp, QString sPort)
{
    m_sIp = sIp;

    m_sPort = sPort;
}

QString CRequestData::getRate()
{
    CData data;
    data.iAciton=ADP_API::RATE;

    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getAllGames()
{

    CData data;
    data.iAciton=ADP_API::GAME_LIST;

    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);


    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getPayType()
{
    CData data;
    data.iAciton=ADP_API::ADD_VALUE_TYPE;

    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);


    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getGameItem(QString sSid)
{
    CData data;
    data.iAciton=ADP_API::GAME_ITEM;
    data.dData["Sid"]=sSid;
    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getCustomer(QString sLineId)
{
    CData data;
    data.iAciton=ADP_API::CUS_DATA;
    data.dData["Line"]=sLineId;
    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getHistory(QString sSid)
{
    CData data;
    data.iAciton=ADP_API::CUS_HISTORY;
    data.dData["Sid"]=sSid;
    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::getCusGame(QString sSid)
{
    CData data;
    data.iAciton=ADP_API::CUS_GAME;
    data.dData["Sid"]=sSid;
    QByteArray output;

    RPKCORE.network.connectHost(m_sIp,m_sPort,data.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
   // qDebug()<<" sRe : "<<sRe;

    return sRe;
}

QString CRequestData::doOrder(QVariantMap data)
{
    CData d;
    d.iAciton=ADP_API::ORDER;
    d.dData=data;

    QByteArray output;


    RPKCORE.network.connectHost(m_sIp,m_sPort,d.enCodeJson(),output);

    CData re(output);

    QString sRe =QString::fromUtf8(re.dData["data"].toByteArray());
    return sRe;
}



QString CRequestData::listToJson(QVariantList list)
{

    // Convert QVariantList to QJsonArray
    QJsonArray jsonArray;
    for (const QVariant& variant : list) {
        jsonArray.append(QJsonValue::fromVariant(variant));
    }

    // Convert QJsonArray to QJsonDocument
    QJsonDocument jsonDocument(jsonArray);

    // Convert QJsonDocument to JSON string
    QString jsonString = jsonDocument.toJson(QJsonDocument::Compact);

    return jsonString;
}
