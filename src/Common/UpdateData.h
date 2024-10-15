#ifndef UPDATEDATA_H
#define UPDATEDATA_H

#include <QObject>
#include "RpkCore.h"

#include <QTimer>
#include "DataProviderObj.h"
#include <QRandomGenerator>
#include <QThread>
#define DATA UpdateData::Instance()

#define TEST_ACTION 0


class UpdateData : public QObject
{
    Q_OBJECT
public:
    explicit UpdateData(QObject *parent = nullptr);

    static UpdateData& Instance();

    //int connectIp(QString sIp,QString sPort);
    void setTarget(QStringList list);
    void setRun(bool b);

    void runUpdate();

    QList<OrderData> getOrder();

    OrderData getOrder(QString sSid);

    QList<OrderData> getOrderByDate(QDate date);



    QList<CustomerData> getCustomerList();
    CustomerData getCustomer(QString sCusId);

    QList<UserData> getUserList();
    UserData getUser(QString sSid);

    QList<DataGameList> getGameList(bool bShowDelete =true);
    DataGameList getGameList(QString sSid);
    QString getGameName(QString sId);
    QString getGameId(QString sName);


    QList<DataGameItem> getGameItemList();
    DataGameItem getGameItem(QString sSid);
    QList<DataGameItem> getGameItemFromGameSid(QString sGameSid,bool showDelete= true);
    QString findGameSid(QString sGameItemSid);
    double getGameItemPayCount(QString sGameItemSid, QString sPaySid);

    QList<DataRate> costRateList();
    DataRate costRate(QString sSid="");
    QList<DataRate> primeRateList();
    DataRate primeRate(QString sSid="");

    QList<DataCustomerClass> getCustomerClassList();
    DataCustomerClass getCustomerClass(QString sSid);

    QList<DataFactory> getFactoryClassList();
    DataFactory getFactoryClass(QString sSid);

    QList<DataPayType> getPayTypeList();
    DataPayType getPayType(QString sSid);
    CListPair getAddValueType();
    QString getAddValueName(QString sSid);
    QString getPayRate(QString sPayTypeSid);

    QVariantMap getUserBonus(QString sUserSid);

    QVariantList getBulletin();

    QMap< QString ,DataProvider* > m_data;

    QThread m_thread;


    QString m_sUserSid="";

public slots:
    void slotRead(QString sConnect, QString sId,QByteArray data,int Error);


private slots:

    void slotTimer();
private:
    static UpdateData *m_pInstance;


    QTimer m_timer;
    bool m_bRun=false;

    bool isOnSync();

    QStringList m_listTarget;
    int m_iWaitRecvSec=0;


    QString sHhmm="";

    int m_runCount = 0;

    int iForTestInt =1;


signals:
    void updateNotify(int iType, QStringList listSid );

    void firstFinished();

    void callUpdate(QByteArray data);


};

#endif // UPDATEDATA_H
