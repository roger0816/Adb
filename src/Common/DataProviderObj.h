#ifndef DATAPROVIDEROBJ_H
#define DATAPROVIDEROBJ_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include "DEF.h"
#include "VojData.h"

enum {
    ORDER_DATA=1,
    CUSTOMER_DATA,
    USER_DATA,
    GAME_LIST,
    GAME_ITEM,
    EXCHANGE_RATE,
    PRIMECOST_RATE,
    CUSTOMER_CLASS,
    FACTORY_CLASS,
    PAY_TYPE,
    USER_BONUS,
    BULLETIN_DATA

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
    bool m_bIsFirst= true;
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


class CustomerClassProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit CustomerClassProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataCustomerClass d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataCustomerClass> m_listData;

};

class FactoryClassProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit FactoryClassProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {
        std::sort(m_list.begin(), m_list.end(), [](const QVariant &a, const QVariant &b) {
            return a.toMap()["Sort"].toInt() <b.toMap()["Sort"].toInt();
        });

        m_listData.clear();
        foreach(const QVariant v, m_list)
        {
            DataFactory d(v.toMap());
            m_listData.append(d);
        }
    }

    QList<DataFactory> m_listData;

};


class PayTypeProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit PayTypeProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}

    void changeData() override
    {

        std::sort(m_list.begin(), m_list.end(), [](const QVariant &a, const QVariant &b) {
            return a.toMap()["Sort"].toInt() <b.toMap()["Sort"].toInt();
        });


        m_listData.clear();
        m_listAddValueType.clear();
        foreach(const QVariant v, m_list)
        {
            DataPayType d(v.toMap());
            m_listData.append(d);

            QPair<QString,QString> pair;
            pair.first=d.Sid;
            pair.second=d.Name;
            m_listAddValueType.append(pair);
        }
    }

    QList<DataPayType> m_listData;

    CListPair m_listAddValueType;


};


class UserBonusProvider : public DataProvider
{
    Q_OBJECT
public:
    explicit UserBonusProvider(int iTag,QObject *parent = nullptr):DataProvider(iTag,parent){}
    void changeData() override
    {
        m_listData=m_list;
    }
    QVariantList m_listData;
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







#endif // DATAPROVIDEROBJ_H
