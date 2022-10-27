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

    // m_rate = ACTION.rate("",true).last();

    m_rate = ACTION.primeRate("",true);


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

    QDateTime time = GLOBAL.dateTimeUtc8();
    m_lastCostData.UserSid = ACTION.m_currentUser.Sid;

    m_lastCostData.CustomerSid = m_dataCustomer.Sid;

    m_lastCostData.OrderTime = time.toString("yyyyMMddhhmmss");

    m_lastCostData.Currency = m_dataCustomer.Currency;

    ui->lbCurrentCost->setText(m_lastCostData.Total);

    ui->lbCurrentCost_2->setText(m_lastCostData.Total);

    ui->lbTime->setText(time.toString("yyyy/MM/dd hh:mm"));
}

void LayerAddCost::checkTotal()
{

    m_addValue = ui->sb->value();

    int iTmp = qBound(0,m_rate.listKey().indexOf(ui->lbCurrency->text()),m_rate.listData.length()-1);

    double sCustomerRate = m_rate.listData.at(iTmp).second.toDouble();


    double sSelectRate=1;

    if(ui->cbCurrency->currentText()!=ui->lbCurrency->text())
    {
        //  QString sSelectKey = GLOBAL.originCurrency(ui->cbCurrency->currentText());
        int iIdx = qBound(0,m_rate.listKey().indexOf(ui->cbCurrency->currentText()),m_rate.listData.length()-1);
        sSelectRate = m_rate.listData.at(iIdx).second.toDouble();

        qDebug()<<"select rate : "<<sSelectRate;

        m_addValue = m_addValue*(sSelectRate+ui->sbAdd->value())/sCustomerRate;

        ui->lbDiff->setText( QString::number(sCustomerRate )+" : "+QString::number(sSelectRate+ui->sbAdd->value()));

    }
    else
    {
        ui->lbDiff->setText( "1 : 1");

    }

    //  ui->lbChange->setText(ui->lbCurrency->text()+" : $ "+QString::number(m_addValue,'f',2));


    m_lastCostData.ChangeValue=QString::number(m_addValue,'f',2);

    m_lastCostData.Total= QString::number(m_addValue+ ui->lbCurrentCost->text().toDouble(),'f',2);

    ui->lbAdd->setText(m_lastCostData.ChangeValue);

    ui->lbAfAdd->setText(m_lastCostData.Total);
}

void LayerAddCost::showEvent(QShowEvent *)
{
    ui->lbTime->setText(GLOBAL.dateTimeUtc8().toString("yyyy/MM/dd hh:mm"));

    QTimer::singleShot(50,Qt::PreciseTimer,this,SLOT(refresh()));


}

QString LayerAddCost::getNewOrderId()
{
    QString sRe ;

    QVariantMap out;

    QString sError;

    ACTION.action(ACT::LAST_CUSTOMER_COST_ID,QVariantMap(),out,sError);

    QString sLast = out["OrderId"].toString();

    QStringList list = sLast.split("-");
    int iIdx = list.last().toInt();

    sRe = list.first()+"_"+QString::number(iIdx);

    return sRe;
}

void LayerAddCost::refresh()
{
    QString sError;
    QVariantMap tmp;
    tmp["ASC"]="Id";
    QVariantList listOut;
    ACTION.action(ACT::QUERY_CUSTOM_DEBIT,tmp,listOut,sError);

    m_listDebit = listOut;

    QStringList list =GLOBAL.listMapToList(m_listDebit,"Name");

    ui->cbDebit->clear();

    ui->cbDebit->addItems(list);
}

void LayerAddCost::on_btnAddCostBack_clicked()
{
    emit back(1);
}

void LayerAddCost::on_btnCopy_clicked()
{
    QString sMsg="客戶編號: "+ui->lbId->text()+
            "\n客戶名稱: "+ui->lbName->text();

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

    ui->lbRate->setText("匯率: "+m_rate.listData.at(idx).second);

    checkTotal();

    m_bLock=false;
}


void LayerAddCost::on_sb_valueChanged(int )
{
    checkTotal();
}


void LayerAddCost::on_btnOk_clicked()
{
    if(ui->sb->value()==0)
    {
        DMSG.showMsg("","請設定金額","OK");

        return ;
    }



    m_lastCostData.Sid="";


    m_lastCostData.OrderId=getNewOrderId();
    m_lastCostData.Note0=ui->txNote0->toPlainText();

    QVariantMap debit = m_listDebit.at(qBound(0,ui->cbDebit->currentIndex(),m_listDebit.length()-1)).toMap();
    m_lastCostData.DebitSid=debit["Sid"].toString();
    m_lastCostData.DebitNote=ui->txDebitNote->text();

    m_lastCostData.AddRate = ui->sbAdd->text();
    //m_lastCostData.Rate = ACTION.rate().Sid;

    // m_lastCostData.Rate = ACTION.rate("",true,true).last().Sid;

    m_lastCostData.Rate = ACTION.primeRate("",true).Sid;



    QString sMsg = "請確認加值內容\n "+ui->lbCurrency->text()+": $"+m_lastCostData.ChangeValue+"\n確定要送出嗎?";

    int iRet = UI.showMsg("提醒!",sMsg,QStringList()<<"否"<<"是");
    if(iRet==1)
    {
         QString sError;

        if(ui->wPic0->m_bHasPic)
        {

            QString sMd5 = ui->wPic0->uploadPic();

            if(sMd5=="")
            {
                DMSG.showMsg("","圖片1上傳失敗\n"+sError,"OK");

                return ;
            }
            else
            {
                m_lastCostData.Pic0 = sMd5;
            }
        }
        //

        if(ui->wPic1->m_bHasPic)
        {


            QString sMd5 = ui->wPic1->uploadPic();

            if(sMd5=="")
            {
                DMSG.showMsg("","圖片1上傳失敗\n"+sError,"OK");

                return ;
            }
            else
            {
                m_lastCostData.Pic1 = sMd5;
            }

        }




        bool b=ACTION.setCustomerCost(m_lastCostData,sError);

        UI.showMsg("",sError,"OK");

        if(b)
        {
            m_dataCustomer.Money=m_lastCostData.Total;


            ACTION.action(ACT::EDIT_CUSTOMER,m_dataCustomer.data(),sError);

            setCustomer(m_dataCustomer.data());

            checkTotal();
        }

        emit back();

    }



}




void LayerAddCost::on_sbAdd_valueChanged(double )
{
    checkTotal();
}



