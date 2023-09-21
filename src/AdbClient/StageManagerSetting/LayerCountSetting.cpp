#include "LayerCountSetting.h"
#include "ui_LayerCountSetting.h"

LayerCountSetting::LayerCountSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCountSetting)
{
    ui->setupUi(this);

    ui->tb->hideColumn(0);
    ui->tb->hideColumn(6);
    ui->tb->setColumnWidth(1,300);

    connect(ui->cbGame,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCbChangeIdx(int)));
}

LayerCountSetting::~LayerCountSetting()
{
    delete ui;
}

void LayerCountSetting::showEvent(QShowEvent *)
{

    QVariantMap in;

    QVariantList out;

    QString sError;

    ACTION.action(ACT::QUERY_GAME_LIST,in,out,sError);

    m_listGame.clear();
    ui->cbGame->clear();
    for(int i=0;i<out.length();i++)
    {
        DataGameList game(out.at(i).toMap());
        ui->cbGame->addItem(game.Name);
        m_listGame.append(game);
    }

    if(m_listGame.length()>0)
    {
        ui->cbGame->setCurrentIndex(0);
        slotCbChangeIdx(0);
    }


}


void LayerCountSetting::slotCbChangeIdx(int idx)
{
    if(idx<0 || idx>=m_listGame.length())
        return;

    QString sGameSid = m_listGame.at(idx).Sid;

    m_countData = getDataCount(sGameSid);

    QVariantMap in;

    QVariantList out;

    QString sError;
    in["GameSid"]=sGameSid;
    in["ASC"]="Sort";
    ACTION.action(ACT::QUERY_GAME_ITEM,in,out,sError,true);

    ui->tb->setRowCount(0);
    int iRow=0;

    for(int i=0;i<out.length();i++)
    {
        ui->tb->setRowCount(iRow+1);
        QVariantMap v = out.at(i).toMap();
        DataGameItem item(v);
        QString sGameItemSid =item.Sid;

        DataCount data = m_countData.value(sGameItemSid);

        QString sName =item.Name;
        int iCount = data.CurrentCount;
        int iSell = data.TotalSell;
        int iTotal = data.TotalCount;

        ui->tb->setItem(iRow,0,UI.tbItem(sGameItemSid));
        ui->tb->setItem(iRow,1,UI.tbItem(sName));
        ui->tb->setItem(iRow,2,UI.tbItem(iCount));
        ui->tb->setItem(iRow,3,UI.tbItem(iSell));
        ui->tb->setItem(iRow,4,UI.tbItem(iTotal));
        ui->tb->setItem(iRow,5,UI.tbItem("修改",GlobalUi::_BUTTON));
        ui->tb->setItem(iRow,6,UI.tbItem("詳細",GlobalUi::_BUTTON));

        iRow++;

    }

}

QMap<QString, DataCount> LayerCountSetting::getDataCount(QString sGameSid)
{

    QVariantMap in;

    QVariantList out;

    QString sError;
    in["GameSid"]=sGameSid;
    ACTION.action(ACT::QUERY_COUNT,in,out,sError,true);


    QMap<QString,DataCount> re;
    for(int i=0;i<out.length();i++)
    {
        QVariantMap v = out.at(i).toMap();
        DataCount data;
        data.Name =v["Name"].toString();
        data.GameSid=v["GameSid"].toString();
        data.GameItemSid=v["GameItemSid"].toString();
        data.TotalSell = v["TotalSell"].toInt();
        data.TotalCount= v["TotalCount"].toInt();
        data.CurrentCount = data.TotalCount-data.TotalSell;

        re[data.GameItemSid]=data;
    }

    return re;
}

void LayerCountSetting::refresh()
{
    slotCbChangeIdx(ui->cbGame->currentIndex());
}

void LayerCountSetting::on_tb_cellClicked(int row, int column)
{
    if(row<0 )
        return;

    if(column==5)
    {
        DialogInput input;
        input.hideDelete();
        input.setTitle("增加庫存數量\n"+ui->tb->item(row,1)->text());
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


            QString sGameItemSid = ui->tb->item(row,0)->text().trimmed();
            qlonglong iTotal = ui->tb->item(row,4)->text().toLongLong();

            DataCount countData = m_countData.value(sGameItemSid);

            DataItemCount data;

            data.GameSid = countData.GameSid;

            data.GameItemSid = sGameItemSid;
            data.Name = countData.Name;

            //data.ChangeValue=0;
            //   data.ChangeValue=input.data()["Count"].toULongLong();

           // data.TotalSell=last.TotalSell;

            data.TotalCount=iTotal+iCount;


            data.UserSid=ACTION.m_currentUser.Sid;

            QString sError;

            ACTION.action(ACT::ADD_ITEM_COUNT,data.data(),sError);

            DMSG.showMsg("",sError,"OK");

            refresh();
        }

    }
}

