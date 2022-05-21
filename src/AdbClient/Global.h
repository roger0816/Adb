#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QDebug>
#include "Action.h"
#include "VojData.h"

#define GLOBAL Global::Instance()
#define ACTION Global::Instance().m_action
#define DATA Global::Instance().m_action.VojData

class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);


    bool isDiff(QStringList listKey, QVariantMap pre, QVariantMap current);

    DataExchange::Rate rate();

    static Global& Instance();

    Action m_action;
private:
    static Global *m_pInstance;


    QString strNumber(double number);


signals:

};

#endif // GLOBAL_H
