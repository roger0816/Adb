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
    ACTION.action(ACT::QUERY_PAY_TYPE,in,m_listData,sError);

    ui->tb->setRowCount(0);

    for(int i=0;i<m_listData.length();i++)
    {
        ui->tb->setRowCount(i+1);
        QVariantMap data = m_listData.at(i).toMap();

        ui->tb->setItem(i,0,UI.tbItem(data["Name"].toString()));

        QStringList list = data["Value"].toString().split(";");

        while(list.length()<9)
            list.append("0");

        ui->tb->setItem(i,1,UI.tbItem(list.at(8)));
        ui->tb->setItem(i,2,UI.tbItem(list.at(7)));
        ui->tb->setItem(i,3,UI.tbItem(list.at(0)));
        ui->tb->setItem(i,4,UI.tbItem(list.at(1)));
        ui->tb->setItem(i,5,UI.tbItem(list.at(2)));
        ui->tb->setItem(i,6,UI.tbItem(list.at(3)));
        ui->tb->setItem(i,7,UI.tbItem(list.at(4)));
        ui->tb->setItem(i,8,UI.tbItem(list.at(5)));
        ui->tb->setItem(i,9,UI.tbItem(list.at(6)));

       // ui->tb->setItem(i,j+1,UI.tbItem(list.at(j)));


//        for(int j=0;j<16;j++)
//        {
//            ui->tb->setItem(i,j+1,UI.tbItem(list.at(j)));
//        }

    }

}

void LayerAddValueType::on_btnAdd_clicked()
{
    DialogAddValueTypeEdit dialog;

    QList<DataRate> list =ACTION.listRate("",true,false);

    if(list.length()<1)
    {
        DMSG.showMsg("","讀取不到成本匯率","OK");

        return;

    }

    DataRate rate =list.last();

    dialog.setRate(rate.listKey(),rate.listValue());


    QString sError;

    if(dialog.exec()==1)
    {
        QVariantMap d;

        d["Sid"]="";

        d["Name"]=dialog.Name();

        d["Value"] =dialog.data().join(";");

        ACTION.action(ACT::ADD_PAY_TYPE,d,sError);

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

    QList<DataRate> list =ACTION.listRate("",true,false);

    if(list.length()<1)
    {
        DMSG.showMsg("","讀取不到成本匯率","OK");

        return;

    }

    DataRate rate =list.last();

    dialog.setRate(rate.listKey(),rate.listValue());


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

        ACTION.action(ACT::EDIT_PAY_TYPE,d,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }

    if(iRet==3)
    {
        QVariantMap d;

        d["Sid"]=data["Sid"];

        ACTION.action(ACT::DEL_PAY_TYPE,d,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}

