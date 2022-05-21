#include "Global.h"

Global *Global::m_pInstance = nullptr;

Global::Global(QObject *parent)
    : QObject{parent}
{

}

bool Global::isDiff(QStringList listKey, QVariantMap pre, QVariantMap current)
{


    for(int i=0;i<listKey.length();i++)
    {
        QString sKey = listKey.at(i);

        if(pre.keys().indexOf(sKey)<0 && current.keys().indexOf(sKey)<0)
            continue;

        if(pre.keys().indexOf(sKey)<0 && current.keys().indexOf(sKey)>=0)
            return true;

        if(pre.keys().indexOf(sKey)>=0 && current.keys().indexOf(sKey)<0)
            return true;


        if(pre[sKey]!= current[sKey])
            return true;

    }


    return false;

}

DataExchange::Rate Global::rate()
{
    QVariantList input,listRate;

    QString sError;

    bool bRateOk = m_action.action(ACT::READ_EXCHANGE,input,listRate,sError);

    DataExchange::Rate rate;

    if(bRateOk)
    {
        DataExchange tmp(listRate);

        rate = tmp.last();
    }

    return rate;
}

Global &Global::Instance()
{
    if(m_pInstance==0)
        m_pInstance=new Global();
    return *m_pInstance;
}

QString Global::strNumber(double number)
{
    QString sRe = QString::number(number, 'f', 2);

    for(int point = 0, i = (sRe.lastIndexOf('.') == -1 ? sRe.length() : sRe.lastIndexOf('.')); i > 0; --i, ++point)
    {
        if(point != 0 && point % 3 == 0)
        {
            sRe.insert(i, ',');
        }
    }

    return sRe;
}
