#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include "Action.h"
#include "VojData.h"
#include "DataSync.h"

#define GLOBAL Global::Instance()

#define ACTION Global::Instance().m_action

#define QUERY Global::Instance().m_action.m_queryObj


//#define DATA Global::Instance().m_data






class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    ~Global();

//    GLOBAL_DATA::Data m_data;

    void setServer(bool b = true,QString sIp="127.0.0.1",QString sPort="6000");

    QStringList listMapToList(const QVariantList list,QString sKey);

    bool isDiff(QStringList listKey, QVariantMap pre, QVariantMap current);

    QString displayCurrency(QString st);

    QString originCurrency(QString st);

    QString displayCustomerLv(QString iLv);

    QString sidAdd(QString last);

    QVariantList reData(QVariantList data,QStringList listKey);

    QStringList toList(QString sData);

    QString toString(QStringList list);

    QString toString(CListPair listPair);

    CListPair toListPair(QString st);

    QStringList mapping(CListPair listData, QStringList listKey, bool bMappingFirst = true);

    void loadConfig();

    static Global& Instance();

    Action m_action;

    QVariant config(QString st);

    QDateTime dateTimeUtc8();

    QString userLvToStr(int iLv);

  //  double subFloat(double v,int f);  //小數點無條件進位

    int m_virtualSec=0;

    bool checkSearch(QString sFilterStr,QVariantMap dTarget,bool caseNeedDiff=false);

    QVariantMap m_copyGameItem;

private:
    static Global *m_pInstance;


    QString strNumber(double number);

    QMap<QString,QVariant> m_config;


    DataSync m_dataSync;



signals:

};

#endif // GLOBAL_H
