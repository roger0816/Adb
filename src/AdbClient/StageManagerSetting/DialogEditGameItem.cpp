#include "DialogEditGameItem.h"
#include "ui_DialogEditGameItem.h"

DialogEditGameItem::DialogEditGameItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGameItem)
{
    ui->setupUi(this);

    this->setWindowTitle("商品設定");


    connect(ui->sbNTD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbUSD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbHKD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbRMB,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbMYR,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbSGD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));


    ui->tableWidget->setColumnWidth(1,110);
}

DialogEditGameItem::~DialogEditGameItem()
{
    delete ui;
}


void DialogEditGameItem::setRate(QString sTitle, DataRate rate)
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

    ui->sbOrderUSD->setValue(m_data["Bonus"].toDouble());

    ui->sbNTD->setValue(m_data["NTD"].toDouble());

    QStringList tmp = data["AddValueTypeSid"].toString().split(SPLIT1);

    CListPair listPairSid(data["AddValueTypeSid"].toString());

    ui->tableWidget->setRowCount(0);

    CListPair listCurrent = ACTION.getAddValueType();

    for(int i=0;i<listPairSid.length();i++)
    {
        QString sSid = listPairSid.at(i).first;
        double cost = listPairSid.at(i).second.toDouble();

        int iIdx = listCurrent.listFirst().indexOf(sSid);

        if(iIdx<0 || iIdx>listCurrent.listSecond().length())
            continue;

        QString sName= listCurrent.listSecond().at(iIdx);

        appendCb(iIdx,cost);

    }

}

QVariantMap DialogEditGameItem::data()
{
    m_data["Name"] = ui->txName->text();

    m_data["Enable"] = ui->cbEnable->isChecked();

    m_data["OrderNTD"] = ui->sbOrderNTD->value();

    m_data["Bonus"] = ui->sbOrderUSD->value();

    m_data["NTD"] =ui->sbNTD->value();

    CListPair listAddValueType;

    CListPair listCurrentType = ACTION.getAddValueType();


    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {


        QString target = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,0))->currentText();

        int iTypeIdx = listCurrentType.listSecond().indexOf(target);

        if(iTypeIdx<0)
            continue;

        CPair data =listCurrentType.at(iTypeIdx);

        QDoubleSpinBox *sp =dynamic_cast<QDoubleSpinBox*>(ui->tableWidget->cellWidget(i,1));

        QString cost = QString::number(sp->value(),'f',2);

        listAddValueType.append(CPair(data.first,cost));

    }

    m_data["AddValueTypeSid"] = listAddValueType.toString();


    return m_data;
}

void DialogEditGameItem::appendCb(int iCbIdx, double cost)
{
    int iRowCount = ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(iRowCount+1);

    QComboBox *cb = new QComboBox(ui->tableWidget);

    cb->addItems(ACTION.getAddValueType().listSecond());

    int idx= qBound(0,iCbIdx,cb->count()-1);

    cb->setCurrentIndex(idx);

    ui->tableWidget->setCellWidget(iRowCount,0,cb);

    QDoubleSpinBox *sp = new QDoubleSpinBox(ui->tableWidget);

    sp->setAlignment(Qt::AlignHCenter);

    sp->setDecimals(2);

    sp->setRange(0.1,10000.00);

    sp->setValue(cost);

    ui->tableWidget->setCellWidget(iRowCount,1,sp);
}

void DialogEditGameItem::on_btnCostAdd_clicked()
{
    appendCb();
}


void DialogEditGameItem::on_btnCostSub_clicked()
{
    if(ui->tableWidget->rowCount()<1)
        return;

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);

}


void DialogEditGameItem::on_btnOk_clicked()
{
    if(ui->txName->text().trimmed()=="")
    {
        DMSG.showMsg("","商品名稱不能空白","OK");
        return;
    }

    if(ui->tableWidget->rowCount()<1)
    {
        DMSG.showMsg("","支付方式未設定","OK");
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
//    ui->lbHKD->setText(QString::number(arg1/m_rate.NTD*m_rate.HKD,'f', 2));
//    ui->lbRMB->setText(QString::number(arg1/m_rate.NTD*m_rate.RMB,'f', 2));
//    ui->lbMYR->setText(QString::number(arg1/m_rate.NTD*m_rate.MYR,'f', 2));
//    ui->lbSGD->setText(QString::number(arg1/m_rate.NTD*m_rate.SGD,'f', 2));
}



void DialogEditGameItem::on_btnGameEditDel_clicked()
{
    done(3);
}

void DialogEditGameItem::valueChange(double arg)
{
    if(m_bLock)
        return;

    m_bLock = true;

    QDoubleSpinBox *t = dynamic_cast<QDoubleSpinBox*>(sender());

    double ntd;

    if(t==ui->sbNTD)
    {

      ntd= arg;
      ui->sbUSD->setValue(ntd/m_rate.USD());
      ui->sbHKD->setValue(ntd/m_rate.HKD());
      ui->sbRMB->setValue(ntd/m_rate.RMB());
      ui->sbMYR->setValue(ntd/m_rate.MYR());
      ui->sbSGD->setValue(ntd/m_rate.SGD());
    }
    else if(t==ui->sbUSD)
    {
      ntd= arg*m_rate.USD();
      ui->sbHKD->setValue(ntd/m_rate.HKD());
      ui->sbNTD->setValue(ntd);
      ui->sbRMB->setValue(ntd/m_rate.RMB());
      ui->sbMYR->setValue(ntd/m_rate.MYR());
      ui->sbSGD->setValue(ntd/m_rate.SGD());
    }
    else if(t==ui->sbHKD)
    {

      ntd= arg*m_rate.HKD();
      ui->sbUSD->setValue(ntd/m_rate.USD());
      ui->sbNTD->setValue(ntd);
      ui->sbRMB->setValue(ntd/m_rate.RMB());
      ui->sbMYR->setValue(ntd/m_rate.MYR());
      ui->sbSGD->setValue(ntd/m_rate.SGD());
    }
    else if(t==ui->sbRMB)
    {

      ntd= arg*m_rate.RMB();
      ui->sbUSD->setValue(ntd/m_rate.USD());
      ui->sbNTD->setValue(ntd);
      ui->sbHKD->setValue(ntd/m_rate.HKD());
      ui->sbMYR->setValue(ntd/m_rate.MYR());
      ui->sbSGD->setValue(ntd/m_rate.SGD());
    }
    else if(t==ui->sbMYR)
    {

      ntd= arg*m_rate.MYR();
      ui->sbUSD->setValue(ntd/m_rate.USD());
      ui->sbNTD->setValue(ntd);
      ui->sbRMB->setValue(ntd/m_rate.RMB());
      ui->sbHKD->setValue(ntd/m_rate.HKD());
      ui->sbSGD->setValue(ntd/m_rate.SGD());
    }
    else if(t==ui->sbSGD)
    {

      ntd= arg*m_rate.SGD();
      ui->sbUSD->setValue(ntd/m_rate.USD());
      ui->sbNTD->setValue(ntd);
      ui->sbRMB->setValue(ntd/m_rate.RMB());
      ui->sbHKD->setValue(ntd/m_rate.HKD());
      ui->sbMYR->setValue(ntd/m_rate.MYR());
    }



    m_bLock = false;
}



