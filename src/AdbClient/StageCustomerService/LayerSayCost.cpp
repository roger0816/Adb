#include "LayerSayCost.h"
#include "ui_LayerSayCost.h"

LayerSayCost::LayerSayCost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSayCost)
{
    ui->setupUi(this);

    setWindowTitle(" ");

    ui->tbGameItem->setColumnWidth(0,60);
    ui->tbInfo->setColumnWidth(0,60);
    ui->tbInfo->setColumnWidth(1,200);
    ui->tbInfo->setColumnWidth(2,60);

    ui->wBottom->setCurrentIndex(0);

    ui->wSelect->hide();

    //    ui->cbServer->hide();

    //    ui->cbChr->hide();

    //    ui->lbCHrT->hide();

    //    ui->lbServerT->hide();

    //        label->setText(
    //                                       QObject::tr("<font color = red>%1</font>").arg("abc"))+
    //                                       QObject::tr("<font color = blue>%1</font>").arg("efg")+
    //                                       "hij"
    //                                       );

}

LayerSayCost::~LayerSayCost()
{
    delete ui;
}

void LayerSayCost::orderMode()
{
    ui->lbTitle->setText("下單");

    ui->btnSayOk->setText("送出下單");

    OrderData tmp;

    if(m_sLoadOrderSid=="")
    {
        tmp= ACTION.getOrderByCustomerSid(m_dataCustomer.Sid,true);


        if(tmp.Step=="0")
        {
            m_order = tmp;
        }
    }
    else
    {
        m_order= ACTION.getOrder(m_sLoadOrderSid);

    }

    if(m_bReadOnly)
    {
        if(m_order.Name.trimmed()=="")
        {
            ui->lbTitle->setText("已報價狀態");
        }
        else
            ui->lbTitle->setText(m_order.Id+"    "+m_order.Name);
    }

    QStringList tmpRecord = m_order.UiRecord.split(",");

    while(tmpRecord.length()<4)
        tmpRecord.append("0");

    qDebug()<<"m_order UI :"<<tmpRecord;
    ui->cbGame->setCurrentIndex(qBound(0,tmpRecord.first().toInt(),ui->cbGame->count()-1));
    ui->cbAccount->setCurrentIndex(qBound(0,tmpRecord[1].toInt(),ui->cbAccount->count()-1));
    ui->cbServer->setCurrentIndex(qBound(0,tmpRecord[2].toInt(),ui->cbServer->count()-1));
    ui->cbChr->setCurrentIndex(qBound(0,tmpRecord[3].toInt(),ui->cbChr->count()-1));




    QList<UserData> listUser =ACTION.getUser(true);
    QStringList listCb;
    //    listCb.append("艾比代");
    /*
    m_listOwnerUser.clear();

    for(int i=0;i<listUser.length();i++)
    {
        if(listUser.at(i).Lv==USER_LV::_LV2)
        {
            m_listOwnerUser.append(listUser.at(i));

            listCb.append(listUser.at(i).Name);
        }

    }
    */

    /*
    QList<DataFactory> listFac = ACTION.getFactoryClass("",true);

    for(int i=0;i<listFac.length();i++)
    {
        listCb.append(listFac.at(i).Name);
    }


    ui->cbSelect->clear();

    ui->cbSelect->addItems(listCb);
    */
    ui->wSelect->show();


    CListPair list(m_order.Item);

    m_listInto.clear();
    for(int j=0;j<list.length();j++)
    {
        QString sid =list.listFirst().at(j);
        QString count =list.listSecond().at(j);

        for(int i=0;i<m_listGameItem.length();i++)
        {
            QVariantMap d= m_listGameItem.at(i).toMap();


            if(d["Sid"]==sid)
            {
                d["Count"] = count;

                m_listInto.append(d);
            }

        }

    }

    refreshInfo();

}

void LayerSayCost::setCustomer(QVariantMap data, QString sOrderSid)
{
    qDebug()<<"set customer : "<<data;
    m_listInto.clear();

    ui->tbInfo->setRowCount(0);

    ui->tbGameItem->setRowCount(0);

    QVariantList listOut;
    QVariantMap dIn;
    dIn["Sid"] =data["Sid"];
    QString sError;
    ACTION.action(ACT::QUERY_CUSTOMER,dIn,listOut,sError);

    m_sLoadOrderSid = sOrderSid;

    if(listOut.length()>0)
        m_dataCustomer.setData(listOut.first().toMap());

    // ACTION.rate(m_sLoadRateSid,true);



    ui->lbId->setText(m_dataCustomer.Id);

    ui->lbName->setText(m_dataCustomer.Name);

    QString sCurrency = "新台幣";

    sCurrency = GLOBAL.displayCurrency(m_dataCustomer.Currency);
    //    if(m_dataCustomer.Currency=="HKD")
    //        sCurrency = "港幣";
    //    else if(m_dataCustomer["Currency"]=="RMB")
    //        sCurrency = "人民幣";
    //    else if(m_dataCustomer["Currency"]=="MYR")
    //        sCurrency = "林吉特";
    //    else if(m_dataCustomer["Currency"]=="SGD")
    //        sCurrency = "新加坡元";

    ui->lbCurrency->setText(sCurrency);

    QVariantMap d;

    d["CustomerId"] = m_dataCustomer.Id;


    ACTION.action(ACT::QUERY_GAME_INFO,d,m_listGameInfo,sError);


    QStringList cbName;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap tmp = m_listGameInfo.at(i).toMap();

        QString sName= ACTION.getGameName(tmp["GameSid"].toString());


        if(cbName.indexOf(sName)<0)
            cbName.append(sName);
    }

    ui->cbGame->clear();


    ui->cbGame->addItems(cbName);



    if(m_bOrderMode)
        orderMode();
    else
        m_order=OrderData();

    //    m_exRate = ACTION.listRate(m_order.ExRateSid,false,true).first();

    //    m_primeRate = ACTION.listRate(m_order.PrimeRateSid,false,false).first();


    m_costRate = ACTION.costRate(m_order.ExRateSid,true);
    qDebug()<<"set rate : "<<m_costRate.USD();
    m_primeRate = ACTION.primeRate(m_order.PrimeRateSid,true);


    if(m_order.Sid=="")
    {
        m_order.ExRateSid = m_costRate.Sid;
        m_order.PrimeRateSid = m_primeRate.Sid;
    }
}

void LayerSayCost::setReadOnly()
{

    m_bReadOnly= true;
    ui->btnSayCostBack->hide();
    ui->wBottom->setCurrentIndex(1);

    ui->tbGameItem->hideColumn(0);
    ui->tbInfo->hideColumn(0);

    ui->txNote1->setReadOnly(true);

    ui->cbGame->setEnabled(false);

    ui->cbAccount->setEnabled(false);

    ui->cbServer->setEnabled(false);

    ui->cbChr->setEnabled(false);

    setWindowTitle("訂單詳細內容");

    //  ui->wBottom->hide();
}

void LayerSayCost::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,this,SLOT(delayShowEvent()));
}

void LayerSayCost::refreshInfo()
{
    addPayTypeToCb();
    qDebug()<<"refresh Into ";
    ui->tbInfo->setRowCount(0);

    for(int i=0;i<m_listInto.length();i++)
    {

        int iIdx = ui->tbInfo->rowCount();

        ui->tbInfo->setRowCount(iIdx+1);

        QVariantMap data = m_listInto.at(i).toMap();



        qDebug()<<"into target : "<<data;
        ui->tbInfo->setItem(iIdx,0,UI.tbItem("移除",GlobalUi::_BUTTON));

        ui->tbInfo->setItem(iIdx,1,UI.tbItem(data["Name"]));


        QSpinBox *sp = new QSpinBox(this);

        sp->setRange(1,99);

        sp->setAlignment(Qt::AlignCenter);

        sp->setFont(UI.font());

        sp->setValue(data["Count"].toInt());

        sp->setEnabled(!m_bReadOnly);


        QObject::connect(sp,SIGNAL(valueChanged(int)),this,SLOT(spValue(int)));
        ui->tbInfo->setCellWidget(iIdx,2,sp);


    }

    checkTotal();
}

double LayerSayCost::checkTotal()
{
    qDebug()<<"checkTotal";
    double re = 0;


    //  DataExchange::Rate rate = ACTION.rate(m_sLoadOrderSid);

    double bouns=0;

    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        QSpinBox *sp =dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,2));

        double iPrice =sp->value();

        double r = m_listInto.at(i).toMap()["NTD"].toDouble();

        bouns+=m_listInto.at(i).toMap()["Bonus"].toDouble()*iPrice;

        int iIdx = m_costRate.listKey().indexOf(m_dataCustomer.Currency);

        if(iIdx<0)
            continue;
        //  double target= pRate.listData.at(iIdx).second.toDouble();

        qDebug()<<"customer currency : "<<m_dataCustomer.Currency;


        if(m_dataCustomer.Currency.toUpper().indexOf("USD"))
        {
            qDebug()<<"cost : "<<r;
            qDebug()<<"costRate : "<<m_costRate.USD();
            r=r/m_costRate.USD();

        }

        else if(m_dataCustomer.Currency.toUpper().indexOf("HKD"))
        {
            r = r/m_costRate.HKD();
        }

        else if(m_dataCustomer.Currency=="RMB")
            r = r/m_costRate.RMB();
        else if(m_dataCustomer.Currency=="MYR")
            r = r/m_costRate.MYR();
        else if(m_dataCustomer.Currency=="SGD")
            r = r/m_costRate.SGD();


        double cost = r* iPrice;


        re=re+cost;
        ui->tbInfo->setItem(i,3,UI.tbItem(cost));
    }
    m_iTotal=re;

    m_iBouns = bouns;

    ui->lbTotal->setText(QString::number(re,'f',2));
    //    DATA.rate()


    return re;
}

void LayerSayCost::addPayTypeToCb()
{

    if(m_listInto.length()<1)
        return;

    CListPair tmp;

    checkPayType(tmp);


    m_order.CanSelectPayType = GLOBAL.toString(tmp.listFirst());


    auto factoryPaySid =[=](QStringList list)
    {

        QList<DataFactory> listRe;

        QList<DataFactory> listFac = ACTION.getFactoryClass("",true);

        for(int j=0;j<listFac.length();j++)
        {
            DataFactory factory = listFac.at(j);


            for(int i=0;i<list.length();i++)
            {

                if(factory.PayTypdSid.indexOf(list.at(i))>=0)
                {

                    listRe.append(factory);
                    break;
                }
            }

        }

        return listRe;
    };



    m_listCbItem =factoryPaySid(tmp.listFirst());

    ui->cbSelect->clear();

    QStringList cbData;
    for(int i=0;i<m_listCbItem.length();i++)
    {
        cbData.append(m_listCbItem.at(i).Name);

    }

    ui->cbSelect->addItems(cbData);


}

bool LayerSayCost::checkPayType(CListPair &data)
{
    if(m_listInto.length()<1)
        return true;

    CListPair tmp;

    for(int i=0;i<m_listInto.length();i++)
    {
        DataGameItem t(m_listInto.at(i).toMap());

        if(i==0)
        {
            tmp.append(CListPair(t.AddValueTypeSid));
        }
        else
        {
            tmp.getTheSameKey(CListPair(t.AddValueTypeSid));
        }

    }

    tmp.getTheSameKey(data);

    data = tmp;


    return data.listFirst().length()>0;

}

QString LayerSayCost::getNewOrderId()
{
    QVariantMap data,out;

    QString sError;

    data["OrderDate"] = QDate::currentDate().toString("yyyyMMdd");

    ACTION.action(ACT::LAST_ORDER_ID,data,out,sError);

    QString sRe =GLOBAL.sidAdd(out["Id"].toString());

    qDebug()<<"order id "<<sRe;
    return sRe;
}

QString LayerSayCost::getNewOrderName()
{
    QVariantMap data,out;

    QString sError;

    data["OrderDate"] = QDate::currentDate().toString("yyyyMMdd");
    /*
    UserData owner=m_listOwnerUser.at(ui->cbSelect->currentIndex());
    data["Owner"] = owner.Sid;
    */

    QString sName = ui->cbSelect->currentText();
    data["Owner"] = sName;

    ACTION.action(ACT::LAST_ORDER_NAME,data,out,sError);

    QString sRe =out["Name"].toString();

    sRe=sRe.replace(sName,"");

    if(sRe=="")
    {
        sRe=sName+"1";
    }
    else
    {
        sRe= sName+QString::number(sRe.toInt()+1);
    }




    return sRe;
}



void LayerSayCost::on_btnSayCostBack_clicked()
{
    emit back(1);
}

void LayerSayCost::spValue(int i)
{

    checkTotal();

}


void LayerSayCost::on_cbGame_currentTextChanged(const QString &arg1)
{
    m_sCurrentGameSid = ACTION.getGameId(arg1);

    ui->lbGameName->setText(arg1);

    QStringList cbAcc;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap d = m_listGameInfo.at(i).toMap();

        if(d["GameSid"].toString() == m_sCurrentGameSid
                &&cbAcc.indexOf(d["LoginAccount"].toString())<0)
        {
            cbAcc.append(d["LoginAccount"].toString());
        }
    }

    ui->cbAccount->clear();

    ui->cbAccount->addItems(cbAcc);

    QVariantMap v;

    v["GameSid"] = m_sCurrentGameSid;

    v["Enable"] =1;


    QString sError;

    ACTION.action(ACT::QUERY_GAME_ITEM,v,m_listGameItem,sError);

    ui->tbGameItem->setRowCount(0);

    for(int i=0;i<m_listGameItem.length();i++)
    {
        int iRow = ui->tbGameItem->rowCount();

        ui->tbGameItem->setRowCount(iRow+1);

        QVariantMap dItem = m_listGameItem.at(i).toMap();

        ui->tbGameItem->setItem(iRow,1,UI.tbItem(dItem["Name"]));

        ui->tbGameItem->setItem(iRow,0,UI.tbItem("加入",GlobalUi::_BUTTON));

    }

}


void LayerSayCost::on_cbAccount_currentTextChanged(const QString &arg1)
{
    ui->lbGameAccount->setText(arg1);

    ui->cbServer->clear();

    QStringList server;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap tmp = m_listGameInfo.at(i).toMap();

        QString sName= tmp["ServerName"].toString();


        if(tmp["GameSid"].toString() == m_sCurrentGameSid &&
                tmp["LoginAccount"].toString() == ui->cbAccount->currentText() &&
                server.indexOf(sName)<0)
        {
            server.append(sName);
        }


    }

    ui->cbServer->addItems(server);

    return;


    //    for(int i=0;i<m_listGameInfo.length();i++)
    //    {
    //        QVariantMap d = m_listGameInfo.at(i).toMap();

    //        if(d["GameSid"].toString() == m_sCurrentGameSid &&
    //                d["LoginAccount"].toString() == arg1)
    //        {
    //            ui->lbLoginType->setText(d["LoginType"].toString());

    //            ui->lbServer->setText(d["ServerName"].toString());

    //            ui->lbChr->setText(d["Character"].toString());


    //        }
    //    }
}


void LayerSayCost::on_cbServer_currentTextChanged(const QString &arg1)
{

    ui->lbServer->setText(arg1);

    QStringList chr;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap tmp = m_listGameInfo.at(i).toMap();

        QString sName= tmp["Character"].toString();

        if(tmp["GameSid"].toString() == m_sCurrentGameSid &&
                tmp["LoginAccount"].toString() == ui->cbAccount->currentText() &&
                tmp["ServerName"].toString() == ui->cbServer->currentText() &&
                chr.indexOf(sName)<0)
        {
            chr.append(sName);
        }


    }

    ui->cbChr->clear();

    ui->cbChr->addItems(chr);


}


void LayerSayCost::on_cbChr_currentTextChanged(const QString &arg1)
{
    ui->lbChr->setText(arg1);

    for(int i=0;i<m_listGameInfo.length();i++)
    {

        QVariantMap d = m_listGameInfo.at(i).toMap();


        if(d["GameSid"].toString() == m_sCurrentGameSid &&
                d["ServerName"].toString() == ui->cbServer->currentText() &&
                d["Character"].toString() == arg1 &&
                d["LoginAccount"].toString() == ui->cbAccount->currentText())
        {
            ui->lbLoginType->setText(d["LoginType"].toString());

            //            ui->lbServer->setText(d["ServerName"].toString());

            //            ui->lbChr->setText(d["Character"].toString());


        }
    }
}



void LayerSayCost::on_tbGameItem_cellClicked(int row, int column)
{
    if(column!=0)
        return;


    QString sItemName = ui->tbGameItem->item(row,1)->text();

    for(int i=0;i<m_listGameItem.length();i++)
    {
        QVariantMap data = m_listGameItem.at(i).toMap();

        if(data["Name"] != sItemName)
            continue;


        if(ACTION.mapping(m_listInto,"Sid",data["Sid"].toString())<0)
        {

            CListPair t;
            t.fromString(DataGameItem(data).AddValueTypeSid);
            if(checkPayType(t))
            {
                data["Count"] = 1;
                m_listInto.append(data);
            }
            else
            {
                DMSG.showMsg("","多項商品，沒有共同的支付方式，無法加在同一單",QStringList()<<"OK");
            }

        }
        else
        {

            int iCurrentCount = m_listInto.at(row).toMap()["Count"].toInt();
            data["Count"] =iCurrentCount+1;
            m_listInto[row] = data;

        }


        refreshInfo();
    }



}


void LayerSayCost::on_tbInfo_cellPressed(int row, int column)
{

    if(column==0 && row>=0 && row<m_listInto.length())
    {
        m_listInto.removeAt(row);

        refreshInfo();
    }
}


void LayerSayCost::on_btnCopy_clicked()
{
    //   QClipboard* clipboard = QApplication::clipboard();

    QString sMsg="客戶編號: "+ui->lbId->text()+"\n客戶名稱: "+ui->lbName->text()+"\n";

    sMsg+=ui->label_1->text()+" %1\n"+ui->label_2->text()+"   %2\n"+
            ui->label_3->text()+" %3\n"+ui->label_4->text()+" %4\n"+
            ui->label_5->text()+" %5\n"+ui->label_6->text()+" %6\n"+ui->label_7->text()+" %7\n";

    sMsg =sMsg.arg(ui->lbTime->text())
            .arg(ui->lbCurrency->text())
            .arg(ui->lbGameName->text())
            .arg(ui->lbLoginType->text())
            .arg(ui->lbGameAccount->text())
            .arg(ui->lbServer->text())
            .arg(ui->lbChr->text());


    QString sCost="";


    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        sCost+=ui->tbInfo->item(i,1)->text();
        sCost+=" x "+ dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,2))->text();

        if(!m_bOrderMode)
            sCost+="  "+ui->tbInfo->item(i,3)->text()+"\n";

    }

    if(!m_bOrderMode)
        sCost+="總計: $ "+ui->lbTotal->text();

    UI.copyMsg(sMsg+sCost);

    //    clipboard->setText(sMsg+sCost, QClipboard::Clipboard);

    //    if (clipboard->supportsSelection()) {
    //        clipboard->setText(sMsg, QClipboard::Selection);
    //    }




}




void LayerSayCost::on_btnSayOk_clicked()
{

    if(m_listInto.length()<1)
    {
        UI.showMsg("","請選擇商品","OK");

        return;
    }


    if(m_bOrderMode && m_order.Sid=="")
    {
        UI.showMsg("","沒預先報價流程，請先進行報價",QStringList()<<"OK");
        return;
    }

    QString sMsg="確定送出嗎？";

    int iRet =UI.showMsg("",sMsg,QStringList()<<"否"<<"是");

    if(iRet!=1)
    {

        return;
    }
    if(!m_bOrderMode)
    {
        m_order.Owner="";
        // m_order.Sid="";
        m_order.Note0 = ui->txNote1->toPlainText();
        m_order.User[0] = ACTION.m_currentUser.Sid;
        m_order.Bouns = QString::number(m_iBouns,'f',2);
        m_order.Step="0";
    }
    else
    {
        //  m_order.Sid="";
        // m_order.ExRateSid = m_exRateSid;
        m_order.Note0 = ui->txNote1->toPlainText();
        m_order.User[1] = ACTION.m_currentUser.Sid;
        m_order.StepTime[1] = m_date.toString("yyyyMMddhhmmss");
        //        m_order.OrderDate = m_date.toString("yyyyMMdd");
        //        m_order.OrderTime = m_date.toString("hhmmss");
        m_order.Step="1";
        m_order.Bouns = QString::number(m_iBouns,'f',2);
        // m_order.Owner = m_listOwnerUser.at(ui->cbSelect->currentIndex()).Sid;
        m_order.Owner = ui->cbSelect->currentText();
        m_order.Id = getNewOrderId();

        m_order.Name = getNewOrderName();

    }

    if( m_order.Sid=="")
    {
        m_order.OrderDate = m_date.toString("yyyyMMdd");
        m_order.OrderTime = m_date.toString("hhmmss");
    }

    QString sUiRecord=QString::number(ui->cbGame->currentIndex())+","+
            QString::number(ui->cbAccount->currentIndex())+","+
            QString::number(ui->cbServer->currentIndex())+","+
            QString::number(ui->cbChr->currentIndex());

    m_order.UiRecord=sUiRecord;


    m_order.CustomerSid = m_dataCustomer.Sid;
    m_order.Cost=QString::number(m_iTotal,'f',2);

    qDebug()<<"bound : "<<m_order.Bouns<<" ,  "<<m_iBouns;

    CListPair list;

    for(int i=0;i<m_listInto.length();i++)
    {
        //        QString sTmp="";
        //        sTmp+=m_listInto.at(i).toMap()["Sid"].toString();
        //        sTmp+=","+m_listInto.at(i).toMap()["Count"].toString();

        //        if(i!=0)
        //            sItem+=";";

        //        sItem+=sTmp;

        CPair p;
        p.first = m_listInto.at(i).toMap()["Sid"].toString();

        int iCount = dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,2))->value();

        p.second = QString::number(iCount);

        list.append(p);

    }

    m_order.Item = list.toString();

    QString sError;
    bool bOk = ACTION.replaceOrder(m_order,sError);

    if(bOk && !m_bOrderMode)
        sError="報價送出完成";

    UI.showMsg("",sError,"OK");

    emit back();


}


void LayerSayCost::on_btnSayClose_clicked()
{
    hide();
}

void LayerSayCost::delayShowEvent()
{
    qDebug()<<"show Event ";
    m_listPayType = ACTION.getAddValueType();


    m_date = QDateTime::currentDateTime();

    QString sDate = m_date.QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");
    ui->lbTime->setText(sDate);

    QString sError;

    QVariantMap v;
    ACTION.action(ACT::QUERY_GAME_ITEM,v,m_listGameItem,sError);

    refreshInfo();
}

