#include "LayerCostTable.h"
#include "ui_LayerCostTable.h"

LayerCostTable::LayerCostTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostTable)
{
    ui->setupUi(this);

    ui->tbGameItem->setColumnWidth(1,140);

    ui->tabWidget->setCurrentWidget(ui->page0);

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slotTabCurrentChanged(int)));

    connect(ui->btnClear,&QPushButton::clicked,[=]()
    {
        ui->txSearch->clear();
    });

}

LayerCostTable::~LayerCostTable()
{
    delete ui;
}

void LayerCostTable::init()
{
    refreshGameList();
}


void LayerCostTable::refreshGameList()
{

    bool bEdit = ACTION.m_currentUser.Lv>=USER_LV::_LV2;

#if (QT_VERSION<= QT_VERSION_CHECK(5,15,0))
    ui->tabWidget->setTabEnabled(1,bEdit);
    ui->tabWidget->setTabEnabled(2,bEdit);
#else
    ui->tabWidget->setTabVisible(1,bEdit);
    ui->tabWidget->setTabVisible(2,bEdit);
#endif



   // m_listGame = ACTION.getGameList(true);
    m_listGame = DATA.getGameList(false);

    int iOldIdx = ui->tbGame->currentRow();

    ui->tbGame->setRowCount(0);

    m_listGameDisplay.clear();

    for(int i=0;i<m_listGame.length();i++)
    {

        int iRow = ui->tbGame->rowCount();

        if(!checkSearch(m_listGame[i].data()))
            continue;

        ui->tbGame->setRowCount(iRow+1);

        ui->tbGame->setItem(iRow,0,UI.tbItem(m_listGame.at(i).Id));

        //  ui->tbGame->setItem(i,1,UI.tbItem(m_gameList.listData.at(i).Enable));

        ui->tbGame->setItem(iRow,1,UI.tbItem(m_listGame.at(i).Name));

        m_listGameDisplay.append(m_listGame.at(i));
    }

    if(iOldIdx>=0 && iOldIdx< ui->tbGame->rowCount())
    {
        ui->tbGame->setCurrentCell(iOldIdx,0);

    }

}




void LayerCostTable::on_tbGame_cellPressed(int row, int )
{
    if(row<0 || row>=m_listGameDisplay.length())
        return;

    QString sGameSid = m_listGameDisplay.at(row).Sid;

    double iGameRate = m_listGameDisplay.at(row).GameRate;

    ui->txEdit->setText(m_listGameDisplay.at(row).SellNote);

    DataRate rate = DATA.costRate("");

    QVariantMap d;

    d["GameSid"] = sGameSid;

    QVariantList listItem;

    QString sError;

    m_currentItems =DATA.getGameItemFromGameSid(sGameSid,false);




    ui->tbGameItem->setRowCount(0);

    for(int i=0;i<m_currentItems.length();i++)
    {
        int iRow = ui->tbGameItem->rowCount();


        DataGameItem item = m_currentItems.at(i);


        double iOriNtd = item.Bonus.toDouble()*iGameRate;

        double iNtd =COMMON.addFlow(iOriNtd);

        double iUsd = COMMON.addFlow(iOriNtd/rate.USD(),2);
        double iHkd = COMMON.addFlow(iOriNtd/rate.HKD());
        double iRmb = COMMON.addFlow(iOriNtd/rate.RMB());
        double iMyr = COMMON.addFlow(iOriNtd/rate.MYR());
        double iSgd = COMMON.addFlow(iOriNtd/rate.SGD(),1);


        ui->tbGameItem->setRowCount(iRow+1);

        ui->tbGameItem->setItem(iRow,0,UI.tbItem(item.Sid));

        ui->tbGameItem->setItem(iRow,1,UI.tbItem(item.Name));

        ui->tbGameItem->setItem(iRow,2,UI.tbItem(iNtd));

        ui->tbGameItem->setItem(iRow,3,UI.tbItem(iUsd));

        ui->tbGameItem->setItem(iRow,4,UI.tbItem(iHkd));

        ui->tbGameItem->setItem(iRow,5,UI.tbItem(iRmb));

        ui->tbGameItem->setItem(iRow,6,UI.tbItem(iMyr));

        ui->tbGameItem->setItem(iRow,7,UI.tbItem(iSgd));
    }


    ui->txt->clear();

    ui->txt->appendPlainText(trText());



    /*
    bool bOk = ACTION.action(ACT::QUERY_GAME_ITEM,d,listItem,sError);

    if(!bOk )
    {
        UI.showMsg("",sError,"OK");

        return;
    }

    QString sMsg="";


    //  DataExchange::Rate rate = ACTION.rate();

    for(int i=0;i<listItem.length();i++)
    {
        double NTD=listItem.at(i).toMap()["NTD"].toDouble();
        sMsg+="\n";
        sMsg+=listItem.at(i).toMap()["Name"].toString()+"="+
                QString::number(NTD);
    }


    //    ui->txt1->setPlainText(sMsg);

    */

}




void LayerCostTable::on_btnClear_clicked()
{
    ui->txSearch->clear();
    refreshGameList();

}


void LayerCostTable::on_btnCopy_clicked()
{
    UI.copyMsg(ui->txt->toPlainText().trimmed());
}


void LayerCostTable::slotTabCurrentChanged(int index)
{

    QStringList listHeader;
    listHeader<<"代號"<<"商品名稱"<<"新台幣"<<"美金"<<"港幣"<<"人民幣"<<"林吉特"<<"新加坡元";

    QStringList listHeader2;
    listHeader2<<""<<"%Item"<<"%NTD"<<"%USD"<<"%HKD"<<"%RMB"<<"%MYR"<<"%SGD";

    if(index==0)
    {
        ui->label->setText("商品");
        ui->tbGameItem->setHorizontalHeaderLabels(listHeader);
    }
    else
    {
        ui->label->setText("資料聯動碼");
        ui->tbGameItem->setHorizontalHeaderLabels(listHeader2);
    }
}


void LayerCostTable::on_btnSaveText_clicked()
{
    int iRow = ui->tbGame->currentRow();



    if(iRow<0 || iRow>=m_listGameDisplay.length())
        return;

    DataGameList data = m_listGameDisplay.at(iRow);

    data.SellNote= ui->txEdit->toPlainText();
    QString sError;
    bool bOk =ACTION.action(ACT::EDIT_GAME_LIST,data.data(),sError);

    if(bOk)
        sError="修改完成";

    DMSG.showMsg("",sError,"OK");

    refreshGameList();
}

QString LayerCostTable::trText()
{
    QString st=ui->txEdit->toPlainText();
    //    listHeader2<<"%Item"<<"%NTD"<<"%USD"<<"%HKD"<<"%RMB"<<"%MYR"<<"%SGD";


    QVariantList list;



    for(int i=0;i<ui->tbGameItem->rowCount();i++)
    {
        QString sSid= ui->tbGameItem->item(i,0)->text().trimmed();
        QVariantMap d;
        d["%Item("+sSid+")"] = ui->tbGameItem->item(i,1)->text().split("_").first();
        d["%NTD("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,2)->text(),"NTD");
        d["%USD("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,3)->text(),"USD");
        d["%HKD("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,4)->text(),"HKD");
        d["%RMB("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,5)->text(),"RMB");
        d["%MYR("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,6)->text(),"MYR");
        d["%SGD("+sSid+")"] = COMMON.addFlow(ui->tbGameItem->item(i,7)->text(),"SGD");
        list.append(d);
    }

    for(int i=list.length()-1;i>=0;i--)
    {
        QVariantMap d=list.at(i).toMap();
        QStringList listKey = d.keys();

        foreach(QString v,listKey)
        {

            st=st.replace(v,d[v].toString());

        }


    }

   st= st.replace("%User",ACTION.m_currentUser.Name);
   st= st.replace("%Time", GLOBAL.dateTimeUtc8().toString("yyyy/MM/dd hh:mm"));


    return st;
}

bool LayerCostTable::checkSearch(QVariantMap data)
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


void LayerCostTable::on_txEdit_textChanged()
{
    ui->txt->clear();

    ui->txt->appendPlainText(trText());
}




void LayerCostTable::on_txSearch_textChanged(const QString &)
{
    refreshGameList();
}

