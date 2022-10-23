#ifndef DIALOGCUSTOMERCOSTHISTORY_H
#define DIALOGCUSTOMERCOSTHISTORY_H

#include <QDialog>
#include <QShowEvent>
#include "Global.h"
#include "GlobalUi.h"

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
private:

    void refresh();
    Ui::DialogCustomerCostHistory *ui;

    CustomerData m_cus;
};

#endif // DIALOGCUSTOMERCOSTHISTORY_H
