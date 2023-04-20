#include "DialogMsg.h"
#include "ui_DialogMsg.h"

DialogMsg *DialogMsg::m_pInstance=nullptr;

DialogMsg::DialogMsg(QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::DialogMsg)
{
    ui->setupUi(this);

    ui->btnOk->setFocus();

    this->setWindowTitle("  ");
}

DialogMsg::~DialogMsg()
{
    delete ui;
}

int DialogMsg::showMsg(QString sTitle, QString sMsg, QStringList listBtn)
{


    if(dynamic_cast<QWidget*>(parent())!=nullptr)
    {
        qDebug()<<"GGGGGGGGGGGGGG "<<dynamic_cast<QWidget*>(parent())->rect();
    }

    ui->lbTitle->setText(sTitle);

    ui->stackedWidget->setCurrentWidget(ui->page0);

    ui->lbMsg->setText(sMsg);

    setButton(listBtn);

   // qApp->desktop()

    return exec();
}

int DialogMsg::showMsg(QString sTitle, QString sMsg, QString btnName)
{
    return showMsg(sTitle,sMsg,QStringList()<<btnName);
}

void DialogMsg::setDialogInfo(QString sMsg, QStringList listBtnText)
{
    ui->stackedWidget->setCurrentWidget(ui->page0);

    ui->lbMsg->setText(sMsg);

    setButton(listBtnText);


}

void DialogMsg::setInput(QString sTitle,QString sPreInplut, QStringList listBtnName)
{
    ui->stackedWidget->setCurrentWidget(ui->pageInput);

    ui->lbTitle->setText(sTitle);

    ui->txInput->setText(sPreInplut);

    setButton(listBtnName);

}

void DialogMsg::setButton(QStringList listName)
{
    if(listName.length()>=2)
    {
        ui->btnCancel->setText(listName.at(0));

         ui->btnCancel->setVisible(true);

        ui->btnOk->setText(listName.at(1));

           ui->btnOk->setVisible(true);
    }
    else if(listName.length()>0)
    {
        ui->btnOk->setText(listName.at(0));

        ui->btnOk->setVisible(true);

        ui->btnCancel->setVisible(false);


    }
    else
    {
        ui->btnOk->setVisible(true);

        ui->btnCancel->setVisible(false);
    }
}

QString DialogMsg::getInput()
{
    return ui->txInput->text().trimmed();
}



void DialogMsg::on_btnCancel_clicked()
{
    done(0);
}

void DialogMsg::on_btnOk_clicked()
{
    done(1);
}

DialogMsg &DialogMsg::Instance()
{
    if(m_pInstance==nullptr)
        m_pInstance=new DialogMsg();
    return *m_pInstance;
}
