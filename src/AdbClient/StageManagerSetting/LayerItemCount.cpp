#include "LayerItemCount.h"
#include "ui_LayerItemCount.h"

LayerItemCount::LayerItemCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerItemCount)
{
    ui->setupUi(this);
}

LayerItemCount::~LayerItemCount()
{
    delete ui;
}

void LayerItemCount::showEvent(QShowEvent *)
{
    // QTimer::singleShot(50,this,[=](){ refresh();});
}

QPair<int, int> LayerItemCount::checkCount(QString itemSid)
{
    int iCount=0;
    int iCountSell=0;

    qDebug()<<"IIIIIIIIIII : "<<m_listData.length();

    for(int i=0;i<m_listData.length();i++)
    {
        DataItemCount data(m_listData.at(i).toMap());

        if(data.GameItemSid==itemSid)
        {
            qDebug()<<"change : "<<data.ChangeValue;
            if(data.ChangeValue<0)
            {
                iCountSell+=qAbs(data.ChangeValue);
            }
            else
            {
                iCount+=data.ChangeValue;
            }

        }
    }

    QPair<int,int> re;

    re.first=iCountSell;

    re.second=iCount;

    return re;
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

    ui->cbGame->addItems(listCbName);

}



void LayerItemCount::on_cbGame_currentIndexChanged(int index)
{
    if(index<0 || index>=m_listGame.length())
        return;


    QString sGameSid = m_listGame.at(index).Sid;

    m_listGameItem  = ACTION.getGameItemFromGameSid(sGameSid,true);

    ui->tb->setRowCount(0);

    for(int i=0;i<m_listGameItem.length();i++)
    {
        ui->tb->setRowCount(ui->tb->rowCount()+1);

        DataGameItem v = m_listGameItem.at(i);

        QPair<int,int > p = checkCount(v.Sid);

        ui->tb->setItem(i,0,UI.tbItem(v.Name));
        int iSell = p.first;
        int iCount = p.second;

        if(iSell==0)
            ui->tb->setItem(i,1,UI.tbItem(p.first));
        else
            ui->tb->setItem(i,1,UI.tbItem(p.first,GlobalUi::_BUTTON));

        int iTmp = iCount-iSell;

        ui->tb->setItem(i,2,UI.tbItem(iTmp));

        if(iCount==0)
            ui->tb->setItem(i,3,UI.tbItem(p.second));
        else
            ui->tb->setItem(i,3,UI.tbItem(p.second,GlobalUi::_BUTTON));

        ui->tb->setItem(i,4,UI.tbItem("入庫",GlobalUi::_BUTTON));
    }



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

        input.addInput("增加數量",d);

        int iRet = input.exec();
        if(iRet==1)
        {

            DataGameItem item = m_listGameItem.at(row);

            //            DataItemCount last;

            //            QVariantMap tmp;

            //            tmp["DESC"] ="Sid";
            //            tmp["GameItemSid"]=item.Sid;

            //            QVariantList listOut

            QPair<int,int> count =checkCount(item.Sid);

            DataItemCount data;

            data.GameItemSid = item.Sid;

            data.TotalSell=count.first;

            data.TotalCount=count.second+input.data()["Count"].toInt();

            data.ChangeValue=input.data()["Count"].toInt();

            data.UserSid=ACTION.m_currentUser.Sid;

            QString sError;

            ACTION.action(ACT::ADD_ITEM_COUNT,data.data(),sError);

            DMSG.showMsg("",sError,"OK");
        }

    }
}

