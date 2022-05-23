#include "Global.h"

Global *Global::m_pInstance = nullptr;

Global::Global(QObject *parent)
    : QObject{parent}
{

}

void GLOBAL_DATA::Data::reQuerty()
{
    getUser(true);

    getGameList(true);

    getCustomerClass(true);

    rate(true);
}

QList<UserData> GLOBAL_DATA::Data::getUser(bool bQuery)
{
    if(bQuery)
        m_listUser = ACTION.queryUser();

    return m_listUser;
}

UserData GLOBAL_DATA::Data::getUser(QString sSid,bool bQuery)
{
    UserData re;
    getUser(bQuery);
    for(int i=0;i<m_listUser.length();i++)
    {
        if(sSid==m_listUser.at(i).Sid)
            re =m_listUser.at(i);
    }

    return re;
}

QList<DataCustomerClass> GLOBAL_DATA::Data::getCustomerClass(bool bQuery)
{
    if(bQuery)
    {
        m_listCustomerClass.clear();

        QVariantList in,listClass;

        QString sError;

        ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,listClass,sError);

        foreach(QVariant v,listClass)
        {
            DataCustomerClass tmp;

            tmp.setData(v.toMap());

            m_listCustomerClass.append(tmp);
        }

    }
    return m_listCustomerClass;
}

DataCustomerClass GLOBAL_DATA::Data::getCustomerClass(QString sSid, bool bQuery)
{
    getCustomerClass(bQuery);

    DataCustomerClass re;

    for(int i=0;i<m_listCustomerClass.length();i++)
    {
        if(sSid == m_listCustomerClass.at(i).Sid)
        {
            re = m_listCustomerClass.at(i);

            break;
        }
    }

    return re;
}


QList<DataGameList> GLOBAL_DATA::Data::getGameList(bool bQuery)
{
    if(bQuery)
    {
        m_listGameList.clear();

        QVariantList in,list;

        QString sError;

        ACTION.action(ACT::QUERY_GAME_LIST,in,list,sError);

        foreach(QVariant v,list)
        {
            DataGameList tmp;

            tmp.setData(v.toMap());

            m_listGameList.append(tmp);
        }

    }
    return m_listGameList;
}

DataGameList GLOBAL_DATA::Data::getGameList(QString sSid, bool bQuery)
{
    getGameList(bQuery);

    DataGameList re;

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sSid == m_listGameList.at(i).Sid)
        {
            re = m_listGameList.at(i);

            break;
        }
    }

    return re;
}

QList<DataGameItem> GLOBAL_DATA::Data::getGameItem(bool bQuery)
{
    if(!bQuery)
        return m_listGameItem;

    QList<DataGameItem> listRe;

    QVariantMap d;

    //    d["GameSid"] = sGameSid;

    QVariantList listOut;

    QString sError;

    ACTION.action(ACT::QUERY_GAME_ITEM,d,listOut,sError);

    m_listGameItem.clear();

    for(int i=0;i<listOut.length();i++)
    {
        DataGameItem item(listOut.at(i).toMap());

        m_listGameItem.append(item);
    }

    return listRe;
}

QList<DataGameItem> GLOBAL_DATA::Data::getGameItem(QString sGameSid, bool bQuery)
{
    getGameItem(bQuery);

    QList<DataGameItem> listRe;


    for(int i=0;i<m_listGameItem.length();i++)
    {
        DataGameItem data = m_listGameItem.at(i);
        if(data.GameSid == sGameSid)
        {
            listRe.append(data);
        }
    }

    return listRe;
}

QString GLOBAL_DATA::Data::getGameName(QString sId)
{
    QString sRe="";

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sId==m_listGameList.at(i).Sid)
        {
            sRe =m_listGameList.at(i).Name;

            break;
        }
    }

    return sRe;

}

QString GLOBAL_DATA::Data::getGameId(QString sName)
{
    QString sRe="";

    for(int i=0;i<m_listGameList.length();i++)
    {
        if(sName==m_listGameList.at(i).Name)
        {
            sRe =m_listGameList.at(i).Sid;

            break;
        }
    }

    return sRe;
}

QVariant GLOBAL_DATA::Data::trKey(QVariantList list, QVariantMap info, QString sTargetKey)
{
    QVariant sRe="";
    for(int i=0;list.length();i++)
    {
        QVariantMap d = list.at(i).toMap();
        if(d[info.firstKey()] == info.first())
        {
            sRe = d[sTargetKey];
        }
    }

    return sRe;
}

QStringList GLOBAL_DATA::Data::mapToList(QVariantList list, QString sKey)
{
    QStringList listRe;

    foreach(QVariant v ,list)
    {
        listRe.append(v.toMap()[sKey].toString());


    }

    return listRe;
}

int GLOBAL_DATA::Data::mapping(QVariantList list, QString sKey, QString var)
{
    int iIdx=-1;

    for(int i=0;i<list.length();i++)
    {
        if(list.at(i).toMap()[sKey] == var)
        {
            iIdx=i;

            break;
        }
    }


    return iIdx;
}


DataExchange::Rate GLOBAL_DATA::Data::rate(bool bRequest)
{
    if(!bRequest)
        return m_rate;
    QVariantList input,listRate;

    QString sError;

    bool bRateOk =true;

    bRateOk= ACTION.action(ACT::READ_EXCHANGE,input,listRate,sError);

    if(bRateOk)
    {
        DataExchange tmp(listRate);

        m_rate = tmp.last();
    }

    return m_rate;
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
