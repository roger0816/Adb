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

    ui->sb->setValue(0);

    ui->wPic0->slotClear();


    ui->wPic1->slotClear();

    m_rate = ACTION.primeRate("",true);


    m_dataCustomer.setData(data);
    ui->lbId->setText(m_dataCustomer.Id);

    ui->lbName->setText(m_dataCustomer.Name);

    ui->lbCurrency->setText(m_dataCustomer.Currency);

    ui->lbCurrency_2->setText(m_dataCustomer.Currency);

    ui->cbCurrency->clear();

    ui->sbAdd->setValue(0);

    m_bLock = true;
    ui->cbCurrency->addItems(m_rate.listKey());
    m_bLock = false;

    int idx= m_rate.listKey().indexOf(m_dataCustomer.Currency);

    idx=qBound(0,idx,ui->cbCurrency->count()-1);


    ui->cbCurrency->setCurrentIndex(idx);

    QDateTime time = GLOBAL.dateTimeUtc8();
    ui->lbTime->setText(time.toString("yyyy/MM/dd hh:mm"));


    QString sTotal= ACTION.getCustomerNowMoney(m_dataCustomer.Sid);
    ui->lbCurrentCost->setText(sTotal);

    ui->lbCurrentCost_2->setText(sTotal);

    m_dataCost.Total=sTotal;
    m_dataCost.OrderTime = time.toString("yyyyMMddhhmmss");
    m_dataCost.Currency = m_dataCustomer.Currency;

    m_dataCost.UserSid = ACTION.m_currentUser.Sid;

    m_dataCost.CustomerSid = m_dataCustomer.Sid;

    /*
    QList<CustomerCost> list =ACTION.getCustomerCost(m_dataCustomer.Sid,true);

    if(list.length()>0)
    {
        m_lastCostData = list.last();
    }
    else
    {
        m_lastCostData.Total="0";
    }

    ui->lbCurrentCost->setText(m_lastCostData.Total);

    ui->lbCurrentCost_2->setText(m_lastCostData.Total);

    m_lastCostData.OrderTime = time.toString("yyyyMMddhhmmss");

    m_lastCostData.Currency = m_dataCustomer.Currency;

    m_lastCostData.UserSid = ACTION.m_currentUser.Sid;

    m_lastCostData.CustomerSid = m_dataCustomer.Sid;
    */

    checkTotal();
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



    QString sTmpChangeValue = QString::number(m_addValue,'f',2);
    m_dataCost.ChangeValue= sub(sTmpChangeValue,m_dataCustomer.Currency);


    QString sTmpTotal= QString::number(m_dataCost.ChangeValue.toDouble()+ ui->lbCurrentCost->text().toDouble(),'f',2);

    m_dataCost.Total =   sub(sTmpTotal,m_dataCustomer.Currency);

    ui->lbAdd->setText(m_dataCost.ChangeValue);

    ui->lbAfAdd->setText(m_dataCost.Total);
}

void LayerAddCost::init()
{
    ui->txNote0->clear();

    ui->txDebitNote->clear();

    ui->lbTime->setText(GLOBAL.dateTimeUtc8().toString("yyyy/MM/dd hh:mm"));

    refresh();


}

QString LayerAddCost::getNewOrderId()
{
    QString sRe ;


    QString sTmp=GLOBAL.dateTimeUtc8().toString("hhmmsszzz").mid(0,7);

    qlonglong tmp = sTmp.toLongLong();

    QString sDate=QDate::currentDate().toString("MMdd");

    sTmp=QString("%1").arg(tmp,6,16,QLatin1Char('0'));

    sRe= sDate+"-"+sTmp;

    return sRe;






    //

    QVariantMap out;

    QString sError;

    ACTION.action(ACT::LAST_CUSTOMER_COST_ID,QVariantMap(),out,sError);

    QString sLast = out["OrderId"].toString();

    QStringList list = sLast.split("-");
    int iIdx = list.last().toInt()+1;

    sRe = list.first()+"-"+QString("%1").arg(iIdx,4,10,QLatin1Char('0'));  // QString::number(iIdx);

    return sRe;
}

QString LayerAddCost::sub(QString sCost, QString sCurrency)
{
    QString sRe;

    QStringList listTmp = sCost.split(".");

    sRe = listTmp.first();

    if(sCurrency.indexOf("新加坡元(SGD)")>=0)
    {
        if(listTmp.length()>1 && listTmp.last().length()>0)
        {
            sRe+="."+listTmp.last().mid(0,1);
        }


    }


    return sRe;
}



void LayerAddCost::refresh()
{
    QString sError;
    QVariantMap tmp;
    tmp["ASC"]="Id";
    QVariantList listOut;
    ACTION.action(ACT::QUERY_DEBIT_CLASS,tmp,listOut,sError);

    m_listRowDebit = listOut;

    setDebitCb();

}

void LayerAddCost::setDebitCb()
{
    ui->cbDebit->clear();

    m_listDebit.clear();

    if(ui->cbCurrency->currentIndex()<0 || ui->cbCurrency->currentText().trimmed()=="")
        return;

    QStringList list;

    foreach(QVariant v,m_listRowDebit)
    {
        DebitClass data(v.toMap());

        if(data.Currency==ui->cbCurrency->currentText())
        {
            m_listDebit.append(v);
        }
    }


    list=GLOBAL.listMapToList(m_listDebit,"Name");

    if(list.length()>0)
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
            "\n支付管道:"+ui->cbDebit->currentText()+
            "\n入帳末五碼:"+ui->txDebitNote->text()+
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

    setDebitCb();
    checkTotal();

    m_bLock=false;
}


void LayerAddCost::on_sb_valueChanged(double )
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

    if(ui->cbDebit->count()<=0)
    {
        DMSG.showMsg("","請先到客戶設定，設定支付管道","OK");

        return ;
    }



    m_dataCost.Sid="";

    m_dataCost.IsAddCost=true;



    m_dataCost.OrderId=getNewOrderId();

    m_dataCost.Note0=ui->txNote0->toPlainText();



    QVariantMap debit = m_listDebit.at(qBound(0,ui->cbDebit->currentIndex(),m_listDebit.length()-1)).toMap();


    m_dataCost.DebitSid=debit["Sid"].toString();
    m_dataCost.DebitNote=ui->txDebitNote->text();

    m_dataCost.AddRate = ui->sbAdd->text();

    m_dataCost.OriginCurrency=ui->cbCurrency->currentText();

    m_dataCost.OriginValue=ui->sb->text();

    m_dataCost.Rate = ACTION.primeRate("",true).Sid;



    QString sMsg = "請確認加值內容\n "+ui->lbCurrency->text()+": $"+m_dataCost.ChangeValue+"\n確定要送出嗎?";

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
                m_dataCost.Pic0 = sMd5;
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
                m_dataCost.Pic1 = sMd5;
            }

        }

        bool bOk = ACTION.sendAddValue(m_dataCustomer,m_dataCost,sError);

        if(bOk)
        {
            m_dataCustomer.Money=m_dataCost.Total;

        }

        UI.showMsg("",sError,"OK");

        setCustomer(m_dataCustomer.data());

        emit back();

#if 0

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

#endif



    }



}




void LayerAddCost::on_sbAdd_valueChanged(double )
{
    checkTotal();
}




