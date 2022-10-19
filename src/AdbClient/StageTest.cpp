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
    //include "Global.h"

    QVariantMap in;//輸入參數，空白為全取，都先使用空白

    QVariantList out;// 取回來的資料

    QString sError;

    ACTION.action(ACT::QUERY_ORDER,in,out,sError);


    foreach(QVariant tar,out)
    {
        //每一個單位為db的每行row ，key是對的上
        QVariantMap d = tar.toMap();

        //方式1: 直接用
        QStringList keys=d.keys();

        foreach(QString key,keys)
        {
            QVariant v=d[key];
            ui->textEdit->append(key+"="+v.typeName()+" : "+v.toString());
        }
        ui->textEdit->append("\n");

        //方式2: 用VojData.h
        OrderData data(d);
        qDebug()<<data.Sid;  //變數名字 使用跟db上的key一樣
        qDebug()<<data.Money;

    }


}

