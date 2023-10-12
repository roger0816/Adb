#include "DataProviderAdp.h"


VGameList::VGameList(QVariantMap data)
{
    setData(data);
}

void VGameList::setData(QVariantMap data)
{
    DataGameList::setData(data);

     QList<DataGameItem> list = ACTION.getGameItem(Sid);

     listGameItem.clear();

     foreach(DataGameItem v,list)
     {
         listGameItem.append(VGameItem(v.data()));
     }

}

QVariantMap VGameList::data()
{
    QVariantMap re = DataGameList::data();

    QVariantList list;

    foreach(DataGameItem v, listGameItem)
    {
        list.append(v.data());
    }

    re["listGameItem"] = list;

    return re;
}
//
VGameItem::VGameItem(QVariantMap data)
{
    setData(data);
}

void VGameItem::setData(QVariantMap data)
{
    DataGameItem::setData(data);

    QPair<int,int> tmp = ACTION.getItemCount(Sid,true);

    totalSell = tmp.first;
    totalCount = tmp.second;
    currentCount = totalCount-totalSell;
}

QVariantMap VGameItem::data()
{
    QVariantMap re = DataGameItem::data();

    re["totalSell"] = totalSell;
    re["totalCount"] = totalCount;
    re["currentCount"] = currentCount;

    return re;
}
