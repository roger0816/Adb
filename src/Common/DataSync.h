#ifndef DATASYNC_H
#define DATASYNC_H

#include <QObject>
#include <QTimer>
#include <QVariantMap>
#include <QVariantList>
#include "VojData.h"


class VojDataSync
{
public:
    VojDataSync(){}
    void updateData(QVariantList list);
    QVariantList getList();
    QString lastUpdate(){return m_lastUpdateTime;}
private:
    QStringList m_listKey;

    QVariantMap m_dData;

    QString m_lastUpdateTime="0";
};





class DataSync : public QObject
{
    Q_OBJECT
public:
    explicit DataSync(QObject *parent = nullptr);

    void updateOrderData(QVariantList list);

    QList<OrderData> getOrderData();


private:

    VojDataSync m_orderData;

signals:

private slots:


};

#endif // DATASYNC_H
