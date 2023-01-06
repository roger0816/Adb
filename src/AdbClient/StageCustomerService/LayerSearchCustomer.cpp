#include "LayerSearchCustomer.h"
#include "ui_LayerSearchCustomer.h"

LayerSearchCustomer::LayerSearchCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSearchCustomer)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->pageSayCost,SIGNAL(back(int)),this,SLOT(slotBack(int)));
    connect(ui->pageAddCost,SIGNAL(back(int)),this,SLOT(slotBack(int)));

    connect(ui->pageOrder,SIGNAL(back(int)),this,SLOT(slotBack(int)));

    ui->pageOrder->m_bOrderMode=true;

    connect(ui->page0,&LayerCustomer::into,[=](int iIdx)
    {
        m_iIdx = iIdx;

        changePage(1);
    });

    //  changePage(0);
}

LayerSearchCustomer::~LayerSearchCustomer()
{
    delete ui;
}

void LayerSearchCustomer::init()
{
    qDebug()<<"LayerSearchCustomer init";
    changePage(0);

    //ui->stackedWidget->setCurrentWidget(ui->page0);

    // QTimer::singleShot(50,[this](){ refresh(true); });
}


void LayerSearchCustomer::changePage(int iPage)
{
    qDebug()<<"AAAAAAAAAA"<<iPage;

    if(iPage<0 ||iPage>=ui->stackedWidget->count())
        return;

    if(iPage==0)
    {
        ui->page0->init();

        ui->stackedWidget->setCurrentIndex(iPage);

        return ;
    }
    else
    {
        if(m_iIdx<0)
            return;
    }


    QVariantList tmp;
    QString sError;

    ACTION.action(ACT::QUERY_CUSTOMER,tmp,m_listData,sError);


    if(m_listData.length()<1 && m_iIdx>=m_listData.length())
    {
        return;
    }

    CustomerData customer(m_listData.at(m_iIdx).toMap());

    OrderData order= ACTION.getOrderCustomerLast(customer.Sid,true);

    QString sLastGameSid=order.GameSid;
    qDebug()<<"lastGameSid : "<<sLastGameSid;

    qDebug()<<"page "<<iPage;





    if(iPage==1)
    {

        ui->lbClass->setText(ACTION.getCustomerClass(customer.Class).Name);

        ui->lbId->setText(customer.Id);

        ui->lbName->setText(customer.Name);

        ui->lbCurrency->setText(customer.Currency);

        ui->lbPayType->setText(customer.PayType);

        ui->lbPayInfo->setText(customer.PayInfo);

        ui->lbMoney->setText(ACTION.getCustomerNowMoney(customer.Sid));

        QVariantMap d;

        d["CustomerId"] =customer.Id;
        QVariantList out;
        QString sError;
        ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,d,out,sError);


        ui->lbGame->clear();
        ui->lbLoginType->clear();
        ui->lbGameAccount->clear();
        ui->lbServer->clear();
        ui->lbChr->clear();

        for(int i=0;i<out.length() && sLastGameSid!="";i++ )
        {
            CustomerGameInfo dataGame (out.at(i).toMap());


            if(dataGame.GameSid == sLastGameSid)
            {

                ui->lbGame->setText(ACTION.getGameName(dataGame.GameSid));

                ui->lbLoginType->setText(dataGame.LoginType);

                ui->lbGameAccount->setText(dataGame.LoginAccount);

                ui->lbServer->setText(dataGame.ServerName);

                ui->lbChr->setText(dataGame.Characters);

            }

        }





    }
    else if(iPage==2)
    {
        ui->pageSayCost->setCustomer(customer.data());

        ui->pageSayCost->init();

    }

    else if(iPage==3)
    {

        ui->pageAddCost->setCustomer(customer.data());

        ui->pageAddCost->init();
    }

    else if(iPage==4)
    {


        if(order.Step!="0" || order.Sid=="")
        {
            UI.showMsg("","沒預先報價流程，請先進行報價",QStringList()<<"OK");

            return ;
        }


        ui->pageOrder->setCustomer(customer.data());

        ui->pageOrder->init();


    }

    ui->stackedWidget->setCurrentIndex(iPage);


}

void LayerSearchCustomer::showEvent(QShowEvent *)
{

}


void LayerSearchCustomer::slotBack(int iPage)
{
    changePage(iPage);
}

//void LayerSearchCustomer::on_tb_cellClicked(int row, int column)
//{
//    if(row<0 || row>=m_listData.length())
//        return;

//    if(column==0)
//    {
//        m_iIdx = row;

//        changePage(1);
//    }
//    else if(column==6)
//    {
//        QVariantMap v = m_listData.at(row).toMap();

//        DialogCustomerCostHistory dialog;

//        dialog.setCustomer(CustomerData(v));

//        dialog.exec();
//    }
//}


void LayerSearchCustomer::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page0);
}


void LayerSearchCustomer::on_btnSayCost_clicked()
{
    changePage(2);
}


void LayerSearchCustomer::on_btnOrder_clicked()
{


    changePage(4);
}


void LayerSearchCustomer::on_btnAddCost_clicked()
{
    changePage(3);
}


void LayerSearchCustomer::on_btnHistory_clicked()
{
    DialogCustomerCostHistory dialog;
    CustomerData customer(m_listData.at(m_iIdx).toMap());
    dialog.setCustomer(customer);
    dialog.exec();
}


void LayerSearchCustomer::on_btnDetail_clicked()
{
    CustomerData customer(m_listData.at(m_iIdx).toMap());
    DialogCustomerEdit dialog;

    dialog.setData(customer.Sid);

    dialog.setReadOnly(true);

    dialog.exec();
}

