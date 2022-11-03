#ifndef MODELUSERREPORT_H
#define MODELUSERREPORT_H

#include <QAbstractTableModel>
#include "Global.h"
#include <QFont>
#include <QColor>

namespace _ModelUserReport {

enum _TYPE
{
    _ORDER_TOTAL=0,
    _TIME_TOTAL,
    _TIME_AVE,

    _TYPE_COUNT
};

struct DataUserReport :public UserData
{
    DataUserReport():UserData(){}

    DataUserReport(QVariantMap data):UserData(data){}

    int iTotalStep[6]={0,0,0,0,0,0};


    double iTotalTimer[6]={0,0,0,0,0,0};


};


}

using namespace _ModelUserReport;


class ModelUserReport : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ModelUserReport(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateData(bool bIsMonth, int iType, QDateTime date, QString sFilterStr);


    void requestAction();

    QStringList m_listHeader[_TYPE_COUNT];

    QDateTime m_dateTime;

    QString m_strFilterStr;

    int m_iType=0;

    bool m_bIsMonth=true;

    QVariantList m_listData;
    QList<OrderData> m_listOrder;
    QList<DataUserReport> m_listUser;

    QMap<QString,DataUserReport*> m_dUser; //只是方便調用，等於m_listUser 以sid為key

    /*
    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    */

private:

    QString countText(const int row,  const int col);

    QString timeText(int iRow,int iCol);
};

#endif // MODELUSERREPORT_H
