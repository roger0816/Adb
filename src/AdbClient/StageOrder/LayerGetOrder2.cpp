#include "LayerGetOrder2.h"
#include "ui_LayerGetOrder2.h"

LayerGetOrder2::LayerGetOrder2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerGetOrder2)
{
    ui->setupUi(this);

    ui->wPic0->hide();

     ui->wCopyArea->hide();
    m_layerCost = new LayerOrder;

    m_layerCost->setReadOnly();
    m_layerCost->hide();

    ui->wBottom->setCurrentIndex(0);

    connect(&DATA,&UpdateData::updateNotify,this,[=](int iType)
    {
        if(iType == ORDER_DATA)
            refresh();
    });
}

LayerGetOrder2::~LayerGetOrder2()
{
    delete ui;
}

void LayerGetOrder2::init()
{



    refresh();
}

void LayerGetOrder2::refreshUser(bool bRe)
{

    if(m_bLockLoading)
        return ;

    m_bLockLoading = true;

    int iRow = ui->tbUser->currentRow();
    int iCol = ui->tbUser->currentColumn();


    ui->wBottom->setCurrentIndex(0);
    QList<UserData> list =DATA.getUserList();

    m_listOwner.clear();

    m_data.clear();

    QList<DataFactory> listFac = m_listFactory;

    for(int i=0;i<listFac.length();i++)
    {
        m_data[listFac.at(i).Name] = QVariantList();
    }


    for(int i=0;i<list.length();i++)
    {
        UserData data = list.at(i);
        if(data.Lv==USER_LV::_LV2)
        {
            m_listOwner.append(data);

            // m_data[data.Sid]=QVariantList();
        }
    }

    QList<OrderData> listOrder ;

    listOrder= DATA.getOrder();
    qSort(listOrder.begin(),listOrder.end(),[=](const OrderData &v1, const OrderData &v2)
    {
        QString st1 =v1.OrderDate+v1.OrderTime;
        QString st2 =v2.OrderDate+v2.OrderTime;

        return st1<st2;

    });

    for(int i=0;i<listOrder.length();i++)
    {
        QStringList listKeyUser = m_data.keys();

        OrderData order = listOrder.at(i);

        if(listKeyUser.indexOf(order.Owner)<0)
            continue;

        if(order.Step=="3")// || (order.Step=="3" && order.PaddingUser.trimmed()!=""))
        {

            QVariantList list =m_data[order.Owner].toList();

            list.append(order.data());

            m_data[order.Owner] = list;
        }

    }


    ui->tbUser->setUpdatesEnabled(false);
    ui->tbUser->setRowCount(0);
    ui->tbUser->setColumnCount(0);
    int row=0,col=0;

    for(int i=0;i<listFac.length();i++)
    {
        if(row>=ui->tbUser->rowCount())
            ui->tbUser->setRowCount(row+1);

        DataFactory fac = listFac.at(i);

        QString sCount = QString::number(m_data[fac.Name].toList().length());

        QString st = //fac.Id+"    "+
                fac.Name+"  ("+sCount+")";

        if(ui->tbUser->columnCount()<=col)
            ui->tbUser->setColumnCount(ui->tbUser->columnCount()+1);

        QTableWidgetItem *item = UI.tbItem(st);
        if(sCount!="0")
            item->setForeground(Qt::darkRed);

        ui->tbUser->setItem(row,col,item);

        col++;

        if(col>=6)
        {
            col=0;

            row++;
        }
    }

      ui->tbUser->setUpdatesEnabled(true);

    if(iRow>=0 && iRow<ui->tbUser->rowCount() && iCol>=0 && iCol<ui->tbUser->columnCount())
    {
        ui->tbUser->setCurrentCell(iRow,iCol);
        on_tbUser_cellPressed(iRow,iCol);
    }
    m_bLockLoading = false;

}

void LayerGetOrder2::uiWait()
{
    qDebug()<<"AAAAAAAAAAAAAAAAAAAA";
    QEventLoop *loop=new QEventLoop(this);
    loop->connect(this,&LayerGetOrder2::dataUpdate,loop,&QEventLoop::quit);

    UI.slotLockLoading(true);
    loop->exec();
    UI.slotLockLoading(false);
    loop->disconnect();
    loop->deleteLater();


}



void LayerGetOrder2::on_tbUser_cellPressed(int row, int column)
{

    if(row<0 || row>=ui->tbUser->rowCount())
    {
        ui->tbOrder->setRowCount(0);
        return;
    }


    if(column<0 || column>=ui->tbUser->columnCount())
    {
        ui->tbOrder->setRowCount(0);
        return;
    }



    if( ui->tbUser->item(row,column)==nullptr ||  ui->tbUser->item(row,column)->text()
            .split("(").last().split(")").first().toInt()<1)
    {
        ui->tbOrder->setRowCount(0);
        return;
    }



   // ui->tbUser->setCurrentCell(row,column);




    int iIdx = row*ui->tbUser->columnCount()+column;
    QString sKey= m_listFactory.at(iIdx).Name;
    m_currentDataKey = sKey;
    QVariantList listItem = m_data[sKey].toList();

    ui->tbOrder->setRowCount(0);

    for(int i=0;i<listItem.length();i++)
    {
        ui->tbOrder->setRowCount(i+1);

        OrderData order(listItem.at(i).toMap());

        QString sUserCid="";
        if(order.User.length()>2)
        {
            sUserCid = DATA.getUser(order.User.at(2)).Cid;
        }


        ui->tbOrder->setItem(i,_User,UI.tbItem(sUserCid));

        QTableWidgetItem *tmpItem0 = UI.tbItem(order.Name);
        if(order.User.first().trimmed()=="")
             tmpItem0->setForeground(QColor("#00b500"));

        ui->tbOrder->setItem(i,_Name,tmpItem0);

        ui->tbOrder->setItem(i,_Id,UI.tbItem(order.Id,GlobalUi::_BUTTON));

        QVariantMap customer=DATA.getCustomer(order.CustomerSid).data();

        QTableWidgetItem *tmpItem = UI.tbItem(customer["Id"]);

        if(customer["Vip"].toString()=="1")
        {

            tmpItem->setForeground(QColor("#996515"));
        }
        else
        {
            tmpItem->setForeground(QColor(Qt::darkGray));
        }

        ui->tbOrder->setItem(i,_CustomerId,tmpItem);


        ui->tbOrder->setItem(i,_CustomerName,UI.tbItem(customer["Name"]));


        QString sGameItemSid= order.Item.split(";;").first().split(",,").first();
        QVariantMap item=DATA.getGameItem(sGameItemSid).data();

        ui->tbOrder->setItem(i,_GameName,UI.tbItem(DATA.getGameName(item["GameSid"].toString())));
        ui->tbOrder->setItem(i,_Bouns,UI.tbItem(order.Bouns));

        QString sNote="";

        if(order.Note0.length()>=5)
            sNote=order.Note0[4];

        ui->tbOrder->setItem(i,_Note,UI.tbItem(sNote,true));


        if(order.Step=="3" )
        {
            if(order.PaddingUser.trimmed()=="")
            {
                ui->tbOrder->setItem(i,_Status,UI.tbItem("待處理"));
                ui->tbOrder->setItem(i,_Action,UI.tbItem("訂單回報",GlobalUi::_BUTTON));
            }

            else
            {

                ui->tbOrder->setItem(i,_Status,UI.tbItem(DATA.getUser(order.PaddingUser).Name+" 處理中"));
                if(order.PaddingUser==ACTION.m_currentUser.Sid)
                {
                    ui->tbOrder->setItem(i,_Action,UI.tbItem("處理訂單",true));
                }
                else
                {
                    ui->tbOrder->setItem(i,_Action,UI.tbItem(""));
                }
            }
        }

        if(order.Sid==m_sPreSid)
        {
            ui->tbOrder->setFocus();

            ui->tbOrder->setCurrentCell(i, 0); // 設置當前單元格為指定的行和列

            if(order.PaddingUser == ACTION.m_currentUser.Sid)
            {
                on_tbOrder_cellPressed(i,0);
            }

        }

    }


}


void LayerGetOrder2::on_tbOrder_cellPressed(int row, int column)
{

    QVariantList listData =m_data[m_currentDataKey].toList();

    if(row<0 || row>=listData.length())
        return;

    ui->wBottom->setCurrentIndex(0);
    OrderData order(listData.at(row).toMap());
    if(m_sPreSid!=order.Sid)
    {
        m_sPreSid = order.Sid;
            ui->wPic0->slotClear();
    }
    if(column==_Id)
    {


        m_layerCost->setData(order);

        m_layerCost->show();

        return ;
    }


    if(column==_Action && ui->tbOrder->item(row,_Action)->text()=="訂單回報")
    {
        if(1==UI.showMsg("",QString("請確認是否鎖定處理訂單 :%1？").arg(order.Id),QStringList()<<"否"<<"是"))
        {
            bool bCheck= false;

            OrderData reGet = DATA.getOrder(order.Sid);

            if(reGet.Sid!=order.Sid)
                DMSG.showMsg("","錯誤，找不到該訂單","OK");
            else
            {
                if(reGet.PaddingUser=="")
                    bCheck=true;
                else
                    DMSG.showMsg("","該訂單已被'"+DATA.getUser(reGet.PaddingUser).Name+"'鎖定","OK");

            }

            if(bCheck)
            {
                QString sError;
                order.PaddingUser=ACTION.m_currentUser.Sid;
                order.Step="3";

                bool bRe = ACTION.replaceOrder(order,sError);
                uiWait();
                if(!bRe)
                    UI.showMsg("",sError,"OK");
            }
            refreshUser();
        }

        return;
    }

    if(column==_Note)
    {
        DialogNote dialogNote;

        QStringList listName;

        foreach(QString sUserSid,order.User)
        {
            listName.append(DATA.getUser(sUserSid).Name);
        }

        dialogNote.setUser(listName);

        dialogNote.setData(order.Note0);

        dialogNote.exec();

        return;

    }


    if(order.PaddingUser==ACTION.m_currentUser.Sid)
    {

        /*
        QString sValue="0";
        CustomerCost costData = ACTION.getCustomerLastCost(order.CustomerSid);

        if(costData.CustomerSid ==order.CustomerSid)
        {
            sValue = costData.Total;
        }


        ui->lbOri->setText(sValue);

        ui->lbCost->setText(order.Cost);

        QString sCurrency=order.Currency;
        if(sCurrency=="")
        {
            sCurrency =costData.Currency;
        }

        if(sCurrency =="")
        {
            sCurrency = DATA.getCustomer(order.CustomerSid).Currency;
        }


        ui->lbCurrency->setText(sCurrency);

        QString sNote0;
        if(order.Note0.length()>4)
            sNote0=order.Note0.at(4);

        ui->txNote->setText(sNote0);




        double d = sValue.toDouble()-order.Cost.toDouble();

        ui->lbFinal->setText(QString::number(d,'f',2));
        */



        ui->wBottom->setCurrentIndex(1);

    }

}


void LayerGetOrder2::on_btnBackOrder_clicked()
{
    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    int iRet= UI.showMsg("",QString("確定要將此訂單(%1) \n解除處理中的狀態？").arg(order.Id),QStringList()<<"否"<<"是");

    if(iRet==1)
    {

        QString sError;

        order.PaddingUser="";

        order.Step="3";

        //ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);
        ACTION.replaceOrder(order,sError);
        uiWait();
        UI.showMsg("",sError,"OK");

        refreshUser();

        return;
    }

}


void LayerGetOrder2::on_btnFinish_clicked()
{
//    if(!ui->wPic0->m_bHasPic)
//    {
//        UI.showMsg("","請先更新餘額給客戶，並上傳截圖，再完成回報。","OK");

//        return;
//    }



    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data;
    if(listData.length()>0)
        data=listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);


    int iRet;

    if(ui->lbFinal->text().toDouble()<0)
    {
        iRet= UI.showMsg("",QString("本次下單餘額不足，是否完成回報處理？"),QStringList()<<"否"<<"是");

        if(iRet==0)
            return;
    }
    else
        iRet= UI.showMsg("",QString("請再確認訂單(%1) \n已完成回報處理？").arg(order.Id),QStringList()<<"否"<<"是");

    if(iRet==1)
    {


        qDebug()<<" Time : 1:"<<GLOBAL.dateTimeUtc8().toString("yy/MM/dd hh:mm:ss:zzz");

        QString sError;

        order.PaddingUser="";

        order.User[4] = ACTION.m_currentUser.Sid;
        order.StepTime[4]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

        order.Step="4";

        order.Note0[4] =ui->txNote->toPlainText();

        if(ui->wPic0->isVisible() && ui->wPic0->m_bHasPic)
            order.Pic1 = ui->wPic0->uploadPic();


        QString sOriCost="0";
        CustomerCost costData = ACTION.getCustomerLastCost(order.CustomerSid);

        if(costData.CustomerSid ==order.CustomerSid)
        {
            sOriCost = costData.Total;
        }

        QString sCurrency=order.Currency;
        if(sCurrency=="")
        {
            sCurrency =costData.Currency;
        }

        if(sCurrency =="")
        {
            sCurrency = DATA.getCustomer(order.CustomerSid).Currency;
        }

        double d = sOriCost.toDouble()-order.Cost.toDouble();

        QString sFinisiCost = QString::number(d,'f',2);


        QString sText ="客戶編號:    "+DATA.getCustomer(order.CustomerSid).Id+"\n"+
                "幣別:    "+sCurrency+"\n"+
                "原始餘額:    $"+sOriCost+"\n"+
                "本次消費:    $"+order.Cost+"\n"+
                "目前餘額:    $"+sFinisiCost+"\n";

        order.Note3=sText;

        bool bOk =ACTION.replaceOrder(order,sError);
        uiWait();
        QString sMsg = "回報完成";
        qDebug()<<" Time : 3:"<<GLOBAL.dateTimeUtc8().toString("yy/MM/dd hh:mm:ss:zzz");

        if(bOk)
        {
            UI.showMsg("","回報完成\n\n"+sText,QStringList()<<"完成，並複製文字");

            UI.copyMsg(sText);
        }



        refreshUser();
        qDebug()<<" Time : 4:"<<GLOBAL.dateTimeUtc8().toString("yy/MM/dd hh:mm:ss:zzz");

        return;
    }
}

void LayerGetOrder2::refresh()
{
    if(m_bLockLoading)
        return ;

    m_bLockLoading = true;


    ui->wBottom->setCurrentIndex(0);




    //ACTION.getUser(true);

    //ACTION.getOrder(true);

    m_listFactory.clear();


    DataFactory tmp;

    tmp.Id="ABD";

    tmp.Name="艾比代";

    //    m_listFactory.append(tmp);

    m_listFactory.append(DATA.getFactoryClassList());

    if(m_listFactory.length()>0)
    {
        if(m_listFactory.last().Id=="未" && m_listFactory.last().Name=="未分配")
        {
            m_listFactory.pop_back();
        }
    }

    ui->tbOrder->setRowCount(0);

    //ui->cbAddValueType->clear();

    m_bLockLoading = false;

    refreshUser();

    emit dataUpdate();
}


void LayerGetOrder2::on_btnOrder2Copy_clicked()
{
    QString sMsg = ui->lbT->text()+":    "+ui->lbCurrency->text()+"\n"+
            ui->lb0->text()+":    $"+ui->lbOri->text()+"\n"+
            ui->lb1->text()+":    $"+ui->lbCost->text()+"\n"+
            ui->lb2->text()+":    $"+ui->lbFinal->text();
    UI.copyMsg(sMsg);
}


void LayerGetOrder2::on_btnNoteChange_clicked()
{
    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);


    QString sError;


    QString sNote= ui->txNote->toPlainText();

    order.Note0[4]=sNote;

    ACTION.replaceOrder(order,sError);
    uiWait();

    refreshUser();
}

