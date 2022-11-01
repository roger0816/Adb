#ifndef STAGETEST_H
#define STAGETEST_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class StageTest;
}

class StageTest : public QWidget
{
    Q_OBJECT

public:
    explicit StageTest(QWidget *parent = nullptr);
    ~StageTest();

    void showEvent(QShowEvent * )override;

private slots:


    void on_btnTestDate_clicked();

private:
    Ui::StageTest *ui;
};

#endif // STAGETEST_H
