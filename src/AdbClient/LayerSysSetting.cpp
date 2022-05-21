#include "LayerSysSetting.h"
#include "ui_LayerSysSetting.h"

LayerSysSetting::LayerSysSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSysSetting)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

LayerSysSetting::~LayerSysSetting()
{
    delete ui;
}

void LayerSysSetting::on_btnBulletinAdd_clicked()
{
    DialogBulletinEdit dialog;


    if(dialog.exec()==1)
    {
        QString sError;

        QVariantMap data = dialog.data();

        data["UserSid"] = ACTION.m_currentUser.Sid.toInt();

        ACTION.action(ACT::ADD_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }

}

void LayerSysSetting::showEvent(QShowEvent *)
{



    refreshBulletin();

    refreshCustomer();

    refreshFactory();
}

void LayerSysSetting::refreshBulletin()
{

    m_listBulletin.clear();

    QVariantList tmp;

    QString sError;

    ACTION.action(ACT::QUERY_BULLETIN,tmp,m_listBulletin,sError);

    ui->tbBulletin->setRowCount(0);



    for(int i=0;i<m_listBulletin.length();i++)
    {


        ui->tbBulletin->setRowCount(i+1);


        QVariantMap data = m_listBulletin.at(i).toMap();

        QVariantMap v;
        v["Sid"] = data["UserSid"];

        QVariantList listUser;
        ACTION.action(ACT::QUERY_USER,v,listUser,sError);

        UserData user(listUser.first().toMap());

        ui->tbBulletin->setItem(i,0,UI.tbItem(user.Name));

        ui->tbBulletin->setItem(i,1,UI.tbItem(QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss")));

        ui->tbBulletin->setItem(i,2,UI.tbItem(data["Title"]));

        ui->tbBulletin->setItem(i,3,UI.tbItem(data["Content"]));


    }
}

void LayerSysSetting::refreshCustomer()
{
    QVariantMap tmp;

    m_listCustomer.clear();

    QString sError;

    ACTION.action(ACT::QUERY_CUSTOM_CLASS,tmp,m_listCustomer,sError);

    ui->tbCusClass->setRowCount(0);


    for(int i=0;i<m_listCustomer.length();i++)
    {
        ui->tbCusClass->setRowCount(i+1);

        ui->tbCusClass->setItem(i,0,UI.tbItem(m_listCustomer.at(i).toMap()["Id"]));


        ui->tbCusClass->setItem(i,1,UI.tbItem(m_listCustomer.at(i).toMap()["Name"]));

    }



}

void LayerSysSetting::refreshFactory()
{
    QVariantMap tmp;

    m_listFactory.clear();

    QString sError;

    ACTION.action(ACT::QUERY_FACTORY_CLASS,tmp,m_listFactory,sError);

    ui->tbFactory->setRowCount(0);


    for(int i=0;i<m_listFactory.length();i++)
    {
        ui->tbFactory->setRowCount(i+1);

        ui->tbFactory->setItem(i,0,UI.tbItem(m_listFactory.at(i).toMap()["Id"]));


        ui->tbFactory->setItem(i,1,UI.tbItem(m_listFactory.at(i).toMap()["Name"]));

    }

}


void LayerSysSetting::on_tbBulletin_cellDoubleClicked(int row, int column)
{
    on_btnBulletinEdit_clicked();
}


void LayerSysSetting::on_btnBulletinEdit_clicked()
{

    int iRow = ui->tbBulletin->currentRow();

    if(iRow<0 || iRow >= m_listBulletin.length())
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");

        return;
    }

    DialogBulletinEdit dialog;

    dialog.setData(m_listBulletin.at(iRow).toMap());

    int iRet =dialog.exec();
    if(iRet==1)
    {
        QString sError;

        QVariantMap data = dialog.data();

        data["UserSid"] = ACTION.m_currentUser.Sid.toInt();

        ACTION.action(ACT::EDIT_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }
    else if(iRet==3)
    {
        QString sError;

        QVariantMap data;

        data["Sid"]= dialog.data()["Sid"];

        ACTION.action(ACT::DEL_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }

}





void LayerSysSetting::on_btnCusClassAdd_clicked()
{
    DialogInput dialog;

    dialog.setTitle("客戶分類");

    QVariantMap id,name;

    id["Id"] = "";

    name["Name"] ="";

    dialog.addInput("代碼",id);

    dialog.addInput("名稱",name);

    int ret  =  dialog.exec();

    QString sError;

    if(ret==1)
    {
        QVariantMap d;

        ACTION.action(ACT::ADD_CUSTOM_CLASS,dialog.data(),sError);

        UI.showMsg("",sError,"OK");

        refreshCustomer();
    }
}


void LayerSysSetting::on_btnCusClassEdit_clicked()
{
    int iRow = ui->tbCusClass->currentRow();

    if(iRow<0 || iRow>= m_listCustomer.length() )
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");
        return;
    }

    QString sError;

    QVariantMap data = m_listCustomer.at(iRow).toMap();

    DialogInput dialog;

    dialog.setTitle("客戶分類");

    QVariantMap d0;

    d0["Id"] =data["Id"];

    dialog.addInput("代碼",d0);

    QVariantMap d1;

    d1["Name"] =data["Name"];

    dialog.addInput("名稱",d1);

    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap input = dialog.data();
        input["Sid"] = data["Sid"];

        ACTION.action(ACT::EDIT_CUSTOM_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refreshCustomer();
    }
    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        ACTION.action(ACT::DEL_CUSTOM_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refreshCustomer();
    }


}


void LayerSysSetting::on_tbCusClass_cellDoubleClicked(int , int )
{
    on_btnCusClassEdit_clicked();
}


void LayerSysSetting::on_btnFactoryAdd_clicked()
{
    DialogInput dialog;

    dialog.setTitle("廠商類型");


    QVariantMap id,name;

    id["Id"] = "";

    name["Name"] ="";

    dialog.addInput("代號",id);

    dialog.addInput("名稱",name);

    int ret  =  dialog.exec();

    QString sError;

    if(ret==1)
    {
        QVariantMap d;

        ACTION.action(ACT::ADD_FACTORY_CLASS,dialog.data(),sError);

        UI.showMsg("",sError,"OK");

        refreshFactory();
    }
}


void LayerSysSetting::on_btnFactoryEdit_clicked()
{
    int iRow = ui->tbFactory->currentRow();

    if(iRow<0 || iRow>= m_listFactory.length() )
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");
        return;
    }

    QString sError;

    QVariantMap data = m_listFactory.at(iRow).toMap();

    DialogInput dialog;

    dialog.setTitle("廠商類型");

    QVariantMap d0;

    d0["Id"] =data["Id"];

    dialog.addInput("代號",d0);

    QVariantMap d1;

    d1["Name"] =data["Name"];

    dialog.addInput("名稱",d1);

    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap input = dialog.data();
        input["Sid"] = data["Sid"];

        ACTION.action(ACT::EDIT_FACTORY_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refreshFactory();
    }
    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        ACTION.action(ACT::DEL_FACTORY_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refreshFactory();
    }

}

