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


    changePage(0);
}

LayerSearchCustomer::~LayerSearchCustomer()
{
    delete ui;
}

void LayerSearchCustomer::init()
{

    ui->stackedWidget->setCurrentWidget(ui->page0);

    QTimer::singleShot(50,[this](){ refresh(true); });
}

void LayerSearchCustomer::refresh(bool bReQuery)
{
    qDebug()<<"refresh serachCustomer";


    QVariantList in;

    QString sError;
    if(bReQuery)
        ACTION.action(ACT::QUERY_CUSTOMER,in,m_listData,sError);

    qDebug()<<"CUSTOMER len : "<<m_listData.length();

    ui->tb->setRowCount(0);

    for(int i=0;i<m_listData.length();i++)
    {
        QVariantMap v = m_listData.at(i).toMap();

        CustomerData data(v);

        bool bCheck = checkSearch(data);

        if(!bCheck)
            continue;

        int iIdx = ui->tb->rowCount();

        ui->tb->setRowCount(iIdx+1);


        ui->tb->setItem(iIdx,0,UI.tbItem("進入",GlobalUi::_BUTTON));

        ui->tb->setItem(iIdx,1,UI.tbItem(data.Id));
        qDebug()<<"data class : "<<data.Class;
        QString sClassName = ACTION.getCustomerClass(data.Class).Name;
        qDebug()<<"class 2 "<<sClassName;
        ui->tb->setItem(iIdx,2,UI.tbItem(sClassName));

        ui->tb->setItem(iIdx,3,UI.tbItem(data.Name));

        QString sLv = GLOBAL.displayCustomerLv(data.Vip);

        ui->tb->setItem(iIdx,4,UI.tbItem(sLv));

        ui->tb->setItem(iIdx,5,UI.tbItem(data.Currency));

        ui->tb->setItem(iIdx,6,UI.tbItem(data.PayInfo));

        QDateTime date=QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss");

        ui->tb->setItem(iIdx,7,UI.tbItem(date.date()));

        //   ui->tb->setItem(iIdx,8,UI.tbItem("查詢",GlobalUi::_BUTTON));

    }


}

void LayerSearchCustomer::changePage(int iPage)
{
    if(iPage<0 || m_iIdx<0 || iPage>=ui->stackedWidget->count())
        return;


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

    if(iPage==1)
    {

        ui->lbClass->setText(ACTION.getCustomerClass(customer.Class).Name);

        ui->lbId->setText(customer.Id);

        ui->lbName->setText(customer.Name);

        ui->lbCurrency->setText(customer.Currency);

        ui->lbPayType->setText(customer.PayType);

        ui->lbPayInfo->setText(customer.PayInfo);

        ui->lbMoney->setText(customer.Money);

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

    }

    else if(iPage==3)
    {
        ui->pageAddCost->setCustomer(customer.data());


    }

    else if(iPage==4)
    {


        if(order.Step!="0" || order.Sid=="")
        {
            UI.showMsg("","沒預先報價流程，請先進行報價",QStringList()<<"OK");

            return ;
        }


        ui->pageOrder->setCustomer(customer.data());


    }

    ui->stackedWidget->setCurrentIndex(iPage);


}

void LayerSearchCustomer::showEvent(QShowEvent *)
{
    QTimer::singleShot(50,[this](){ refresh(false); });
}

bool LayerSearchCustomer::checkSearch(CustomerData data)
{
    if(m_sSearchKey.trimmed()=="")
        return true;

    QStringList listKey = m_sSearchKey.split("&");


    bool bRe = false;

    QList<int> listOk;

    foreach(QString v, listKey)
    {
        int iOk = 0;
        QString dateTime=QDateTime::fromString("yyyyMMddhhmmss").toString("yyyy/MM/dd hh:mm:ss");

        QString sKey = v.toUpper().trimmed();
        //  if(data["Name"].toString().indexOf(m_sSearchKey,Qt::CaseInsensitive)>=0)
        //奇怪，Qt::CaseInsensitive 不起作用
        if(data.Name.toUpper().contains(sKey))
            iOk = 1;
        else if(data.Id.toUpper().contains(sKey))
            iOk =1;
        else if(data.Currency.toUpper().contains(sKey))
            iOk =1;
        else if(data.PayInfo.toUpper().contains(sKey))
            iOk =1;
        else if(dateTime.toUpper().contains(sKey))
            iOk =1;

        listOk.append(iOk);
    }

    bRe = !listOk.contains(0);

    return bRe;
}

void LayerSearchCustomer::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
        on_btnCheck_clicked();
    }
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
    if(row<0 || row>=m_listData.length())
        return;

    if(column==0)
    {
        m_iIdx = row;

        changePage(1);
    }
    else if(column==6)
    {
        QVariantMap v = m_listData.at(row).toMap();

        DialogCustomerCostHistory dialog;

        dialog.setCustomer(CustomerData(v));

        dialog.exec();
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


void LayerSearchCustomer::on_btnDetail_clicked()
{
    CustomerData customer(m_listData.at(m_iIdx).toMap());
    DialogCustomerEdit dialog;

    dialog.setData(customer.Sid);

    dialog.setReadOnly(true);

    dialog.exec();
}

