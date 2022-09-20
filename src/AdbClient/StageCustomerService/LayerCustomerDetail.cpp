#include "LayerCustomerDetail.h"
#include "ui_LayerCustomerDetail.h"

LayerCustomerDetail::LayerCustomerDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomerDetail)
{
    ui->setupUi(this);
}

LayerCustomerDetail::~LayerCustomerDetail()
{
    delete ui;
}
