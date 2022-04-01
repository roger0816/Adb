#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("艾比代管理系統");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
//    QByteArray in,out;



//    LIB.network()->connectHost("127.0.0.1","6000",in,out);


}

