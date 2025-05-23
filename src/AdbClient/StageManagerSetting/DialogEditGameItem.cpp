#include "DialogEditGameItem.h"
#include "ui_DialogEditGameItem.h"

DialogEditGameItem::DialogEditGameItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGameItem)
{
    ui->setupUi(this);

    ui->cbApi->setCurrentIndex(1);

    this->setWindowTitle("商品設定");

    ui->lbUSDtitle->hide();

    ui->sbUSD->hide();


    connect(ui->sbNTD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbUSD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbHKD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbRMB,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbMYR,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));
    connect(ui->sbSGD,SIGNAL(valueChanged(double)),this,SLOT(valueChange(double)));



    ui->tableWidget->hideColumn(_Sort);
    ui->tableWidget->hideColumn(_Sid);

    ui->tableWidget->setColumnWidth(_Sort,60);
    ui->tableWidget->setColumnWidth(_Sid,60);
    ui->tableWidget->setColumnWidth(_Name,150);

    ui->cbEnable->setChecked(true);
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


void DialogEditGameItem::setData(double iGameRate,QVariantMap data)
{
    m_data = data;

    ui->txName->setText(m_data["Name"].toString());

    m_iGameRate = iGameRate;

    ui->lbGameRate->setText(QString::number(m_iGameRate));

    ui->cbEnable->setChecked(m_data["Enable"].toBool());

    ui->sbOrderNTD->setValue(m_data["OrderNTD"].toDouble());

    ui->sbOrderBouns->setValue(m_data["Bonus"].toDouble());

    ui->sbSort->setValue(m_data["Sort"].toInt());

    ui->cbApi->setCurrentIndex(m_data["ForApi"].toInt());

    // ui->sbNTD->setValue(m_data["NTD"].toDouble());

    //ui->sbNTD->setValue(m_iGameRate*m_data["Bonus"].toDouble());


    refreshCb();

}

void DialogEditGameItem::setEanbleCount(bool bShowCountEdit)
{

    if(!ACTION.isNewVersion())
    {
        ui->wCountArea->setVisible(false);
        return;
    }

    ui->wCountArea->setVisible(bShowCountEdit);
}

bool DialogEditGameItem::isEnableCount()
{
    return ui->wCountArea->isVisible();
}

QVariantMap DialogEditGameItem::data()
{
    m_data["Name"] = ui->txName->text();

    m_data["Enable"] = ui->cbEnable->isChecked();

    m_data["OrderNTD"] = ui->sbOrderNTD->value();

    m_data["Bonus"] = ui->sbOrderBouns->value();

    m_data["Sort"] = ui->sbSort->value();
    m_data["NTD"] =ui->sbNTD->value();

    m_data["ForApi"] = ui->cbApi->currentIndex();

    if(ACTION.isNewVersion())
    {
        //for item count
        m_data["Count"] = ui->sbCount->value();
    }

    CListPair listAddValueType;

    CListPair listCurrentType = DATA.getAddValueType();


    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QComboBox *cb=dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(i,_Name));

        QStringList listItem =cb->property("items").toStringList();
        if(cb->currentIndex()<0 || cb->currentIndex()>=listItem.length())
            continue;
        QString target = listItem.at(cb->currentIndex());

        int iTypeIdx = listCurrentType.listSecond().indexOf(target);

        if(iTypeIdx<0)
            continue;

        CPair data =listCurrentType.at(iTypeIdx);

        _DialogEditGameItem::DoubleSpinBox *sp =dynamic_cast<_DialogEditGameItem::DoubleSpinBox*>(ui->tableWidget->cellWidget(i,_PrimeCount));

        //QString cost = QString::number(sp->value(),'f',2);

        QString cost = QString::number(sp->value());


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

    QStringList listText = DATA.getAddValueType().listSecond();

    cb->setProperty("items",listText);

    cb->addItems(listText);

    cb->setEditable(true);

    QCompleter *completer=new QCompleter(cb->model(),this);
    //        completer->setCompletionMode(QCompleter::PopupCompletion);
    cb->setCompleter(completer);


    int idx= qBound(0,iCbIdx,cb->count()-1);

    cb->setCurrentIndex(idx);

    ui->tableWidget->setCellWidget(iRowCount,_Name,cb);

    _DialogEditGameItem::DoubleSpinBox *sp = new _DialogEditGameItem::DoubleSpinBox(ui->tableWidget);

    sp->setAlignment(Qt::AlignHCenter);

    sp->setDecimals(2);

    sp->setRange(0,1000000);

    sp->setValue(cost);

    ui->tableWidget->setCellWidget(iRowCount,_PrimeCount,sp);
}

void DialogEditGameItem::on_btnCostAdd_clicked()
{

    if(ui->tableWidget->rowCount()>32)
    {
        DMSG.showMsg("","超過上限","OK");

        return ;
    }


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
    return ;

    if(m_bLock)
        return;

    m_bLock = true;



    m_bLock = false;
}

double DialogEditGameItem::valueToUp(double d, int decimals)
{

    //to do
    Q_UNUSED(decimals)
    return d;
    QStringList list = QString::number(d).split(".");

    if(list.length()<2)
        return d;

    if(list.last().length()<=decimals)
        return d;

    QString sInt = list.first();

    QString sFloat = list.last().mid(0,decimals);

    if(sFloat.mid(decimals,1)!="0")
    {
        sFloat= QString::number(sFloat.toInt()+1);
    }

    QString sRe = sInt+"."+sFloat;

    return sRe.toDouble();

}




void DialogEditGameItem::on_sbOrderBouns_valueChanged(double arg1)
{

    //  ui->lbRateUsd->setText(QString::number(m_rate.USD()));

    ui->lbRateHkd->setText(QString::number(m_rate.HKD()));

    ui->lbRateRmb->setText(QString::number(m_rate.RMB()));

    ui->lbRateMyr->setText(QString::number(m_rate.MYR()));

    ui->lbRateSgd->setText(QString::number(m_rate.SGD()));



    double ntd =arg1*m_iGameRate;


    ui->sbNTD->setValue(COMMON.addFlow(ntd));
    ui->sbUSD->setValue(COMMON.addFlow(ntd/m_rate.USD(),2));
    ui->sbHKD->setValue(COMMON.addFlow(ntd/m_rate.HKD()));
    ui->sbRMB->setValue(COMMON.addFlow(ntd/m_rate.RMB()));
    ui->sbMYR->setValue(COMMON.addFlow(ntd/m_rate.MYR()));
    ui->sbSGD->setValue(COMMON.addFlow(ntd/m_rate.SGD(),1));

}


void DialogEditGameItem::on_btnCopy_clicked()
{
    GLOBAL.m_copyGameItem = data();
}


void DialogEditGameItem::on_btnPaste_clicked()
{

    if(GLOBAL.m_copyGameItem.keys().indexOf("AddValueTypeSid")>=0)
    {
        QString tmp = GLOBAL.m_copyGameItem["AddValueTypeSid"].toString();


        m_data["AddValueTypeSid"] = tmp;

        refreshCb();

    }

}

void DialogEditGameItem::refreshCb()
{
    QStringList tmp = m_data["AddValueTypeSid"].toString().split(SPLIT1);

    CListPair listPairSid(m_data["AddValueTypeSid"].toString());

    ui->tableWidget->setRowCount(0);

    CListPair listCurrent = DATA.getAddValueType();

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

