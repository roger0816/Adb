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

    bool insertTb(QString sTableName, QVariantMap input, QString &sError);

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


    bool addGame(QVariantList list, QString &sError);


private:
    void createTable();

    QSqlDatabase m_db;

    QSqlDatabase m_local;

    QStringList fieldNames(QSqlRecord record);

signals:

};

#endif // CSQLCLASS_H
