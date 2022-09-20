#ifndef LAYERORDER_H
#define LAYERORDER_H

#include <QWidget>
#include "LayerSayCost.h"

namespace Ui {
class LayerOrder;
}

class LayerOrder : public LayerSayCost
{
    Q_OBJECT

public:
    explicit LayerOrder(QWidget *parent = nullptr);
    ~LayerOrder();



private:
    Ui::LayerOrder *ui;
};

#endif // LAYERORDER_H
