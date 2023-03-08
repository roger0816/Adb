#include "StageOrder.h"
#include "ui_StageOrder.h"

StageOrder::StageOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageOrder)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    m_btns.addButton(ui->btn3,3);

    m_btns.addButton(ui->btn4,4);

        m_btns.addButton(ui->btn5,5);

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(changePage(int)));

    ui->stackedWidget->setCurrentIndex(0);
}

StageOrder::~StageOrder()
{
    delete ui;
}

void StageOrder::init()
{
    if(m_bFirst)
    {
        m_bFirst = false;
        changePage(0);
    }
}

void StageOrder::changePage(int iPage)
{
    if(iPage==0)
    {
        ui->pageCostTable->init();
    }
    else if(iPage==1)
    {
        ui->pageGetOrder1->init();
    }

    else if(iPage==2)
    {
        ui->pageGetOrder2->init();
    }
    else if(iPage==3)
    {
        ui->pageDayReport->init();
    }

    else if(iPage==4)
    {
        ui->pageDayDebit->init();
    }

    else if(iPage==5)
    {
        ui->pageCostReport->init();
    }



    ui->stackedWidget->setCurrentIndex(iPage);
    //本來在各頁showEvent 做init，調出來換頁時call
}
