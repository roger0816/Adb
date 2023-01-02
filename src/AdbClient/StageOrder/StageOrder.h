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
       void init();
private:
    Ui::StageOrder *ui;

    bool m_bFirst = true;

    QButtonGroup m_btns;

private slots:
    void changePage(int iPage);
};

#endif // STAGEORDER_H
