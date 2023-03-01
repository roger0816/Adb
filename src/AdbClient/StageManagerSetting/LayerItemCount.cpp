#include "LayerItemCount.h"
#include "ui_LayerItemCount.h"

LayerItemCount::LayerItemCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerItemCount)
{
    ui->setupUi(this);

    ui->cbGame->setProperty("lock",false);

    ui->tb->setColumnWidth(0,250);

}

LayerItemCount::~LayerItemCount()
{
    delete ui;
}

void LayerItemCount::showEvent(QShowEvent *)
{
    QTimer::singleShot(50,this,[=](){ refresh();});
}

DataItemCount LayerItemCount::checkCount(QString itemSid)
{
    DataItemCount re;

    re.ChangeValue=0;
    re.TotalCount=0;
    re.TotalSell=0;
    for(int i=0;i<m_listData.length();i++)
    {
        DataItemCount data(m_listData.at(i).toMap());

        if(data.GameItemSid==itemSid)
        {
            re =data;

        }
    }


    return re;
}

void LayerItemCount::updateTb()
{
    int iIdx = ui->cbGame->currentIndex();

    QString sGameSid = m_listGame.at(iIdx).Sid;

    m_listGameItem  = ACTION.getGameItemFromGameSid(sGameSid,true);


    ui->tb->setRowCount(0);

    for(int i=0;i<m_listGameItem.length();i++)
    {

        ui->tb->setRowCount(ui->tb->rowCount()+1);

        DataGameItem v = m_listGameItem.at(i);

        ui->tb->setItem(i,0,UI.tbItem(v.Name));


        DataItemCount dataCount = checkCount(v.Sid);


        qlonglong iSell = dataCount.TotalSell;
        qlonglong iTotalCount = dataCount.TotalCount;

        //        if(iSell!=0)
        //            ui->tb->setItem(i,1,UI.tbItem(p.first,GlobalUi::_BUTTON));
        //         else
        ui->tb->setItem(i,1,UI.tbItem(iSell));

        qlonglong iTmp = iTotalCount-iSell;

        if(v.Sid=="690")
        {
            qDebug()<<"BBBBB : item sid : "<<v.Sid;
            qDebug()<<"iSell : "<<iSell<<" icount : "<<iTotalCount;
        }


        ui->tb->setItem(i,2,UI.tbItem(iTmp));

        //        if(iCount!=0)
        //            ui->tb->setItem(i,3,UI.tbItem(p.second,GlobalUi::_BUTTON));
        //        else
        ui->tb->setItem(i,3,UI.tbItem(iTotalCount));


        ui->tb->setItem(i,4,UI.tbItem("入庫",GlobalUi::_BUTTON));
    }
}

void LayerItemCount::refresh()
{

    QVariantMap in;
    in["ASC"]="Sid";
    QVariantList listOut;

    QString sError;

    ACTION.action(ACT::QUERY_ITEM_COUNT,in,listOut,sError);


    m_listData = listOut;

    m_listGame = ACTION.getGameList(true);

    QStringList listCbName;

    foreach(DataGameList v,m_listGame)
    {
        listCbName.append(v.Name);
    }


    ui->cbGame->setProperty("lock",true);

    ui->cbGame->clear();

    ui->cbGame->addItems(listCbName);

    ui->cbGame->setProperty("lock",false);

    ui->cbGame->setCurrentIndex(m_iCbGame);

    int iIdx = ui->cbGame->currentIndex();

    if(iIdx<0 || iIdx>= m_listGame.length())
    {
        ui->tb->setRowCount(0);

        return;
    }

    updateTb();

}



void LayerItemCount::on_cbGame_currentIndexChanged(int index)
{

    qDebug()<<"iIdx : "<<index<<", "<<m_listGame.length()<<" , "<<ui->cbGame->property("lock").toBool();

    if(index<0 || index>=m_listGame.length() || ui->cbGame->property("lock").toBool())
        return;

    m_iCbGame = index;

    updateTb();



}


void LayerItemCount::on_tb_cellClicked(int row, int column)
{
    if(row<0 )
        return;

    if(column==4)
    {
        DialogInput input;
        input.hideDelete();
        input.setTitle("增加庫存數量\n"+ui->tb->item(row,0)->text());
        QVariantMap d;

        uint tmp = 0;

        d["Count"] = tmp;

        input.addSpinBox("增加數量",-9999999,9999999,1);


        int iRet = input.exec();
        if(iRet==1)

        {
            int iCount =input.datas().first().toInt();  //加減數有被sp限制，總數才需要longlong
            if(iCount==0)
            {
                DMSG.showMsg("","請輸入有效數量","OK");
                return;

            }

            DataGameItem item = m_listGameItem.at(row);

            //            DataItemCount last;

            //            QVariantMap tmp;

            //            tmp["DESC"] ="Sid";
            //            tmp["GameItemSid"]=item.Sid;

            //            QVariantList listOut

            DataItemCount last =checkCount(item.Sid);

            DataItemCount data;

            data.GameItemSid = item.Sid;

            data.ChangeValue=0;
            //   data.ChangeValue=input.data()["Count"].toULongLong();

            data.TotalSell=last.TotalSell;

            data.TotalCount=last.TotalCount+iCount;


            data.UserSid=ACTION.m_currentUser.Sid;

            QString sError;

            ACTION.action(ACT::ADD_ITEM_COUNT,data.data(),sError);

            DMSG.showMsg("",sError,"OK");

            refresh();
        }

    }
}

