#include "LayerPrimeCostRate.h"
#include "ui_LayerPrimeCostRate.h"

LayerPrimeCostRate::LayerPrimeCostRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerPrimeCostRate)
{
    ui->setupUi(this);

    ui->tb1->setColumnWidth(0,50);
    ui->tb1->setColumnWidth(1,160);

    ui->tb1->setMouseTracking(true);

    //    QRegExp p("^([1-9][0-9]*)+(.[0-9]{1,3})?$");
    //   QRegExpValidator *r =new QRegExpValidator(p,this);
    ui->txUSD->setValidator(UI.regRate);

    ui->txHKD->setValidator(UI.regRate);

    ui->txRMB->setValidator(UI.regRate);
    ui->txMYR->setValidator(UI.regRate);

    ui->txSGD->setValidator(UI.regRate);

}

LayerPrimeCostRate::~LayerPrimeCostRate()
{
    delete ui;
}

void LayerPrimeCostRate::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}

void LayerPrimeCostRate::setExchangeType()
{
    m_bExchangeType =true;

    ui->tb0->setRowCount(0);

    ui->tb0->hide();

    ui->btnAdd->hide();

    ui->btnSub->hide();

}

void LayerPrimeCostRate::on_btnAdd_clicked()
{
    int iRowCount =ui->tb0->rowCount()+1;

    ui->tb0->setRowCount(iRowCount);
    QLineEdit *txt = new QLineEdit(ui->tb0);

    ui->tb0->setCellWidget(iRowCount-1,0,txt);

    //    QDoubleSpinBox *sb = new QDoubleSpinBox(ui->tb0);
    //    sb->setAlignment(Qt::AlignCenter);
    //    sb->setDecimals(3);
    //    sb->setRange(0,99999);
    //      ui->tb0->setCellWidget(iRowCount-1,1,sb);
    QLineEdit *rate=new QLineEdit(ui->tb0);
    rate->setAlignment(Qt::AlignCenter);
    rate->setValidator(UI.regRate);

    ui->tb0->setCellWidget(iRowCount-1,1,rate);




}

void LayerPrimeCostRate::refreshRate()
{
    ui->tb0->setRowCount(0);

    if(m_listRate.length()<1)
        return;

    QList<QPair<QString,QString> > list = m_listRate.last().listData;

    if(list.length()<6)
        return;

    int iRowCount = 0;

    for(int i=6;i<list.length();i++)
    {

        ui->tb0->setRowCount(++iRowCount);

        QLineEdit *txt = new QLineEdit(ui->tb0);
        txt->setText(list.at(i).first);
        ui->tb0->setCellWidget(iRowCount-1,0,txt);

        //        QDoubleSpinBox *sb = new QDoubleSpinBox(ui->tb0);
        //        sb->setAlignment(Qt::AlignCenter);
        //        sb->setDecimals(3);
        //        sb->setRange(0,99999);
        //        sb->setValue(list.at(i).second.toDouble());

        QLineEdit *rate=new QLineEdit(ui->tb0);
        rate->setAlignment(Qt::AlignCenter);
        rate->setValidator(UI.regRate);
        rate->setText(list.at(i).second);

        ui->tb0->setCellWidget(iRowCount-1,1,rate);

    }


}

void LayerPrimeCostRate::refreshTbDetail()
{
    ui->tb1->setRowCount(0);
    for(int i=0;i<m_listRate.length();i++)
    {

        DataRate rate = m_listRate.at(i);
        int iRow =ui->tb1->rowCount();
        ui->tb1->setRowCount(ui->tb1->rowCount()+1);

        ui->tb1->setItem(iRow,0,UI.tbItem(rate.Sid));

        // QStringList list=rate.data()["Name"].toString().split(";");

        CListPair listData = rate.listData;

        if(listData.length()>0)
            listData.pop_front();
        ui->tb1->setItem(iRow,1,UI.tbItem(QDateTime::fromString(rate.UpdateTime,"yyyyMMddhhmmss").toString("MM/dd hh:mm:ss")));
        QString sUserName = ACTION.getUser(rate.UserSid).Name;

        ui->tb1->setItem(iRow,2,UI.tbItem(sUserName));


        ui->tb1->setItem(iRow,3,UI.tbItem(listData.toString().replace(",,","="),GlobalUi::_TOOLTIP));



    }
}


void LayerPrimeCostRate::on_btnSub_clicked()
{
    if(ui->tb0->rowCount()==0)
        return;

    ui->tb0->setRowCount(ui->tb0->rowCount()-1);
}


void LayerPrimeCostRate::on_btnSave_clicked()
{
    CListPair list;

    CPair tmp("新台幣(NTD)","1");
    CPair tmp0(ui->lb0->text(),ui->txUSD->text());
    CPair tmp1(ui->lb1->text(),ui->txHKD->text());
    CPair tmp2(ui->lb2->text(),ui->txRMB->text());
    CPair tmp3(ui->lb3->text(),ui->txMYR->text());
    CPair tmp4(ui->lb4->text(),ui->txSGD->text());

    list<<tmp<<tmp0<<tmp1<<tmp2<<tmp3<<tmp4;

    for(int i=0;i<ui->tb0->rowCount();i++)
    {
        QString key,value;

        key =  dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,0))->text();

        if(key.trimmed()=="")
            continue;

        value =  dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,1))->text();

        QPair< QString,QString > tmp(key,value);

        list.append(tmp);
    }

    DataRate rate;

    rate.listData = list;

    rate.UserSid = ACTION.m_currentUser.Sid;

    QString sError;

    ACTION.addRate(rate.data(),sError,m_bExchangeType);

    UI.showMsg("",sError,"OK");

    reLineEdit();

    refreshRate();

    refreshTbDetail();
}

void LayerPrimeCostRate::reLineEdit()
{
    //    m_listRate =ACTION.listRate("",true,m_bExchangeType);

    //    if(m_listRate.length()>0)
    //    {




    DataRate rate = ACTION.primeRate("",true);

    if(m_bExchangeType)
        rate = ACTION.costRate("",true);

    ui->txUSD->setText(QString::number(rate.USD()));
    ui->txHKD->setText(QString::number(rate.HKD()));

    ui->txRMB->setText(QString::number(rate.RMB()));
    ui->txMYR->setText(QString::number(rate.MYR()));
    ui->txSGD->setText(QString::number(rate.SGD()));


    //  }

}




void LayerPrimeCostRate::on_tb1_itemEntered(QTableWidgetItem *item)
{

    int row = item->row();
    int column = item->column();

    if(row<0 || row>=ui->tb1->rowCount())
        return;

    if(column==3)
    {

        QString st = item->text().replace(";","\n").replace("="," : ");

        QToolTip::showText(QCursor::pos(),st);

    }
    else
    {
        // QToolTip::hideText();
    }

}

void LayerPrimeCostRate::refresh()
{
    reLineEdit();

    refreshRate();

    refreshTbDetail();
}

