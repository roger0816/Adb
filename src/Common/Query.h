#ifndef QUERY_H
#define QUERY_H

#include "QueryObj.h"
#include "DEF.h"
#include "VojData.h"
#include <QCryptographicHash>
#include <QTimer>





class Query : public QueryObj
{
    Q_OBJECT
public:
    explicit Query(QObject *parent = nullptr);

    CData implementRecall(CData data) override;


    bool changeMoney(QString sCustomerSid, QString sValue, QString &sError);

    bool changeMoney(CustomerData cus,QString sValue,QString &sError);

    bool getCustomer(QString sSid,CustomerData &data);

    UserData getUser(QString sSid);

    QString getNewOrderId();

    void printTime(QString st="");

    void setPic(QVariantMap data);

signals:

};

#endif // QUERY_H
