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



void StageTest::on_pushButton_clicked()
{
    QVariantMap in;

    QVariantList out;

    QString sError;

    ACTION.action(ACT::QUERY_ORDER,in,out,sError);


    foreach(QVariant tar,out)
    {
        QVariantMap d = tar.toMap();

        QStringList keys=d.keys();

        foreach(QString key,keys)
        {
            QVariant v=d[key];
            ui->textEdit->append(key+"="+v.typeName()+" : "+v.toString());
        }
        ui->textEdit->append("\n");

    }


}

