#ifndef MODELGAMEREPORT_H
#define MODELGAMEREPORT_H

#include <QAbstractTableModel>
#include "Global.h"
#include "GlobalUi.h"
#include "DataProviderAdp.h"

namespace _ModelGameReport {

enum
{
    _NORMAL=0,

    _TYPE_COUNT
};

struct DataGameReport :public VGameList
{
    DataGameReport():VGameList(){}

    DataGameReport(QVariantMap data);

    int totalOrderByDate(QDateTime date,bool bIsMonth=true);

    int iFinishOrder=0;   //完成的訂單
    int iRuningOrder=0;   //進行中 step 1~4
    int iSayOrder=0;     //報價 step=0

    QStringList listOrderSid;
    int iTotalOrder=0;

    int iRevenue=0;  //營業額

    int iPrime=0;  //成本
};


};



class ModelGameReport : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModelGameReport(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateData(bool bIsMonth, int iType, QDateTime date, QString sFilterStr);

    void requestAction();

private:

    QStringList m_listHeader[_ModelGameReport::_TYPE_COUNT];

    QDateTime m_dateTime;

    QString m_strFilter;

    int m_iType=0;

    bool m_bIsMonth=true;

    QList<_ModelGameReport::DataGameReport> m_listData;


    QList<_ModelGameReport::DataGameReport> m_listGame;

    QMap<QString,_ModelGameReport::DataGameReport*> m_dGame; //只是方便調用，等於m_listGame 以sid為key


    QList<OrderData> m_listOrder;

    int findGameIndex(QString sGameSid);

};

#endif // MODELGAMEREPORT_H
