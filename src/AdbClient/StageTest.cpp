#include "StageTest.h"
#include "ui_StageTest.h"

#include "Global.h"


StageTest::StageTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageTest)
{
    ui->setupUi(this);
    // login super user     root :   1234    for test class



}

StageTest::~StageTest()
{
    delete ui;
}

void StageTest::showEvent(QShowEvent *)
{

    ui->dateEdit->setDate(GLOBAL.dateTimeUtc8().date());

    ui->timeEdit->setTime(GLOBAL.dateTimeUtc8().time());

}


void StageTest::on_btnTestDate_clicked()
{

    QDateTime date;

    date.setDate(ui->dateEdit->date());

    date.setTime(ui->timeEdit->time());

    GLOBAL.m_virtualSec=0;

    GLOBAL.m_virtualSec = date.toUTC().addSecs(60*60*8).toSecsSinceEpoch() -GLOBAL.dateTimeUtc8().toSecsSinceEpoch();




}

