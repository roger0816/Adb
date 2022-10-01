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

    QVariantList tmp;

    QString sError;

    ACTION.action(ACT::QUERY_BULLETIN,tmp,m_listBulletin,sError);

    ui->tbBulletin->setRowCount(0);



    for(int i=0;i<m_listBulletin.length();i++)
    {


        ui->tbBulletin->setRowCount(i+1);


        QVariantMap data = m_listBulletin.at(i).toMap();

        QVariantMap v;
        v["Sid"] = data["UserSid"];

        QVariantList listUser;
        ACTION.action(ACT::QUERY_USER,v,listUser,sError);

        UserData user(listUser.first().toMap());

        ui->tbBulletin->setItem(i,0,UI.tbItem(user.Name));

        ui->tbBulletin->setItem(i,1,UI.tbItem(QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss")));

        ui->tbBulletin->setItem(i,2,UI.tbItem(data["Title"]));

        ui->tbBulletin->setItem(i,3,UI.tbItem(data["Content"]));


    }
}



void LayerSysSetting::on_tbBulletin_cellDoubleClicked(int row, int column)
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














