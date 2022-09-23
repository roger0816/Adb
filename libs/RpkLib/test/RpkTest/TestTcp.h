#ifndef TESTTCP_H
#define TESTTCP_H

#include <QWidget>
#include <QDebug>
#include "RpkCore.h"
#include <QTime>
#include <QTimer>
#include <synchapi.h>
namespace Ui {
class TestTcp;
}

class TestTcp : public QWidget
{
    Q_OBJECT

public:
    explicit TestTcp(QWidget *parent = nullptr);
    ~TestTcp();

private slots:
    void on_btnClear_clicked();

    void on_btnRunServer_clicked();

    void getFromClient(QByteArray data,uintptr_t handlerID);

    void slotReply(QString sId,QByteArray data,int Error);
    void on_btnClientSend_clicked();

    void on_btnClientLogClear_clicked();

    void on_btnSendBig_clicked();

private:
    Ui::TestTcp *ui;






};

#endif // TESTTCP_H
