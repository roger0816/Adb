#ifndef MODELUSERREPORT_H
#define MODELUSERREPORT_H

#include <QAbstractTableModel>
#include "Global.h"
#include <QFont>
#include <QColor>

namespace _ModelUserReport {

enum
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

    QList<int> iTotalStep={0,0,0,0,0,0};

    QList<double> iTotalTimer={0,0,0,0,0,0};

    QStringList sTotalTimer={"0","0","0","0","0","0"};
    QStringList sAveTimer={"0","0","0","0","0","0"};


    QVariantMap data()
    {
        QVariantMap re =UserData::data();

        QStringList sTotalStep;
        sTotalStep<<QString::number(iTotalStep[0])
                <<QString::number(iTotalStep[1])
                <<QString::number(iTotalStep[2])
                <<QString::number(iTotalStep[3])
                <<QString::number(iTotalStep[4])
                <<QString::number(iTotalStep[5]);

        re["sTotalStep"] = sTotalStep;
        re["sTotalTimer"] =sTotalTimer;
        re["sAveTimer"] =sAveTimer;
        return re;
    }

};


}


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

    QStringList m_listHeader[_ModelUserReport::_TYPE_COUNT];

    QDateTime m_dateTime;

    QString m_strFilter;

    int m_iType=0;

    bool m_bIsMonth=true;

    QList<_ModelUserReport::DataUserReport> m_listData;
    QList<OrderData> m_listOrder;
    QList<_ModelUserReport::DataUserReport> m_listUser;


    QMap<QString,_ModelUserReport::DataUserReport*> m_dUser; //只是方便調用，等於m_listUser 以sid為key

    QString timeStr(int iSec);



    /*
    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    */

private:


};

#endif // MODELUSERREPORT_H
