#include "LayerSearchCustomer.h"
#include "ui_LayerSearchCustomer.h"

LayerSearchCustomer::LayerSearchCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSearchCustomer)
{
    ui->setupUi(this);

    ui->tb->setColumnWidth(0,60);


    ui->tb->setColumnWidth(7,60);

    //ui->stackedWidget->setCurrentIndex(0);

    connect(ui->pageSayCost,SIGNAL(back(int)),this,SLOT(slotBack(int)));
    connect(ui->pageAddCost,SIGNAL(back(int)),this,SLOT(slotBack(int)));

    connect(ui->pageOrder,SIGNAL(back(int)),this,SLOT(slotBack(int)));

    ui->pageOrder->m_bOrderMode=true;

 //   changePage(0);
}

LayerSearchCustomer::~LayerSearchCustomer()
{
    delete ui;
}

void LayerSearchCustomer::refresh(bool bReQuery)
{
    qDebug()<<"refresh serachCustomer";

    if(m_bFirstShow)
    {

        changePage(0);

        m_bFirstShow = false;
    }



    QVariantList in;

    QString sError;
    if(bReQuery)
        ACTION.action(ACT::QUERY_CUSTOMER,in,m_listData,sError);

    ui->tb->setRowCount(0);

    for(int i=0;i<m_listData.length();i++)
    {
        QVariantMap data = m_listData.at(i).toMap();

        bool bCheck = checkSearch(data);

        if(!bCheck)
            continue;

        int iIdx = ui->tb->rowCount();

        ui->tb->setRowCount(iIdx+1);


        ui->tb->setItem(iIdx,0,UI.tbItem("進入",GlobalUi::_BUTTON));

        ui->tb->setItem(iIdx,1,UI.tbItem(data["Id"]));

        ui->tb->setItem(iIdx,2,UI.tbItem(data["Name"]));

        ui->tb->setItem(iIdx,3,UI.tbItem(data["Currency"]));

        ui->tb->setItem(iIdx,4,UI.tbItem(data["PayInfo"]));

        QDateTime date=QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

        ui->tb->setItem(iIdx,5,UI.tbItem(date.date()));

        ui->tb->setItem(iIdx,6,UI.tbItem("查詢",GlobalUi::_BUTTON));

    }


}

void LayerSearchCustomer::changePage(int iPage)
{
    if(iPage<0 || iPage>=ui->stackedWidget->count())
        return;

    QVariantList tmp;
    QString sError;

    ACTION.action(ACT::QUERY_CUSTOMER,tmp,m_listData,sError);


    if(iPage==1)
    {

        QVariantMap data = m_listData.at(m_iIdx).toMap();

        ui->lbClass->setText(ACTION.getCustomerClass(data["Class"].toString()).Name);

        ui->lbId->setText(data["Id"].toString());

        ui->lbName->setText(data["Name"].toString());

        ui->lbCurrency->setText(data["Currency"].toString());

        ui->lbPayType->setText(data["PayType"].toString());

        ui->lbPayInfo->setText(data["PayInfo"].toString());

        ui->lbMoney->setText(data["Money"].toString());

        QVariantMap d;

        d["CustomerId"] =data["Id"];
        QVariantList out;
        QString sError;
        ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,d,out,sError);

        if(out.length()>0)
        {
            QVariantMap dataGame = out.last().toMap();

            ui->lbGame->setText(ACTION.getGameName(dataGame["GameSid"].toString()));

            ui->lbLoginType->setText(dataGame["LoginType"].toString());

            ui->lbGameAccount->setText(dataGame["LoginAccount"].toString());

            ui->lbServer->setText(dataGame["ServerName"].toString());

            ui->lbChr->setText(dataGame["Character"].toString());


        }


    }
    else if(iPage==2)
    {
        ui->pageSayCost->setCustomer(m_listData.at(m_iIdx).toMap());

    }

    else if(iPage==3)
    {
        ui->pageAddCost->setCustomer(m_listData.at(m_iIdx).toMap());


    }

    else if(iPage==4)
    {
        CustomerData customer(m_listData.at(m_iIdx).toMap());

        OrderData order= ACTION.getOrderByCustomerSid(customer.Sid,true);


        if(order.Step!="0" || order.Sid=="")
        {
            UI.showMsg("","沒預先報價流程，請先進行報價",QStringList()<<"OK");

            return ;
        }


        ui->pageOrder->setCustomer(m_listData.at(m_iIdx).toMap());


    }

    ui->stackedWidget->setCurrentIndex(iPage);


}

void LayerSearchCustomer::showEvent(QShowEvent *)
{
    ui->stackedWidget->setCurrentWidget(ui->page0);

    QTimer::singleShot(50,[this](){ refresh(true); });
}

bool LayerSearchCustomer::checkSearch(QVariantMap data)
{
    if(m_sSearchKey.trimmed()=="")
        return true;

    bool bRe = false;

    if(data["Name"].toString().indexOf(m_sSearchKey)>=0)
        bRe = true;
    else if(data["Id"].toString().indexOf(m_sSearchKey)>=0)
        bRe =true;
    else if(data["Currency"].toString().indexOf(m_sSearchKey)>=0)
        bRe =true;
    else if(data["PayInfo"].toString().indexOf(m_sSearchKey)>=0)
        bRe =true;
    else if(data["UpdateTime"].toString().indexOf(m_sSearchKey)>=0)
        bRe =true;


    return bRe;
}

void LayerSearchCustomer::slotBack(int iPage)
{
    changePage(iPage);
}

void LayerSearchCustomer::on_btnCheck_clicked()
{
    m_sSearchKey = ui->txSearch->text();

    refresh();
}


void LayerSearchCustomer::on_btnClear_clicked()
{
    ui->txSearch->setText("");
    m_sSearchKey = ui->txSearch->text();

    refresh(false);
}


void LayerSearchCustomer::on_tb_cellClicked(int row, int column)
{
    if(column==0)
    {
        m_iIdx = row;


        changePage(1);
    }
}


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

