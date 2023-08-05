#ifndef CREQUESTDATA_H
#define CREQUESTDATA_H

#include <QObject>
#include <QDebug>
#include "DEF.h"
#include "VojData.h"
#include "RpkCore.h"
#include <QJsonDocument>
#include <QJsonArray>

class CRequestData : public QObject
{
    Q_OBJECT
public:
    explicit CRequestData(QObject *parent = nullptr);

    void setServer(QString sIp,QString sPort);

       QString getRate();

    QString getAllGames();

    QString getPayType();

    QString getGameItem(QString sSid);


    QString getCustomer(QString sLineId);

    QString getHistory(QString sSid);

    QString getCusGame(QString sSid);



private:
    QString m_sIp="127.0.0.1";
    QString m_sPort="7001";


    QString listToJson(QVariantList list);

signals:

};

#endif // CREQUESTDATA_H
