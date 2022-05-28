#include "StageTest.h"
#include "ui_StageTest.h"

StageTest::StageTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageTest)
{
    ui->setupUi(this);




}

StageTest::~StageTest()
{
    delete ui;
}

void StageTest::on_pushButton_clicked()
{
    LayerSayCost layer;

    QVariantMap d;



    DialogCommon dialog;

    dialog.setWidget(&layer);

    dialog.exec();

}

