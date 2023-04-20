#include "DataSync.h"

DataSync::DataSync(QObject *parent)
    : QObject{parent}
{

}

void DataSync::updateOrderData(QVariantList list)
{
    m_orderData.updateData(list);
}

QList<OrderData> DataSync::getOrderData()
{
    QList<OrderData> listRe;

    QVariantList list =m_orderData.getList();

    foreach(QVariant v,list)
    {
       OrderData d(v.toMap());
       listRe.append(d);
    }


    return listRe;

}







void VojDataSync::updateData(QVariantList list)
{
    for(int i=0;i<list.length();i++)
    {
        QVariantMap v = list.at(i).toMap();

        if(v["UpdateTime"].toString()>m_lastUpdateTime)
            m_lastUpdateTime= v["UpdateTime"].toString();

        QString sSid=v["Sid"].toString();

        if(!m_listKey.contains(sSid) && sSid.trimmed()!="")
        {
            m_listKey.append(sSid);
        }

        if(m_listKey.contains(sSid))
        {
            m_dData[sSid]=v;
        }

    }


}

QVariantList VojDataSync::getList()
{
    QVariantList listRe;

    foreach(QString v,m_listKey)
    {
        listRe.append(m_dData[v]);
    }

    return listRe;
}


