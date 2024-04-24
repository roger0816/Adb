#include "LayerBulletin.h"
#include "ui_LayerBulletin.h"
#include <QTimer>

LayerBulletin::LayerBulletin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerBulletin)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);

    connect(&DATA,&UpdateData::updateNotify,this,[=](int iType){
        if(iType==BULLETIN_DATA)
            refresh();
    });
}

LayerBulletin::~LayerBulletin()
{
    delete ui;
}

void LayerBulletin::showEvent(QShowEvent *)
{
    //QTimer::singleShot(300,[this](){ refresh(true); });
}

void LayerBulletin::refresh(bool bRequery)
{

    if(m_block)
        return ;

    if(m_bFirst)
    {
        bRequery = false;

        m_bFirst =false;
    }

    m_block=true;





    QString sError;

    m_listData=DATA.getBulletin();


    ui->tbTop->setRowCount(0);

    ui->tbSys->setRowCount(0);

//    QVariantMap in;
//    in["DESC"] ="Sid";
//    qDebug()<<"layer Bulletin";
//    if(bRequery)
//    {
//        ACTION.action(ACT::QUERY_BULLETIN,in,m_listData,sError);
//    }
    m_listTop.clear();
    m_listSys.clear();
    for(int i=0;i<m_listData.length();i++)
    {

        QVariantMap data = m_listData.at(i).toMap();


        QDateTime End=QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss");

        if(End.toSecsSinceEpoch()<=GLOBAL.dateTimeUtc8().toSecsSinceEpoch())
            continue;


        if(data["Type"].toString() =="0")
        {
            m_listTop.append(data);
            intoTopTb(data);
        }
        else if(data["Type"].toString() =="1")
        {
            m_listSys.append(data);
            intoSysTb(data);
        }
    }






    m_block=false;

}

void LayerBulletin::intoTopTb(QVariantMap data)
{
    int iRow = ui->tbTop->rowCount();

    ui->tbTop->setRowCount(iRow+1);

    QDateTime d = QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

    ui->tbTop->setItem(iRow,0,UI.tbItem(d));
    ui->tbTop->setItem(iRow,1,UI.tbItem(userName(data["UserSid"].toString())));

    QLabel *lb0 = new QLabel(ui->tbTop);
    lb0->setText(data["Title"].toString());
    ui->tbTop->setCellWidget(iRow,2,lb0);

    QLabel *lb1 = new QLabel(ui->tbTop);
    lb1->setText(data["Content"].toString());
    ui->tbTop->setCellWidget(iRow,3,lb1);
}

void LayerBulletin::intoSysTb(QVariantMap data)
{
    int iRow = ui->tbSys->rowCount();

    ui->tbSys->setRowCount(iRow+1);

    QDateTime d = QDateTime::fromString(data["UpdateTime"].toString(),"yyyyMMddhhmmss");

    ui->tbSys->setItem(iRow,0,UI.tbItem(d));
    ui->tbSys->setItem(iRow,1,UI.tbItem(userName(data["UserSid"].toString())));
    ui->tbSys->setItem(iRow,2,UI.tbItem(data["Title"]));

    QLabel *lb0 = new QLabel(ui->tbSys);
    lb0->setText(data["Title"].toString());
    ui->tbSys->setCellWidget(iRow,2,lb0);

    QLabel *lb1 = new QLabel(ui->tbSys);
    lb1->setText(data["Content"].toString());

    ui->tbSys->setCellWidget(iRow,3,lb1);
}

QString LayerBulletin::userName(QString sId)
{
    QString sRe="";

    QList<UserData> list = DATA.getUserList();

    for(int i=0;i<list.length();i++)
    {
        UserData data = list.at(i);

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
    if(row<0 || row>=m_listSys.length())
        return;

    QVariantMap d = m_listSys.at(row).toMap();


    //    QDateTime date = QDateTime::fromString(ui->tbSys->item(row,0)->text(),"yyyy/MM/dd hh:mm");

    //    d["UpdateTime"] = date.toString("yyyyMMddhhmm00");

    QString sUserName = ui->tbSys->item(row,1)->text();
    //    d["Title"] = ui->tbSys->item(row,2)->text();
    //    d["Content"] = ui->tbSys->item(row,3)->text();

    DialogBulletinEdit dialog;

    dialog.setData(d,sUserName);

    dialog.exec();

}


void LayerBulletin::on_tbTop_cellDoubleClicked(int row, int )
{
    if(row<0 || row>=m_listTop.length())
        return;

    QVariantMap d = m_listTop.at(row).toMap();


    //    QDateTime date = QDateTime::fromString(ui->tbTop->item(row,0)->text(),"yyyy/MM/dd hh:mm");

    //    d["UpdateTime"] = date.toString("yyyyMMddhhmm00");

    QString sUserName = ui->tbTop->item(row,1)->text();
    //    d["Title"] = ui->tbTop->item(row,2)->text();
    //    d["Content"] = ui->tbTop->item(row,3)->text();

    DialogBulletinEdit dialog;

    dialog.setData(d,sUserName);

    dialog.exec();

}

