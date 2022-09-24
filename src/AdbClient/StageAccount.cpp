#include "StageAccount.h"
#include "ui_StageAccount.h"

StageAccount::StageAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageAccount)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(slotPage(int)));

}

StageAccount::~StageAccount()
{
    delete ui;
}

void StageAccount::showEvent(QShowEvent *)
{
    m_btns.button(0)->setChecked(true);

    ui->stackedWidget->setCurrentIndex(0);
}

void StageAccount::readUser()
{
    qDebug()<<"current user : "<<ACTION.m_currentUser.Sid;

    m_user = ACTION.getUser(ACTION.m_currentUser.Sid);

    ui->txId->setText(m_user.Id);

    ui->lbCid->setText(m_user.Cid);

    ui->txName->setText(m_user.Name);

    int iLv = qBound(0,m_user.Lv-1,ui->cbType->count()-1);

    ui->cbType->setCurrentIndex(iLv);

    ui->dateStart->setDate(QDate::fromString(m_user.StartDay,"yyyyMMdd"));

    ui->dateBirty->setDate(QDate::fromString(m_user.BirthDay,"yyyyMMdd"));

    ui->txTel->setText(m_user.Tel);

    ui->txEmail->setText(m_user.Email);

    ui->txNote->setText(m_user.Note1);

}

void StageAccount::on_btnPassword_clicked()
{
    DialogMsg dialog;

    QList<UserData> list= ACTION.queryUser(ACTION.m_currentUser.Id);

    if(list.length()<1)
    {
        DMSG.showMsg("","未知錯誤",QStringList()<<"OK");

        return ;
    }

    UserData user = list.first();

    if(user.Password!=ui->txPass->text().trimmed())
    {
        DMSG.showMsg("Error","密碼輸入錯誤",QStringList()<<"OK");

        return ;
    }

    if(ui->txNewPass->text().trimmed() != ui->txNewPass2->text().trimmed())
    {
        DMSG.showMsg("Error","密碼再確認錯誤",QStringList()<<"OK");

        return ;
    }

    user.Password = ui->txNewPass->text().trimmed();

    QString sError;

    bool bOk = ACTION.editUser(user.data(),sError);

    if(!bOk)
    {
        DMSG.showMsg("Error",sError,QStringList()<<"OK");

        return;
    }
    else
    {
        DMSG.showMsg("","新密碼修改完成",QStringList()<<"OK");

    }

}

void StageAccount::slotPage(int i)
{
    ui->stackedWidget->setCurrentIndex(i);

    if(i==1)
    {
        QList<UserData> list = ACTION.queryUser(ACTION.m_currentUser.Sid);

        if(list.length()>0)
        {
            readUser();

        }


    }
}


void StageAccount::on_btnEdit_clicked()
{
    m_user.Name = ui->txName->text().trimmed();

    m_user.Tel = ui->txTel->text().trimmed();

    m_user.Email= ui->txEmail->text().trimmed();

    m_user.BirthDay = ui->dateBirty->date().toString("yyyyMMdd");

    m_user.Note1 = ui->txNote->text().trimmed();

    QString sError;

    bool bOk =ACTION.editUser(m_user.data(),sError);

    if(bOk)
    {
        DMSG.showMsg("","資料已修改",QStringList()<<"OK");
    }
    else
    {
        DMSG.showMsg("Error",sError,QStringList()<<"OK");
    }
}


void StageAccount::on_btnCancel_clicked()
{
    readUser();
}

