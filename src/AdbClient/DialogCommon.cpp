#include "DialogCommon.h"
#include "ui_DialogCommon.h"

DialogCommon::DialogCommon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCommon)
{
    ui->setupUi(this);
}

DialogCommon::~DialogCommon()
{
    delete ui;
}

void DialogCommon::setWidget(QWidget *w)
{
    QGridLayout *lay = new QGridLayout;

    lay->addWidget(w);

    ui->wBody->setLayout(lay);

}

void DialogCommon::on_btnOk_clicked()
{
    reject();
}

