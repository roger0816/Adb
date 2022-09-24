#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include "Action.h"
#include "VojData.h"

#define GLOBAL Global::Instance()

#define ACTION Global::Instance().m_action


//#define DATA Global::Instance().m_data






class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    ~Global();

//    GLOBAL_DATA::Data m_data;

    bool isDiff(QStringList listKey, QVariantMap pre, QVariantMap current);

    QString displayCurrency(QString st);

    QString originCurrency(QString st);

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



private:
    static Global *m_pInstance;


    QString strNumber(double number);

    QMap<QString,QVariant> m_config;



signals:

};

#endif // GLOBAL_H
