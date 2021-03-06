#include "LayerAddCost.h"
#include "ui_LayerAddCost.h"

LayerAddCost::LayerAddCost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddCost)
{
    ui->setupUi(this);
}

LayerAddCost::~LayerAddCost()
{
    delete ui;
}

void LayerAddCost::setCustomer(QVariantMap data)
{

    m_dataCustomer.setData(data);
    ui->lbId->setText(m_dataCustomer.Id);

    ui->lbName->setText(m_dataCustomer.Name);

    ui->lbCurrency->setText(m_dataCustomer.Currency);

    ui->lbCurrency_2->setText(m_dataCustomer.Currency);

    ui->cbCurrency->clear();

    m_bLock = true;
    ui->cbCurrency->addItems(m_rate.listKey());
    m_bLock = false;

    int idx= m_rate.listKey().indexOf(m_dataCustomer.Currency);

    idx=qBound(0,idx,ui->cbCurrency->count()-1);


    ui->cbCurrency->setCurrentIndex(idx);


    QList<CustomerCost> list =ACTION.getCustomerCost(m_dataCustomer.Sid,true);

    if(list.length()>0)
        m_lastCostData = list.last();

    QDateTime time = QDateTime::currentDateTime();
    m_lastCostData.UserSid = ACTION.m_currentUser.Sid;

    m_lastCostData.CustomerSid = m_dataCustomer.Sid;

    m_lastCostData.OrderTime = time.toString("yyyyMMddhhmmss");

    m_lastCostData.Currency = m_dataCustomer.Currency;

    ui->lbCurrentCost->setText(m_lastCostData.Value);

    ui->lbCurrentCost_2->setText(m_lastCostData.Value);

    ui->lbTime->setText(time.toString("yyyy/MM/dd hh:mm"));
}

void LayerAddCost::checkTotal()
{

    m_addValue = ui->sb->value();


  //  QString sCustomerKey = GLOBAL.originCurrency(ui->lbCurrency->text());

    int iTmp = qBound(0,m_rate.listKey().indexOf(ui->lbCurrency->text()),m_rate.listData.length()-1);

    double sCustomerRate = m_rate.listData.at(iTmp).second.toDouble();

     double sSelectRate=1;

    if(ui->cbCurrency->currentText()!=ui->lbCurrency->text())
    {
      //  QString sSelectKey = GLOBAL.originCurrency(ui->cbCurrency->currentText());
        int iIdx = qBound(0,m_rate.listKey().indexOf(ui->cbCurrency->currentText()),m_rate.listData.length()-1);
        sSelectRate = m_rate.listData.at(iIdx).second.toDouble();

        m_addValue = m_addValue*(sSelectRate+ui->sbAdd->value())/sCustomerRate;

        ui->lbDiff->setText( QString::number(sCustomerRate )+" : "+QString::number(sSelectRate+ui->sbAdd->value()));

    }
    else
    {
        ui->lbDiff->setText( "1 : 1");

    }

    //  ui->lbChange->setText(ui->lbCurrency->text()+" : $ "+QString::number(m_addValue,'f',2));


    m_lastCostData.Change=QString::number(m_addValue,'f',2);

    m_lastCostData.Value= QString::number(m_addValue+ ui->lbCurrentCost->text().toDouble(),'f',2);

    ui->lbAdd->setText(m_lastCostData.Change);

    ui->lbAfAdd->setText(m_lastCostData.Value);
}

void LayerAddCost::showEvent(QShowEvent *)
{
    ui->lbTime->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));

    m_rate = ACTION.primeRate("",true).last();

//    QPair<QString,QString>s("?????????(NTD)","1");

//    m_rate.listData.insert(0,s);
}

void LayerAddCost::on_btnAddCostBack_clicked()
{
    emit back();
}

void LayerAddCost::on_btnCopy_clicked()
{
    QString sMsg="????????????: "+ui->lbId->text()+
            "\n????????????: "+ui->lbName->text();

    sMsg+="\n"+ui->lb0->text()+ui->lbCurrency_2->text()+
            "\n"+ui->lb1->text()+ui->lbTime->text()+
            "\n"+ui->lb2->text()+ui->lbCurrentCost_2->text()+
            "\n"+ui->lb3->text()+ui->lbAdd->text()+
            "\n"+ui->lb4->text()+ui->lbAfAdd->text();

    UI.copyMsg(sMsg);

}

void LayerAddCost::on_cbCurrency_currentIndexChanged(int index)
{

//    if(m_bLock)
//        return;

    m_bLock= true;

    ui->wRate->setHidden(ui->cbCurrency->currentText()==ui->lbCurrency->text());
    int idx = qBound(0,index,m_rate.listData.length()-1);

    ui->lbRate->setText("??????: "+m_rate.listData.at(idx).second);

    checkTotal();

    m_bLock=false;
}


void LayerAddCost::on_sb_valueChanged(int )
{
    checkTotal();
}


void LayerAddCost::on_btnOk_clicked()
{

    m_lastCostData.Sid="";
    m_lastCostData.OrderId="-1";
    m_lastCostData.Note1=ui->txNote1->toPlainText();
    m_lastCostData.Type=ui->txType->text();
    m_lastCostData.AddRate = ui->sbAdd->text();
    m_lastCostData.Rate = ACTION.rate().Sid;

    QString sMsg = "?????????????????????\n "+ui->lbCurrency->text()+": $"+m_lastCostData.Change+"\n???????????????????";

    int iRet = UI.showMsg("??????!",sMsg,QStringList()<<"???"<<"???");
    if(iRet==1)
    {
        QString sError;

        bool b=ACTION.setCustomerCost(m_lastCostData,sError);

        UI.showMsg("",sError,"OK");

        if(b)
        {
            m_dataCustomer.Money=m_lastCostData.Value;

            QVariantMap out;

            ACTION.action(ACT::EDIT_CUSTOMER,m_dataCustomer.data(),out,sError);

            setCustomer(m_dataCustomer.data());

            checkTotal();
        }

    }

}




void LayerAddCost::on_sbAdd_valueChanged(double arg1)
{
       checkTotal();
}

