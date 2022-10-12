#include "StageTest.h"
#include "ui_StageTest.h"
#include "Label3.h"


StageTest::StageTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageTest)
{
    ui->setupUi(this);


    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {

        Label3 *l0 = new Label3(ui->tableWidget);

            Label3 *l1 = new Label3(ui->tableWidget);
                Label3 *l2 = new Label3(ui->tableWidget);
                    Label3 *l3 = new Label3(ui->tableWidget);
                        Label3 *l4 = new Label3(ui->tableWidget);
        ui->tableWidget->setCellWidget(i,0,l0);

        ui->tableWidget->setCellWidget(i,1,l1);

        ui->tableWidget->setCellWidget(i,2,l2);

        ui->tableWidget->setCellWidget(i,3,l3);

        ui->tableWidget->setCellWidget(i,4,l4);


    }



}

StageTest::~StageTest()
{
    delete ui;
}


