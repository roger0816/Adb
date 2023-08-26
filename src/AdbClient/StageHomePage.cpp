#include "StageHomePage.h"
#include "ui_StageHomePage.h"

StageHomePage::StageHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageHomePage)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    ui->wPic->setReadOnly(true);

    ui->wPic->setNoButton();

    ui->wFn->hide();

    connect(ui->btn0,&QPushButton::clicked,ui->wPic,&ItemPic::slotSetPic);
    connect(ui->btn1,&QPushButton::clicked,ui->wPic,&ItemPic::slotClear);
    connect(ui->btn2,&QPushButton::clicked,ui->wPic,&ItemPic::slotClip);
    connect(ui->btn3,&QPushButton::clicked,ui->wPic,&ItemPic::slotPase);

    ui->btn3->setToolTip("按下 win+shift+s ");

    connect(ui->btnSend,&QPushButton::clicked,this,&StageHomePage::slotSavePic);

#if HIDE_PIC
    ui->wPic->hide();
#endif
}

StageHomePage::~StageHomePage()
{
    delete ui;
}

void StageHomePage::setBulletinData(QVariantList list)
{
    ui->wBulletin->m_listData = list;
}


void StageHomePage::showEvent(QShowEvent *)
{

    ui->btnFn->setVisible(ACTION.m_currentUser.Lv>=USER_LV::_LV3);



    QTimer::singleShot(100,this,[=]()
    {

        if(m_bLock)
            return;

        m_bLock = true;


#ifndef HIDE_PIC

        QVariantMap in;
        QVariantList listOut;
        in["Type"]=2;
        QString sError;
        ACTION.action(ACT::QUERY_BULLETIN,in,listOut,sError);
        ui->wPic->slotClear();

        qDebug()<<"listPicLen"<<listOut.length();

        if(listOut.length()>0)
        {
            QString sPicMd5 = listOut.last().toMap()["Content"].toString();
            qDebug()<<"pic : "<<sPicMd5;

            QVariant inPic,outPic;

            ui->wPic->setMd5(sPicMd5);

        }
#endif
        ui->wBulletin->refresh(true);

        m_bLock = false;


    });
}

void StageHomePage::on_btnFn_clicked()
{

    ui->wFn->setVisible(ui->btnFn->isChecked());

}



void StageHomePage::slotSavePic()
{
    QVariantMap in,data;
    in["Type"]=2;
    QString sError;
    ACTION.action(ACT::QUERY_BULLETIN,in,data,sError);


    data["UserSid"]=ACTION.m_currentUser.Sid;
    data["Type"]=2;
    data["Title"]="首頁圖更新";
    data["Content"]=ui->wPic->uploadPic();
    QVariantMap tmp;
    bool b =ACTION.action(ACT::ADD_BULLETIN,data,tmp,sError);

    if(b)
    {
        sError="首頁圖已修改";
    }


    DMSG.showMsg("",sError,"OK");


}


void StageHomePage::on_tabWidget_currentChanged(int )
{

#ifndef HIDE_PIC
    ui->wPic->setVisible(ui->tabWidget->currentIndex()==0);
#endif
}




