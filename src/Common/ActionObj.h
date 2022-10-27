#ifndef ACTIONOBJ_H
#define ACTIONOBJ_H

#include <QObject>

//#include "CSqlClass.h"
#include "RpkCore.h"
#include "DEF.h"
#include "QueryObj.h"
#include "VojData.h"
#include <QTimer>




class ActionObj : public QObject
{
    Q_OBJECT
public:
    explicit ActionObj(QObject *parent = nullptr);

    ~ActionObj();

    void setStartSyanc(bool b);

    virtual bool userCacheData(){return false;}

    bool action(int act, QString sKey, QVariant sValue, QVariantMap &output);

    bool action(int act, QVariantMap input, QVariantList &output);

    bool action(int act, QVariantList listData, QString &sError);

    bool action(int act, QVariantMap data, QString &sError);

    bool action(int act, QVariantMap data, QVariantMap &out, QString &sError);

    bool action(int act, QVariantMap data,QVariantList &listOut, QString &sError);

    bool action(int act, QVariantList listData, QVariantList &listOut, QString &sError);

    CData query(CData data);

    QueryObj m_queryObj;

protected:
    CData callServer(CData data);

    bool isQueryApi(int iApi);

    bool isNeedFromServer(int iApi, const QVariantMap conditions);

    bool m_bDataFromServer = true;

    QString m_ip;

    QString m_port;

    QString m_sCurrentUserId;

    QString m_sCurrentUserName;

private:

    QTimer m_timer;

    QMap<QString,QString > m_dLocalTrigger;

    QMap<QString,QString > m_dUpdateTrigger;

    QVariantMap m_dKeepData;

   // void writeTrigger(QString sTrigger,bool isFromHeartBeat);

    QString apiCacheKey(QString sApi, QVariantMap conditions);

signals:

    void lockLoading(bool b);

    void updateTrigger(QString sApiGroup);

public slots:
    void serverTrigger(QString sId, QByteArray data, int);


};

#endif // ACTIONOBJ_H
