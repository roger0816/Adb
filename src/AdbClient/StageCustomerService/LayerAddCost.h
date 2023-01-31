#ifndef LAYERADDCOST_H
#define LAYERADDCOST_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QShowEvent>

namespace Ui {
class LayerAddCost;
}

class LayerAddCost : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAddCost(QWidget *parent = nullptr);
    ~LayerAddCost();
    void setCustomer(QVariantMap data);


    void init();

private:
    Ui::LayerAddCost *ui;

    CustomerData m_dataCustomer;

      CustomerCost m_dataCost;

   // CustomerCost m_lastCostData;

    QVariantList m_listDebit;    //支付管道:篩選後填入comboBox的資料

    QVariantList m_listRowDebit; //支付管道:原始資料

    void checkTotal();

    double m_addValue=0;

    DataRate m_rate;

    bool m_bLock=false;

    QString getNewOrderId();

    QString sub(QString sCost,QString sCurrency);


signals:
    void back(int iPage=0);

public slots:

    void refresh();

    void setDebitCb();

    void on_btnAddCostBack_clicked();

private slots:
    void on_btnCopy_clicked();
    void on_cbCurrency_currentIndexChanged(int index);

    void on_sb_valueChanged(double);
    void on_btnOk_clicked();

    void on_sbAdd_valueChanged(double);


};

#endif // LAYERADDCOST_H
