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

    QString getNewOrderId(QString sOrderDate);

    void printTime(QString st="");

    void setPic(QVariantMap data);

    bool checkItemCount(OrderData orderData, QList<DataItemCount> &listLast , QStringList &sErrorGameItemSid);

    bool isBackSayCost(OrderData orderData);

    bool changeItemCount(OrderData orderData, bool bIsAdd, QString &sErrorMsg);

        bool orderStep0(OrderData &order,QString &sError);
    bool orderStep1(OrderData &order,OrderData current,QString &sError);
    bool orderStep2(OrderData &order,OrderData current,QString &sError);
    bool orderStep3(OrderData &order,OrderData current,QString &sError);
    bool orderStep4(OrderData &order,OrderData current,QString &sError);


signals:

};

#endif // QUERY_H
