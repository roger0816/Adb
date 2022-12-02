#include "LayerBulletin.h"
#include "ui_LayerBulletin.h"
#include <QTimer>

LayerBulletin::LayerBulletin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerBulletin)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);
}

LayerBulletin::~LayerBulletin()
{
    delete ui;
}

void LayerBulletin::showEvent(QShowEvent *)
{
    QTimer::singleShot(300,[this](){ refresh(true); });
}

void LayerBulletin::refresh(bool bRequery)
{

    if(bRequery)
    {
        QString sError;

        m_listData.clear();

        m_listUser.clear();

        ui->tbTop->setRowCount(0);

        ui->tbSys->setRowCount(0);

        QVariantMap in;
        in["DESC"] ="Sid";

        m_listUser = ACTION.queryUser();

        ACTION.action(ACT::QUERY_BULLETIN,in,m_listData,sError);

        for(int i=0;i<m_listData.length();i++)
        {

            QVariantMap data = m_listData.at(i).toMap();


            QDateTime End=QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss");

            if(End.toSecsSinceEpoch()<=GLOBAL.dateTimeUtc8().toSecsSinceEpoch())
                continue;


            if(data["Type"].toString() =="0")
            {
                intoTopTb(data);
            }
            else if(data["Type"].toString() =="1")
            {
                intoSysTb(data);
            }
        }



    }
}

void LayerBulletin::intoTopTb(QVariantMap data)
{
    int iRow = ui->tbTop->rowCount();

    ui->tbTop->setRowCount(iRow+1);

    QDateTime d = QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

    ui->tbTop->setItem(iRow,0,UI.tbItem(d));
    ui->tbTop->setItem(iRow,1,UI.tbItem(userName(data["UserSid"].toString())));
    ui->tbTop->setItem(iRow,2,UI.tbItem(data["Title"]));
    QString stContent=data["Content"].toString().replace("\n","");

    ui->tbTop->setItem(iRow,3,UI.tbItem(stContent));


}

void LayerBulletin::intoSysTb(QVariantMap data)
{
    int iRow = ui->tbSys->rowCount();

    ui->tbSys->setRowCount(iRow+1);

    QDateTime d = QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

    ui->tbSys->setItem(iRow,0,UI.tbItem(d));
    ui->tbSys->setItem(iRow,1,UI.tbItem(userName(data["UserSid"].toString())));
    ui->tbSys->setItem(iRow,2,UI.tbItem(data["Title"]));
    QString stContent=data["Content"].toString().replace("\n","");

    ui->tbSys->setItem(iRow,3,UI.tbItem(stContent));
}

QString LayerBulletin::userName(QString sId)
{
    QString sRe="";

    for(int i=0;i<m_listUser.length();i++)
    {
        UserData data = m_listUser.at(i);

        if(sId==data.Sid)
        {
            sRe = data.Name;
            break;
        }
    }


    return sRe;
}

void LayerBulletin::on_tbSys_cellDoubleClicked(int row, int )
{
    if(row<0)
        return;

    QVariantMap d;


    QDateTime date = QDateTime::fromString(ui->tbSys->item(row,0)->text(),"yyyy/MM/dd hh:mm");

    d["UpdateTime"] = date.toString("yyyyMMddhhmm00");

    QString sUserName = ui->tbSys->item(row,1)->text();
     d["Title"] = ui->tbSys->item(row,2)->text();
    d["Content"] = ui->tbSys->item(row,3)->text();

    DialogBulletinEdit dialog;

    dialog.setData(d,sUserName);

    dialog.exec();

}


void LayerBulletin::on_tbTop_cellDoubleClicked(int row, int )
{
    if(row<0)
        return;

    QVariantMap d;


    QDateTime date = QDateTime::fromString(ui->tbTop->item(row,0)->text(),"yyyy/MM/dd hh:mm");

    d["UpdateTime"] = date.toString("yyyyMMddhhmm00");

    QString sUserName = ui->tbTop->item(row,1)->text();
     d["Title"] = ui->tbTop->item(row,2)->text();
    d["Content"] = ui->tbTop->item(row,3)->text();

    DialogBulletinEdit dialog;

    dialog.setData(d,sUserName);

    dialog.exec();

}

