#include "LayerCostTable.h"
#include "ui_LayerCostTable.h"

LayerCostTable::LayerCostTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostTable)
{
    ui->setupUi(this);
}

LayerCostTable::~LayerCostTable()
{
    delete ui;
}


void LayerCostTable::refreshGameList()
{


    QVariantList listIn,listOut;

    QString sError;
    ACTION.action(ACT::QUERY_GAME_LIST,listIn,listOut,sError);

    m_gameList.setGameList(listOut);

    ui->tbGame->setRowCount(0);

    for(int i=0;i<m_gameList.listData.length();i++)
    {
        ui->tbGame->setRowCount(i+1);


        ui->tbGame->setItem(i,0,UI.tbItem(m_gameList.listData.at(i).Id));

      //  ui->tbGame->setItem(i,1,UI.tbItem(m_gameList.listData.at(i).Enable));

        ui->tbGame->setItem(i,1,UI.tbItem(m_gameList.listData.at(i).Name));


    }

}

void LayerCostTable::showEvent(QShowEvent *)
{
   // ACTION.rate("",true);
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refreshGameList()));
}

bool LayerCostTable::check(GameList::GameData data)
{
    if(ui->txSearch->text().trimmed()=="")
        return true;

    if(data.Name.indexOf(ui->txSearch->text().trimmed())<0)
        return false;

    if(data.Id.indexOf(ui->txSearch->text().trimmed())<0)
        return false;

    return true;
}

void LayerCostTable::on_tbGame_cellPressed(int row, int )
{
    if(row<0 || row>=m_gameList.listData.length())
        return;

    QString sGameSid = m_gameList.listData.at(row).Sid;

    QVariantMap d;

    d["GameSid"] = sGameSid;

    QVariantList listItem;

    QString sError;

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


    ui->txt1->setPlainText(sMsg);



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
    UI.copyMsg(ui->txt0->toPlainText().trimmed()+"\n"+
               ui->txt1->toPlainText().trimmed()+"\n"+
               ui->txt2->toPlainText().trimmed());
}

