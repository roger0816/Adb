#include "StageCustomer.h"
#include "ui_StageCustomer.h"

StageCustomer::StageCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageCustomer)
{
    ui->setupUi(this);

    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    connect(&m_btns,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

StageCustomer::~StageCustomer()
{
    delete ui;
}
