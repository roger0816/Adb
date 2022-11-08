#include "StageReport.h"
#include "ui_StageReport.h"

StageReport::StageReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageReport)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    m_btns.addButton(ui->btn3,3);

    ui->btn3->hide();

    connect(&m_btns,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));


    ui->stackedWidget->setCurrentIndex(0);

    ui->page0->setEditMode(true);



}

StageReport::~StageReport()
{
    delete ui;
}
