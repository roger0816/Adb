#include "Global.h"

Global *Global::m_pInstance = nullptr;

Global::Global(QObject *parent)
    : QObject{parent}
{
    loadConfig();
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

QString Global::displayCurrency(QString st)
{
    return st;
    QString sRe="新台幣";

    if(st.trimmed()=="HKD")
        sRe="港幣";
    if(st.trimmed()=="USD")
        sRe="美金";
    else if(st.trimmed()=="RMB")
        sRe="人民幣";
    else if(st.trimmed()=="MYR")
        sRe="林吉特";
    else if(st.trimmed()=="SGD")
        sRe="新加坡元";
    return sRe;

}

QString Global::originCurrency(QString st)
{
    return st;
    QString sRe="NTD";

    if(st.trimmed()=="港幣")
        sRe="HKD";
    else if(st.trimmed()=="人民幣")
        sRe="RMB";
    else if(st.trimmed()=="美金")
        sRe="USD";
    else if(st.trimmed()=="林吉特")
        sRe="MYR";
    else if(st.trimmed()=="新加坡元")
        sRe="SGD";
    return sRe;
}

QString Global::sidAdd(QString last)
{
    if(last=="")
    {
        return QDate::currentDate().toString("yyyyMMdd").remove(0,2)+"-"+"A001";
    }
    QString sId="";
    if(last.length()>=4)
    {
        QString sTmp = last.mid(last.length()-4,4);

        QString sSecond = sTmp.mid(1,3);

        QString sFirst = sTmp.mid(0,1);

        if(sSecond.toInt()<999)
        {
            QString sNum = QString("%1").arg(sSecond.toInt()+1,3,10,QLatin1Char('0'));

            sId = last.mid(0,last.length()-4)+sFirst+sNum;
        }
        else
        {


            sFirst=QChar::fromLatin1(sFirst.at(0).toLatin1()+1);

            sId = last.mid(0,last.length()-4)+sFirst+"001";
        }

    }

    return sId;
}

QVariantList Global::reData(QVariantList data, QStringList listKey)
{
    QVariantList listRe;

    for(int i=0;i<data.length();i++)
    {
        QVariantMap v;
        QVariantMap t =data.at(i).toMap();

        for(int j=0;j<listKey.length();j++)
        {
            QString sKey = listKey.at(j);
            v[sKey] = t[sKey];
        }

        listRe.append(v);
    }

    return listRe;
}

QStringList Global::toList(QString sData)
{
    return sData.split(SPLIT1);
}

QString Global::toString(QStringList list)
{
    return list.join(SPLIT1);
}

QString Global::toString(CListPair listPair)
{
    return listPair.toString();
}

CListPair Global::toListPair(QString st)
{
    return CListPair(st);
}

QStringList Global::mapping(CListPair listData, QStringList listKey, bool bMappingFirst)
{
    QStringList listRe;

    QStringList keys = listData.listFirst();

    QStringList values = listData.listSecond();

    if(!bMappingFirst)
    {
        keys = listData.listSecond();

        values = listData.listFirst();
    }

    for(int i=0;i<listKey.length();i++)
    {
        int iIdx = keys.indexOf(listKey.at(i));

        if(iIdx<0)
            continue;

        listRe.append(values.at(i));

    }


    return listRe;
}

void Global::loadConfig()
{
    qDebug()<<"loading config";

    QString file=QCoreApplication::applicationDirPath()+"/conf.ini";

    QSettings conf(file, QSettings::IniFormat);

    QStringList list = conf.allKeys();

    if(list.indexOf("ServerIp")<0)
        list.append("ServerIp");


    if(list.indexOf("ServerPort")<0)
        list.append("ServerPort");

    for(int i=0;i<list.length();i++)
    {
        QString sKey = list.at(i);

        if(sKey=="ServerIp")
        {
            m_config[list.at(i)]= conf.value(list.at(i),"127.0.0.1");
        }
        else if(sKey=="ServerPort")
        {
            m_config[list.at(i)]= conf.value(list.at(i),"6000");
        }
        else
        {
            m_config[list.at(i)]= conf.value(list.at(i));
        }
    }


}







Global &Global::Instance()
{
    if(m_pInstance==0)
        m_pInstance=new Global();
    return *m_pInstance;
}

QVariant Global::config(QString st)
{
    qDebug()<<m_config;

return m_config.value(st);
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
