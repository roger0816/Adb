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



#define DATA UpdateData::Instance()

enum {
    ORDER_DATA=1,
    CUSTOMER_DATA,
    USER_DATA,
    GAME_LIST,
    GAME_ITEM,
    BULLETIN_DATA,
    EXCHANGE_RATE,
    PRIMECOST_RATE
};



class DataProvider : public QObject
{
    Q_OBJECT
public:
    explicit DataProvider(int iTag, QObject *parent = nullptr);
    QMap< int ,QVariant>  m_oriData;
    QVariantList m_list;
    QString m_lastUpdate="0";

    bool setData(QVariantList data);
    virtual void changeData(){}
    bool m_bOnSync=false;

    int m_iTag;
signals:

};

class OrderDataProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit OrderDataProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}
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


class CustomerDataProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit CustomerDataProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            CustomerData d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<CustomerData> m_listData;

};

class UserDataProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit UserDataProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            UserData d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<UserData> m_listData;

};

class GameListProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit GameListProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataGameList d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataGameList> m_listData;

};

class GameItemProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit GameItemProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataGameItem d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataGameItem> m_listData;

};

class ExchangeRateProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit ExchangeRateProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataRate d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataRate> m_listData;

};

class PrimeCostRateProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit PrimeCostRateProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataRate d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataRate> m_listData;

};



class BulletinDataProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit BulletinDataProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}
    void changeData() override
    {
        m_listData=m_list;
    }
    QVariantList m_listData;
};




class UpdateData : public QObject
{
    Q_OBJECT
public:
    explicit UpdateData(QObject *parent = nullptr);

    static UpdateData& Instance();

    int connectIp(QString sIp,QString sPort);
    void setTarget(QStringList list);
    void setRun(bool b);

    void runUpdate();

    QList<OrderData> getOrder();

    OrderData getOrder(QString sSid);


    QList<CustomerData> getCustomerList();
    CustomerData getCustomer(QString sCusId);

    QList<UserData> getUserList();
    UserData getUser(QString sSid);

    QList<DataGameList> getGameList();
    DataGameList getGameList(QString sSid);
    QString getGameName(QString sId);
    QString getGameId(QString sName);


    QList<DataGameItem> getGameItem();
    QList<DataGameItem> getGameItemFromGameSid(QString sGameSid);

    QList<DataRate> costRateList();

    DataRate costRate(QString sSid="");


    QVariantList getBulletin();

    QMap< QString ,DataProvider* > m_data;

public slots:
    void slotRead(QString sConnect, QString sId,QByteArray data,int Error);


private slots:

    void slotTimer();
private:
    static UpdateData *m_pInstance;

    QTimer m_timer;
    bool m_bRun=false;

    bool isOnSync();

    QStringList m_listTarget;
    int m_iWaitRecvSec=0;


    QString sHhmm="";
signals:
    void updateNotify(int iType, QStringList listSid );


};

#endif // UPDATEDATA_H
