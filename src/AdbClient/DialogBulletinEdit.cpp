#include "DialogBulletinEdit.h"
#include "ui_DialogBulletinEdit.h"

DialogBulletinEdit::DialogBulletinEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBulletinEdit)
{
    ui->setupUi(this);

    setWindowTitle("設定系統公告");

    ui->dateEnd->setDateTime(QDateTime::currentDateTimeUtc().addDays(7));

    ui->stackedBottom->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(1);

    ui->txContent->setTextInteractionFlags(Qt::LinksAccessibleByMouse);



}

DialogBulletinEdit::~DialogBulletinEdit()
{
    delete ui;
}

void DialogBulletinEdit::setReadyOnly()
{
    ui->stackedBottom->setCurrentIndex(1);

    ui->wTop->hide();


    ui->txContent->setReadOnly(true);

    ui->txContentSrc->setReadOnly(true);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->tabBar()->hide();


    setWindowTitle(" ");
}

void DialogBulletinEdit::setData(QVariantMap data, QString sName)
{

    if(sName!="")
    {
        ui->lbUser->setText(sName);


        setReadyOnly();
    }


    m_data = data;

    bool bIsTop = m_data["Type"].toInt()==0;

    ui->cbTop->setChecked(bIsTop);
    ui->lbTitle->setText(m_data["Title"].toString());

    ui->txTitle->setText(m_data["Title"].toString());

    ui->txContentSrc->setPlainText(m_data["Content"].toString());

    ui->txContent->setText(m_data["Content"].toString());

    ui->dateEnd->setDateTime(QDateTime::fromString(m_data["EndTime"].toString(),"yyyyMMddhhmmss"));



}

QVariantMap DialogBulletinEdit::data()
{
    int iType=1;

    if(ui->cbTop->isChecked())
        iType=0;

    m_data["Type"] = iType;
    m_data["Title"] = ui->txTitle->text().trimmed();
    m_data["Content"] = ui->txContentSrc->toPlainText();

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


void DialogBulletinEdit::on_txContentSrc_textChanged()
{
    ui->txContent->setText(ui->txContentSrc->toPlainText());
}


void DialogBulletinEdit::on_txTitle_textChanged(const QString &arg1)
{
    ui->lbTitle->setText(ui->txTitle->text());
}

