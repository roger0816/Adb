#ifndef DIALOGCUSTOMERCOSTHISTORY_H
#define DIALOGCUSTOMERCOSTHISTORY_H

#include <QDialog>
#include <QShowEvent>
#include <QButtonGroup>
#include "Global.h"
#include "GlobalUi.h"
#include "ItemPic.h"

namespace Ui {
class DialogCustomerCostHistory;
}

class DialogCustomerCostHistory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCustomerCostHistory(QWidget *parent = nullptr);
    ~DialogCustomerCostHistory();



    void showEvent(QShowEvent *) override;

    void setCustomer(CustomerData data);
private slots:
    void btnCustomerHistory();



    void on_tableWidget_cellClicked(int row, int column);
 void refresh(int =-1);
private:



    QVariantList filterData();

    void mergeData();
    Ui::DialogCustomerCostHistory *ui;

    CustomerData m_cus;


    QVariantList m_listOrder;
    QVariantList m_listAddCost;

    QVariantList m_listRowData;

    QButtonGroup m_btns;

    QDialog *m_dialogPic = new QDialog();
    ItemPic *m_itemPic  = new ItemPic(m_dialogPic);



};

#endif // DIALOGCUSTOMERCOSTHISTORY_H
