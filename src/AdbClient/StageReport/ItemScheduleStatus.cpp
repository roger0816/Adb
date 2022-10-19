#include "ItemScheduleStatus.h"
#include "ui_ItemScheduleStatus.h"

ItemScheduleStatus::ItemScheduleStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemScheduleStatus)
{
    ui->setupUi(this);

    ui->tb->hideColumn(2);

    ui->tbEdit->setMouseTracking(true);

    ui->tabWidget->setTabVisible(1,false);
}

ItemScheduleStatus::~ItemScheduleStatus()
{
    delete ui;
}

QString ItemScheduleStatus::data()
{
    QStringList listData;


    for(int i=0;i<m_data.length();i++)
    {
        QVariantMap d = m_data.at(i).toMap();

        QString sTmp=d["title"].toString()+
                "::"+d["content"].toString()+
                "::"+d["cost"].toString()+
                "::"+d["color"].toString();


        listData.append(sTmp);
    }

    return listData.join(",,");

}

void ItemScheduleStatus::setData(QString sData)
{
    QStringList listData = sData.split(",,");

    m_data.clear();

    for(int i=0;i<listData.length();i++)
    {
        QVariantMap d;

        QStringList tmp = listData.at(i).split("::");

        if(tmp.length()>3)
        {
            d["title"] = tmp.first();
            d["content"] = tmp.at(1);
            d["cost"] = tmp.at(2);
            d["color"] = tmp.at(3);
            m_data.append(d);
        }

    }

    refresh();

}

void ItemScheduleStatus::setEditMode(bool b)
{
    m_bEditMode = b;

    ui->tabWidget->setTabVisible(1,m_bEditMode);
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
        sCost = sCost.arg(d["cost"].toString().split("+").first())
                .arg(d["cost"].toString().split("+").last());

        QTableWidgetItem *item =  UI.tbItem(sTitle);

        item->setForeground(QColor(d["color"].toString()));

        ui->tbEdit->setItem(i,0,item);

        ui->tbEdit->setItem(i,1,UI.tbItem(sContent));

        ui->tbEdit->setItem(i,2,UI.tbItem(sCost));

        QTableWidgetItem *item2 =  UI.tbItem(sTitle);
        item2->setForeground(QColor(d["color"].toString()));

         ui->tb->setItem(i,0,item2);

        ui->tb->setItem(i,1,UI.tbItem(sContent));

       // ui->tb->setItem(i,2,UI.tbItem(sCost));

        ui->tb->setItem(i,2,UI.tbItem(d["color"].toString()));


    }

}

bool ItemScheduleStatus::checkHasTitle(QString sTitle,QString sColor)
{

    for(int i=0;i<m_data.length();i++)
    {
        QString sTmp = m_data.at(i).toMap()["title"].toString();

        QString sTmp2 = m_data.at(i).toMap()["color"].toString();

        if(sTitle==sTmp && sColor == sTmp2)
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

    if(checkHasTitle(ui->txTitle->text().trimmed(),m_sAddColor))
    {
        DMSG.showMsg("","此狀態已存在，不能重覆新增",QStringList()<<"OK");

        return ;
    }


    QVariantMap d;

    d["title"] = ui->txTitle->text().trimmed();
    d["content"] = ui->txContent->text().trimmed();
    d["cost"] = ui->spX->text()+"+"+ui->spAdd->text();
    d["color"]= m_sAddColor;
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

    QString sColor = ui->tb->item(iRow,2)->text();

    if(m_bEditMode)
        emit sendClicked(sText,sColor);
}


void ItemScheduleStatus::on_btnStyle_clicked()
{

    QColorDialog dialog;

  //  dialog.setOption(QColorDialog::DontUseNativeDialog);

    dialog.setCurrentColor(QColor(m_sAddColor));

    if(dialog.exec()!=1)
        return;

    QColor color = dialog.selectedColor();

   // QColor color = dialog.getColor(txColor,nullptr,"",QColorDialog::ShowAlphaChannel);

    ui->btnStyle->setStyleSheet("background-color:"+color.name());

    ui->txTitle->setStyleSheet("color:"+color.name());

    m_sAddColor = color.name();


}

