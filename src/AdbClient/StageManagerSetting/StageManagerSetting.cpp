#include "StageManagerSetting.h"
#include "ui_StageManagerSetting.h"

StageManagerSetting::StageManagerSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageManagerSetting)
{
    ui->setupUi(this);


    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    m_btns.addButton(ui->btn3,3);
    m_btns.addButton(ui->btn4,4);

    m_btns.addButton(ui->btn5,5);
    m_btns.addButton(ui->btn6,6);
    m_btns.addButton(ui->btn7,7);
    m_btns.addButton(ui->btn8,8);

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(changePage(int)));


    ui->stackedWidget->setCurrentIndex(0);

    ui->pageExchangeRate->setExchangeType();
}

StageManagerSetting::~StageManagerSetting()
{
    delete ui;
}



void StageManagerSetting::showEvent(QShowEvent *)
{

}

void StageManagerSetting::changePage(int iIdx)
{
    if(iIdx == ui->stackedWidget->indexOf(ui->pageItemCount))
        ui->pageItemCount->refresh();

    ui->stackedWidget->setCurrentIndex(iIdx);
}






