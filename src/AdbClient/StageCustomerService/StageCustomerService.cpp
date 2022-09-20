#include "StageCustomerService.h"
#include "ui_StageCustomerService.h"

StageCustomerService::StageCustomerService(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageCustomerService)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    ui->btn2->hide();

    connect(&m_btns,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));



    qDebug()<<"new customerService";
}

StageCustomerService::~StageCustomerService()
{
    delete ui;
}

