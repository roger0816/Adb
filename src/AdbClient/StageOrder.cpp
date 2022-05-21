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
}

StageOrder::~StageOrder()
{
    delete ui;
}

void StageOrder::showEvent(QShowEvent *)
{

}
