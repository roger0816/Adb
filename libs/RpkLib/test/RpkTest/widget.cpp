#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    btns.addButton(ui->btnTcp,1);
    btns.addButton(ui->btnOther,0);

    connect(&btns,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

Widget::~Widget()
{
    delete ui;
}


