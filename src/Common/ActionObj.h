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



    virtual bool userCacheData(){return false;}

    bool action(ACT::_KEY act, QVariantList listData, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QVariantMap &out, QString &sError);


    bool action(ACT::_KEY act, QVariantMap data,QVariantList &listOut, QString &sError);

    bool action(ACT::_KEY act, QVariantList listData, QVariantList &listOut, QString &sError);

    CData query(CData data);
protected:
    QueryObj m_queryObj;


    CData callServer(CData data);


    bool m_bDataFromServer = true;

    bool m_bUserMysql = false;

    QString m_ip;

    QString m_port;

    QString m_sCurrentUserId;

    QString m_sCurrentUserName;

private:

    QTimer m_timer;

    QVariantMap m_sDataCache;

    QMap<QString,int > m_dLocalIdx;

    QMap<QString,int > m_dUpdateIdx;

signals:

    void lockLoading(bool b);

public slots:
    void updateIndx(QString sId,QByteArray data,int Error);


};

#endif // ACTIONOBJ_H
