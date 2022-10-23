#ifndef LAYERCUSTOMER_H
#define LAYERCUSTOMER_H

#include <QWidget>
#include "DialogCustomerEdit.h"
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerCustomer;
}

class LayerCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCustomer(QWidget *parent = nullptr);
    ~LayerCustomer();

    void init();

private slots:
    void on_btnAdd_clicked();

    void refresh();

    void on_btnEdit_clicked();

    void on_tb_cellPressed(int row, int column);

private:
    Ui::LayerCustomer *ui;

    QVariantList m_listData;

    void showEvent(QShowEvent *) override;
};

#endif // LAYERCUSTOMER_H
