#include "LayerCustomerSetting.h"
#include "ui_LayerCustomerSetting.h"

LayerCustomerSetting::LayerCustomerSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomerSetting)
{
    ui->setupUi(this);

    ui->tbDebit->setColumnWidth(0,70);
}

LayerCustomerSetting::~LayerCustomerSetting()
{
    delete ui;
}

void LayerCustomerSetting::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}


void LayerCustomerSetting::refresh()
{


    m_primeRate= DATA.primeRate("");


    QVariantMap tmp;

    m_listCustomer.clear();


    QString sError;
    tmp["Type"] = "CustomerGroup";

    ACTION.action(ACT::QUERY_CUSTOM_CLASS,tmp,m_listCustomer,sError);

    ui->tbCusClass->setRowCount(0);


    for(int i=0;i<m_listCustomer.length();i++)
    {
        ui->tbCusClass->setRowCount(i+1);

        ui->tbCusClass->setItem(i,0,UI.tbItem(m_listCustomer.at(i).toMap()["Id"]));


        ui->tbCusClass->setItem(i,1,UI.tbItem(m_listCustomer.at(i).toMap()["Name"]));

    }


    m_listDebit.clear();
    ACTION.action(ACT::QUERY_DEBIT_CLASS,QVariantMap(),m_listDebit,sError);
    ui->tbDebit->setRowCount(0);


    for(int i=0;i<m_listDebit.length();i++)
    {
        ui->tbDebit->setRowCount(i+1);

        DebitClass data(m_listDebit.at(i).toMap());

        ui->tbDebit->setItem(i,0,UI.tbItem(data.Sort));
           ui->tbDebit->setItem(i,1,UI.tbItem(data.Currency));
        ui->tbDebit->setItem(i,2,UI.tbItem(data.Name));

    }


  /*

    m_listDebit.clear();

    tmp["Type"] = "Debit";
    tmp["ASC"]="Id";
    ACTION.action(ACT::QUERY_CUSTOM_DEBIT,tmp,m_listDebit,sError);

    ui->tbDebit->setRowCount(0);


    for(int i=0;i<m_listDebit.length();i++)
    {
        ui->tbDebit->setRowCount(i+1);

        ui->tbDebit->setItem(i,0,UI.tbItem(m_listDebit.at(i).toMap()["Id"]));

        ui->tbDebit->setItem(i,1,UI.tbItem(m_listDebit.at(i).toMap()["Name"]));

    }

    */



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
        QVariantMap input = dialog.data();
        //input["Type"]="CustomGroup";
        ACTION.action(ACT::ADD_CUSTOM_CLASS,input,sError);

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
        //  input["Type"]="CustomGroup";
        ACTION.action(ACT::EDIT_CUSTOM_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        //  input["Type"]="CustomGroup";
        ACTION.action(ACT::DEL_CUSTOM_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }

}

void LayerCustomerSetting::on_tbCusClass_cellDoubleClicked(int, int)
{
    on_btnCusClassEdit_clicked();
}

void LayerCustomerSetting::on_btnDebitAdd_clicked()
{
    DialogInput dialog;

    dialog.hideDelete();

    dialog.setTitle("支付管道");

    QVariantMap id;

    id["Sort"] =QString::number(m_listDebit.length()+1).toUInt();

    dialog.addInput("排序",id);

    QVariantMap name;

    name["Name"] ="";

    dialog.addInput("名稱",name);

     QVariantMap currency;
    currency["Currency"] = m_primeRate.listKey();
    dialog.addComboBox("幣別",currency);

    int ret  =  dialog.exec();

    QString sError;

    if(ret==1)
    {
        QVariantMap input = dialog.data();

        ACTION.action(ACT::ADD_DEBIT_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}

void LayerCustomerSetting::on_btnDebitEdit_clicked()
{
    int iRow = ui->tbDebit->currentRow();

    if(iRow<0 || iRow>= m_listDebit.length() )
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");
        return;
    }

    QString sError;

    QVariantMap data = m_listDebit.at(iRow).toMap();

    DialogInput dialog;

    dialog.setTitle("支付管道");

    QVariantMap d0,d1;

    d0["Sort"] = data["Sort"].toUInt();
    dialog.addInput("排序",d0);

    d1["Name"] =data["Name"];

    dialog.addInput("名稱",d1);

    QVariantMap currency;
   currency["Currency"] = m_primeRate.listKey();

   dialog.addComboBox("幣別",currency);

    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap input = dialog.data();
        input["Sid"] = data["Sid"];
        //  input["Type"]="Debit";
        ACTION.action(ACT::EDIT_DEBIT_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        ACTION.action(ACT::DEL_DEBIT_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}




void LayerCustomerSetting::on_tbDebit_cellDoubleClicked(int , int )
{
    on_btnDebitEdit_clicked();

}

