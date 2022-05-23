#include "LayerAddCost.h"
#include "ui_LayerAddCost.h"

LayerAddCost::LayerAddCost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAddCost)
{
    ui->setupUi(this);
}

LayerAddCost::~LayerAddCost()
{
    delete ui;
}
