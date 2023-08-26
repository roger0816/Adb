#ifndef ACTIONOBJ_H
#define ACTIONOBJ_H

#include <QObject>

//#include "CSqlClass.h"
#include "RpkCore.h"
#include <QElapsedTimer>
#include "DEF.h"
#include "QueryObj.h"
#include "VojData.h"
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>


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

    bool action(int act, QVariantMap data, QVariantMap &out, QString &sError,bool bStrong=false);

    bool action(int act, QVariantMap data,QVariantList &listOut, QString &sError, bool bStrong=false);

    bool action(int act, QVariantList listData, QVariantList &listOut, QString &sError);

    CData query(CData data,bool bStrong=false);

    QueryObj m_queryObj;

    bool m_bIsLock = false;

    QString m_sCurrentUserId;

    QString m_sCurrentUserName;


    QString m_sCurrentSession="";
protected:
    CData callServer(CData data,bool bStrong=false);


    bool isQueryApi(int iApi);

    bool isNeedFromServer(int iApi, const QVariantMap conditions);

    bool m_bDataFromServer = true;

    QString m_ip;

    QString m_port;



 protected:

    QTimer m_timer;

    int m_iWaitHeart=0;

    QMap<QString,QString > m_dLocalTrigger;

    QMap<QString,QString > m_dUpdateTrigger;

    QVariantMap m_dKeepData;

   // void writeTrigger(QString sTrigger,bool isFromHeartBeat);

    QString apiCacheKey(QString sApi, QVariantMap conditions);

    void clearCache(int iApi);

    virtual QVariantMap syncData(){return QVariantMap();}


signals:

    void lockLoading(bool b);

    void updateTrigger(QString sApiGroup);

    void sessionError();

public slots:
    void serverTrigger(QString sId, QByteArray data, int);

    void decodeTrigger(QString sData);

private slots:

    void checklock(bool b);

private :
    QEventLoop m_lockLoop;


    QString m_sUpdateSid;





};

#endif // ACTIONOBJ_H
