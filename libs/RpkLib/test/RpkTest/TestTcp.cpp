#include "TestTcp.h"
#include "ui_TestTcp.h"

TestTcp::TestTcp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestTcp)
{
    ui->setupUi(this);

    connect(&RPKCORE.network,SIGNAL(replyFromServer(QString,QByteArray,int)),this,SLOT(slotReply(QString,QByteArray,int)));

    connect(&RPKCORE.network,SIGNAL(signalReadAll(QByteArray,uintptr_t)),this,SLOT(getFromClient(QByteArray,uintptr_t)));


}

TestTcp::~TestTcp()
{
    delete ui;
}

void TestTcp::on_btnClear_clicked()
{
    ui->txServerLog->clear();

    ui->lbServerLen->clear();
}


void TestTcp::on_btnRunServer_clicked()
{
    if(ui->btnRunServer->isChecked())
    {
        RPKCORE.network.runTcpServer(ui->txPort->text().trimmed());

        ui->txServerLog->append("Start TcpServer");
    }
    else
    {
        RPKCORE.network.stopTcpServer();

        ui->txServerLog->append("Stop");
    }
}

void TestTcp::getFromClient(QByteArray data, uintptr_t handlerID)
{
    qDebug()<<"from Client : "<<QString(data).toStdString().c_str();

    ui->txServerLog->append(QString(data).toStdString().c_str());

    ui->lbServerLen->setText(QString::number(data.length()));
    auto delay =[=](double sec)
    {
        QTime t;
        t.start();
        while(t.elapsed()<1000*sec)
            QCoreApplication::processEvents();

    };


    QString sRe;

    if(QString(data)==ui->txSetQuery->toPlainText())
    {
        sRe = ui->txSetReply->toPlainText();

        //  fn(ui->sbSetDelay->value());

        delay(ui->sbSetDelay->value());

    }
    else if(QString(data)==ui->txSetQuery_2->toPlainText())
    {
        sRe = ui->txSetReply_2->toPlainText();

        delay(ui->sbSetDelay_2->value());
    }
    else
    {
        sRe = QString(data);
    }

    RPKCORE.network.recallClient(sRe.toLatin1(), handlerID);
}

void TestTcp::slotReply(QString sId, QByteArray data, int Error)
{
    if(ui->cbBlock->isChecked())
        return;

    Q_UNUSED(sId);
    Q_UNUSED(Error);
    ui->txOutput->append(QString(data));

    ui->lbClientLen->setText(QString::number(data.length()));
}


void TestTcp::on_btnClientSend_clicked()
{
    QByteArray in;

    in.append(ui->txInput->toPlainText());


    if(!ui->cbBlock->isChecked())
    {
        RPKCORE.network.connectHost("",ui->txIp->text().trimmed(),ui->txPort->text().trimmed(),in);
    }
    else
    {
        QByteArray out;

        RPKCORE.network.connectHost(ui->txIp->text().trimmed(),ui->txPort->text().trimmed(),in,out);

        ui->txOutput->append(QString(out));

        ui->lbClientLen->setText(QString::number(out.length()));
    }
}


void TestTcp::on_btnClientLogClear_clicked()
{
    ui->txOutput->clear();

    ui->lbClientLen->clear();
}


void TestTcp::on_btnSendBig_clicked()
{

    QString st;
    for(int i=0;i<ui->sbBigCount->value();i++)
    {
        st+=ui->txBig->text().trimmed();
    }

    QByteArray in;

    in.append(st);

    if(!ui->cbBlock->isChecked())
    {
        RPKCORE.network.connectHost("",ui->txIp->text().trimmed(),ui->txPort->text().trimmed(),in);
    }

    else
    {
        QByteArray out;

        RPKCORE.network.connectHost(ui->txIp->text().trimmed(),ui->txPort->text().trimmed(),in,out);

        ui->txOutput->append(QString(out));

        ui->lbClientLen->setText(QString::number(out.length()));
    }
    //    qDebug()<<QDateTime::currentDateTime().toString("hh:mm:ss:zzz");
    //    for(int i=0;i<10000;i++)
    //    {
    //        Sleep(10);
    //        QByteArray t;
    //        t.append(QString::number(i));
    //        RPKCORE.network.connectHost("",ui->txIp->text().trimmed(),ui->txPort->text().trimmed(),t);

    //    }

    //    qDebug()<<QDateTime::currentDateTime().toString("hh:mm:ss:zzz");


}

