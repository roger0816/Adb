#ifndef LAYERSEARCHCUSTOMER_H
#define LAYERSEARCHCUSTOMER_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QDateTime>
namespace Ui {
class LayerSearchCustomer;
}

class LayerSearchCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSearchCustomer(QWidget *parent = nullptr);
    ~LayerSearchCustomer();

private slots:
    void on_btnCheck_clicked();

    void on_btnClear_clicked();

    void on_tb_cellClicked(int row, int column);

    void on_btnBack_clicked();

    void on_btnSayCost_clicked();

    void on_btnOrder_clicked();

    void on_btnAddCost_clicked();

private:
    Ui::LayerSearchCustomer *ui;

    void refresh(bool bReQuery = true);

    void changePage(int iPage);

    void showEvent(QShowEvent *) override;

    QVariantList m_listData;

    bool checkSearch(QVariantMap data);

    QString m_sSearchKey="";

    int m_iIdx=-1;

public slots:
    void slotBack();
};

#endif // LAYERSEARCHCUSTOMER_H
