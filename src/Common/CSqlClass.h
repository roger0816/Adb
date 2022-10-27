#ifndef CSQLCLASS_H
#define CSQLCLASS_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include <QVariantList>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "RpkCore.h"
class CSqlClass : public QObject
{
    Q_OBJECT
public:
    explicit CSqlClass(QObject *parent = nullptr);


    bool insertTb(QString sTableName, QVariantMap input, QString &sError,bool bOrRplace=false);

    bool delFromTb(QString sTableName,QVariantMap conditions, QString &sError);

    bool queryTb(QString sTableName,QVariantList &listOut,QString &sError);

    bool queryTb(QString sTableName, QVariantMap conditions, QVariantList &listOut, QString &sError);

    bool updateTb(QString sTableName, QVariantMap conditions, QVariantMap data, QString &sError);


    bool checkLogin(QString sUser,QString sPass,QVariantMap &out,QString &sError);

    bool addUser(QString sId, QString sPass, QString sCid, QString sName, int iLv, QString startDate, QString &sError);

    bool delUser(QString sId,QString &sError);

    bool editUser(QVariantMap data , QString &sError);

    bool queryUser(QString sId,QVariantMap &sData);

    QVariantList queryUser(QString sId="");

    bool saveExchange(QVariantList list,QString &sError);

    QVariantList readExchange(int iSid=-1);



    bool lsatCustomerId(QString sClassSid,QString sClassId,QString &out,QString &sError);

    bool lastCustomerAddCostId(QString sDate, QString &sId, QString &sError);


    bool lastOrderId(QString sDate, QString &sId, QString &sError);

    bool lastOrderName(QString sOwnerSid, QString sDate, QString &sRe, QString &sError);



    bool openDb(bool bMysql, QString sIp, QString sPort="3306",QString sDbName="adp");

    bool bRunMysql = false;


   // void setTrigger(QString sTableName, QString sDateTime);

    void saveTrigger(QString sApi,QString sDateTime);

    QMap<QString,QString> readTrigger();

    QDateTime currentDateTime();

private:
    void createTable();

    void createTableSqlite();

    void createTableMysql();

    QSqlDatabase m_db;

    QSqlDatabase m_local;

    QStringList fieldNames(QSqlRecord record);


   // void loadTrigger();

signals:

    void tbUpdate(QString tbName,QString sDateTime);

};

#endif // CSQLCLASS_H
