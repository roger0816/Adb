#include "StageTest.h"
#include "ui_StageTest.h"

#include "Global.h"


StageTest::StageTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageTest)
{
    ui->setupUi(this);
// login super user     root :   1234    for test class



    ui->widget->setBtns(QStringList()<<"AA"<<"BB"<<"CC"<<"EE");
}

StageTest::~StageTest()
{
    delete ui;
}



void StageTest::on_pushButton_clicked()
{
    //include "Global.h"



}

