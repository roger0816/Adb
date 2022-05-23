#include "DialogEditUser.h"
#include "ui_DialogEditUser.h"

DialogEditUser::DialogEditUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditUser)
{
    ui->setupUi(this);

     setWindowTitle("設定使用者");
}

DialogEditUser::~DialogEditUser()
{
    delete ui;
}

void DialogEditUser::setData(QVariantMap data)
{
    m_data.setData(data);

    ui->txId->setText(m_data.Id);

    ui->txCid->setText(m_data.Cid);

    ui->txName->setText(m_data.Name);

    ui->dateStart->setDate(QDate::fromString(m_data.StartDay,"yyyyMMdd"));

    ui->dateBirty->setDate(QDate::fromString(m_data.BirthDay,"yyyyMMdd"));

    ui->txEmal->setText(m_data.Email);

    ui->txTel->setText(m_data.Tel);

    ui->txNote->setText(m_data.Note1);

    int iLvIdx =qBound(0,m_data.Lv-1,ui->cbType->count()-1);


    ui->cbType->setCurrentIndex(iLvIdx);

}

QVariantMap DialogEditUser::data()
{
    return m_data.data();
}

void DialogEditUser::on_btnOk_clicked()
{

    m_data.Cid = ui->txCid->text().trimmed();

    if(ui->txPass->text().trimmed()!="")
    {
        m_data.Password= ui->txPass->text().trimmed();
    }

    int iLv = USER_LV::_LV1;

    if(ui->cbType->currentIndex() == ui->cbType->count()-1)
        iLv = USER_LV::_ROOT;
    else
        iLv = ui->cbType->currentIndex()+1;


    m_data.Lv = iLv;

    m_data.Name = ui->txName->text().trimmed();

    m_data.StartDay = ui->dateStart->date().toString("yyyyMMdd");

    m_data.BirthDay = ui->dateBirty->date().toString("yyyyMMdd");

    m_data.Email = ui->txEmal->text().trimmed();

    m_data.Tel = ui->txTel->text().trimmed();

    m_data.Note1 = ui->txNote->text().trimmed();

    m_data.UpdateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    done(1);
}


void DialogEditUser::on_btnCancel_clicked()
{
    done(0);
}

