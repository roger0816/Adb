#ifndef ACTION_H
#define ACTION_H

#include <QObject>
//#include "CSqlClass.h"
#include "RpkCore.h"
#include "DEF.h"
#include "QueryObj.h"
#include "VojData.h"


namespace _KEY {
static QString isRememberLogin="isRememberLogin";

static QString lastLogin="lastLogin";

}


// client action
class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

    VojData VojData;

    void setDataFromServer(bool b = true);

    bool action(ACT::_KEY act, QVariantList listData, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QString &sError);

    bool action(ACT::_KEY act, QVariantMap data, QVariantMap &out, QString &sError);


    bool action(ACT::_KEY act, QVariantMap data,QVariantList &listOut, QString &sError);

    bool action(ACT::_KEY act, QVariantList listData, QVariantList &listOut, QString &sError);


    bool checkLogin(QString sUser,QString sPass,QString &sError);

    bool addUser(QString sUser, QString sPass, QString sCid, QString sName, int iLv, QDate startDate, QString &sError);

    bool editUser(QVariantMap userData, QString &sError);

    bool delUser(QString sUser, QString &sError);

    // QVariantList queryUser(QString sId="");

    QList<UserData> queryUser(QString sId="");

    bool setKeyValue(QString key, QString value,bool inLocal=true);

    QString getKeyValue(QString key, bool inLocal=true);



    void reQuerty();

    QList<UserData> getUser(bool bQuery=false);
    UserData getUser(QString sSid, bool bQuery=false);

    QList<DataCustomerClass> getCustomerClass(bool bQuery=false);
    DataCustomerClass getCustomerClass(QString sSid, bool bQuery=false);

    QList<DataGameList> getGameList(bool bQuery=false);
    DataGameList getGameList(QString sSid, bool bQuery=false);

    QList<DataGameItem> getGameItem(bool bQuery = false);

    QList<DataGameItem> getGameItem(QString sGameSid, bool bQuery=false);


    QString getGameName(QString sId);
    QString getGameId(QString sName);

    QList<CustomerCost> getCustomerCost(QString sCustomerSid,bool bQuery=false);
    bool setCustomerCost(CustomerCost costData, QString &sError);

    bool replaceOrder(OrderData order, QString &sError);

    QList<OrderData> getOrder(bool bRequest = false);

    OrderData getOrder(QString sSid, bool bRequest = false);
    OrderData getOrderByCustomerSid(QString sSid, bool bRequest = false);



    QVariant trKey(QVariantList list,QVariantMap info,QString sTargetKey);


    QStringList mapToList(QVariantList list, QString sKey);

    int mapping(QVariantList list, QString sKey,QString var);

    DataExchange::Rate rate(QString sSid="",bool bRequest=false);


    UserData m_currentUser;

private :

    QueryObj m_queryObj;

    CData query(CData data);


    CData callServer(CData data);


    bool m_bDataFromServer = true;

private:
    QList<UserData> m_listUser;

    QList<DataCustomerClass> m_listCustomerClass;

    QList<DataGameList> m_listGameList;

    QList<DataGameItem> m_listGameItem;

    QList<CustomerCost> m_listCustomerCost;

    QList<OrderData> m_listOrder;

    DataExchange::Rate m_rate;


signals:

};

#endif // ACTION_H
