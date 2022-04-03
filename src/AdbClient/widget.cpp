#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("艾比代管理系統");

    m_btns.addButton(ui->btn0,0);
    m_btns.addButton(ui->btn1,1);
    m_btns.addButton(ui->btn2,2);
    m_btns.addButton(ui->btn3,3);
    m_btns.addButton(ui->btnAccount,4);

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(slotPage(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotPage(int iIdx)
{
    ui->stackedWidget->setCurrentIndex(iIdx);
}




