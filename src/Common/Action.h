#ifndef ACTION_H
#define ACTION_H

#include "ActionObj.h"

namespace _KEY {
static QString isRememberLogin="isRememberLogin";

static QString lastLogin="lastLogin";

}


// client action
class Action : public ActionObj
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

    ~Action();


    void setServer(bool b = true,QString sIp="127.0.0.1",QString sPort="6000");

    int checkLogin(QString sUser,QString sPass,QString &sError);

    bool addUser(QString sUser, QString sPass, QString sCid, QString sName, int iLv, QDate startDate, QString &sError);

    bool editUser(QVariantMap userData, QString &sError);

    bool delUser(QString sUser, QString &sError);

    // QVariantList queryUser(QString sId="");

    QList<UserData> queryUser(QString sId="");

    bool setKeyValue(QString key, QString value,bool inLocal=true);

    QString getKeyValue(QString key, bool inLocal=true);


    bool addGroupData(int iType,GroupData data,QString &sError);

    bool delGroupData(int iType, QString sSid, QString &sError);

    bool editGroupData(int iType,GroupData data,QString &sError);

    QList<GroupData> getGroupData(int iType,QString &sError);


    void reQuerty();

    QList<UserData> getUser(bool bQuery=false);
    UserData getUser(QString sSid, bool bQuery=false);

    CustomerData getCustomer(QString sSid, bool bQuery=false);
    QList<DataCustomerClass> getCustomerClass(bool bQuery=false);
    DataCustomerClass getCustomerClass(QString sSid, bool bQuery=false);

    QList<DataFactory> getFactoryClass(QString sSid="",bool bQuery=false);
    bool editFacotryClass(QVariantMap data,QString &sError);


    QList<DataGameList> getGameList(bool bQuery=false);
    DataGameList getGameList(QString sSid, bool bQuery=false);

    QList<DataGameItem> getGameItem(bool bQuery = false);

    QList<DataGameItem> getGameItem(QString sGameSid, bool bQuery=false);

    void updateGameItemPrice(QString sGameSid,double iGameRate);

    DataGameItem getGameItemFromSid(QString sSid,bool bQuery=false);

    QList<DataGameItem> getGameItemFromGameSid(QString sGameSid,bool bQuery=false);


    QString getGameName(QString sId);
    QString getGameId(QString sName);

    QList<CustomerCost> getCustomerCost(QString sCustomerSid,bool bQuery=false);
    bool setCustomerCost(CustomerCost costData, QString &sError);

    bool replaceOrder(OrderData order, QString &sError);

    QList<OrderData> getOrder(bool bRequest = false);

    OrderData getOrder(QString sSid, bool bRequest = false);
    OrderData getOrderCustomerLast(QString sCustomerSid, bool bRequest = false);



    QVariant trKey(QVariantList list,QVariantMap info,QString sTargetKey);


    QStringList mapToList(QVariantList list, QString sKey);

    int mapping(QVariantList list, QString sKey,QString var);

    // DataExchange::Rate rate(QString sSid="",bool bRequest=false);

    bool addRate(QVariantMap data, QString &sError, bool bExchangeType=false);

    QList<DataRate> listRate(QString sSid="", bool bRequest=true, bool bExchangeType=false);

    DataRate costRate(QString sSid="", bool bRequest=true)
    {return listRate(sSid,bRequest,true).last();}

    DataRate primeRate(QString sSid="", bool bRequest=true)
    {return listRate(sSid,bRequest,false).last();}

    QList<DataUserBonus> listBouns(QString sUserSid);


    UserData m_currentUser;

    CListPair getAddValueType(bool bRequest=true);

    QString getAddValueName(QString sSid);


    double payTypeToNTD(QString payTypeSid, DataRate rate);

    bool orderUpdateCount(QString sOrderSid, QString sUserSid, QString sOrderItem);

    int checkItemCount(QString sGameItemSid);



    void clearCacheData(int iApi);

private:
    QList<UserData> m_listUser;

    QList<DataCustomerClass> m_listCustomerClass;

    QList<CustomerData> m_listCustomer;

    QList<DataFactory> m_listFactoryClass;


    QList<DataGameList> m_listGameList;

    QList<DataGameItem> m_listGameItem;

    QList<CustomerCost> m_listCustomerCost;

    QList<OrderData> m_listOrder;


    CListPair m_listAddValueType;

    QVariantList m_primeRate;

    QVariantList m_exRate;


};

#endif // ACTION_H
