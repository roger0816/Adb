#include "DialogGameEdit.h"
#include "ui_DialogGameEdit.h"

DialogGameEdit::DialogGameEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGameEdit)
{
    ui->setupUi(this);

    setWindowTitle("遊戲清單設定");

    ui->btnDel->hide();

    setTabOrder(ui->cbEnable,ui->txId);

    setTabOrder(ui->txId,ui->txName);

    setTabOrder(ui->txName,ui->btnOk);

    ui->lbMsg->clear();


    QRegExp r("\\w{0,5}");

    ui->txId->setValidator(new QRegExpValidator(r,this));
}

DialogGameEdit::~DialogGameEdit()
{
    delete ui;
}

void DialogGameEdit::setData(QString sSid, bool bEnable, QString sId, QString sName)
{
    m_sSid = sSid;

    ui->btnDel->show();

    ui->lbTitle->setText("編輯遊戲");

    ui->txId->setReadOnly(true);

    ui->txId->setEnabled(false);

    ui->txId->setText(sId);

    ui->txName->setText(sName);

    ui->cbEnable->setChecked(bEnable);
}

void DialogGameEdit::on_btnCancel_clicked()
{
    reject();
}


void DialogGameEdit::on_btnOk_clicked()
{
    ui->lbMsg->clear();


    if(ui->txId->text().trimmed()=="" || ui->txName->text().trimmed()=="")
    {
        ui->lbMsg->setText("代號與名稱，不能空白。");
        return;
    }

    m_sId = ui->txId->text().trimmed();

    m_sName = ui->txName->text().trimmed();

    m_bEnable = ui->cbEnable->isChecked();


    if(m_sSid=="")
    {
        //add
        done(1);

    }
    else
    {
        //edit
        done(2);
    }



}


void DialogGameEdit::on_btnDel_clicked()
{
    int iRet = DMSG.showMsg("","刪除遊戲時，對應的商品也會全刪除，確定是否刪除？",QStringList()<<"否"<<"是");

    if(iRet==1)
    {

        done(3);
    }
}

