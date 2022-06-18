#include "LayerDayReport.h"
#include "ui_LayerDayReport.h"

LayerDayReport::LayerDayReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayReport)
{
    ui->setupUi(this);

    m_detialOrder = new LayerSayCost;
      m_detialOrder->m_bOrderMode = true;
    m_detialOrder->setReadOnly();
    m_detialOrder->hide();
    ui->tb->hideColumn(2);

    ui->tb->setColumnWidth(1,140);
    ui->tb->setColumnWidth(3,60);
    ui->tb->setColumnWidth(4,60);
    ui->tb->setColumnWidth(5,80);
    ui->tb->setColumnWidth(6,80);
    ui->tb->setColumnWidth(7,70);
    ui->tb->setColumnWidth(9,60);
    ui->tb->setColumnWidth(11,80);
    //   ui->tb->setColumnWidth(7,80);
}

LayerDayReport::~LayerDayReport()
{
    if(m_detialOrder!=nullptr)
    {
        m_detialOrder->hide();
        delete m_detialOrder;
    }

    delete ui;
}

void LayerDayReport::showEvent(QShowEvent *)
{
    ui->dateEdit->setDate(QDate::currentDate());

    refreshTb();
}

void LayerDayReport::refreshTb()
{
    m_listOrder = ACTION.getOrder(true);

    ui->tb->setRowCount(0);
    QString sError;

    m_listInto.clear();

    for(int i=0;i<m_listOrder.length();i++)
    {
        OrderData data = m_listOrder.at(i);
        if(checkFilter(data))
        {

            m_listInto.append(data);
            int iRow = ui->tb->rowCount();
            ui->tb->setRowCount(iRow+1);

            ui->tb->setItem(iRow,0,UI.tbItem(data.Id));
            UserData owner =ACTION.getUser(data.Owner);

            QVariantMap d;
            d["Sid"] = data.CustomerSid;
            QVariantList listCustomer;
            ACTION.action(ACT::QUERY_CUSTOMER,d,listCustomer,sError);
            CustomerData customer(listCustomer.first().toMap());
            QString sDate=data.OrderDate+data.OrderTime;

            QDateTime date=QDateTime::fromString(sDate,"yyyyMMddhhmmss");
            ui->tb->setItem(iRow,1,UI.tbItem(date));
            ui->tb->setItem(iRow,2,UI.tbItem(""));


            ui->tb->setItem(iRow,3,UI.tbItem(owner.Id));
            ui->tb->setItem(iRow,4,UI.tbItem(data.Name));
            ui->tb->setItem(iRow,5,UI.tbItem(customer.Id));
            ui->tb->setItem(iRow,6,UI.tbItem("詳細",true));


            QString sStatus = data.Step;

            if(sStatus=="0")
            {
                sStatus+="報價";
            }
            if(sStatus=="1")
            {
                sStatus+="下單";
            }
            if(sStatus=="2")
            {
                sStatus+="待處理";
            }
            if(sStatus=="3")
            {
                sStatus+="待回報";
            }
            if(sStatus=="4")
            {
                sStatus+="主管確認";
            }
            if(sStatus=="5")
            {
                sStatus="訂單結束";
            }



            ui->tb->setItem(iRow,7,UI.tbItem(sStatus));
            ui->tb->setItem(iRow,8,UI.tbItem(data.Cost));
            ui->tb->setItem(iRow,9,UI.tbItem(customer.Currency));
            ui->tb->setItem(iRow,10,UI.tbItem(data.Bouns));
            if(data.Step=="4")
            {
                ui->tb->setItem(iRow,11,UI.tbItem("點擊確認",true));
            }
            else if(data.Step=="5")
            {
                ui->tb->setItem(iRow,11,UI.tbItem("已確認"));
            }
            else
            {
                ui->tb->setItem(iRow,11,UI.tbItem("流程未到"));
            }

        }

    }



}

bool LayerDayReport::checkFilter(OrderData order)
{
    QString step = order.Step;
    QString sDate = order.OrderDate;

    if(ui->dateEdit->date().toString("yyyyMMdd") != sDate)
        return false;

    if(step=="0" && !ui->cbStep0->isChecked())
        return false;
    if(step=="1" && !ui->cbStep1->isChecked())
        return false;
    if(step=="2" && !ui->cbStep2->isChecked())
        return false;
    if(step=="3" && !ui->cbStep3->isChecked())
        return false;
    if(step=="4" && !ui->cbStep4->isChecked())
        return false;
    if(step=="5" && !ui->cbStep5->isChecked())
        return false;


    return true;
}

void LayerDayReport::on_tb_cellPressed(int row, int column)
{
    if(row<0 || row>=m_listInto.length())
        return;

    if(column==6)
    {
        OrderData data = m_listInto.at(row);

        QVariantMap d;

        d["Sid"] = data.CustomerSid;


        m_detialOrder->setCustomer(d,data.Sid);

        m_detialOrder->raise();

        m_detialOrder->show();

        // layer.setReadOnly(data.Sid);

        //        DialogCommon dialog;

        //        dialog.setWidget(&layer);

        //        dialog.exec();
    }
}


void LayerDayReport::on_cbStep0_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep1_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep2_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep3_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep4_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep5_clicked()
{
    refreshTb();
}

