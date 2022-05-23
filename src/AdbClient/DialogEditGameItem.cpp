#include "DialogEditGameItem.h"
#include "ui_DialogEditGameItem.h"

DialogEditGameItem::DialogEditGameItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGameItem)
{
    ui->setupUi(this);

    this->setWindowTitle("商品設定");

    ui->wCost1->hide();

    ui->btnCostSub->hide();




}

DialogEditGameItem::~DialogEditGameItem()
{
    delete ui;
}

void DialogEditGameItem::setRate(QString sTitle, DataExchange::Rate rate)
{
    ui->lbTitle->setText(sTitle);

    m_rate = rate;
}


void DialogEditGameItem::setData(QVariantMap data)
{
    m_data = data;

    ui->txName->setText(m_data["Name"].toString());

    ui->cbEnable->setChecked(m_data["Enable"].toBool());

    ui->sbOrderNTD->setValue(m_data["OrderNTD"].toDouble());

    ui->sbOrderUSD->setValue(m_data["OrderUSD"].toDouble());

    ui->sbNTD->setValue(m_data["NTD"].toDouble());

    ui->cbCostEnable->setChecked(m_data["EnableCost"].toBool());

    QStringList listTmp = m_data["Cost"].toString().split(";");

    if(listTmp.length()>1 && listTmp.last().trimmed()=="")
        listTmp.pop_back();

    if(listTmp.length()>1 && listTmp.first().trimmed()=="")
        listTmp.pop_front();

    if(listTmp.length()>0)
    {
        ui->sb0Count->setValue(listTmp.first().split("=").first().toInt());

        ui->sb0Value->setValue(listTmp.first().split("=").last().toInt());
    }

    if(listTmp.length()>1)
    {

        ui->wCost1->show();

        ui->btnCostSub->show();

        ui->btnCostAdd->hide();

        ui->sb1Count->setValue(listTmp.last().split("=").first().toInt());

        ui->sb1Value->setValue(listTmp.last().split("=").last().toInt());

    }



}

QVariantMap DialogEditGameItem::data()
{
    m_data["Name"] = ui->txName->text();

    m_data["Enable"] = ui->cbEnable->isChecked();

    m_data["OrderNTD"] = ui->sbOrderNTD->value();

    m_data["OrderUSD"] = ui->sbOrderUSD->value();

    m_data["NTD"] =ui->sbNTD->value();

    m_data["EnableCost"] = ui->cbCostEnable->isChecked();

    QString sCost = ui->sb0Count->text()+"="+ui->sb0Value->text();

    if(!ui->wCost1->isHidden())
    {

        sCost+=";"+ui->sb1Count->text()+"="+ui->sb1Value->text();
    }

    m_data["Cost"] = sCost;

    return m_data;
}

void DialogEditGameItem::on_btnCostAdd_clicked()
{
    ui->wCost1->show();

    ui->btnCostAdd->hide();

    ui->btnCostSub->show();
}


void DialogEditGameItem::on_btnCostSub_clicked()
{
    ui->wCost1->hide();

    ui->btnCostSub->hide();

    ui->btnCostAdd->show();
}


void DialogEditGameItem::on_btnOk_clicked()
{
    if(ui->txName->text().trimmed()=="")
    {
        DMSG.showMsg("","商品名稱不能空白","OK");
        return;
    }

    done(1);
}


void DialogEditGameItem::on_btnCancel_clicked()
{
    reject();
}


void DialogEditGameItem::on_sbNTD_valueChanged(double arg1)
{
    ui->lbHKD->setText(QString::number(arg1/m_rate.NTD*m_rate.HKD,'f', 2));
    ui->lbRMB->setText(QString::number(arg1/m_rate.NTD*m_rate.RMB,'f', 2));
    ui->lbMYR->setText(QString::number(arg1/m_rate.NTD*m_rate.MYR,'f', 2));
    ui->lbSGD->setText(QString::number(arg1/m_rate.NTD*m_rate.SGD,'f', 2));
}



void DialogEditGameItem::on_btnGameEditDel_clicked()
{
      done(3);
}

