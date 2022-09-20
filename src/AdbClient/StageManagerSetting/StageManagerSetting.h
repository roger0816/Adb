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


private:
    Ui::StageManagerSetting *ui;

    void showEvent(QShowEvent *) override;


     QButtonGroup m_btns;

};

#endif // STAGEMANAGERSETTING_H
