#include "StageOrder.h"
#include "ui_StageOrder.h"

StageOrder::StageOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageOrder)
{
    ui->setupUi(this);
}

StageOrder::~StageOrder()
{
    delete ui;
}
