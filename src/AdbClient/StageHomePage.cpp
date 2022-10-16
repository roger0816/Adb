#include "StageHomePage.h"
#include "ui_StageHomePage.h"

StageHomePage::StageHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageHomePage)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
}

StageHomePage::~StageHomePage()
{
    delete ui;
}
