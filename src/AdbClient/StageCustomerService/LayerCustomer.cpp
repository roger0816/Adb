#include "LayerCustomer.h"
#include "ui_LayerCustomer.h"

LayerCustomer::LayerCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomer)
{
    ui->setupUi(this);
}

LayerCustomer::~LayerCustomer()
{
    delete ui;
}

void LayerCustomer::init()
{
    ui->btnEdit->setEnabled(false);

    QTimer::singleShot(50,this,SLOT(refresh()));
}

void LayerCustomer::on_btnAdd_clicked()
{
    DialogCustomerEdit dialog;

    QVariantList in,outClass,outGame;

    QString sError;

    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    dialog.setCb(outClass,outGame);


    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap data = dialog.data();

        data["UserSid"] =ACTION.m_currentUser.Sid;


        in=dialog.dataGameInfo();

        ACTION.action(ACT::REPLACE_GAME_INFO,in,sError);




        ACTION.action(ACT::ADD_CUSTOMER,data,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}

void LayerCustomer::refresh()
{
    ACTION.reQuerty();

    QString sError;

    QVariantList in;

    ACTION.action(ACT::QUERY_CUSTOMER,in,m_listData,sError);


    ui->tb->setRowCount(0);

    for(int i=0;i<m_listData.length();i++)
    {
        QVariantMap data = m_listData.at(i).toMap();

        ui->tb->setRowCount(i+1);

        ui->tb->setItem(i,0,UI.tbItem(data["Id"]));

        QString sClassSid = ACTION.getCustomerClass(data["Class"].toString()).Name;

        ui->tb->setItem(i,1,UI.tbItem(sClassSid));
        ui->tb->setItem(i,2,UI.tbItem(data["Name"]));

        ui->tb->setItem(i,3,UI.tbItem(data["Currency"]));
        ui->tb->setItem(i,4,UI.tbItem(data["Money"]));

        QDateTime updatetime =QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

        QString sUserName = ACTION.getUser(data["UserSid"].toString()).Name;

        ui->tb->setItem(i,7,UI.tbItem(updatetime));
        ui->tb->setItem(i,8,UI.tbItem(sUserName));
        ui->tb->setItem(i,9,UI.tbItem(data["Note1"]));

    }
}

void LayerCustomer::showEvent(QShowEvent *)
{

}


void LayerCustomer::on_btnEdit_clicked()
{
    DialogCustomerEdit dialog;

    QVariantList in,outClass,outGame,outGameInfo;

    QString sError;

    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,outGameInfo,sError);


    dialog.setData(outClass,outGame,outGameInfo,m_listData.at(ui->tb->currentRow()).toMap());


    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap data = dialog.data();

        data["UserSid"] =ACTION.m_currentUser.Sid;


        ACTION.action(ACT::REPLACE_GAME_INFO,dialog.dataGameInfo(),sError);
        ACTION.action(ACT::EDIT_CUSTOMER,data,sError);

        ACTION.action(ACT::DEL_GAME_INFO,dialog.deleteGameInfo(),sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
    else if(iRet==3)
    {
        QVariantMap data;

        data=dialog.data();


        ACTION.action(ACT::DEL_CUSTOMER,data,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}


void LayerCustomer::on_tb_cellPressed(int row, int column)
{
    ui->btnEdit->setEnabled(true);
}

