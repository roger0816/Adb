#include "DataProviderObj.h"




DataProvider::DataProvider(int iTag, QObject *parent)
    : QObject{parent}
{
    m_iTag = iTag;
}

bool DataProvider::setData(QVariantList data)
{
    if(data.length()<1)
    {
        return false;
    }

    m_bOnSync = true;
    QVariantMap d;
    QVariant v =d["data"];

    foreach(QVariant v ,data)
    {
        m_oriData[v.toMap()["Sid"].toInt()]=v;
    }


    QString sOldDate =m_lastUpdate;

    QList<int> keys=m_oriData.keys();
    // 使用 Qt 的 qSort 函數進行排序
    qSort(keys.begin(), keys.end());

    m_list.clear();

    for(int i=0;i<keys.length();i++)
    {
        QVariant d =m_oriData[keys[i]];
        QString sUpdateTime = d.toMap()["UpdateTime"].toString();
        m_list.append(d);
        if(sUpdateTime>m_lastUpdate)
            m_lastUpdate=sUpdateTime;
    }


    changeData();

    m_bOnSync = false;

    if(sOldDate!="0")
        m_bIsFirst=false;

    return m_lastUpdate != sOldDate;
}
