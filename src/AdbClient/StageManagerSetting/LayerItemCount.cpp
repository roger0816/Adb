#include "LayerItemCount.h"
#include "ui_LayerItemCount.h"

LayerItemCount::LayerItemCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerItemCount)
{
    ui->setupUi(this);
}

LayerItemCount::~LayerItemCount()
{
    delete ui;
}
