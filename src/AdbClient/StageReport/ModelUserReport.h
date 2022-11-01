#ifndef MODELUSERREPORT_H
#define MODELUSERREPORT_H

#include <QAbstractTableModel>
#include "Global.h"


namespace _ModelUserReport {

struct DataUserReport :public UserData
{
    DataUserReport():UserData(){}

    DataUserReport(QVariantMap data):UserData(data){}

    int iTotalStep[6]={0,0,0,0,0,0};

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

    void updateData(bool bIsMonth,QDateTime date,QString sFilterStr);


    void requestAction();

    QStringList m_listHeader;

    QDateTime m_dateTime;

    QString m_strFilterStr;

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
};

#endif // MODELUSERREPORT_H
