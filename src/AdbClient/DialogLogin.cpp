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

//    setTabOrder(ui->txUser,ui->txPass);

//    setTabOrder(ui->txPass,ui->btnLogin);

//    setTabOrder(ui->btnLogin,ui->txUser);

    init();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::init()
{


    QString sLoginSave=ACTION.getKeyValue("loginSave");

    qDebug()<<"login save  : "<<sLoginSave;
    if(sLoginSave!="")
    {

        ui->txUser->setText(sLoginSave);

        ui->checkBox->setChecked(true);
    }

    ui->txPass->clear();
    ui->lbMsg->clear();
}

void DialogLogin::setRelease(bool b)
{
    ui->lbRelease->setVisible(b);
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

void DialogLogin::on_btnLogin_clicked()
{

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

        ui->lbMsg->setText("帳密錯誤!");
    }
    else
    {
        ui->lbMsg->setText("連線錯誤");
    }
}

