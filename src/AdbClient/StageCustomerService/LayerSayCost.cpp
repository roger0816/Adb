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
    ui->tbInfo->setColumnWidth(1,30);
    ui->tbInfo->setColumnWidth(2,200);
    ui->tbInfo->setColumnWidth(3,70);

    ui->wBottom->setCurrentIndex(0);

    ui->wSelect->hide();

    ui->tbInfo->hideColumn(1);
    connect(ui->tbGameItem,&QTableWidget::cellClicked,this,&LayerSayCost::slotTbGameItemCellClicked);

    ui->cbGame->setEnabled(false);
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
        tmp= ACTION.getOrderCustomerLast(m_dataCustomer.Sid,true);


        if(tmp.Step=="0")
        {
            m_order = tmp;
        }
    }
    else
    {

        QVariantMap inTmp,out;
        QString sError;

        inTmp["Sid"] = m_sLoadOrderSid;
        ACTION.action(ACT::QUERY_ORDER,inTmp,out,sError);

        m_order.setData(out);
    }

    if(m_bReadOnly)
    {
        if(m_order.Name.trimmed()=="")
        {
            ui->lbTitle->setText("已報價狀態");
        }
        else
            ui->lbTitle->setText(m_order.Id+"    "+m_order.Name);

        if(m_order.Note0.length()>1)
            ui->txNote1->setText(m_order.Note0.at(1));
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

    //    if(m_order.GameRate.trimmed()!="")
    //        m_gameRate=m_order.GameRate;
    //    else
    //        m_gameRate = ACTION.getGameRate(m_order.GameSid).Rate;

    refreshInfo();

}

void LayerSayCost::setCustomer(QVariantMap data, QString sOrderSid)
{
    qDebug()<<"set customer : "<<data<<" ,orderSid : "<<sOrderSid;
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

    ui->lbCurrency->setText(sCurrency);

    QVariantMap d;

    d["CustomerSid"] = m_dataCustomer.Sid;


    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,d,m_listGameInfo,sError);


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
    {
        orderMode();
    }
    else
    {
        ui->cbGame->setEnabled(true);
        m_order=OrderData();
    }
    //    m_exRate = ACTION.listRate(m_order.ExRateSid,false,true).first();

    //    m_primeRate = ACTION.listRate(m_order.PrimeRateSid,false,false).first();


    m_costRate = ACTION.costRate(m_order.ExRateSid,true);
    qDebug()<<"set rate : "<<m_costRate.USD();
    m_primeRate = ACTION.primeRate(m_order.PrimeRateSid,true);



}

void LayerSayCost::init()
{
    ui->txNote1->clear();

    delayShowEvent();
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


void LayerSayCost::refreshInfo()
{

    qDebug()<<"refresh Into ";
    ui->tbInfo->setRowCount(0);

    auto checkTbRow = [=](QString sName)
    {

        for(int i=0;i<ui->tbGameItem->rowCount();i++)
        {
            if(sName == ui->tbGameItem->item(i,1)->text())
            {
                ui->tbGameItem->setItem(i,0,UI.tbItem(""));

                return i;
            }
        }

        return -1;

    };


    for(int i=0;i<m_listInto.length();i++)
    {

        int iIdx = ui->tbInfo->rowCount();

        ui->tbInfo->setRowCount(iIdx+1);

        QVariantMap data = m_listInto.at(i).toMap();



        qDebug()<<"into target : "<<data;
        ui->tbInfo->setItem(iIdx,0,UI.tbItem("移除",GlobalUi::_BUTTON));


        ui->tbInfo->setItem(iIdx,1,UI.tbItem(data["Sid"]));

        ui->tbInfo->setItem(iIdx,2,UI.tbItem(data["Name"]));

        checkTbRow(data["Name"].toString());


        QSpinBox *sp = new QSpinBox(this);

        QPair<qlonglong ,qlonglong > tmp =  ACTION.getItemCount(DataGameItem(data).Sid);

        int iTotalItem = tmp.second-tmp.first;

        sp->setRange(1,iTotalItem);

        sp->setAlignment(Qt::AlignCenter);

        sp->setFont(UI.font());

        sp->setValue(data["Count"].toInt());

        sp->setEnabled(!m_bReadOnly);


        QObject::connect(sp,SIGNAL(valueChanged(int)),this,SLOT(spValue(int)));
        ui->tbInfo->setCellWidget(iIdx,3,sp);


    }

    ui->cbGame->setEnabled(ui->tbInfo->rowCount()==0 && !m_bOrderMode);
    addPayTypeToCb();
    checkTotal();
}

bool LayerSayCost::checkHasInto(QString gameItemSid)
{

    for(int i=0;i<m_listInto.length();i++)
    {
        if(DataGameItem(m_listInto.at(i).toMap()).Sid==gameItemSid)
            return true;
    }

    return false;
}

double LayerSayCost::checkTotal()
{

    double re = 0;


    //  DataExchange::Rate rate = ACTION.rate(m_sLoadOrderSid);

    double totalBouns=0;

    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        QSpinBox *sp =dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,3));

        double iPrice =sp->value();

        //double ntd = m_listInto.at(i).toMap()["NTD"].toDouble();

        // QString sCost = QString::number(ntd,'f',0);

        totalBouns+=m_listInto.at(i).toMap()["Bonus"].toDouble()*iPrice;

        double bouns = m_listInto.at(i).toMap()["Bonus"].toDouble();
        int iIdx = m_costRate.listKey().indexOf(m_dataCustomer.Currency);

        if(iIdx<0)
            continue;
        //  double target= pRate.listData.at(iIdx).second.toDouble();

        qDebug()<<"customer currency : "<<m_dataCustomer.Currency;


        double ntd = m_gameRate.toDouble()*bouns;
        qDebug()<<"ABC : bound "<<bouns<<" game rate : "<<m_gameRate<<" ntd : "<<ntd;
        QString sCost = QString::number(GLOBAL.addFlow(ntd));


        if(m_dataCustomer.Currency.toUpper().contains("USD"))
        {
            sCost = QString::number(GLOBAL.addFlow(ntd/m_costRate.USD(),2));

        }

        else if(m_dataCustomer.Currency.toUpper().contains("HKD"))
        {

            sCost = QString::number(GLOBAL.addFlow(ntd/m_costRate.HKD()));
        }

        else if(m_dataCustomer.Currency.toUpper().contains("RMB"))
        {

            sCost = QString::number(GLOBAL.addFlow(ntd/m_costRate.RMB()));

        }
        else if(m_dataCustomer.Currency.toUpper().contains("MYR"))
        {
            sCost = QString::number(GLOBAL.addFlow(ntd/m_costRate.MYR()));

        }
        else if(m_dataCustomer.Currency.toUpper().contains("SGD"))
        {

            sCost = QString::number(GLOBAL.addFlow(ntd/m_costRate.SGD(),1));

        }

        double cost = sCost.toDouble()* iPrice;


        //   QString sTmp = QString::number(iNTD/rate2.USD(),'f',2);


        re=re+cost;
        ui->tbInfo->setItem(i,4,UI.tbItem(cost));
    }
    m_iTotal=re;

    m_iBouns = totalBouns;


    if(re<0)
        re=0.00;

    ui->lbTotal->setText(QString::number(re,'f',2));
    //    DATA.rate()


    return re;
}

void LayerSayCost::addPayTypeToCb()
{
    qDebug()<<"add pay type to cb";
    if(m_listInto.length()<1)
        return;

    CListPair tmp;

    checkPayType(tmp);


    m_order.CanSelectPayType = GLOBAL.toString(tmp.listFirst());

    qDebug()<<"canselect pay type : "<<m_order.CanSelectPayType;

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

        qDebug()<<"into dataGameItem : "<<t.data();

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
    return "byServer";
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

    return "byServer";
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

void LayerSayCost::spValue(int )
{

    checkTotal();

}


void LayerSayCost::on_cbGame_currentTextChanged(const QString &arg1)
{
    m_sCurrentGameSid = ACTION.getGameId(arg1);
    qDebug()<<"game sid : "<<m_sCurrentGameSid<<" ,name "<<arg1;


    if(m_order.OrderDate.toInt()<=20230216)
    {
        m_gameRate=ACTION.getGameRate(m_sCurrentGameSid).Rate;
        qDebug()<<"game rate by old query : "<<m_gameRate;
    }

    else if(m_order.GameRate.trimmed()!="" && (m_bReadOnly || m_bOrderMode) ) //下單、讀取訂單內容時 ，且gamerate有資料
    {
        m_gameRate = m_order.GameRate;
        qDebug()<<"game rate by order : "<<m_gameRate;
    }
    else
    {
        m_gameRate=ACTION.getGameRate(m_sCurrentGameSid).Rate;
        qDebug()<<"game rate by query : "<<m_gameRate;
    }


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

        DataGameItem item (m_listGameItem.at(i).toMap());

        ui->tbGameItem->setItem(iRow,1,UI.tbItem(item.Name));


        if(m_bReadOnly || checkHasInto(item.Sid))
        {
            ui->tbGameItem->setItem(iRow,0,UI.tbItem(""));

        }
        else
        {

            QPair<int,int> tmp = ACTION.getItemCount(item.Sid);
            int iCount  =tmp.second-tmp.first;

            if(iCount>0)
                ui->tbGameItem->setItem(iRow,0,UI.tbItem("加入",GlobalUi::_BUTTON));
            else
                ui->tbGameItem->setItem(iRow,0,UI.tbItem("完售"));
        }


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

        CustomerGameInfo data(tmp);

        QString sName= data.ServerName;


        if(data.GameSid == m_sCurrentGameSid &&
                data.LoginAccount== ui->cbAccount->currentText() &&
                server.indexOf(sName)<0)
        {
            server.append(sName);

            ui->lbGamePassword->setText(data.LoginPassword);


        }


    }

    ui->cbServer->addItems(server);

}


void LayerSayCost::on_cbServer_currentTextChanged(const QString &arg1)
{

    ui->lbServer->setText(arg1);

    QStringList chr;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap tmp = m_listGameInfo.at(i).toMap();

        CustomerGameInfo data(tmp);



        if(data.GameSid == m_sCurrentGameSid &&
                data.LoginAccount == ui->cbAccount->currentText() &&
                data.ServerName == ui->cbServer->currentText() &&
                chr.indexOf(data.Characters)<0)
        {
            chr.append(data.Characters);
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

        CustomerGameInfo data(d);

        if(data.GameSid == m_sCurrentGameSid &&
                data.ServerName == ui->cbServer->currentText() &&
                data.Characters == arg1 &&
                data.LoginAccount == ui->cbAccount->currentText())
        {
            ui->lbLoginType->setText(data.LoginType);

            //            ui->lbServer->setText(d["ServerName"].toString());

            //            ui->lbChr->setText(d["Character"].toString());


        }
    }
}



void LayerSayCost::slotTbGameItemCellClicked(int row, int column)
{


    if(column!=0 || ui->tbGameItem->item(row,0)->text()!="加入")
        return;

    QString sItemName = ui->tbGameItem->item(row,1)->text();


    for(int i=0;i<m_listGameItem.length();i++)
    {
        // QVariantMap data = m_listGameItem.at(i).toMap();

        DataGameItem item(m_listGameItem.at(i).toMap());


        if(item.GameSid!= m_sCurrentGameSid)
            continue;

        if(item.Name!= sItemName)
            continue;

        int iMappingIdx =ACTION.mapping(m_listInto,"Sid",item.Sid);

        if(iMappingIdx<0)
        {

            CListPair t;
            t.fromString(item.AddValueTypeSid);
            if(checkPayType(t))
            {
                item.Count = 1;
                m_listInto.append(item.data());
            }
            else
            {
                DMSG.showMsg("","多項商品，沒有共同的支付方式，無法加在同一單",QStringList()<<"OK");
            }

        }
        else
        {

            int iCurrentCount = m_listInto.at(iMappingIdx).toMap()["Count"].toInt();

            item.Count =iCurrentCount+1;

            m_listInto[iMappingIdx] = item.data();


        }


        refreshInfo();
    }



}


void LayerSayCost::on_tbInfo_cellPressed(int row, int column)
{

    auto checkTbRow = [=](QString sName)
    {

        for(int i=0;i<ui->tbGameItem->rowCount();i++)
        {
            if(sName == ui->tbGameItem->item(i,1)->text())
                return i;
        }

        return -1;

    };



    if(column==0 && row>=0 && row<m_listInto.length())
    {
        QString sName = ui->tbInfo->item(row,2)->text();

        int iTbRow = checkTbRow(sName);

        if(iTbRow>=0)
            ui->tbGameItem->setItem(iTbRow,0,UI.tbItem("加入",GlobalUi::_BUTTON));


        m_listInto.removeAt(row);

        refreshInfo();
    }


}


void LayerSayCost::on_btnCopy_clicked()
{
    //   QClipboard* clipboard = QApplication::clipboard();

    QString sMsg="客戶編號: "+ui->lbId->text()+"\n"+
            ui->tTime->text()+" "+ui->lbTime->text()+"\n";

    QString sInfo;

    if(!m_bOrderMode) //報價
    {
        sMsg+= ui->tGameName->text()+"  "+ui->lbGameName->text()+"\n"
                +ui->tLoginType->text()+"  "+ui->lbLoginType->text()+"\n"
                +ui->tAccount->text()+"  "+ui->lbGameAccount->text()+"\n"
                +ui->tPassword->text()+"  "+ui->lbGamePassword->text()+"\n"
                +ui->tServerName->text()+"  "+ui->lbServer->text()+"\n"
                +ui->tChr->text()+"  "+ui->lbChr->text()+"\n";


    }
    else                //下單
    {
        sMsg+= ui->tGameName->text()+"  "+ui->lbGameName->text()+"\n"
                +ui->tLoginType->text()+"  "+ui->lbLoginType->text()+"\n"
                +ui->tAccount->text()+"  "+ui->lbGameAccount->text()+"\n"
                +ui->tPassword->text()+"  "+ui->lbGamePassword->text()+"\n"
                +ui->tServerName->text()+"  "+ui->lbServer->text()+"\n"
                +ui->tChr->text()+"  "+ui->lbChr->text()+"\n";

    }



    //    sMsg+=ui->label_1->text()+" %1\n"+ui->label_2->text()+"   %2\n"+
    //            ui->label_3->text()+" %3\n"+ui->label_4->text()+" %4\n"+
    //            ui->label_5->text()+" %5\n"+ui->label_10->text()+" %6\n"+
    //            ui->label_6->text()+" %7\n"+ui->label_7->text()+" %8\n";

    //    sMsg =sMsg.arg(ui->lbTime->text())
    //            .arg(ui->lbCurrency->text())
    //            .arg(ui->lbGameName->text())
    //            .arg(ui->lbLoginType->text())
    //            .arg(ui->lbGameAccount->text())
    //            .arg(ui->lbGamePassword->text())
    //            .arg(ui->lbServer->text())
    //            .arg(ui->lbChr->text());


    QString sCost="";


    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        sCost+=ui->tbInfo->item(i,2)->text();
        sCost+="  x "+ dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,3))->text();

        if(!m_bOrderMode)
        {
            sCost+="  "+ui->tbInfo->item(i,4)->text();
        }

        sCost+="\n";

    }

    if(!m_bOrderMode)
    {
        sCost+="\n總計: $ "+ui->lbTotal->text()+"\n"
                +"幣別: "+ui->lbCurrency->text();
    }
    else
    {
        sCost+="\n備註: "+ui->txNote1->toPlainText();
    }
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
        m_order.Note0[0] = ui->txNote1->toPlainText();

        m_order.Bouns = QString::number(m_iBouns,'f',2);
        m_order.User[0] = ACTION.m_currentUser.Sid;
        m_order.StepTime[0] = m_date.toString("yyyyMMddhhmmss");
        m_order.Step="0";
    }
    else
    {
        //  m_order.Sid="";
        // m_order.ExRateSid = m_exRateSid;
        m_order.Note0[1] = ui->txNote1->toPlainText();
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

    //  if( m_order.Sid=="")
    //  {
    m_order.OrderDate = m_date.toString("yyyyMMdd");
    m_order.OrderTime = m_date.toString("hhmmss");
    //  }


    //QVariantMap d= m_listGameInfo.at(qBound(0,ui->cbGame->currentIndex(),m_listGameInfo.length()-1)).toMap();


    //CustomerGameInfo info(d);
    m_order.GameSid = m_sCurrentGameSid;
    // m_order.GameRate=m_gameRate;  //game rate 報價時server會填上


    QString sUiRecord=QString::number(ui->cbGame->currentIndex())+","+
            QString::number(ui->cbAccount->currentIndex())+","+
            QString::number(ui->cbServer->currentIndex())+","+
            QString::number(ui->cbChr->currentIndex());

    m_order.UiRecord=sUiRecord;


    m_order.CustomerSid = m_dataCustomer.Sid;
    m_order.Cost=QString::number(m_iTotal,'f',2);


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

        int iCount = dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,3))->value();

        p.second = QString::number(iCount);

        list.append(p);

    }

    m_order.Item = list.toString();
    m_order.UpdateTime = m_date.toString("yyyyMMddhhmmss");

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


    m_date = GLOBAL.dateTimeUtc8();

    QString sDate = m_date.toString("yyyy/MM/dd hh:mm");
    ui->lbTime->setText(sDate);

    QString sError;

    QVariantMap v;
    ACTION.action(ACT::QUERY_GAME_ITEM,v,m_listGameItem,sError);

    refreshInfo();
}

