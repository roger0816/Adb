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

class QueryApi : public QObject
{
    Q_OBJECT
public:
    explicit QueryApi(QObject *parent = nullptr);

    CData api(CData data);

    CSqlClass *m_sql=nullptr;

private:

    bool getRate(QString &data);

    bool getGameList(QString &data);

    bool getGameItemFromGame(QString sSid,QString &data);

    bool getCusFromLineId(QString sLine, QString &data);

    bool getCusHistory(QString sSid, QString &data);


    bool getCusGame(QString sSid, QString &data);

    bool getPayType(QString &data);


    bool doOrder(QVariantMap input, QString &data);


    bool doOrder(QString sCusSid, QStringList listItem, QStringList listCount, QString &data);

    QString listToJson(QVariantList list, QStringList listKey={});

    QVariantList jsonToList(const QString& jsonString);

    QString mapToJson(QVariantMap map, QStringList listKey={});


    bool checkGameItem(QStringList listItem, QStringList listCount , QString &sGameSid,QStringList &listCanType);


    //
    bool checkLogin(QString sUser, QString sPassword);


signals:

    void signalDoOrder(QVariantMap data);

};

#endif // QUERYAPI_H
