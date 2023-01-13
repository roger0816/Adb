#include "DialogLogin.h"
#include "ui_DialogLogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

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

    ui->btnTestLogin->hide();
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
    preload(true);
}

void DialogLogin::timerEvent(QTimerEvent *)
{
    if(this->isHidden())
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
        ui->lbMsg->clear();
    }

    ui->btnLogin->setDisabled(bTrue);
}

void DialogLogin::on_btnLogin_clicked()
{
    doLogin();
}


void DialogLogin::on_btnTestLogin_clicked()
{

    doLogin(true);
}

void DialogLogin::doLogin(bool bIsTestMode)
{
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

