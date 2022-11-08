#ifndef DATAPROVIDERADP_H
#define DATAPROVIDERADP_H

#include <QObject>

#include "Global.h"
/*VojData 需要呈現database的原型，這個類是為方便使用複合、延伸
*      特別事項: 因為這個有做Action，引用層級不同，不該被GLOBAL調用
*
*/

struct VGameItem :public DataGameItem
{
    VGameItem():DataGameItem(){}

    VGameItem(QVariantMap data);

    void setData(QVariantMap data);

    QVariantMap data();

    int totalCount;
    int totalSell;
    int currentCount;

};


struct VGameList :public DataGameList
{
    VGameList():DataGameList(){}

    VGameList(QVariantMap data);

    void setData(QVariantMap data);

    QVariantMap data();

    QList<VGameItem> listGameItem;

};




#endif // DATAPROVIDERADP_H
