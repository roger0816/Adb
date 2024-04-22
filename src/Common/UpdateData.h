#ifndef UPDATEDATA_H
#define UPDATEDATA_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include "DEF.h"
#include "VojData.h"
#include "RpkCore.h"
#include <QTimer>

class DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(QObject *parent = nullptr);
    QMap< int ,QVariant>  m_oriData;
    QVariantList m_list;
    QString m_lastUpdate="20230102030405";

    QString setData(QVariantList data);
    virtual void changeData(){}
    bool m_bOnSync=false;
signals:

};

class OrderDataProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit OrderDataProvider(QObject *parent = nullptr):DataProvider(parent){}
    void changeData()override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            OrderData d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<OrderData> m_listData;
};


class UpdateData : public QObject
{
    Q_OBJECT
public:
    explicit UpdateData(QObject *parent = nullptr);
    int connectIp(QString sIp,QString sPort);
    void setRun(bool b);

    void runUpdate();

    struct queryDateTime
    {
        queryDateTime()
        {
            Order=initDateTime(-33);
            Customer=initDateTime(-33);
        }
        QString Order;
        QString Customer;

        QString initDateTime(int iDay)
        {
            return QDateTime::currentDateTimeUtc().addMSecs(60*60*8).addDays(iDay).toString("yyyyMMddhhmmss");
        }
    };

    queryDateTime queryDateTime;

    OrderDataProvider order;

public slots:
    void slotRead(QString sConnect, QString sId,QByteArray data,int Error);


private slots:

    void slotTimer();
private:
    QTimer m_timer;
    bool m_bRun=false;
    void sendData(QByteArray arrInput);


};

#endif // UPDATEDATA_H
