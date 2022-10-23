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
    // QTimer::singleShot(50,this,[=](){refresh();});
}

void DialogCustomerCostHistory::setCustomer(CustomerData data)
{
    m_cus = data;

    ui->lbId->setText(m_cus.Id);
    ui->lbClass->setText(m_cus.Class);
    ui->lbName->setText(m_cus.Name);
    ui->lbCurrency->setText(m_cus.Currency);
    ui->lbMoney->setText(m_cus.Money);
    ACTION.costRate("",true);
    refresh();

}

void DialogCustomerCostHistory::refresh()
{

    QVariantMap in;

    in["CustomerSid"]=m_cus.Sid;

    QVariantList out;

    QString sError;


    ACTION.action(ACT::QUERY_CUSTOMER_COST,in,out,sError);

    m_listAddCost = out;

    ACTION.action(ACT::QUERY_ORDER,in,out,sError);

    m_listOrder = out;

    mergeData();



}

void DialogCustomerCostHistory::mergeData()
{
    //merge cost and order  for table data


    foreach(QVariant v, m_listAddCost)
    {
        CustomerCost d(v.toMap());
        //key is row index
        QVariantMap re;


        QString sSid=d.Sid;

        while(sSid.length()<6)
            sSid="0"+sSid;

        re["0"] =sSid;

        re["1"] ="加值";

        re["2"]=d.ChangeValue;

        QString sTmpRate =  QString::number(ACTION.costRate(d.Rate,false).findValue(d.Currency));

        if(d.AddRate.toInt()!=0)
            sTmpRate+="+"+d.AddRate;
        re["3"] = sTmpRate;


    }
}
