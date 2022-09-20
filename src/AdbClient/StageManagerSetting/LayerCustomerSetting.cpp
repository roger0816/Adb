#include "LayerCustomerSetting.h"
#include "ui_LayerCustomerSetting.h"

LayerCustomerSetting::LayerCustomerSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomerSetting)
{
    ui->setupUi(this);
}

LayerCustomerSetting::~LayerCustomerSetting()
{
    delete ui;
}

void LayerCustomerSetting::refresh()
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

void LayerCustomerSetting::showEvent(QShowEvent *)
{
    refresh();
}

void LayerCustomerSetting::on_btnCusClassAdd_clicked()
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

        refresh();
    }
}

void LayerCustomerSetting::on_btnCusClassEdit_clicked()
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

        refresh();
    }
    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        ACTION.action(ACT::DEL_CUSTOM_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }

}

void LayerCustomerSetting::on_tbCusClass_cellDoubleClicked(int, int)
{
    on_btnCusClassEdit_clicked();
}
