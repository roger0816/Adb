#ifndef LAYERCUSTOMERSETTING_H
#define LAYERCUSTOMERSETTING_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerCustomerSetting;
}

class LayerCustomerSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCustomerSetting(QWidget *parent = nullptr);
    ~LayerCustomerSetting();



    void showEvent(QShowEvent *) override;

private slots:

    void refresh();

    void on_btnCusClassAdd_clicked();

    void on_btnCusClassEdit_clicked();

    void on_tbCusClass_cellDoubleClicked(int, int);


    void on_btnDebitEdit_clicked();

    void on_btnDebitAdd_clicked();

    void on_tbDebit_cellDoubleClicked(int, int);

private:
    Ui::LayerCustomerSetting *ui;

         QVariantList m_listCustomer;

         QVariantList m_listDebit;

         DataRate m_primeRate;
};

#endif // LAYERCUSTOMERSETTING_H
