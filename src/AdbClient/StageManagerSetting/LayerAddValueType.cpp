#include "LayerAddValueType.h"
#include "ui_LayerAddValueType.h"

LayerAddValueType::LayerAddValueType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddValueType)
{
    ui->setupUi(this);

    ui->tb->setColumnWidth(0,200);
}

LayerAddValueType::~LayerAddValueType()
{
    delete ui;
}

void LayerAddValueType::showEvent(QShowEvent *)
{
    refresh();
}

void LayerAddValueType::refresh()
{
    QVariantMap in;
    m_listData.clear();
    QString sError;
    ACTION.action(ACT::QUERY_ADDVALUE_TYPE,in,m_listData,sError);

    ui->tb->setRowCount(0);

    for(int i=0;i<m_listData.length();i++)
    {
        ui->tb->setRowCount(i+1);
        QVariantMap data = m_listData.at(i).toMap();

        ui->tb->setItem(i,0,UI.tbItem(data["Name"].toString()));

        QStringList list = data["Value"].toString().split(";");

        while(list.length()<16)
            list.append("0");

        for(int j=0;j<16;j++)
        {
            ui->tb->setItem(i,j+1,UI.tbItem(list.at(j)));
        }

    }

}

void LayerAddValueType::on_btnAdd_clicked()
{
    DialogAddValueTypeEdit dialog;

    QString sError;

    if(dialog.exec()==1)
    {
        QVariantMap d;

        d["Sid"]="";

        d["Name"]=dialog.Name();

        d["Value"] =dialog.data().join(";");

        ACTION.action(ACT::ADD_ADDVALUE_TYPE,d,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}




void LayerAddValueType::on_btnEdit_clicked()
{
    if(ui->tb->currentRow()<0 || ui->tb->currentRow()>=m_listData.length())
    {
        UI.showMsg("","請先選擇編輯的目標","OK");
        return;
    }
    QVariantMap data = m_listData.at(ui->tb->currentRow()).toMap();

    DialogAddValueTypeEdit dialog;

    dialog.setName(data["Name"].toString());

    dialog.setData(data["Value"].toString().split(";"));
    QString sError;
     int iRet = dialog.exec();
    if(iRet==1)
    {
        QVariantMap d;

        d["Sid"]=data["Sid"];

        d["Name"]=dialog.Name();

        d["Value"] =dialog.data().join(";");

        ACTION.action(ACT::EDIT_ADDVALUE_TYPE,d,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }

    if(iRet==3)
    {
        QVariantMap d;

        d["Sid"]=data["Sid"];

        ACTION.action(ACT::DEL_ADDVALUE_TYPE,d,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}

