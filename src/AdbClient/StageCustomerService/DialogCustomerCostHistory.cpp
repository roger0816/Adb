#include "DialogCustomerCostHistory.h"
#include "ui_DialogCustomerCostHistory.h"

DialogCustomerCostHistory::DialogCustomerCostHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomerCostHistory)
{
    ui->setupUi(this);
}

DialogCustomerCostHistory::~DialogCustomerCostHistory()
{
    delete ui;
}

void DialogCustomerCostHistory::showEvent(QShowEvent *)
{
    QTimer::singleShot(50,this,[=](){refresh();});
}

void DialogCustomerCostHistory::setCustomer(CustomerData data)
{
    m_cus = data;
}

void DialogCustomerCostHistory::refresh()
{
   // ACTION.action(ACT::QUERY_CUSTOMER,)
}
