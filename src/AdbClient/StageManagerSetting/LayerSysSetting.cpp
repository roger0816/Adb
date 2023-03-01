#include "LayerSysSetting.h"
#include "ui_LayerSysSetting.h"

LayerSysSetting::LayerSysSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSysSetting)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

LayerSysSetting::~LayerSysSetting()
{
    delete ui;
}

void LayerSysSetting::on_btnBulletinAdd_clicked()
{
    DialogBulletinEdit dialog;


    if(dialog.exec()==1)
    {
        QString sError;

        QVariantMap data = dialog.data();

        data["UserSid"] = ACTION.m_currentUser.Sid.toInt();

        ACTION.action(ACT::ADD_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }

}

void LayerSysSetting::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refreshBulletin()));
}

void LayerSysSetting::refreshBulletin()
{

    m_listBulletin.clear();

    QVariantMap tmp;

    QString sError;
    tmp["DESC"]="Sid";
    ACTION.action(ACT::QUERY_BULLETIN,tmp,m_listBulletin,sError);

    ui->tbBulletin->setRowCount(0);



    for(int i=0;i<m_listBulletin.length();i++)
    {


        QVariantMap data = m_listBulletin.at(i).toMap();

        if(data["Type"]==2)
            continue;
        int iRow = ui->tbBulletin->rowCount();
        ui->tbBulletin->setRowCount(iRow+1);


         QString sUserName="";

        QList<UserData> listUser =ACTION.queryUser(data["UserSid"].toString());

        if(listUser.length()>0)
            sUserName=listUser.first().Name;

        ui->tbBulletin->setItem(iRow,0,UI.tbItem(sUserName));

        ui->tbBulletin->setItem(iRow,1,UI.tbItem(QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss")));

      //  ui->tbBulletin->setItem(iRow,2,UI.tbItem(data["Title"]));
        QLabel *lb0 = new QLabel(ui->tbBulletin);
        lb0->setText(data["Title"].toString());

        ui->tbBulletin->setCellWidget(iRow,2,lb0);

        QLabel *lb = new QLabel(ui->tbBulletin);
        lb->setText(data["Content"].toString());

        ui->tbBulletin->setCellWidget(iRow,3,lb);

    }
}



void LayerSysSetting::on_tbBulletin_cellDoubleClicked(int , int )
{
    on_btnBulletinEdit_clicked();
}


void LayerSysSetting::on_btnBulletinEdit_clicked()
{

    int iRow = ui->tbBulletin->currentRow();

    if(iRow<0 || iRow >= m_listBulletin.length())
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");

        return;
    }

    DialogBulletinEdit dialog;

    dialog.setData(m_listBulletin.at(iRow).toMap());

    int iRet =dialog.exec();
    if(iRet==1)
    {
        QString sError;

        QVariantMap data = dialog.data();

        data["UserSid"] = ACTION.m_currentUser.Sid.toInt();

        ACTION.action(ACT::EDIT_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }
    else if(iRet==3)
    {
        QString sError;

        QVariantMap data;

        data["Sid"]= dialog.data()["Sid"];

        ACTION.action(ACT::DEL_BULLETIN,data,sError);

        DMSG.showMsg("",sError,"OK");

        refreshBulletin();
    }

}














