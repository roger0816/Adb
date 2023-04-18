#include "LayerOkInfo.h"
#include "ui_LayerOkInfo.h"

LayerOkInfo::LayerOkInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerOkInfo)
{
    ui->setupUi(this);

    connect(ui->btnBACK,SIGNAL(clicked()),this,SIGNAL(back()));

}

LayerOkInfo::~LayerOkInfo()
{
    delete ui;
}

void LayerOkInfo::setData(QVariantMap data)
{
    m_dData = data;
    m_bOrderMode = data["OrderMode"].toBool();
    ui->lbMsg->setText(data["Msg"].toString());
    ui->lbId->setText(data["Id"].toString());
    ui->lbName->setText(data["Name"].toString());

    ui->lbCurrency->setText(data["Currency"].toString());
    ui->lbTime->setText(data["Time"].toString());
    ui->lbGameName->setText(data["GameName"].toString());
    ui->lbLoginType->setText(data["LoginType"].toString());
    ui->lbGameAccount->setText(data["GameAccount"].toString());
    ui->lbGamePassword->setText(data["GamePassword"].toString());
    ui->lbServer->setText(data["Server"].toString());
    ui->lbChr->setText(data["Chr"].toString());
    ui->txNote0->setText(data["Note0"].toString());
    ui->lbTotal->setText(data["Total"].toString());
    ui->txCost->setText(data["Cost"].toString());
}

void LayerOkInfo::on_btnCopy_clicked()
{
    QString sMsg="客戶編號: "+ui->lbId->text()+"\n"+
            ui->tTime->text()+" "+ui->lbTime->text()+"\n";

    QString sInfo;

    if(!m_bOrderMode) //報價
    {
        sMsg+= ui->tGameName->text()+"  "+ui->lbGameName->text()+"\n"
                +ui->tLoginType->text()+"  "+ui->lbLoginType->text()+"\n"
                +ui->tAccount->text()+"  "+ui->lbGameAccount->text()+"\n"
                +ui->tPassword->text()+"  "+ui->lbGamePassword->text()+"\n"
                +ui->tServerName->text()+"  "+ui->lbServer->text()+"\n"
                +ui->tChr->text()+"  "+ui->lbChr->text()+"\n";


    }
    else                //下單
    {
        sMsg+= ui->tGameName->text()+"  "+ui->lbGameName->text()+"\n"
                +ui->tLoginType->text()+"  "+ui->lbLoginType->text()+"\n"
                +ui->tAccount->text()+"  "+ui->lbGameAccount->text()+"\n"
                +ui->tPassword->text()+"  "+ui->lbGamePassword->text()+"\n"
                +ui->tServerName->text()+"  "+ui->lbServer->text()+"\n"
                +ui->tChr->text()+"  "+ui->lbChr->text()+"\n";

    }




    QString sCost=m_dData["Cost"].toString();




    if(!m_bOrderMode)
    {
        sCost+="\n總計: $ "+ui->lbTotal->text()+"\n"
                +"幣別: "+ui->lbCurrency->text();
    }
    else
    {
        sCost+="\n備註: "+ui->txNote0->toPlainText();
    }
    UI.copyMsg(sMsg+sCost);
}

