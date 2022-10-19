#ifndef QUERYOBJ_H
#define QUERYOBJ_H

#include <QObject>
#include <QDebug>
#include <QVariantMap>
#include "CSqlClass.h"
#include "DEF.h"
#include "RpkCore.h"



/*
 Api  規則，因需要做寫入的api影響qeury 的trigger，需要做匹配

    使用4碼:
    第一碼不能為0
    前二碼為分類號
    第三碼3開頭為query使用(被其它所影響的trigger)
    第四碼為流水號

    舉例:  AddUser  EditUser QueryUser
          AddOrder QueryOrder QueryLastOrder

    AddUser跟EditUser 會影響QueryUser的更新時間標記
    所以放同一組 10 開頭，QeuryUser為被查詢時間標記
    AddUser = 1001
    EditUser = 1002
    QueryUser = 1031;

    AddOrder=1101;
    QueryOrder=1131;
    QueryLastOrder=1132;


 */



class QueryObj : public QObject
{
    Q_OBJECT
public:
    explicit QueryObj(QObject *parent = nullptr);


    void linkage(int iApi, QList<int> listApi);

    void linkage(int iApi,int iBindApi);


    void setDataBase(bool bMysql, QString sIp="127.0.0.1", QString sPort="3306");

    CData queryData(CData data);

    QByteArray heartBeat();

    CSqlClass m_sql;


    bool isQueryApi(int iApi);

protected:
    virtual CData implementRecall(CData){CData re; return re;}

    QString checkUpdate(int iApi);

    //void updateTrigger(QString sTableName, QString sDateTime);

    //api更新的時間標記
    QMap<QString,QString> m_dTrigger;

    //影響資料變動的api，與聯動trigger的api
    QVariantMap m_dLinkage;
signals:

};



#endif // QUERYOBJ_H
