#ifndef LAYERSAYCOST_H
#define LAYERSAYCOST_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "Common.h"
#include <QSpinBox>
#include <QClipboard>
#include <QCompleter>

namespace Ui {
class LayerSayCost;
}

class LayerSayCost : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSayCost(QWidget *parent = nullptr);
    ~LayerSayCost();

        void orderMode();

     void setCustomer(QVariantMap data,QString sOrderSid="");

     void setReadOnly();

    // void showEvent(QShowEvent *) override;
     void refreshInfo();
     Ui::LayerSayCost *ui;
     bool m_bOrderMode = false;

     QVariantMap getOk();

private:

    void init();
    CustomerData m_dataCustomer;

    QVariantList m_listGameInfo;

    bool checkHasInto(QString gameItemSid);

    QString m_sCurrentGameSid="";

    QVariantList m_listGameItem;

    QVariantList m_listInto;

    QString m_sMsg;



    QList<QSpinBox*> m_listSp;

    double checkTotal();

    QList<UserData> m_listOwnerUser;


    OrderData m_order;

    QDateTime m_date;


    double m_iTotal=0.0;  //客戶幣值，消費金額

    double m_iNtdTotal=0.0; //換成台幣金額(報表要使用)

    double m_iBouns=0.0;

    QString m_sLoadOrderSid="";

    DataRate m_costRate;

  //  DataRate m_primeRate;

    QString m_gameRate;

    bool m_bReadOnly = false;

   // CListPair m_listPayType;

    QList<DataFactory> m_listCbItem;

    void addPayTypeToCb();

    bool checkPayType(CListPair &data);

    CListPair m_mappingPayType;

    QStringList m_listCost; //訂單內容的歷史價格
    QStringList m_listBouns;

    void sayCostData();
    void orderData();


protected:


    QString getNewOrderId();

    QString getNewOrderName();

signals:
    void back(int iPage=0);
public slots:

    void on_btnSayCostBack_clicked();

    void spValue(int);
private slots:
    void on_cbGame_currentTextChanged(const QString &arg1);
    void on_cbAccount_currentTextChanged(const QString &arg1);
    void on_cbServer_currentTextChanged(const QString &arg1);
    void on_cbChr_currentTextChanged(const QString &arg1);
    void slotTbGameItemCellClicked(int row, int column);
    void on_tbInfo_cellPressed(int row, int column);
    void on_btnCopy_clicked();
    void on_btnSayClose_clicked();

    void delayShowEvent();
public slots:
    void on_btnSayOk_clicked();
};

#endif // LAYERSAYCOST_H
