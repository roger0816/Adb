#include "DialogEditFactory.h"
#include "ui_DialogEditFactory.h"

DialogEditFactory::DialogEditFactory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditFactory)
{
    ui->setupUi(this);

    setWindowTitle(" ");
}

DialogEditFactory::~DialogEditFactory()
{
    delete ui;
}

void DialogEditFactory::setData(QVariantMap data)
{

    m_rate = ACTION.primeRate().last();

    m_data = data;

    ui->txId->setText(m_data["Id"].toString());
    ui->txName->setText(m_data["Name"].toString());

    ui->cb->clear();

    ui->cb->addItems(m_rate.listKey());

    ui->sb->setValue(m_data["Cost"].toDouble());

    ui->tb->setRowCount(0);
    DataExchange exchange;
    QStringList list = exchange.listKey;

   // list.push_front("NTD");

    QStringList listSellCurrency = data["SellCurrency"].toString().split(",");

    for(int i=0;i<list.length();i++)
    {
        ui->tb->setRowCount(ui->tb->rowCount()+1);

//        QString st = GLOBAL.displayCurrency(list.at(i));
        QString st = list.at(i);
        QTableWidgetItem *item = UI.tbItem(st);
        item->setCheckState(Qt::CheckState::Unchecked);
        if(listSellCurrency.indexOf(list.at(i))>=0)
            item->setCheckState(Qt::CheckState::Checked);
        ui->tb->setItem(i,0,item);

        //        QCheckBox *ch = new QCheckBox(ui->tb);
        //        ch->setContentsMargins(10,10,10,10);

        //        ch->setText(st);

        //        ui->tb->setCellWidget(i,0,ch);
    }

    if(data["Sid"]=="")
    {
        ui->lbTitle->setText("新增廠商");
    }

}

QVariantMap DialogEditFactory::data()
{

    m_data["Id"] = ui->txId->text();

    m_data["Name"]= ui->txName->text();

    m_data["Currency"] = ui->cb->currentText();

    m_data["Cost"] = ui->sb->text();

    QStringList sellCurrency;

    for(int i=0;i<ui->tb->rowCount();i++)
    {
        if(ui->tb->item(i,0)->checkState()==Qt::Checked)
        {
            QString st = GLOBAL.originCurrency(ui->tb->item(i,0)->text());

            sellCurrency.append(st);
        }
    }

    m_data["SellCurrency"] = sellCurrency.join(",");

    return m_data;
}

void DialogEditFactory::on_btnCancel_clicked()
{
    reject();
}


void DialogEditFactory::on_btnOk_clicked()
{
    bool bOk = true;

    if(ui->txId->text().trimmed()=="")
    {
        bOk = false;
    }
    if(ui->txName->text().trimmed()=="")
    {
        bOk = false;
    }


    if(!bOk)
    {
        DMSG.showMsg("","欄位不能為空白","OK");
        return;
    }
    done(1);
}


void DialogEditFactory::on_btnDel_clicked()
{
    int iRet = DMSG.showMsg("","確定是否刪除？",QStringList()<<"否"<<"是");

    if(iRet==1)
    {
        done(3);
    }
}


void DialogEditFactory::on_tb_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->tb->item(row,0);

    bool b = item->checkState()==Qt::Checked;

    if(b)
        item->setCheckState(Qt::Unchecked);
    else
        item->setCheckState(Qt::Checked);
}

