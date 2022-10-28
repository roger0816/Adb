#ifndef LAYERITEMCOUNT_H
#define LAYERITEMCOUNT_H

#include <QWidget>

namespace Ui {
class LayerItemCount;
}

class LayerItemCount : public QWidget
{
    Q_OBJECT

public:
    explicit LayerItemCount(QWidget *parent = nullptr);
    ~LayerItemCount();

private:
    Ui::LayerItemCount *ui;
};

#endif // LAYERITEMCOUNT_H
