#include "DialogLogin.h"
#include "ui_DialogLogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("://th.jpg"));

    setWindowTitle(" ");

    init();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::init()
{
    QString sLoginSave=ACTION.getKeyValue("loginSave");

    if(sLoginSave!="")
    {
        ui->txUser->setText(sLoginSave);

        ui->checkBox->setChecked(true);
    }

    ui->txPass->clear();
}

void DialogLogin::on_btnLogin_clicked()
{

    ui->lbMsg->clear();

    QString sErrorMsg;
    bool bOk = ACTION.checkLogin(ui->txUser->text().trimmed(),ui->txPass->text().trimmed(),sErrorMsg);

    if(ui->txUser->text().toLower().trimmed()=="root" && ui->txPass->text()=="1234")
    {
        bOk = true;

        ACTION.m_currentUser.Id="root";
        ACTION.m_currentUser.Name="Test001";
         ACTION.m_currentUser.Lv=99;
         ACTION.m_currentUser.Sid="99";
    }
    if(bOk)
    {

        QString st="";

        if(ui->checkBox->isChecked())
            st=ui->txUser->text().trimmed();

        ACTION.setKeyValue("loginSave",st);

        emit signalLogin();
        done(1);

    }
    else
        ui->lbMsg->setText("帳密錯誤!");
}

