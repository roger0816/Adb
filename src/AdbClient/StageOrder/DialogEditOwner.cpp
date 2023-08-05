#include "DialogEditOwner.h"
#include "ui_DialogEditOwner.h"

DialogEditOwner::DialogEditOwner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditOwner)
{
    ui->setupUi(this);
}

DialogEditOwner::~DialogEditOwner()
{
    delete ui;
}
