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

    bool getGameItem(QString sSid,QString &data);

    bool getCusFromLineId(QString sLine, QString &data);

    bool getCusHistory(QString sSid, QString &data);


    bool getCusGame(QString sSid, QString &data);

    bool getPayType(QString &data);

    QString listToJson(QVariantList list, QStringList listKey={});

    QString mapToJson(QVariantMap map, QStringList listKey={});


signals:

};

#endif // QUERYAPI_H
