#ifndef STAGEACCOUNT_H
#define STAGEACCOUNT_H

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QShowEvent>
#include "Global.h"
#include "DialogMsg.h"

namespace Ui {
class StageAccount;
}

class StageAccount : public QWidget
{
    Q_OBJECT

public:
    explicit StageAccount(QWidget *parent = nullptr);
    ~StageAccount();

private slots:
    void on_btnPassword_clicked();

    void slotPage(int i);

    void on_btnEdit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::StageAccount *ui;

    void showEvent(QShowEvent *) override;

     QButtonGroup m_btns;

     void readUser();

     UserData m_user;

};

#endif // STAGEACCOUNT_H
