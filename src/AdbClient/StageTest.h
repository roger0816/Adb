#ifndef STAGETEST_H
#define STAGETEST_H

#include <QWidget>
#include "DialogInput.h"
#include "DialogCommon.h"
#include "LayerSayCost.h"

namespace Ui {
class StageTest;
}

class StageTest : public QWidget
{
    Q_OBJECT

public:
    explicit StageTest(QWidget *parent = nullptr);
    ~StageTest();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StageTest *ui;
};

#endif // STAGETEST_H
