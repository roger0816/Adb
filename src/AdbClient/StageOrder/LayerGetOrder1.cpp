#include "LayerGetOrder1.h"
#include "ui_LayerGetOrder1.h"

LayerGetOrder1::LayerGetOrder1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerGetOrder1)
{
    ui->setupUi(this);

    connect(ui->btnCancel,&QPushButton::clicked,this,&LayerGetOrder1::slotCancel);


    m_layerCost = new LayerOrder;

    m_layerCost->setReadOnly();
    m_layerCost->hide();

    ui->wBottom->setCurrentIndex(0);


    connect(&DATA,&UpdateData::updateNotify,this,[=](int iType,QStringList listSid)
    {
        if(iType == ORDER_DATA)
        {
            refresh();
            if(m_sWaitSid!="" && listSid.contains(m_sWaitSid))
            {
                uiWait(_NONE);
            }

        }
    });

    ui->wPic0->hide();

    startTimer(1000);

}

LayerGetOrder1::~LayerGetOrder1()
{
    delete ui;
}

void LayerGetOrder1::init()
{
    refresh();
}

void LayerGetOrder1::refreshUser()
{


    if(m_bLockLoading)
        return ;

    m_bLockLoading= true;


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



    auto makeData = [=](){

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

            if(listKeyUser.indexOf(order.Owner)<0 &&order.Owner!="")
                continue;

            if(order.Step=="1" || (order.Step=="2" && order.PaddingUser.trimmed()!=""))
            {

                QVariantList list =m_data[order.Owner].toList();

                list.append(order.data());

                m_data[order.Owner] = list;
            }

        }
    };


    makeData();
    //GLOBAL.runWorkerThreadWithTimeout2(makeData,3000);



    auto makeUi=[=](){
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

    };


    makeUi();


    if(iRow>=0 && iRow<ui->tbUser->rowCount() && iCol>=0 && iCol<ui->tbUser->columnCount())
    {
        ui->tbUser->setCurrentCell(iRow,iCol);
        on_tbUser_cellPressed(iRow,iCol);
    }


    m_bLockLoading= false;


}

//void LayerGetOrder1::uiWait(bool bLock)
//{

////    if(!m_bLockUi)
////        return ;

//     UI.slotLockLoading(bLock);

//    // m_bLockUi = bLock;
//    QEventLoop *loop=new QEventLoop(this);
//    loop->connect(this,&LayerGetOrder1::dataUpdate,loop,&QEventLoop::quit);

//    UI.slotLockLoading(true);
//    loop->exec();
//    UI.slotLockLoading(false);
//    loop->disconnect();
//    loop->deleteLater();
//}



void LayerGetOrder1::on_tbUser_cellPressed(int row, int column)
{

    //    if(ui->tbOrder->rowCount()!=0)
    //        return ;

    if(row<0 || row>=ui->tbUser->rowCount())
    {
        ui->tbOrder->setRowCount(0);
        ui->wBottom->setCurrentIndex(0);
        return;
    }
    if(column<0 || column>=ui->tbUser->columnCount())
    {
        ui->tbOrder->setRowCount(0);
        ui->wBottom->setCurrentIndex(0);

        return;
    }
    if(ui->tbUser->item(row,column)==nullptr  || ui->tbUser->item(row,column)->text()
            .split("(").last().split(")").first().toInt()<1)
    {
        ui->tbOrder->setRowCount(0);
        ui->wBottom->setCurrentIndex(0);
        return;
    }

    // QTableWidgetItem *item =ui->tbUser->item(row,column);
    // ui->tbUser->setCurrentCell(row,column);



    int iIdx = row*ui->tbUser->columnCount()+column;
    QString sKey= m_listFactory.at(iIdx).Name;
    m_currentDataKey = sKey;




    //  ui->cbAddValueType->setVisible(sKey=="艾比代");

    QVariantList listItem = m_data[sKey].toList();

    ui->tbOrder->setRowCount(0);



    for(int i=0;i<listItem.length();i++)
    {
        ui->tbOrder->setRowCount(i+1);

        OrderData order(listItem.at(i).toMap());

        QString sUserCid="";
        if(order.User.length()>1)
        {
            sUserCid = DATA.getUser(order.User.at(1)).Cid;
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
            //#98613D
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

        ui->tbOrder->setItem(i,_Note1,UI.tbItem(order.Note0.at(1),true));

        ui->tbOrder->setItem(i,_Note2,UI.tbItem(order.Note0.at(2),true));

        ui->tbOrder->setItem(i,_Bouns,UI.tbItem(order.Bouns));


        if(order.Step=="1")
        {
            ui->tbOrder->setItem(i,_Status,UI.tbItem("待處理"));
            ui->tbOrder->setItem(i,_Action,UI.tbItem("確認接單",GlobalUi::_BUTTON));
        }

        if(order.Step=="2")
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


void LayerGetOrder1::on_tbOrder_cellPressed(int row, int column)
{

    QVariantList listData =m_data[m_currentDataKey].toList();

    if(row<0 || row>=listData.length())
        return;

    ui->wBottom->setCurrentIndex(0);
    OrderData order(listData.at(row).toMap());
    m_sPreSid = order.Sid;

    if(column==_Id)
    {


        m_layerCost->setData(order);

        m_layerCost->show();

        return ;
    }


    if(column==_Action && ui->tbOrder->item(row,_Action)->text()=="確認接單")
    {
        if(ui->tbUser->currentItem()->text().contains("未分配"))
        {
            QStringList tmpCanType =order.CanSelectPayType.split(";;");
            QStringList tmpCb;

            ui->cbFacChange->clear();

            foreach(DataFactory fac, m_listFactory)
            {
                bool bHas= false;

                foreach(QString sFacPay,fac.PayTypeSid)
                {
                    if(tmpCanType.contains(sFacPay))
                        bHas = true;
                }

                if(bHas)
                    tmpCb.append(fac.Name);
            }

            ui->cbFacChange->addItems(tmpCb);
            while(order.Note0.length()<2)
                order.Note0.append("");
            ui->lbFacNote0->setText(order.Note0.at(1));
            ui->wBottom->setCurrentIndex(2);
            return ;
        }



        if(1==UI.showMsg("",QString("請確認是否鎖定處理編號:%1？").arg(order.Id),QStringList()<<"否"<<"是"))
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
                order.Step="2";
                order.User[2] = ACTION.m_currentUser.Sid;
                order.StepTime[2]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

                //接單(鎖定)
                bool bRe = ACTION.replaceOrder(order,sError);


                if(!bRe)
                {
                    UI.showMsg("Error",sError,"OK");
                }
                else
                {
                    m_sWaitSid=order.Sid;
                    uiWait(_CHECK);
                    return;
                }


            }

            refreshUser();

        }

        return;
    }


    if(column==_Note1 || column==_Note2)
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

        ui->wPic0->slotClear();

        //        QVariantList list;

        //        QVariantMap in;

        //        QString sError;

        //        in["ASC"]="Sort";
        //        ACTION.action(ACT::QUERY_PAY_TYPE,in,list,sError);


        QList<DataPayType> listPayType = DATA.getPayTypeList();


        auto getFac=[=]()
        {
            DataFactory re;

            QList<DataFactory> list=DATA.getFactoryClassList();

            for(int i=0;i<list.length();i++)
            {
                if(list.at(i).Name == order.Owner)
                {
                    re= list.at(i);
                }
            }

            return re;
        };

        DataFactory currentFac = getFac();

        QStringList listCb;

        for(int i=0;i<listPayType.length();i++)
        {
            QString sSid = listPayType.at(i).Sid;

            if(GLOBAL.toList(order.CanSelectPayType).indexOf(sSid)>=0)
            {
                if(currentFac.PayTypeSid.contains(sSid))
                {

                    listCb.append(listPayType.at(i).Name);
                }
            }
        }
        ui->cbAddValueType->clear();

        ui->cbAddValueType->addItems(listCb);



        ui->cbAddValueType->setEditable(true);



        QCompleter *completer=new QCompleter(ui->cbAddValueType->model(),this);
        //        completer->setCompletionMode(QCompleter::PopupCompletion);
        ui->cbAddValueType->setCompleter(completer);


        QString sNote0_0,sNote0_1,sNote0_2;
        if(order.Note0.length()>2)
        {
//            sNote0_0 = order.Note0.at(0);

//            sNote0_1 = order.Note0.at(1);

            sNote0_2=order.Note0.at(2);

        }

        ui->btnDelayOrder->setChecked(sNote0_2.contains("["+ui->btnDelayOrder->text()+"]"));

        ui->txNote->setText(sNote0_2.replace("[訂單延誤]",""));
//        ui->txNote0_0->setText(sNote0_0);

//        ui->txNote0_1->setText(sNote0_1);


        ui->wBottom->setCurrentIndex(1);

    }




}


void LayerGetOrder1::on_btnBackOrder_clicked()
{
    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    int iRet= UI.showMsg("",QString("確定要將此訂單(%1) \n解除處理中的狀態？").arg(order.Id),QStringList()<<"否"<<"是");
    if(iRet !=1)
        return;


    QString sError;

    order.PaddingUser="";
    order.StepTime[2]="";

    order.User[2] = "";


    order.Step="1";
    //解除鎖定
    bool bRe =ACTION.replaceOrder(order,sError);

    if(bRe)
    {
        m_sWaitSid=order.Sid;
        uiWait(_NO_CHECK);
    }
    else
    {
        UI.showMsg("Error",sError,"OK");

        refreshUser();


    }


}


void LayerGetOrder1::on_btnFinish_clicked()
{


    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    if(ui->cbAddValueType->count()<1)
    {

        UI.showMsg("","儲值方式錯誤",QStringList()<<"OK");
        return ;
    }



    QString sText=ui->cbAddValueType->currentText();



    if(ui->cbAddValueType->findText(sText)<0)
    {
        UI.showMsg("","錯誤,請填寫正確的儲值方式",QStringList()<<"OK");
        return ;
    }

    //166;;165;;154;;158;;181;;151;;149;;152;;155;;153;;167;;156
    //171;;180;;181;;150

    int iRet= UI.showMsg("",QString("請再確認訂單(%1) \n已完成儲值處理？").arg(order.Id),QStringList()<<"否"<<"是");

    if(iRet!=1)
        return;


    QString sError;

    order.PaddingUser="";

    int iIdxPayType = m_listPayType.listSecond().indexOf(ui->cbAddValueType->currentText());


    if(iIdxPayType>=0)
    {
        QString PayTypeSid = m_listPayType.listFirst().at(iIdxPayType);
        order.PayType=PayTypeSid;
    }
    order.Step="3";

    order.StepTime[3]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");


    order.User[3] = ACTION.m_currentUser.Sid;

    QString sNote= ui->txNote->toPlainText();


    if(ui->btnDelayOrder->isChecked())
    {
        sNote="["+ui->btnDelayOrder->text()+"]"+sNote;
    }


    order.Note0[3]=sNote;


    order.Pic0 = ui->wPic0->uploadPic();

    bool bRe=ACTION.replaceOrder(order,sError);

    if(bRe)
    {
        m_sWaitSid=order.Sid;
        uiWait(_FINISH,sError);
    }
    else
    {
        UI.showMsg("Error",sError,"OK");

        refreshUser();
    }


}

void LayerGetOrder1::refresh()
{

    if(m_bLockLoading)
        return ;

    m_bLockLoading= true;

    ui->wBottom->setCurrentIndex(0);
    //ACTION.getUser(true);

    // ACTION.getOrder(true);

    m_listPayType = DATA.getAddValueType();

    m_listFactory.clear();


    m_listFactory.append(DATA.getFactoryClassList());

    ui->cbFacChange->clear();

    QStringList listFacName;
    foreach(DataFactory fc,m_listFactory)
    {
        listFacName.append(fc.Name);
    }

    ui->cbFacChange->addItems(listFacName);

    //    DataFactory fcLine;
    //    fcLine.Name="未分配";

    //    m_listFactory.append(fcLine);


    ui->tbOrder->setRowCount(0);

    ui->cbAddValueType->clear();

    m_bLockLoading= false;


    refreshUser();


    emit dataUpdate();
}


void LayerGetOrder1::on_btnChangeNote_clicked()
{
    // ui->lbDelay->setVisible(ui->btnDelay->isChecked());

    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);


    QString sError;


    QString sNote= ui->txNote->toPlainText();


    if(ui->btnDelayOrder->isChecked())
    {
        sNote="["+ui->btnDelayOrder->text()+"]"+sNote;
    }


    order.Note0[2]=sNote;

    bool bRe=ACTION.replaceOrder(order,sError);

    if(bRe)
    {
        m_sWaitSid=order.Sid;
        uiWait(_NOTE);
    }
    else
    {
        UI.showMsg("Error",sError,"OK");

        refreshUser();
    }






}


void LayerGetOrder1::slotCancel()
{


    if(UI.showMsg("","確定要取消訂單嗎？",QStringList()<<"否"<<"是")==0)
        return;



    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    order.Step="-1";

    order.StepTime[1]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

    // order.PaddingUser="";
    order.Pic0 = ui->wPic0->uploadPic();
    QString sError;
    bool bOk =ACTION.replaceOrder(order,sError);
    if(bOk)
    {
        m_sWaitSid=order.Sid;
        uiWait(_CANCEL,"訂單已取消");
    }
    else
    {
        UI.showMsg("",sError,"OK");

        refreshUser();
    }


}


void LayerGetOrder1::on_btnDelayOrder_clicked()
{

}


void LayerGetOrder1::on_btnFacChange_clicked()
{
    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    order.StepTime[1]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

    // order.PaddingUser="";
    order.Owner=ui->cbFacChange->currentText();
    order.User[1]=ACTION.m_currentUser.Sid;
    QString sError;
    bool bOk =ACTION.replaceOrder(order,sError);


    if(bOk)
    {
        m_sWaitSid=order.Sid;
        uiWait(_API_SET,"已修改訂單負責人");
    }
    else
    {
        UI.showMsg("",sError,"OK");

        refreshUser();
    }



}


void LayerGetOrder1::on_btnFacCancel_clicked()
{


    QVariantList listData =m_data[m_currentDataKey].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    order.Step="-1";

    order.StepTime[1]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

    // order.PaddingUser="";
    //order.Pic0 = ui->wPic0->uploadPic();
    QString sError;
    bool bOk =ACTION.replaceOrder(order,sError);

    if(bOk)
    {
        m_sWaitSid=order.Sid;

        uiWait(_API_CANCEL,"訂單已取消");
    }
    else
    {
        UI.showMsg("",sError,"OK");

        refreshUser();
    }



}

void LayerGetOrder1::uiWait(_LockStatus iType, QString sMsg)
{
    if(iType==_NONE && m_uiLockStatus==_NONE)
    {
        m_iUiLockTimeSec=0;

        return;
    }


    if(iType!=_NONE && iType!=_TIMEOUT)
    {
        m_uiLockStatus = iType;

        m_sUnLockMsg =sMsg;

        UI.slotLockLoading(true);

        return;
    }



    _LockStatus unLockStatus=m_uiLockStatus;

    UI.slotLockLoading(false);
    m_sWaitSid="";
    m_uiLockStatus = _NONE;
    m_iUiLockTimeSec=0;

    if(iType==_TIMEOUT)
    {
        m_sUnLockMsg="連線逾時";
    }

    if(unLockStatus!=_CHECK && unLockStatus!=_NO_CHECK && unLockStatus!=_NOTE)
        UI.showMsg("",m_sUnLockMsg,"OK");


}

void LayerGetOrder1::timerEvent(QTimerEvent *)
{
    if(m_uiLockStatus!=_NONE)
    {
        m_iUiLockTimeSec++;

        if(m_iUiLockTimeSec>15)
        {

            uiWait(_TIMEOUT);

        }


    }


}



