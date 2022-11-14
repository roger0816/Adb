#include "LayerCostTable.h"
#include "ui_LayerCostTable.h"

LayerCostTable::LayerCostTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostTable)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->page0);

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slotTabCurrentChanged(int)));
}

LayerCostTable::~LayerCostTable()
{
    delete ui;
}


void LayerCostTable::refreshGameList()
{



    m_listGame = ACTION.getGameList(true);


    ui->tbGame->setRowCount(0);

    for(int i=0;i<m_listGame.length();i++)
    {
        ui->tbGame->setRowCount(i+1);

        ui->tbGame->setItem(i,0,UI.tbItem(m_listGame.at(i).Id));

        //  ui->tbGame->setItem(i,1,UI.tbItem(m_gameList.listData.at(i).Enable));

        ui->tbGame->setItem(i,1,UI.tbItem(m_listGame.at(i).Name));


    }

}

void LayerCostTable::showEvent(QShowEvent *)
{
    // ACTION.rate("",true);
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refreshGameList()));
}



void LayerCostTable::on_tbGame_cellPressed(int row, int )
{
    if(row<0 || row>=m_listGame.length())
        return;

    QString sGameSid = m_listGame.at(row).Sid;

    double iGameRate = m_listGame.at(row).GameRate;

    ui->txEdit->setText(m_listGame.at(row).SellNote);
    qDebug()<<"GameRate : "<<iGameRate;

    DataRate rate = ACTION.costRate("",true);

    QVariantMap d;

    d["GameSid"] = sGameSid;

    QVariantList listItem;

    QString sError;

    m_currentItems =ACTION.getGameItem(sGameSid,true);


    auto fn=[=](double d,int f=0)
    {
        return QString::number(d,'f',f);
    };


    ui->tbGameItem->setRowCount(0);

    for(int i=0;i<m_currentItems.length();i++)
    {
        int iRow = ui->tbGameItem->rowCount();


        DataGameItem item = m_currentItems.at(i);

        qDebug()<<"bouns : "<<item.Bonus.toDouble();

        double iNtd = item.Bonus.toDouble()*iGameRate;

        double iUsd = iNtd/rate.USD();
        double iHkd = iNtd/rate.HKD();
        double iRmb = iNtd/rate.RMB();
        double iMyr = iNtd/rate.MYR();
        double iSgd = iNtd/rate.SGD();


        ui->tbGameItem->setRowCount(iRow+1);

        ui->tbGameItem->setItem(iRow,0,UI.tbItem(item.Name));

        ui->tbGameItem->setItem(iRow,1,UI.tbItem(fn(iNtd)));

        ui->tbGameItem->setItem(iRow,2,UI.tbItem(fn(iUsd,2)));

        ui->tbGameItem->setItem(iRow,3,UI.tbItem(fn(iHkd)));

        ui->tbGameItem->setItem(iRow,4,UI.tbItem(fn(iRmb)));

        ui->tbGameItem->setItem(iRow,5,UI.tbItem(fn(iMyr)));

        ui->tbGameItem->setItem(iRow,6,UI.tbItem(fn(iSgd,1)));
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


void LayerCostTable::on_btnSearch_clicked()
{
    refreshGameList();
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
    listHeader<<"商品名稱"<<"新台幣"<<"美金"<<"港幣"<<"人民幣"<<"林吉特"<<"新加坡元";

    QStringList listHeader2;
    listHeader2<<"%Item"<<"%NTD"<<"%USD"<<"%HKD"<<"%RMB"<<"%MYR"<<"%SGD";

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

    if(iRow<0 || iRow>=m_listGame.length())
        return;

    DataGameList data = m_listGame.at(iRow);

    data.SellNote= ui->txEdit->toPlainText();
    QString sError;
    bool bOk =ACTION.action(ACT::EDIT_GAME_LIST,data.data(),sError);

    if(bOk)
        sError="修改完成";

    DMSG.showMsg("",sError,"OK");
}

QString LayerCostTable::trText()
{
    QString st=ui->txEdit->toPlainText();
    //    listHeader2<<"%Item"<<"%NTD"<<"%USD"<<"%HKD"<<"%RMB"<<"%MYR"<<"%SGD";

    QVariantMap d;

    for(int i=0;i<ui->tbGameItem->rowCount();i++)
    {
        d["%Item"+QString::number(i+1)] = ui->tbGameItem->item(i,0)->text();
        d["%NTD"+QString::number(i+1)] = ui->tbGameItem->item(i,1)->text();
        d["%USD"+QString::number(i+1)] = ui->tbGameItem->item(i,2)->text();
        d["%RMB"+QString::number(i+1)] = ui->tbGameItem->item(i,3)->text();
        d["%MYR"+QString::number(i+1)] = ui->tbGameItem->item(i,4)->text();
        d["%SGD"+QString::number(i+1)] = ui->tbGameItem->item(i,5)->text();

    }

    d["%User"] = ACTION.m_currentUser.Name;
    d["%Time"] = GLOBAL.dateTimeUtc8().toString("yyyy/MM/dd hh:mm");


    QStringList listKey = d.keys();

    foreach(QString v,listKey)
    {
        st=st.replace(v,d[v].toString());
    }



    return st;
}


void LayerCostTable::on_txEdit_textChanged()
{
    ui->txt->clear();

    ui->txt->appendPlainText(trText());
}



