#include "DialogLogin.h"
#include "ui_DialogLogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

    setWindowTitle(" ");
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_btnLogin_clicked()
{

    ui->lbMsg->clear();

    QString sErrorMsg;
    bool bOk = GLOBAL.SQL().checkLogin(ui->txUser->text(),ui->txPass->text(),sErrorMsg);

    if(bOk)
        done(1);
    else
        ui->lbMsg->setText("帳密錯誤!");
}

