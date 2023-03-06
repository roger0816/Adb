#ifndef LAYERORDER_H
#define LAYERORDER_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerOrder;
}

class LayerOrder : public QWidget
{
    Q_OBJECT

public:
    explicit LayerOrder(QWidget *parent = nullptr);
    ~LayerOrder();

    void setReadOnly();

    void setData(OrderData order, CustomerData cus);

        void setData(OrderData order);
private:
    void init();

    void setInfo(QStringList listInfo);

    void setBuyData();

    void setCb();

    CustomerData m_cus;

    OrderData m_order;

    QDateTime m_date;

    bool m_bIsReadOnly = false;//false是下單畫面； true是訂單內容

signals:
    void back(int iPage=0);
private slots:
    void on_btnOrderBack_clicked();

    void on_btnOrderSend_clicked();

    void on_btnClose_clicked();

    void on_btnCopy_clicked();

private:
    Ui::LayerOrder *ui;
};

#endif // LAYERORDER_H
