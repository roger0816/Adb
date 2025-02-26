#include "LayerAddValueType.h"
#include "ui_LayerAddValueType.h"

LayerAddValueType::LayerAddValueType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddValueType)
{
    ui->setupUi(this);
    ui->tb->setColumnWidth(0,60);
    ui->tb->setColumnWidth(1,200);
    ui->tb->setColumnWidth(2,120);
}

LayerAddValueType::~LayerAddValueType()
{
    delete ui;
}

void LayerAddValueType::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}

void LayerAddValueType::refresh()
{
    QVariantMap in;
    m_listData.clear();

    QString sError;
    in["ASC"]="Sort";
    ACTION.action(ACT::QUERY_PAY_TYPE,in,m_listData,sError);

    ui->tb->setRowCount(0);


    DataRate primeRate =DATA.primeRate("");


    for(int i=0;i<m_listData.length();i++)
    {
        ui->tb->setRowCount(i+1);
        DataPayType data(m_listData.at(i).toMap());

        ui->tb->setItem(i,0,UI.tbItem(data.Sort));

        ui->tb->setItem(i,1,UI.tbItem(data.Name));

        ui->tb->setItem(i,2,UI.tbItem(data.Currency));

        QString sPrimeRate = QString::number(primeRate.findValue(data.Currency),'f',3);

        ui->tb->setItem(i,3,UI.tbItem(sPrimeRate));

        ui->tb->setItem(i,5,UI.tbItem(data.SubValue.first()));

        ui->tb->setItem(i,6,UI.tbItem(data.Value[0]));
        ui->tb->setItem(i,7,UI.tbItem(data.Value[1]));
        ui->tb->setItem(i,8,UI.tbItem(data.Value[2]));
        ui->tb->setItem(i,9,UI.tbItem(data.Value[3]));

        double total = primeRate.findValue(data.Currency)
                *data.Value[0].toDouble()*data.Value[1].toDouble()
                *data.Value[2].toDouble()*data.Value[3].toDouble()
                /data.SubValue.first().toDouble();

        QString sTotal = QString::number(total,'f',3);
               ui->tb->setItem(i,4,UI.tbItem(sTotal));

    }

}

void LayerAddValueType::on_btnAdd_clicked()
{
    DialogAddValueTypeEdit dialog;

    DataRate rate =DATA.primeRate("");

//    if(list.length()<1)
//    {
//        DMSG.showMsg("","讀取不到成本匯率","OK");

//        return;

//    }

   // DataRate rate =list.last();

    dialog.setRate(rate.listKey(),rate.listValue());


    QString sError;

    if(dialog.exec()==1)
    {
        QVariantMap d = dialog.data();

        d["Sid"]="";

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

    DataRate rate =DATA.primeRate("");

//    if(list.length()<1)
//    {
//        DMSG.showMsg("","讀取不到成本匯率","OK");

//        return;

//    }

//    DataRate rate =list.last();

    dialog.setRate(rate.listKey(),rate.listValue());

    dialog.setData(data);



    QString sError;
     int iRet = dialog.exec();
    if(iRet==1)
    {
        QVariantMap d = dialog.data();

        d["Sid"]=data["Sid"];

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

