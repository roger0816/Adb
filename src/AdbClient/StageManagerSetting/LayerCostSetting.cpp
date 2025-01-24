#include "LayerCostSetting.h"
#include "ui_LayerCostSetting.h"



LayerCostSetting::LayerCostSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostSetting)
{
    ui->setupUi(this);

    ui->tbGameItem->setColumnWidth(_Sid,60);
    ui->tbGameItem->setColumnWidth(_Name,160);
    ui->tbGameItem->setColumnWidth(_Enable,40);
    ui->tbGameItem->setColumnWidth(_ForApi,40);

    connect(ui->btnSortUp,&QPushButton::clicked,this,&LayerCostSetting::on_btnSortUp);

    connect(ui->btnSortTop,&QPushButton::clicked,this,&LayerCostSetting::on_btnSortTop);

    connect(ui->btnSortDown,&QPushButton::clicked,this,&LayerCostSetting::on_btnSortDown);

    connect(ui->btnSortSave,&QPushButton::clicked,this,&LayerCostSetting::on_btnSortSave);

    ui->lbItemTitle0->hide();

    ui->tbGameItem->setMouseTracking(true);

    connect(ui->btnClear,&QPushButton::clicked,[=]()
    {
        ui->txSearch->clear();
    });


    connect(&DATA,&UpdateData::updateNotify,this,[=](int iType){
        if(iType==GAME_LIST || iType==GAME_ITEM )
            refresh();
    });
}

LayerCostSetting::~LayerCostSetting()
{
    delete ui;
}





void LayerCostSetting::on_btnGameAdd_clicked()
{
    DialogGameEdit dialog;

    if(dialog.exec()==1)
    {



        QVariantMap data;

        data["Enable"] = dialog.m_bEnable;

        //  data["GameRate"] = dialog.m_iGameRate;

        data["Id"] = dialog.m_sId;

        data["Name"] = dialog.m_sName;

        data["GameRate"] = QString::number(dialog.m_iGameRate);

        data["UserSid"] = ACTION.m_currentUser.Sid;

        QString sError;

        ACTION.action(ACT::ADD_GAME_LIST,data,sError);


        UI.showMsg("",sError,"OK");


        refreshGameList();

        refreshItemList();

    }
}

void LayerCostSetting::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}



void LayerCostSetting::refreshGameList()
{
    m_listGame = DATA.getGameList();


    ui->tbGame->setRowCount(0);

    m_gameDisplayData.clear();

    for(int i=0;i<m_listGame.length();i++)
    {
        DataGameList gameList = m_listGame.at(i);
        if(!checkSearch(gameList))
            continue;

        m_gameDisplayData.append(gameList.data());

        int iRow = ui->tbGame->rowCount();

        ui->tbGame->setRowCount(iRow+1);


        ui->tbGame->setItem(iRow,0,UI.tbItem(gameList.Id));

        ui->tbGame->setItem(iRow,1,UI.tbItem(gameList.GameRate));

        ui->tbGame->setItem(iRow,2,UI.tbItem(gameList.Name));

        if(gameList.Sid == m_sPreGameSid)
        {
            ui->tbGame->setCurrentCell(iRow,0);
        }

    }



}

void LayerCostSetting::refreshItemList()
{

    qDebug()<<"refresh item 1";
    int iGameRow = ui->tbGame->currentRow();

    ui->tbGameItem->setRowCount(0);

    if(iGameRow<0 || iGameRow>= m_gameDisplayData.length())
    {
        m_sCurrentGameSid = "";
        ui->lbItemTitle0->hide();
        ui->lbItemTitle1->setText("請先在左側選擇遊戲");

        return;
    }


    qDebug()<<"refresh item 2";

    DataGameList gameData(m_gameDisplayData.at(iGameRow).toMap());

    double GameRate = gameData.GameRate;

    QString sGameName = gameData.Name;

    m_sCurrentGameSid = gameData.Sid;

    ui->lbItemTitle0->show();

    ui->lbItemTitle0->setText(sGameName);

    ui->lbItemTitle1->setText("商品內容");

    m_listGameItem = DATA.getGameItemFromGameSid(m_sCurrentGameSid,false);

    qDebug()<<"refresh item 3";
    DataRate rate2;
    // rate2=ACTION.costRate("",true);
    rate2 = DATA.costRate();

    m_listTipData.clear();

    CListPair listCurrent = DATA.getAddValueType();

    qDebug()<<"refresh item 4";
    for(int i=0;i<m_listGameItem.length();i++)
    {
        QVariantMap toolData;
        DataGameItem data= m_listGameItem.at(i);



        ui->tbGameItem->setRowCount(i+1);

        ui->tbGameItem->setItem(i,_Sid,UI.tbItem(data.Sid));

        ui->tbGameItem->setItem(i,_Name,UI.tbItem(data.Name));

        ui->tbGameItem->setItem(i,_Enable,UI.tbItem(data.Enable));

        ui->tbGameItem->setItem(i,_OrderNTD,UI.tbItem(data.OrderNTD));

        QString sTmp ="是";

        if (!data.ForApi)
            sTmp ="否";

        ui->tbGameItem->setItem(i,_ForApi,UI.tbItem(sTmp));

        ui->tbGameItem->setItem(i,_Bonus,UI.tbItem(data.Bonus));

        double iNTD = GameRate*data.Bonus.toDouble();

        ui->tbGameItem->setItem(i,_Cost,UI.tbItem(COMMON.addFlow(iNTD)));

        //  ui->tbGameItem->setItem(i,4,UI.tbItem(data.NTD));

        toolData["NTD"] = QString::number(COMMON.addFlow(iNTD));
        toolData["USD"] = QString::number(COMMON.addFlow(iNTD/rate2.USD(),2));
        toolData["HKD"] = QString::number(COMMON.addFlow(iNTD/rate2.HKD()));
        toolData["RMB"] = QString::number(COMMON.addFlow(iNTD/rate2.RMB()));
        toolData["MYR"] = QString::number(COMMON.addFlow(iNTD/rate2.MYR()));
        toolData["SGD"] = QString::number(COMMON.addFlow(iNTD/rate2.SGD(),1));
        CListPair p(data.AddValueTypeSid);
        QStringList listSid =p.listFirst();
        QStringList listCost =p.listSecond();

        QStringList listData;

        for(int j=0;j<listSid.length() && j<listCost.length();j++)
        {
            QString sName= DATA.getAddValueName(listSid.at(j));

            if(sName.trimmed()=="")
                continue;

            listData.append(sName+"="+listCost.at(j));
        }


        qDebug()<<"refresh item 5";
        toolData["AddValueTypeSid"] = listData.join("\n");

        m_listTipData.append(toolData);

        ui->tbGameItem->setItem(i,_PayType,UI.tbItem(listData.join(" ; "),GlobalUi::_TOOLTIP));
    }


    qDebug()<<"refresh item 6";
}

bool LayerCostSetting::checkSearch(DataGameList gameData)
{
    QString searchKey = ui->txSearch->text();

    if(searchKey.trimmed()=="")
        return true;
    QStringList listKey = searchKey.split("&");


    bool bRe = false;

    QList<int> listOk;

    foreach(QString v, listKey)
    {

        QString sKey = v.toUpper().trimmed();

        if(sKey=="")
            continue;

        int iOk = 0;

        if(gameData.Name.toUpper().contains(sKey))
            iOk = 1;
        else if(gameData.Id.toUpper().contains(sKey))
            iOk =1;
        else if(QString::number(gameData.GameRate).toUpper().contains(sKey))
            iOk = 1;

        listOk.append(iOk);
    }

    bRe = !listOk.contains(0);

    return bRe;


}

void LayerCostSetting::refresh()
{
    refreshGameList();

    refreshItemList();
}








void LayerCostSetting::on_btnGameEdit_clicked()
{
    int iRow = ui->tbGame->currentRow();

    if(iRow<0)
    {
        UI.showMsg("","請先選擇要編輯的遊戲。","OK");

        return ;
    }

    if(iRow>=m_gameDisplayData.length())
        return ;
    DataGameList gameData (m_gameDisplayData.at(iRow).toMap());

    /*
    if(iRow>=m_gameList.listData.length())
        return ;

    GameList::GameData gameData = m_gameList.listData.at(iRow);
    */
    DialogGameEdit dialog;

    dialog.setData(gameData.Sid, gameData.Enable,gameData.Id,gameData.Name,gameData.GameRate);

    int iRet = dialog.exec();

    if(iRet==2)
    {


        DataGameList d;
        d.Enable=dialog.m_bEnable;
        d.Sid=dialog.m_sSid;
        d.Id=dialog.m_sId;
        d.Name=dialog.m_sName;
        d.GameRate=dialog.m_iGameRate;
        d.UserSid= ACTION.m_currentUser.Sid;

        QVariantMap old =DATA.getGameList(dialog.m_sSid).data();

        old.remove("SellNote");
        d.BK=COMMON.toBkString(old);

        QString sError;

         ACTION.action(ACT::EDIT_GAME_LIST,d.data(),sError);

        UI.showMsg("",sError,"OK");

        if(!ACTION.isNewVersion())
            ACTION.updateGameItemPrice(dialog.m_sSid,dialog.m_iGameRate);

        refreshGameList();

        refreshItemList();

    }
    else if(iRet==3)
    {

        DataGameList d;
        d.Enable=dialog.m_bEnable;
        d.Sid=dialog.m_sSid;
        d.Id=dialog.m_sId;
        d.Name=dialog.m_sName;
        d.GameRate=dialog.m_iGameRate;
        d.UserSid= ACTION.m_currentUser.Sid;
        d.IsDelete=1;

        QString sError;

         ACTION.action(ACT::EDIT_GAME_LIST,d.data(),sError);
        UI.showMsg("",sError.replace("修改","刪除"),"OK");


        refreshGameList();

        refreshItemList();


    }


    /*
    else if(iRet==3)
    {


        QVariantMap data;

        data["Sid"] = dialog.m_sSid;


        QString sError;
        ACTION.action(ACT::DEL_GAME_LIST,data,sError);
        UI.showMsg("",sError,"OK");

        refreshGameList();

        refreshItemList();


    }
    */


}


void LayerCostSetting::on_btnItemAdd_clicked()
{

    if(ui->tbGame->currentRow()<0 || ui->tbGame->currentRow()>= m_gameDisplayData.length())
    {
        UI.showMsg("","請先在左側選擇遊戲","OK");

        return ;
    }


    DialogEditGameItem dialog;

    DataGameList gameData(m_gameDisplayData.at(ui->tbGame->currentRow()).toMap());

    QString sGameName = gameData.Name;

    double iGameRate = gameData.GameRate;


    DataRate rate = DATA.costRate("");

    //    if(ACTION.listRate("",true,true).length()>0)
    //        rate=ACTION.listRate("",true,true).last();

    dialog.setRate(sGameName+" : 新增商品",rate);
    QVariantMap dat;
    dat["Sort"]=m_listGameItem.length()+1;
    dat["Enable"] = true;
    dialog.setData(iGameRate,dat);

    if(dialog.exec()==1)
    {



        QVariantMap data =dialog.data();
        QString sError;

        data["GameSid"] = m_sCurrentGameSid;


        if(!ACTION.isNewVersion())
        {


            bool b = ACTION.action(ACT::ADD_GAME_ITEM,data,sError);


            if(!b)
            {
                UI.showMsg("",sError,"OK");

                return;
            }


            DataItemCount dataCount;

            dataCount.GameSid = data["GameSid"].toString();
            dataCount.GameItemSid = data["Sid"].toString();
            dataCount.Name = data["Name"].toString();
            //dataCount.TotalCount = data["Count"].toLongLong();

            ACTION.action(ACT::ADD_ITEM_COUNT,dataCount.data(),sError);

        }
        else
        {
            QVariantMap tmpD;
            tmpD["Data"]=data;
            tmpD["Count"]=data["Count"].toLongLong();
            bool b = ACTION.action(ACT::ADD_GAME_ITEM,data,sError);

            if(!b)
            {
                UI.showMsg("",sError,"OK");

                return;
            }


        }
        UI.showMsg("",sError,"OK");


        refreshItemList();

    }
}




void LayerCostSetting::on_tbGame_cellClicked(int row , int )
{
    if(row>=0 && row<m_gameDisplayData.length())
    {
        m_sPreGameSid = m_gameDisplayData.at(row).toMap()["Sid"].toString();
    }
    refreshItemList();
}


void LayerCostSetting::on_btnItemEdit_clicked()
{
    if(ui->tbGame->currentRow()<0 || ui->tbGame->currentRow()>= m_gameDisplayData.length())
    {
        UI.showMsg("","請先在左側選擇遊戲","OK");

        return ;
    }

    if(ui->tbGameItem->currentRow()<0 || ui->tbGameItem->currentRow()>= m_listGameItem.length())
    {
        UI.showMsg("","請先選擇要修改的商品","OK");

        return ;
    }


    DialogEditGameItem dialog;

    dialog.setEanbleCount(false);
    DataGameList gameData( m_gameDisplayData.at(ui->tbGame->currentRow()).toMap());

    QString sGameName =gameData.Name;

    double gameRate=gameData.GameRate;

    DataRate rate= DATA.costRate("");


    dialog.setRate(sGameName+" : 修改商品",rate);
    DataGameItem gameItem=m_listGameItem.at(ui->tbGameItem->currentRow());
    dialog.setData(gameRate,gameItem.data());

    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap data =dialog.data();

        data["GameSid"] = m_sCurrentGameSid;

        QString sError;

        ACTION.action(ACT::EDIT_GAME_ITEM,data,sError);

        UI.showMsg("",sError,"OK");

        if(dialog.isEnableCount() || !ACTION.isNewVersion())
        {
            QVariantList dTmp;
            QVariantMap inTmp;
            inTmp["GameItemSid"]=data["Sid"].toString();
            ACTION.action(ACT::QUERY_ITEM_COUNT,inTmp,dTmp,sError);

            DataItemCount dataCount;

            if(dTmp.length()>0)
                dataCount.setData(dTmp.last().toMap());

            dataCount.GameSid = m_sCurrentGameSid;
            dataCount.GameItemSid = data["Sid"].toString();
            dataCount.Name = data["Name"].toString();
            // dataCount.TotalCount =data["Count"].toLongLong();

            ACTION.action(ACT::EDIT_ITEM_COUNT,dataCount.data(),sError);
        }


        refreshItemList();

    }


/*
    if(iRet==3)
    {
        QVariantMap data =dialog.data();

        data["GameSid"] = m_sCurrentGameSid;
        data["IsDelete"]=1;

        QString sError;

        ACTION.action(ACT::EDIT_GAME_ITEM,data,sError);

        sError.replace("修改","刪除");

        UI.showMsg("",sError,"OK");


        refreshItemList();

    }
    */


    if(iRet==3)
    {
        QVariantMap data;

        data["Sid"] =  dialog.data()["Sid"];

        QString sError;

        ACTION.action(ACT::DEL_GAME_ITEM,data,sError);

        UI.showMsg("",sError,"OK");


        QVariantMap dataCount;
        dataCount["GameItemSid"]=data["Sid"];

        ACTION.action(ACT::DEL_ITEM_COUNT,dataCount,sError);


        refreshItemList();

    }

}


//void LayerCostSetting::on_tbGame_cellDoubleClicked(int , int )
//{
//    on_btnGameEdit_clicked();
//}


void LayerCostSetting::on_tbGameItem_cellDoubleClicked(int , int )
{
    on_btnItemEdit_clicked();

}



void LayerCostSetting::on_tbGameItem_itemEntered(QTableWidgetItem *)
{

    // QToolTip::showText(QCursor::pos(),item->text());
}


void LayerCostSetting::on_tbGameItem_cellEntered(int row, int column)
{
    if(row<0 || row>=ui->tbGameItem->rowCount() || row>=m_listTipData.length())
        return;

    //  QString sName =ui->tbGameItem->itemAt(row,0)->text();

    QVariantMap data = m_listTipData.at(row).toMap();

    if(column==_Cost)
    {
        QString st=
                "新台幣 : %1 \n "
                "美金 : %2 \n "
                "港幣 : %3 \n "
                "人民幣 : %4 \n "
                "林吉特 : %5 \n "
                "新加坡元 : %6 ";

        st = st.arg(data["NTD"].toString())
                .arg(data["USD"].toString())
                .arg(data["HKD"].toString())
                .arg(data["RMB"].toString())
                .arg(data["MYR"].toString())
                .arg(data["SGD"].toString());


        QToolTip::showText(QCursor::pos(),st);
    }
    else  if(column==_PayType)
    {

        QToolTip::showText(QCursor::pos(),data["AddValueTypeSid"].toString());
    }
    else
    {
        //  QToolTip::hideText();
    }


}


void LayerCostSetting::on_txSearch_textChanged(const QString &)
{
    refresh();
}



void LayerCostSetting::on_btnSortUp()
{
    int iRow = ui->tbGameItem->currentRow();

    if(iRow==0)
        return ;

    if(iRow<0 || iRow>=ui->tbGameItem->rowCount())
    {
        UI.showMsg("","請先選擇商品","OK");
        return ;
    }

    QTableWidgetItem *current=ui->tbGameItem->currentItem();
    int columnCount = ui->tbGameItem->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbGameItem->takeItem(iRow, col));
    }

    ui->tbGameItem->removeRow(iRow);
    ui->tbGameItem->insertRow(iRow - 1);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbGameItem->setItem(iRow - 1, col, items.at(col));
    }

    ui->tbGameItem->setCurrentItem(current);
}

void LayerCostSetting::on_btnSortTop()
{
    int iRow = ui->tbGameItem->currentRow();

    if(iRow==0)
        return ;

    if(iRow<0 || iRow>=ui->tbGameItem->rowCount())
    {
        UI.showMsg("","請先選擇商品","OK");
        return ;
    }




    QTableWidgetItem *current=ui->tbGameItem->currentItem();
    int columnCount = ui->tbGameItem->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbGameItem->takeItem(iRow, col));
    }

    ui->tbGameItem->removeRow(iRow);
    ui->tbGameItem->insertRow(0);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbGameItem->setItem(0, col, items.at(col));
    }

    ui->tbGameItem->setCurrentItem(current);

}


void LayerCostSetting::on_btnSortDown()
{
    int iRow = ui->tbGameItem->currentRow();

    if(iRow==ui->tbGameItem->rowCount()-1)
        return ;

    if(iRow<0 || iRow>=ui->tbGameItem->rowCount())
    {
        UI.showMsg("","請先選擇商品","OK");
        return ;
    }

    QTableWidgetItem *current=ui->tbGameItem->currentItem();
    int columnCount = ui->tbGameItem->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbGameItem->takeItem(iRow, col));
    }

    ui->tbGameItem->removeRow(iRow);
    ui->tbGameItem->insertRow(iRow + 1);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbGameItem->setItem(iRow + 1, col, items.at(col));
    }

    ui->tbGameItem->setCurrentItem(current);
}


void LayerCostSetting::on_btnSortSave()
{




    QVariantList list;

    for(int i=0;i<ui->tbGameItem->rowCount();i++)
    {
        QVariantMap d;
        d["Sid"]=ui->tbGameItem->item(i,_Sid)->text().toInt();
        d["Sort"]=i+1;
        list.append(d);
    }
    QString sError;





#ifdef _BUSY_TEST
    ACTION.action(ACT::EDIT_GAME_ITEM,list,sError);

    while (1) {

        if(!ACTION.m_bIsLock)
            ACTION.action(ACT::EDIT_GAME_ITEM,list,sError);

    }
#else

    bool bOk=ACTION.action(ACT::EDIT_GAME_ITEM,list,sError);

    if(bOk)
        UI.showMsg("","排序已修改","OK");
    else
        UI.showMsg("",sError,"OK");
#endif
}



