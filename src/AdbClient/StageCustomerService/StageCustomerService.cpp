#include "StageCustomerService.h"
#include "ui_StageCustomerService.h"

StageCustomerService::StageCustomerService(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageCustomerService)
{
    ui->setupUi(this);

    ui->page1->setEditType();

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    ui->btn2->hide();

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(changePage(int)));

    changePage(0);
}

StageCustomerService::~StageCustomerService()
{
    delete ui;
}

void StageCustomerService::changePage(int iPage)
{

    ui->stackedWidget->setCurrentIndex(iPage);

    if(iPage==0)
         ui->page->init();

    if(iPage==1)
         ui->page1->init();
}

