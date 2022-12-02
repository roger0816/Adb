#include "LayerCostSetting.h"
#include "ui_LayerCostSetting.h"

LayerCostSetting::LayerCostSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostSetting)
{
    ui->setupUi(this);

    ui->tbGameItem->setColumnWidth(0,160);
    ui->tbGameItem->setColumnWidth(1,40);

    ui->lbItemTitle0->hide();

    ui->tbGameItem->setMouseTracking(true);

    connect(ui->btnClear,&QPushButton::clicked,[=]()
    {
        ui->txSearch->clear();
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

        GameList d;

        QVariantMap data;

        data["Enable"] = dialog.m_bEnable;

        data["GameRate"] = dialog.m_iGameRate;

        data["Id"] = dialog.m_sId;

        data["Name"] = dialog.m_sName;

        data["GameRate"] = QString::number(dialog.m_iGameRate);

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


    QVariantList listIn,listOut;

    QString sError;
    ACTION.action(ACT::QUERY_GAME_LIST,listIn,listOut,sError);

    m_gameData = listOut;

    ui->tbGame->setRowCount(0);

    m_gameDisplayData.clear();

    for(int i=0;i<m_gameData.length();i++)
    {
        if(!checkSearch(m_gameData.at(i).toMap()))
            continue;

        m_gameDisplayData.append(m_gameData.at(i).toMap());

        int iRow = ui->tbGame->rowCount();

        ui->tbGame->setRowCount(iRow+1);

        DataGameList data(m_gameData.at(i).toMap());

        ui->tbGame->setItem(iRow,0,UI.tbItem(data.Id));

        ui->tbGame->setItem(iRow,1,UI.tbItem(data.GameRate));

        ui->tbGame->setItem(iRow,2,UI.tbItem(data.Name));


    }




    /*
    m_gameList.setGameList(listOut);

    ui->tbGame->setRowCount(0);

    for(int i=0;i<m_gameList.listData.length();i++)
    {
        ui->tbGame->setRowCount(i+1);


        ui->tbGame->setItem(i,0,UI.tbItem(m_gameList.listData.at(i).Id));

        ui->tbGame->setItem(i,1,UI.tbItem(m_gameList.listData.at(i).GameRate));

        ui->tbGame->setItem(i,2,UI.tbItem(m_gameList.listData.at(i).Name));


    }

    */

}

void LayerCostSetting::refreshItemList()
{

    int iGameRow = ui->tbGame->currentRow();
    m_listItem.clear();

    ui->tbGameItem->setRowCount(0);

    if(iGameRow<0 || iGameRow>= m_gameDisplayData.length())
    {
        m_iCurrentGameSid = -1;
        ui->lbItemTitle0->hide();
        ui->lbItemTitle1->setText("請先在左側選擇遊戲");

        return;
    }


    DataGameList gameData(m_gameDisplayData.at(iGameRow).toMap());

    double GameRate = gameData.GameRate;

    QString sGameName = gameData.Name;

    m_iCurrentGameSid = gameData.Sid.toInt();

    ui->lbItemTitle0->show();

    ui->lbItemTitle0->setText(sGameName);

    ui->lbItemTitle1->setText("商品內容");


    QVariantMap d;

    d["GameSid"] = m_iCurrentGameSid;


    QString sError;

    bool bOk = ACTION.action(ACT::QUERY_GAME_ITEM,d,m_listItem,sError);

    if(!bOk)
    {
        UI.showMsg("",sError,"OK");

        return;
    }

    // DataExchange::Rate rate = ACTION.rate();

    QList<DataRate> tmp = ACTION.listRate("",true,true);

    DataRate rate2;

    if(tmp.length()>0)
        rate2 = tmp.last();



    m_listTipData.clear();

    CListPair listCurrent = ACTION.getAddValueType();

    for(int i=0;i<m_listItem.length();i++)
    {
        QVariantMap toolData;
        DataGameItem data(m_listItem.at(i).toMap());


        ui->tbGameItem->setRowCount(i+1);

        ui->tbGameItem->setItem(i,0,UI.tbItem(data.Name));

        ui->tbGameItem->setItem(i,1,UI.tbItem(data.Enable));

        ui->tbGameItem->setItem(i,2,UI.tbItem(data.OrderNTD));

        ui->tbGameItem->setItem(i,3,UI.tbItem(data.Bonus));

        double iNTD = GameRate*data.Bonus.toDouble();

        ui->tbGameItem->setItem(i,4,UI.tbItem(QString::number(iNTD,'f',0)));

        //  ui->tbGameItem->setItem(i,4,UI.tbItem(data.NTD));

        toolData["NTD"] = QString::number(iNTD,'f',0);
        toolData["USD"] = QString::number(iNTD/rate2.USD(),'f',2);
        toolData["HKD"] = QString::number(iNTD/rate2.HKD(),'f',0);
        toolData["RMB"] = QString::number(iNTD/rate2.RMB(),'f',0);
        toolData["MYR"] = QString::number(iNTD/rate2.MYR(),'f',0);
        toolData["SGD"] = QString::number(iNTD/rate2.SGD(),'f',1);
        CListPair p(data.AddValueTypeSid);
        QStringList listSid =p.listFirst();
        QStringList listCost =p.listSecond();

        QStringList listData;

        for(int j=0;j<listSid.length() && j<listCost.length();j++)
        {
            QString sName= ACTION.getAddValueName(listSid.at(j));

            if(sName.trimmed()=="")
                continue;

            listData.append(sName+"="+listCost.at(j));
        }


        toolData["AddValueTypeSid"] = listData.join("\n");

        m_listTipData.append(toolData);

        ui->tbGameItem->setItem(i,5,UI.tbItem(listData.join(" ; "),GlobalUi::_TOOLTIP));
    }



}

bool LayerCostSetting::checkSearch(QVariantMap data)
{
    QString searchKey = ui->txSearch->text();

    if(searchKey.trimmed()=="")
        return true;
    QStringList listKey = searchKey.split("&");

    DataGameList gameData(data);

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
        QVariantMap data;

        data["Enable"] = dialog.m_bEnable;

        data["Sid"] = dialog.m_sSid;

        data["Id"] = dialog.m_sId;

        data["Name"] = dialog.m_sName;

        data["GameRate"] = QString::number(dialog.m_iGameRate);

        QString sError;

        ACTION.action(ACT::EDIT_GAME_LIST,data,sError);
        UI.showMsg("",sError,"OK");


        ACTION.updateGameItemPrice(dialog.m_sSid,dialog.m_iGameRate);

        refreshGameList();

        refreshItemList();

    }
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


    DataRate rate;

    if(ACTION.listRate("",true,true).length()>0)
        rate=ACTION.listRate("",true,true).last();

    dialog.setRate(sGameName+" : 新增商品",rate);
    QVariantMap dat;

    dialog.setData(iGameRate,dat);

    if(dialog.exec()==1)
    {
        QVariantMap data =dialog.data();

        data["GameSid"] = m_iCurrentGameSid;

        QString sError;

        bool b = ACTION.action(ACT::ADD_GAME_ITEM,data,sError);


        if(!b)
        {
            UI.showMsg("",sError,"OK");

            return;
        }
        DataItemCount dataCount;

        dataCount.Id = data["GameSid"].toString();
        dataCount.GameItemSid = data["Sid"].toString();
        dataCount.Name = data["Name"].toString();

        ACTION.action(ACT::ADD_ITEM_COUNT,dataCount.data(),sError);

        UI.showMsg("",sError,"OK");


        refreshItemList();




    }
}




void LayerCostSetting::on_tbGame_cellClicked(int , int )
{

    refreshItemList();
}


void LayerCostSetting::on_btnItemEdit_clicked()
{
    if(ui->tbGame->currentRow()<0 || ui->tbGame->currentRow()>= m_gameDisplayData.length())
    {
        UI.showMsg("","請先在左側選擇遊戲","OK");

        return ;
    }

    if(ui->tbGameItem->currentRow()<0 || ui->tbGameItem->currentRow()>= m_listItem.length())
    {
        UI.showMsg("","請先選擇要修改的商品","OK");

        return ;
    }


    DialogEditGameItem dialog;

    DataGameList gameData( m_gameDisplayData.at(ui->tbGame->currentRow()).toMap());

    QString sGameName =gameData.Name;

    double gameRate=gameData.GameRate;

    DataRate rate;

    QList<DataRate> listTmp =ACTION.listRate("",true,true);

    if(listTmp.length()>0)
        rate = listTmp.last();

    dialog.setRate(sGameName+" : 修改商品",rate);

    dialog.setData(gameRate,m_listItem.at(ui->tbGameItem->currentRow()).toMap());

    int iRet = dialog.exec();

    if(iRet==1)
    {
        QVariantMap data =dialog.data();

        data["GameSid"] = m_iCurrentGameSid;

        QString sError;

        ACTION.action(ACT::EDIT_GAME_ITEM,data,sError);

        UI.showMsg("",sError,"OK");


        QVariantList dTmp;
        QVariantMap inTmp;
        inTmp["GameItemSid"]=data["Sid"].toString();
        ACTION.action(ACT::QUERY_ITEM_COUNT,inTmp,dTmp,sError);

        DataItemCount dataCount;

        if(dTmp.length()>0)
            dataCount.setData(dTmp.last().toMap());

        dataCount.Id = data["GameSid"].toString();
        dataCount.GameItemSid = data["Sid"].toString();
        dataCount.Name = data["Name"].toString();

        ACTION.action(ACT::EDIT_ITEM_COUNT,dataCount.data(),sError);



        refreshItemList();

    }

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


void LayerCostSetting::on_tbGame_cellDoubleClicked(int , int )
{
    on_btnGameEdit_clicked();
}


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

    if(column==4)
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
    else  if(column==5)
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

