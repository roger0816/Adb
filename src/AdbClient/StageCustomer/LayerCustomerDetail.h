#ifndef LAYERCUSTOMERDETAIL_H
#define LAYERCUSTOMERDETAIL_H

#include <QWidget>

namespace Ui {
class LayerCustomerDetail;
}

class LayerCustomerDetail : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCustomerDetail(QWidget *parent = nullptr);
    ~LayerCustomerDetail();

private:
    Ui::LayerCustomerDetail *ui;
};

#endif // LAYERCUSTOMERDETAIL_H
