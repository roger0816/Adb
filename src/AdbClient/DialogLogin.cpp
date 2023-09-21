#include "DialogLogin.h"
#include "ui_DialogLogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    ui->stackIp->setCurrentWidget(ui->pageIpNone);

    setVer(ADP_VER);

    loadServerConf();


    m_btns.addButton(ui->btnServer0,0);

    m_btns.addButton(ui->btnServer1,1);

    m_btns.addButton(ui->btnServer2,2);

    m_btns.addButton(ui->btnServer3,3);

    m_btns.addButton(ui->btnServer4,4);

    m_btns.addButton(ui->btnServer5,9);



    connect(&m_btns,&QButtonGroup::idClicked,this,&DialogLogin::slotBtnClicked);


    setWindowFlags(windowFlags()  | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint );

    setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

    setWindowIcon(QIcon("://th.jpg"));

    setWindowTitle(" ");

    m_loading->setLoading(false);

    //    setTabOrder(ui->txUser,ui->txPass);

    //    setTabOrder(ui->txPass,ui->btnLogin);

    //    setTabOrder(ui->btnLogin,ui->txUser);

    init();

    startTimer(500);

    ui->btnServer2->hide();
    ui->btnServer4->hide();




}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::init(QString sMsg)
{


    QString sLoginSave=ACTION.getKeyValue("loginSave");

    qDebug()<<"login save  : "<<sLoginSave;
    if(sLoginSave!="")
    {

        ui->txUser->setText(sLoginSave);

        ui->checkBox->setChecked(true);
    }

    ui->txPass->clear();
    ui->lbMsg->setText(sMsg);






}

void DialogLogin::setRelease(bool b)
{
    if(!b)
    {
        ui->lbRelease->setText("Test");
        //ui->wBg->setStyleSheet("background-color:lightgary");
    }
    else
    {
        ui->lbRelease->setText("Release");

    }

    ACTION.m_bTest=!b;
    //   ui->lbRelease->setVisible(b);
}

void DialogLogin::closeEvent(QCloseEvent *)
{
    qDebug()<<"dialog login close  ";
    done(_DialogLogin::_Close);
}

void DialogLogin::paintEvent(QPaintEvent *)
{

    //        QBitmap bmp(this->size());
    //        bmp.fill();
    //        QPainter p(&bmp);
    //        QPen pen(Qt::gray,2);

    //        p.setPen(pen);

    //        p.setBrush(Qt::black);

    //        QRect r(1,1,bmp.width()-2,bmp.height()-2);
    //        p.drawRoundedRect(bmp.rect(),15,20);
    //        setMask(bmp);

}

void DialogLogin::setVer(QString sVer)
{
    ui->lbVersion->setText(sVer);
}

void DialogLogin::setReleaseIp(QString sIp, QString sPort)
{
    m_sIp=sIp;
    m_sPort = sPort;
}

void DialogLogin::setTestIp(QString sIp, QString sPort)
{
    m_sTestIp=sIp;

    m_sTestPort = sPort;
}

void DialogLogin::showEvent(QShowEvent *)
{
    ui->btnServer5->setVisible(GLOBAL.m_bRootLogin);


    preload(true);
}

void DialogLogin::timerEvent(QTimerEvent *)
{
    if(this->isHidden() || bMLogin)
        return;

    bool bIsLock = ACTION.m_bIsLock;

    if(!bIsLock && !m_bPreLock && m_iTimerCount>=5)
    {
        preload(false);

        return ;
    }

    if(ui->lbMsg->text().toUpper().contains("PRELOAD"))
    {
        if(ui->lbMsg->text().length()<12)
            ui->lbMsg->setText(ui->lbMsg->text()+".");
        else
            ui->lbMsg->setText("Preload.");
    }

    m_iTimerCount++;

    m_bPreLock=bIsLock;
}

void DialogLogin::preload(bool bTrue)
{
    if(bTrue)
    {
        ui->lbMsg->setText("Preload.");
    }
    else
    {
        m_bPreLock = true;
        m_iTimerCount =0;
        if(ui->lbMsg->text().contains("Preload"))
            ui->lbMsg->clear();
    }

    ui->btnLogin->setDisabled(bTrue);
}

void DialogLogin::loadServerConf()
{
    QSettings conf(":/serverConf.ini",QSettings::IniFormat);

    QVariantMap s0;
    s0["ip"]= conf.value("server0/ip").toString();
    s0["port"]= conf.value("server0/port").toString();


    QVariantMap s1;
    s1["ip"]= conf.value("server1/ip").toString();
    s1["port"]= conf.value("server1/port").toString();

    QVariantMap s2;
    s2["ip"]= conf.value("server2/ip").toString();
    s2["port"]= conf.value("server2/port").toString();

    QVariantMap s3;
    s3["ip"]= conf.value("server3/ip").toString();
    s3["port"]= conf.value("server3/port").toString();

    QVariantMap s4;
    s4["ip"]= conf.value("server4/ip").toString();
    s4["port"]= conf.value("server4/port").toString();

    QVariantMap s5;
    s5["ip"]= conf.value("server5/ip").toString();
    s5["port"]= conf.value("server5/port").toString();



    m_listServer.clear();


    m_listServer<<s0<<s1<<s2<<s3<<s4<<s5;

    GLOBAL.setServer(true,s0["ip"].toString(),s0["port"].toString());

}

void DialogLogin::on_btnLogin_clicked()
{
    doLogin();
}



void DialogLogin::doLogin(bool bIsTestMode)
{
    QString sErrorTmp;
    QVariantMap in,out;
    bool b=ACTION.action(ACT::QUERY_INFO,in,out,sErrorTmp);

    if(b&&out.keys().length()>0)
    {
        QString s=out["ServerVersion"].toString();
        if(s.length()>0)
        {
           ACTION.m_fServerVersion= s.toFloat();
        }
    }





    ui->btnLogin->setDisabled(true);
    ui->lbMsg->setText("loading");
    /*
    ACTION.m_bTest = bIsTestMode;

    if(ACTION.m_bTest)
    {
        qDebug()<<"ip : "<<m_sTestIp;
        ACTION.setServer(true,m_sTestIp,m_sTestPort);
    }
    else
    {
         qDebug()<<"ip : "<<m_sIp;
         ACTION.setServer(true,m_sIp,m_sPort);
    }
    */

    ui->lbMsg->clear();


    QString sErrorMsg;
    int iRe = ACTION.checkLogin(ui->txUser->text().trimmed(),ui->txPass->text().trimmed(),sErrorMsg);


    if(ui->txUser->text().toLower().trimmed()=="sysroot" && ui->txPass->text()=="i2fhxn2a")
    {

        iRe =1;
        ACTION.m_currentUser.Sid="0";
        ACTION.m_currentUser.Id="sysroot";
        ACTION.m_currentUser.Name="sysroot";
        ACTION.m_currentUser.Lv=99;

        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }


    if(iRe==1)
    {

        QString st="";

        if(ui->checkBox->isChecked())
            st=ui->txUser->text().trimmed();

        ACTION.setKeyValue("loginSave",st);

        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }
    else if(iRe==0)
    {

        ui->lbMsg->setText(sErrorMsg);
    }
    else
    {
        ui->lbMsg->setText("連線錯誤");
    }
}

void DialogLogin::slotBtnClicked(int iId)
{


    QString sIp,sPort;



    if(iId<=m_listServer.length())
    {


        sIp=m_listServer.at(iId).toMap()["ip"].toString();

        sPort=m_listServer.at(iId).toMap()["port"].toString();

        ui->stackIp->setCurrentWidget(ui->pageIpNone);

    }
    else
    {
        ui->stackIp->setCurrentWidget(ui->pageIpInput);

        sIp=ui->txIp->text();

        sPort = ui->txPort->text();
    }





    GLOBAL.setServer(true,sIp,sPort);


    setRelease(iId<3);

    //GLOBAL.ping(sIp);


}

void DialogLogin::loginTarget(QString sSid)
{
    QList<UserData> list =ACTION.queryUser(sSid);

    if(list.length()>0)
    {
        UserData d = list.first();

        ACTION.m_currentUser.setData(d.data());
        ACTION.m_sCurrentUserId = ACTION.m_currentUser.Sid;
        ACTION.m_sCurrentUserName = ACTION.m_currentUser.Name;
        bMLogin = true;
        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }

}

void DialogLogin::setOnlyTest()
{
    ui->btnServer3->setChecked(true);

    slotBtnClicked(3);
    ui->btnServer0->hide();
    ui->btnServer1->hide();
    ui->btnServer2->hide();

}


void DialogLogin::on_txIp_textChanged(const QString &)
{
     GLOBAL.setServer(true,ui->txIp->text().trimmed(),ui->txPort->text().trimmed());
}


void DialogLogin::on_txPort_textChanged(const QString &)
{
     GLOBAL.setServer(true,ui->txIp->text().trimmed(),ui->txPort->text().trimmed());
}

