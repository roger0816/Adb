#include "LayerPrimeCostRate.h"
#include "ui_LayerPrimeCostRate.h"

LayerPrimeCostRate::LayerPrimeCostRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerPrimeCostRate)
{
    ui->setupUi(this);

    ui->tb1->setColumnWidth(0,40);
    ui->tb1->setColumnWidth(1,140);

    ui->lbX->hide();

    ui->sbNTD->hide();
}

LayerPrimeCostRate::~LayerPrimeCostRate()
{
    delete ui;
}

void LayerPrimeCostRate::showEvent(QShowEvent *)
{
    reLineEdit();

    refreshRate();

    refreshTbDetail();


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

    QDoubleSpinBox *sb = new QDoubleSpinBox(ui->tb0);
    sb->setAlignment(Qt::AlignCenter);
    sb->setDecimals(3);
    sb->setRange(0,99999);

    ui->tb0->setCellWidget(iRowCount-1,1,sb);


}

void LayerPrimeCostRate::refreshRate()
{
    ui->tb0->setRowCount(0);

    if(m_listRate.length()<1)
        return;

    QList<QPair<QString,QString> > list = m_listRate.last().listData;

    if(list.length()<7)
        return;

    int iRowCount = 0;

    for(int i=6;i<list.length();i++)
    {

        ui->tb0->setRowCount(++iRowCount);

        QLineEdit *txt = new QLineEdit(ui->tb0);
        txt->setText(list.at(i).first);
        ui->tb0->setCellWidget(iRowCount-1,0,txt);

        QDoubleSpinBox *sb = new QDoubleSpinBox(ui->tb0);
        sb->setAlignment(Qt::AlignCenter);
        sb->setDecimals(3);
        sb->setRange(0,99999);
        sb->setValue(list.at(i).second.toDouble());

        ui->tb0->setCellWidget(iRowCount-1,1,sb);

    }


}

void LayerPrimeCostRate::refreshTbDetail()
{
    ui->tb1->setRowCount(0);
    for(int i=0;i<m_listRate.length();i++)
    {

        PrimeRate rate = m_listRate.at(i);
        int iRow =ui->tb1->rowCount();
        ui->tb1->setRowCount(ui->tb1->rowCount()+1);

        ui->tb1->setItem(iRow,0,UI.tbItem(rate.Sid));

        QStringList list=rate.data()["Name"].toString().split(";");

        if(list.length()>0)
            list.pop_front();

        ui->tb1->setItem(iRow,2,UI.tbItem(list.join(";")));

        ui->tb1->setItem(iRow,1,UI.tbItem(QDateTime::fromString(rate.UpdateTime,"yyyyMMddhhmmss")));

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
    QList<QPair< QString,QString > > list;

    QPair< QString,QString > tmpX(ui->lbX->text(),QString::number(ui->sbNTD->value()));
    QPair< QString,QString > tmp0(ui->lb0->text(),QString::number(ui->sbUSD->value()));
    QPair< QString,QString > tmp1(ui->lb1->text(),QString::number(ui->sbHKD->value()));
    QPair< QString,QString > tmp2(ui->lb2->text(),QString::number(ui->sbRMB->value()));
    QPair< QString,QString > tmp3(ui->lb3->text(),QString::number(ui->sbMYR->value()));
    QPair< QString,QString > tmp4(ui->lb4->text(),QString::number(ui->sbSGD->value()));

    list<<tmpX<<tmp0<<tmp1<<tmp2<<tmp3<<tmp4;

    for(int i=0;i<ui->tb0->rowCount();i++)
    {
        QString key,value;

        key =  dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,0))->text();

        if(key.trimmed()=="")
            continue;

        value =  dynamic_cast<QDoubleSpinBox*>(ui->tb0->cellWidget(i,1))->text();

        QPair< QString,QString > tmp(key,value);

        list.append(tmp);
    }

    PrimeRate rate;

    rate.listData = list;

    QString sError;

    ACTION.addPrimeRate(rate.data(),sError,m_bExchangeType);

    UI.showMsg("",sError,"OK");

    reLineEdit();

    refreshRate();

    refreshTbDetail();
}

void LayerPrimeCostRate::reLineEdit()
{
    m_listRate =ACTION.primeRate("",true,m_bExchangeType);

    if(m_listRate.length()>0)
    {
        PrimeRate rate = m_listRate.last();

        if(rate.listData.length()>5)
        {

            ui->sbUSD->setValue(rate.listData.at(1).second.toDouble());
            ui->sbHKD->setValue(rate.listData.at(2).second.toDouble());
            ui->sbRMB->setValue(rate.listData.at(3).second.toDouble());
            ui->sbMYR->setValue(rate.listData.at(4).second.toDouble());
            ui->sbSGD->setValue(rate.listData.at(5).second.toDouble());

        }
    }

}

