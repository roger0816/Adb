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

    void checkTotal();

    void showEvent(QShowEvent*) override;

    double m_addValue=0;

signals:
    void back();
public slots:

    void on_btnAddCostBack_clicked();

private slots:
    void on_btnCopy_clicked();
    void on_cbCurrency_currentTextChanged(const QString &arg1);
    void on_sb_valueChanged(int);
    void on_btnOk_clicked();
};

#endif // LAYERADDCOST_H
