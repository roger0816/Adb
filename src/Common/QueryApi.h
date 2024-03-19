#ifndef QUERYAPI_H
#define QUERYAPI_H

#include <QObject>
#include "DEF.h"
#include "VojData.h"
#include <QDebug>
#include "RpkCore.h"
#include "CSqlClass.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Common.h"
#include <iostream>
#include <cmath>

class QueryApi : public QObject
{
    Q_OBJECT
public:
    explicit QueryApi(QObject *parent = nullptr);

    CData api(CData data);

    CSqlClass *m_sql=nullptr;

private:

    bool getRate(QVariantMap &data);


    bool getGameList(QVariantMap &data);

     bool getGameItemFromGame(QString sSid,QVariantMap &data);


    bool getCusFromLineId(QString sLine, QVariantMap &data);


    bool getCusHistory(QString sSid, QVariantMap &data);


    bool getCusGame(QString sSid, QVariantMap &data);

    bool getPayType(QVariantMap &data);


    bool doOrder(QVariantMap input, QVariantMap &data);


   // bool doOrder(QString sCusSid, QStringList listItem, QStringList listCount, QString &data);



    bool checkGameItem(QStringList listItem, QStringList listCount , QString sInfoGameSid, OrderData &order, QString &sMsg);


    //
    bool checkLogin(QString sUser, QString sPassword);

    bool checkGameInfo(QString sCusSid,QString sGameInfoSid,CustomerGameInfo &gameAccount);

    bool checkRate(DataRate &exRate, DataRate &primeRate);

    bool checkOrderCost(CustomerData cus, DataGameList game, DataRate exRate, OrderData &order);
    QString notFound(QString sOtherMsg="");


signals:

    void signalDoOrder(QVariantMap data);

};

#endif // QUERYAPI_H
