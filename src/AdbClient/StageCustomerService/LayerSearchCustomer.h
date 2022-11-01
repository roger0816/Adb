#ifndef LAYERSEARCHCUSTOMER_H
#define LAYERSEARCHCUSTOMER_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QDateTime>
#include "DialogCustomerEdit.h"
#include "DialogCustomerCostHistory.h"
#include <QKeyEvent>
namespace Ui {
class LayerSearchCustomer;
}

class LayerSearchCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSearchCustomer(QWidget *parent = nullptr);
    ~LayerSearchCustomer();

    void init();

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

    void changePage(int iPage);

    void showEvent(QShowEvent *) override;

    QVariantList m_listData;

    bool checkSearch(CustomerData data);

    QString m_sSearchKey="";

    int m_iIdx=-1;

    void keyPressEvent(QKeyEvent *e) override;

    QString getLastGame(QString sCustomerId);

public slots:
    void slotBack(int iPage=0);

private slots:
    void refresh(bool bReQuery = true);
    void on_btnHistory_clicked();
    void on_btnDetail_clicked();
};

#endif // LAYERSEARCHCUSTOMER_H
