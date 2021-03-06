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
