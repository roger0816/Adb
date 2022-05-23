#include "LayerOrder.h"
#include "ui_LayerOrder.h"

LayerOrder::LayerOrder(QWidget *parent) :
    LayerSayCost(parent),
    ui(new Ui::LayerOrder)
{
    ui->setupUi(this);

    orderMode();

}

LayerOrder::~LayerOrder()
{
    delete ui;
}
