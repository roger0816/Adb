#include "ItemScheduleStatus.h"
#include "ui_ItemScheduleStatus.h"

ItemScheduleStatus::ItemScheduleStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemScheduleStatus)
{
    ui->setupUi(this);

    ui->tbEdit->setMouseTracking(true);

}

ItemScheduleStatus::~ItemScheduleStatus()
{
    delete ui;
}

QString ItemScheduleStatus::data()
{
    QStringList listData;
    //    for(int i=0;i<ui->tb->rowCount();i++)
    //    {
    //        QString st="%1::%2::%3";

    //        st=st.arg(ui->tb->itemAt(i,0)->text())
    //                .arg(ui->tb->itemAt(i,1)->text())
    //                .arg(ui->tb->itemAt(i,2)->text());
    //    }

    for(int i=0;i<m_data.length();i++)
    {
        QVariantMap d = m_data.at(i).toMap();

        QString sTmp=d["title"].toString()+
                "::"+d["content"].toString()+
                "::"+d["cost"].toString();

        listData.append(sTmp);
    }

    return listData.join(";;");

}

void ItemScheduleStatus::setData(QString sData)
{
    QStringList listData = sData.split(";;");

    m_data.clear();

    for(int i=0;i<listData.length();i++)
    {
        QVariantMap d;

        QStringList tmp = listData.at(i).split("::");

        if(tmp.length()>2)
        {
            d["title"] = tmp.first();
            d["content"] = tmp.at(1);
            d["cost"] = tmp.at(2);
            m_data.append(d);
        }

    }

    refresh();

}

void ItemScheduleStatus::refresh()
{
    ui->tbEdit->setRowCount(0);

    ui->tb->setRowCount(0);

    for(int i=0;i<m_data.length();i++)
    {
        if(ui->tbEdit->rowCount()<=i)
            ui->tbEdit->setRowCount(ui->tbEdit->rowCount()+1);

        if(ui->tb->rowCount()<=i)
            ui->tb->setRowCount(ui->tb->rowCount()+1);


        QVariantMap d = m_data.at(i).toMap();

        QString sTitle = d["title"].toString().trimmed();

        QString sContent = d["content"].toString().trimmed();

        QString sCost="x %1 + %2";
        sCost = sCost.arg(d["cost"].toString().split(",,").first())
                .arg(d["cost"].toString().split(",,").last());
        ui->tbEdit->setItem(i,0,UI.tbItem(sTitle));

        ui->tbEdit->setItem(i,1,UI.tbItem(sContent));

        ui->tbEdit->setItem(i,2,UI.tbItem(sCost));


        ui->tb->setItem(i,0,UI.tbItem(sTitle));

        ui->tb->setItem(i,1,UI.tbItem(sContent));

        ui->tb->setItem(i,2,UI.tbItem(sCost));


    }

}

bool ItemScheduleStatus::checkHasTitle(QString sTitle)
{

    for(int i=0;i<m_data.length();i++)
    {
        QString sTmp = m_data.at(i).toMap()["title"].toString();

        if(sTitle==sTmp)
            return true;

    }

    return false;
}

void ItemScheduleStatus::on_btnAdd_clicked()
{
    if(ui->txTitle->text().trimmed()=="" || ui->txContent->text().trimmed()=="")
    {
        DMSG.showMsg("","狀態或內容不能為空白",QStringList()<<"OK");

        return;

    }

    if(checkHasTitle(ui->txTitle->text().trimmed()))
    {
        DMSG.showMsg("","此狀態已存在，不能重覆新增",QStringList()<<"OK");

        return ;
    }


    int iIdx = ui->tbEdit->rowCount();

    ui->tbEdit->setRowCount(iIdx+1);

    ui->tbEdit->setItem(iIdx,0,UI.tbItem(ui->txTitle->text().trimmed()));


    ui->tbEdit->setItem(iIdx,1,UI.tbItem(ui->txContent->text().trimmed()));

    QString sTmp="x %1 + %2";

    ui->tbEdit->setItem(iIdx,2,UI.tbItem(sTmp.arg(ui->spX->value()).arg(ui->spAdd->value())));


    QVariantMap d;

    d["title"] = ui->txTitle->text().trimmed();
    d["content"] = ui->txContent->text().trimmed();
    d["cost"] = ui->spX->text()+",,"+ui->spAdd->text();

    m_data.append(d);

    refresh();

}


void ItemScheduleStatus::on_btnDel_clicked()
{
    if(ui->tbEdit->currentRow()<0)
    {
        DMSG.showMsg("","請先從下方清單，選擇要刪除的目標",QStringList()<<"OK");
        return;
    }


    m_data.removeAt(ui->tbEdit->currentRow());


    refresh();
}


void ItemScheduleStatus::on_tbEdit_itemEntered(QTableWidgetItem *item)
{

    UI.toolTip(item->text());
}

void ItemScheduleStatus::on_tb_itemClicked(QTableWidgetItem *item)
{
    int iRow =  item->row();

    if(iRow<0 || iRow>=ui->tb->rowCount())
        return ;

    QString sText = ui->tb->item(iRow,0)->text();

    emit sendClicked(sText);
}

