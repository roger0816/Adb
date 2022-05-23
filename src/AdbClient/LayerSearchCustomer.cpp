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

    connect(ui->page2,SIGNAL(back()),this,SLOT(slotBack()));

    changePage(0);
}

LayerSearchCustomer::~LayerSearchCustomer()
{
    delete ui;
}

void LayerSearchCustomer::refresh(bool bReQuery)
{
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


        ui->tb->setItem(iIdx,0,UI.tbItem("進入",true));

        ui->tb->setItem(iIdx,1,UI.tbItem(data["Id"]));

        ui->tb->setItem(iIdx,2,UI.tbItem(data["Name"]));

        ui->tb->setItem(iIdx,3,UI.tbItem(data["Money"]));

        ui->tb->setItem(iIdx,4,UI.tbItem(data["Currency"]));

        ui->tb->setItem(iIdx,5,UI.tbItem(data["PayInfo"]));

        QDateTime date=QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

        ui->tb->setItem(iIdx,6,UI.tbItem(date.date()));

        ui->tb->setItem(iIdx,7,UI.tbItem("查詢",true));

    }


}

void LayerSearchCustomer::changePage(int iPage)
{
    ui->stackedWidget->setCurrentIndex(iPage);

    if(iPage==1)
    {
        QVariantMap data = m_listData.at(m_iIdx).toMap();

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
        ACTION.action(ACT::QUERY_GAME_INFO,d,out,sError);

        if(out.length()>0)
        {
            QVariantMap dataGame = out.last().toMap();

            ui->lbGame->setText(DATA.getGameName(dataGame["GameSid"].toString()));

            ui->lbLoginType->setText(dataGame["LoginType"].toString());

            ui->lbGameAccount->setText(dataGame["LoginAccount"].toString());

            ui->lbServer->setText(dataGame["ServerName"].toString());

            ui->lbChr->setText(dataGame["Character"].toString());


        }


    }
    else if(iPage==2)
    {
        ui->page2->setCustomer(m_listData.at(m_iIdx).toMap());


        ui->stackedWidget->setCurrentWidget(ui->page2);
    }

    else if(iPage==3)
    {

        ui->stackedWidget->setCurrentWidget(ui->page3);
    }

    else if(iPage==4)
    {
        ui->page4->setCustomer(m_listData.at(m_iIdx).toMap());


        ui->stackedWidget->setCurrentWidget(ui->page4);
    }


}

void LayerSearchCustomer::showEvent(QShowEvent *)
{
    refresh();
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

void LayerSearchCustomer::slotBack()
{


    if( dynamic_cast<QWidget*>(sender())==ui->page2)
        ui->stackedWidget->setCurrentWidget(ui->page1);
}

void LayerSearchCustomer::on_btnCheck_clicked()
{
    m_sSearchKey = ui->txSearch->text();

    refresh();
}


void LayerSearchCustomer::on_btnClear_clicked()
{
    ui->txSearch->setText("");

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

