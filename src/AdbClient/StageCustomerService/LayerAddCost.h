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

private:
    Ui::LayerAddCost *ui;

    CustomerData m_dataCustomer;

    CustomerCost m_lastCostData;

    QVariantList m_listDebit;

    void checkTotal();

    void showEvent(QShowEvent*) override;

    double m_addValue=0;

    DataRate m_rate;

    bool m_bLock=false;

signals:
    void back(int iPage=0);

public slots:

    void refresh();

    void on_btnAddCostBack_clicked();

private slots:
    void on_btnCopy_clicked();
    void on_cbCurrency_currentIndexChanged(int index);

    void on_sb_valueChanged(int);
    void on_btnOk_clicked();

    void on_sbAdd_valueChanged(double arg1);

};

#endif // LAYERADDCOST_H
