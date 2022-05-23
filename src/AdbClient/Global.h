#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QDebug>
#include "Action.h"
#include "VojData.h"

#define GLOBAL Global::Instance()
#define ACTION Global::Instance().m_action
#define DATA Global::Instance().m_data

namespace GLOBAL_DATA
{
class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr):QObject(parent){}

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


    QVariant trKey(QVariantList list,QVariantMap info,QString sTargetKey);


    QStringList mapToList(QVariantList list, QString sKey);

    int mapping(QVariantList list, QString sKey,QString var);

    DataExchange::Rate rate(bool bRequest=false);



private:
    QList<UserData> m_listUser;

    QList<DataCustomerClass> m_listCustomerClass;

    QList<DataGameList> m_listGameList;

    QList<DataGameItem> m_listGameItem;

    DataExchange::Rate m_rate;

};
}






class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);

    GLOBAL_DATA::Data m_data;

    bool isDiff(QStringList listKey, QVariantMap pre, QVariantMap current);


    static Global& Instance();

    Action m_action;
private:
    static Global *m_pInstance;


    QString strNumber(double number);


signals:

};

#endif // GLOBAL_H
