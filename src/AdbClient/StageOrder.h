#ifndef STAGEORDER_H
#define STAGEORDER_H

#include <QWidget>

namespace Ui {
class StageOrder;
}

class StageOrder : public QWidget
{
    Q_OBJECT

public:
    explicit StageOrder(QWidget *parent = nullptr);
    ~StageOrder();

private:
    Ui::StageOrder *ui;
};

#endif // STAGEORDER_H
