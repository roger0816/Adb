#include "DialogBulletinEdit.h"
#include "ui_DialogBulletinEdit.h"

DialogBulletinEdit::DialogBulletinEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBulletinEdit)
{
    ui->setupUi(this);

    setWindowTitle("設定系統公告");

    ui->stackedBottom->setCurrentIndex(0);

}

DialogBulletinEdit::~DialogBulletinEdit()
{
    delete ui;
}

void DialogBulletinEdit::setReadyOnly()
{
    ui->stackedBottom->setCurrentIndex(1);

    ui->wTop->hide();

    ui->txTitle->setReadOnly(true);

    ui->txContent->setReadOnly(true);

    setWindowTitle(" ");
}

void DialogBulletinEdit::setData(QVariantMap data, QString sName)
{
    m_data = data;

    ui->cbTop->setChecked(m_data["Top"].toBool());

    ui->txTitle->setText(m_data["Title"].toString());

    ui->txContent->setText(m_data["Content"].toString());

    //  ui->dateStart->setDateTime(QDateTime::fromString(m_data["StartTime"].toString(),"yyyyMMddhhmmss"));

    ui->dateEnd->setDateTime(QDateTime::fromString(m_data["EndTime"].toString(),"yyyyMMddhhmmss"));


    if(sName!="")
    {
        ui->lbUser->setText(sName);

        setReadyOnly();
    }

}

QVariantMap DialogBulletinEdit::data()
{
    m_data["Top"] = ui->cbTop->isChecked();
    m_data["Title"] = ui->txTitle->text().trimmed();
    m_data["Content"] = ui->txContent->toPlainText();
    // m_data["StartTime"] = ui->dateStart->dateTime().toString("yyyyMMddhhmmss");
    m_data["EndTime"] = ui->dateEnd->dateTime().toString("yyyyMMddhhmmss");

    return m_data;
}

void DialogBulletinEdit::on_btnOk_clicked()
{
    if(ui->txTitle->text().trimmed()=="")
    {
        DMSG.showMsg("","標題不能空白","OK");

        return;
    }

    done(1);
}


void DialogBulletinEdit::on_btnDel_clicked()
{

    int iRet =  DMSG.showMsg("","確定刪除嗎？",QStringList()<<"否"<<"是");

    if(iRet==1)
    {
        done(3);
    }

}


void DialogBulletinEdit::on_btnClose_clicked()
{
    reject();
}


void DialogBulletinEdit::on_btnCancel_clicked()
{
    reject();
}

