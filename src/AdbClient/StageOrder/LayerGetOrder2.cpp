#include "LayerGetOrder2.h"
#include "ui_LayerGetOrder2.h"

LayerGetOrder2::LayerGetOrder2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerGetOrder2)
{
    ui->setupUi(this);

    m_layerCost = new LayerSayCost;

    m_layerCost->m_bOrderMode = true;
    m_layerCost->setReadOnly();
    m_layerCost->hide();

    ui->wBottom->setCurrentIndex(0);
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


    ui->wBottom->setCurrentIndex(0);
    QList<UserData> list =ACTION.getUser(bRe);

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

    QList<OrderData> listOrder = ACTION.getOrder(bRe);

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

    ui->tbOrder->setRowCount(0);

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

        if(col>=5)
        {
            col=0;

            row++;
        }
    }

    on_tbUser_cellPressed(m_iPreUserRow,m_iPreUserCol);

    m_bLockLoading = false;

}

QVariantMap LayerGetOrder2::gameItem(QString sSid)
{
    QString sError;
    QVariantMap re;
    QVariantMap d1;
    QVariantList listOut;
    d1["Sid"] = sSid;
    ACTION.action(ACT::QUERY_GAME_ITEM,d1,listOut,sError);

    if(listOut.length()>0)
        re = listOut.first().toMap();

    return re;
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


    ui->tbUser->setCurrentCell(row,column);

    m_iPreUserCol = column;
    m_iPreUserRow = row;


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
            sUserCid = ACTION.getUser(order.User.at(2)).Cid;
        }


        ui->tbOrder->setItem(i,_User,UI.tbItem(sUserCid));

        ui->tbOrder->setItem(i,_Name,UI.tbItem(order.Name));
        ui->tbOrder->setItem(i,_Id,UI.tbItem(order.Id,GlobalUi::_BUTTON));

        QVariantMap d;
        QVariantList tmpOut;

        d["Sid"]=order.CustomerSid;

        QString sError;

        ACTION.action(ACT::QUERY_CUSTOMER,d,tmpOut,sError);


        QVariantMap customer;

        if(tmpOut.length()>0)
            customer = tmpOut.first().toMap();

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
        QVariantMap item=gameItem(sGameItemSid);

        ui->tbOrder->setItem(i,_GameName,UI.tbItem(ACTION.getGameName(item["GameSid"].toString())));
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

                ui->tbOrder->setItem(i,_Status,UI.tbItem(ACTION.getUser(order.PaddingUser,true).Name+" 處理中"));
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



    }


}


void LayerGetOrder2::on_tbOrder_cellPressed(int row, int column)
{

    QVariantList listData =m_data[m_currentDataKey].toList();

    if(row<0 || row>=listData.length())
        return;

    ui->wBottom->setCurrentIndex(0);
    OrderData order(listData.at(row).toMap());

    if(column==_Id)
    {

        QVariantMap d;
        d["Sid"] = order.CustomerSid;
        m_layerCost->setCustomer(d,order.Sid);

        m_layerCost->show();

        return ;
    }


    if(column==_Action && ui->tbOrder->item(row,_Action)->text()=="訂單回報")
    {
        if(1==UI.showMsg("",QString("請確認是否鎖定處理訂單 :%1？").arg(order.Id),QStringList()<<"否"<<"是"))
        {
            bool bCheck= false;

            OrderData reGet = ACTION.getOrder(order.Sid,true);

            if(reGet.Sid!=order.Sid)
                DMSG.showMsg("","錯誤，找不到該訂單","OK");
            else
            {
                if(reGet.PaddingUser=="")
                    bCheck=true;
                else
                    DMSG.showMsg("","該訂單已被'"+ACTION.getUser(reGet.PaddingUser).Name+"'鎖定","OK");

            }

            if(bCheck)
            {
                QString sError;
                order.PaddingUser=ACTION.m_currentUser.Sid;
                order.Step="3";

                bool bRe = ACTION.replaceOrder(order,sError);
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
            listName.append(ACTION.getUser(sUserSid).Name);
        }

        dialogNote.setUser(listName);

        dialogNote.setData(order.Note0);

        dialogNote.exec();

        return;

    }


    if(order.PaddingUser==ACTION.m_currentUser.Sid)
    {


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
            sCurrency = ACTION.getCustomer(order.CustomerSid).Currency;
        }


        ui->lbCurrency->setText(sCurrency);

        QString sNote0;
        if(order.Note0.length()>4)
            sNote0=order.Note0.at(4);

        ui->txNote->setText(sNote0);


        ui->wPic0->slotClear();

        double d = sValue.toDouble()-order.Cost.toDouble();

        ui->lbFinal->setText(QString::number(d));

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
        UI.showMsg("",sError,"OK");

        refreshUser();

        return;
    }

}


void LayerGetOrder2::on_btnFinish_clicked()
{
    if(!ui->wPic0->m_bHasPic)
    {
        UI.showMsg("","請先更新餘額給客戶，並上傳截圖，再完成回報。","OK");

        return;
    }



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

        order.Pic1 = ui->wPic0->uploadPic();
        qDebug()<<" Time : 2:"<<GLOBAL.dateTimeUtc8().toString("yy/MM/dd hh:mm:ss:zzz");



        bool bOk =ACTION.replaceOrder(order,sError);

        QString sMsg = "回報完成";
        qDebug()<<" Time : 3:"<<GLOBAL.dateTimeUtc8().toString("yy/MM/dd hh:mm:ss:zzz");

        if(bOk)
            UI.showMsg("","回報完成",QStringList()<<"OK");
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




    ACTION.getUser(true);

    ACTION.getOrder(true);

    m_listFactory.clear();


    DataFactory tmp;

    tmp.Id="ABD";

    tmp.Name="艾比代";

    //    m_listFactory.append(tmp);

    m_listFactory.append(ACTION.getFactoryClass("",true));

    ui->tbOrder->setRowCount(0);

    //ui->cbAddValueType->clear();

    m_bLockLoading = false;

    refreshUser();


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


    refreshUser();
}

