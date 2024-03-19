#include "LayerOrder.h"
#include "ui_LayerOrder.h"

LayerOrder::LayerOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerOrder)
{
    ui->setupUi(this);



    ui->tbInfo->setColumnWidth(0,50);
    ui->tbInfo->setColumnWidth(1,200);
    ui->tbInfo->setColumnWidth(2,70);

    ui->tbInfo->hideColumn(4);


    ui->tbInfo->hideColumn(5);

    ui->wBottom->setCurrentIndex(0);


}

LayerOrder::~LayerOrder()
{
    delete ui;
}

void LayerOrder::setReadOnly()
{
    m_bIsReadOnly = true;
    ui->wBottom->setCurrentIndex(1);
    ui->btnOrderBack->hide();
    ui->lbTitle->setText("訂單內容");
    ui->tbInfo->setColumnHidden(4,false);
    ui->txNote1->setReadOnly(true);

    ui->txNote2->setReadOnly(true);
}

void LayerOrder::setData(OrderData order, CustomerData cus)
{
    init();


    m_cus =cus;

    m_order = order;

    m_date =GLOBAL.dateTimeUtc8();
    if(m_bIsReadOnly)
    {
        m_date = QDateTime::fromString(m_order.OrderDate+m_order.OrderTime,"yyyyMMddhhmmss");

        ui->txNote1->setText(m_order.Note0.at(1));
    }

    ui->lbId->setText(cus.Id);
    ui->lbName->setText(cus.Name);

    ui->lbTime->setText(m_date.toString("yyyy/MM/dd hh:mm"));
    ui->lbCurrency->setText(cus.Currency);
    ui->txNote2->setText(m_order.Note2);

    if(!cus.Currency.contains("台幣"))
    {
        ui->tbInfo->setColumnHidden(5,!m_bIsReadOnly);
    }


    setInfo(m_order.ItemInfo);

    setBuyData();

    setCb();

}

void LayerOrder::setData(OrderData order)
{
    CustomerData cus =ACTION.getCustomer(order.CustomerSid,true);

    setData(order,cus);
}

QVariantMap LayerOrder::getOk()
{


    QString sCost="";


    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        sCost+=ui->tbInfo->item(i,1)->text().split("_").first();
        sCost+="  x "+ ui->tbInfo->item(i,2)->text();

        sCost+="\n";

    }

    QVariantMap dData;
    dData["OrderMode"] = true;
    dData["Msg"] = "下單送出成功，已複製文字";
    dData["Id"] = ui->lbId->text();
    dData["Name"] = ui->lbName->text();
    dData["Currency"] = ui->lbCurrency->text();
    dData["Time"] = ui->lbTime->text();
    dData["GameName"] = ui->lbGameName->text();
    dData["LoginType"]= ui->lbLoginType->text();
    dData["GameAccount"] = ui->lbGameAccount->text();
    dData["GamePassword"] = ui->lbGamePassword->text();
    dData["Server"]=ui->lbServer->text();
    dData["Chr"]=ui->lbChr->text();
    dData["Cost"]=sCost;
    dData["Note0"]=ui->txNote1->toPlainText();
    dData["Total"]=ui->lbTotal->text();

    on_btnCopy_clicked();
    return dData;
}



void LayerOrder::init()
{
    ui->lbId->clear();
    ui->lbName->clear();

    ui->lbTime->clear();
    ui->lbCurrency->clear();

    //依序 六個 orderData的list info
    ui->lbGameName->clear();
    ui->lbLoginType->clear();
    ui->lbGameAccount->clear();
    ui->lbGamePassword->clear();
    ui->lbServer->clear();
    ui->lbChr->clear();
    //

    ui->txNote1->clear();

    ui->txNote2->clear();

    ui->lbTotal->clear();

    ui->cbSelect->clear();

    ui->tbInfo->setRowCount(0);

    ui->lbRate->clear();

    ui->lbGameRate->clear();

}

void LayerOrder::setInfo(QStringList listInfo)
{
    while (listInfo.length()<6) {
        listInfo.append("");

    }

    ui->lbGameName->setText(listInfo.at(0));
    ui->lbLoginType->setText(listInfo.at(1));
    ui->lbGameAccount->setText(listInfo.at(2));
    ui->lbGamePassword->setText(listInfo.at(3));
    ui->lbServer->setText(listInfo.at(4));
    ui->lbChr->setText(listInfo.at(5));

}

void LayerOrder::setBuyData()
{
    ui->lbTotal->setText(m_order.Cost);

    ui->lbGameRate->setText(m_order.GameRate);

    ui->lbRate->setText(m_order.ExRateSid);

    QStringList items = m_order.Item.split(";;");
    QStringList listCost= m_order.ListCost;

    QStringList listBouns= m_order.ListBouns;


    while(listCost.length()<items.length())
    {
        listCost.append("0");
    }

    while(listBouns.length()<items.length())
    {
        listBouns.append("0");
    }

    ui->tbInfo->setRowCount(0);

    for(int i=0;i<items.length();i++)
    {
        QString sCost = QString::number(listCost.at(i).toDouble(),'f',2);
        QString sGameItemSid = items.at(i).split(",,").first();
        int iCount = items.at(i).split(",,").last().toInt();

        double bouns=listBouns.at(i).split("*").first().toDouble();


        int iRow = ui->tbInfo->rowCount();
        ui->tbInfo->setRowCount(iRow+1);

        ui->tbInfo->setItem(iRow,0,UI.tbItem(sGameItemSid));

        QString sItemName = ACTION.getGameItemFromSid(sGameItemSid).Name;

        ui->tbInfo->setItem(iRow,1,UI.tbItem(sItemName));

        ui->tbInfo->setItem(iRow,2,UI.tbItem(iCount));

        QTableWidgetItem *itemCost = UI.tbItem(sCost);

        itemCost->setForeground(QBrush(Qt::blue));

        itemCost->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        ui->tbInfo->setItem(iRow,3,itemCost);

        ui->tbInfo->setItem(iRow,4,UI.tbItem(QString::number(bouns*iCount)));

        double iNtd = COMMON.addFlow(bouns*m_order.GameRate.toDouble());

        QTableWidgetItem *itemNtd = UI.tbItem(iNtd*iCount);

        //   itemNtd->setForeground(QBrush(Qt::blue));

        itemNtd->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        ui->tbInfo->setItem(iRow,5,itemNtd);


    }


}

void LayerOrder::setCb()
{
    QStringList canSelect = m_order.CanSelectPayType.split(";;");

    QList<DataFactory> listFac = ACTION.getFactoryClass("",true);

    QStringList listCb;

    for(int i=0;i<canSelect.length();i++)
    {
        QString sPayType = canSelect.at(i);

        for(int j=0;j<listFac.length();j++)
        {
            DataFactory fac = listFac.at(j);

            QString sFacName = fac.Name;

            if(fac.PayTypdSid.contains(sPayType)
                    && !listCb.contains(sFacName))
            {
                listCb.append(sFacName);
            }

        }


    }

    ui->cbSelect->clear();


    ui->cbSelect->addItems(listCb);



}

void LayerOrder::on_btnOrderBack_clicked()
{
    emit back(1);
}


void LayerOrder::on_btnOrderSend_clicked()
{
    if(ui->cbSelect->currentIndex()<0)
    {
        DMSG.showMsg("ERROR 501","下單失敗，訂單負責人錯誤。","OK");

        return ;
    }

    QString sMsg="確定送出嗎？";

    int iRet =UI.showMsg("",sMsg,QStringList()<<"否"<<"是");

    if(iRet!=1)
    {

        return;
    }

    m_date = GLOBAL.dateTimeUtc8();


    m_order.Owner = ui->cbSelect->currentText();

    m_order.Step="1";
    m_order.Note0[1] = ui->txNote1->toPlainText();
    m_order.User[1] = ACTION.m_currentUser.Sid;
    m_order.StepTime[1] = m_date.toString("yyyyMMddhhmmss");
    m_order.Note2 = ui->txNote2->text().replace(",","");
    m_order.UpdateTime = m_date.toString("yyyyMMddhhmmss");
    m_order.OrderDate = m_date.toString("yyyyMMdd");
    m_order.OrderTime = m_date.toString("hhmmss");



    QString sError;
    bool bOk = ACTION.replaceOrder(m_order,sError);

    if(bOk)
    {
        sError="下單成功";

        emit back(6);

    }
    else
    {
        UI.showMsg("AAAA",sError,"OK");

       // emit back();
    }

}


void LayerOrder::on_btnClose_clicked()
{
    hide();
}


void LayerOrder::on_btnCopy_clicked()
{

    QString sMsg="客戶編號: "+ui->lbId->text()+"\n"+
            ui->tTime->text()+" "+ui->lbTime->text()+"\n";

    QString sInfo;



    sMsg+= ui->tGameName->text()+"  "+ui->lbGameName->text()+"\n"
            +ui->tLoginType->text()+"  "+ui->lbLoginType->text()+"\n"
            +ui->tAccount->text()+"  "+ui->lbGameAccount->text()+"\n"
            +ui->tPassword->text()+"  "+ui->lbGamePassword->text()+"\n"
            +ui->tServerName->text()+"  "+ui->lbServer->text()+"\n"
            +ui->tChr->text()+"  "+ui->lbChr->text()+"\n";


    QString sCost="";


    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        sCost+=ui->tbInfo->item(i,1)->text().split("_").first();
        sCost+="  x "+ ui->tbInfo->item(i,2)->text();



        sCost+="\n";

    }



    sCost+="\n備註: "+ui->txNote1->toPlainText();

     UI.copyMsg(sMsg+sCost);




}

