#ifndef STAGEORDER_H
#define STAGEORDER_H

#include <QWidget>
#include <QShowEvent>
#include <QButtonGroup>
#include <QDebug>

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

    void showEvent(QShowEvent *) override;

    QButtonGroup m_btns;
};

#endif // STAGEORDER_H
