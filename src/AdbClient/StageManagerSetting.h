#ifndef STAGEMANAGERSETTING_H
#define STAGEMANAGERSETTING_H

#include <QWidget>
#include <QButtonGroup>
#include "Global.h"
#include "DialogMsg.h"
#include <QShowEvent>
#include <QMapIterator>
#include <QTableWidgetItem>
#include "DialogEditUser.h"

namespace Ui {
class StageManagerSetting;
}

class StageManagerSetting : public QWidget
{
    Q_OBJECT

public:
    explicit StageManagerSetting(QWidget *parent = nullptr);
    ~StageManagerSetting();

private slots:
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_btnDel_clicked();

private:
    Ui::StageManagerSetting *ui;

    void showEvent(QShowEvent *) override;

     QButtonGroup m_btns;

     void refreshTb();

     QTableWidgetItem *tbItem(int, QString st);

     QList<UserData> m_listUser;
};

#endif // STAGEMANAGERSETTING_H
