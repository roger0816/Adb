#ifndef LAYERADDCOST_H
#define LAYERADDCOST_H

#include <QWidget>

namespace Ui {
class LayerAddCost;
}

class LayerAddCost : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAddCost(QWidget *parent = nullptr);
    ~LayerAddCost();

private:
    Ui::LayerAddCost *ui;
};

#endif // LAYERADDCOST_H
