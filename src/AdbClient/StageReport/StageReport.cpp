#include "StageReport.h"
#include "ui_StageReport.h"

StageReport::StageReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageReport)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(0);

}

StageReport::~StageReport()
{
    delete ui;
}
