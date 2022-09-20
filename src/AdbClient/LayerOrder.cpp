#include "LayerOrder.h"
#include "ui_LayerOrder.h"

LayerOrder::LayerOrder(QWidget *parent) :
    LayerSayCost(parent),
    ui(new Ui::LayerOrder)
{
    ui->setupUi(this);


    m_bOrderMode=true;
}

LayerOrder::~LayerOrder()
{
    delete ui;
}
