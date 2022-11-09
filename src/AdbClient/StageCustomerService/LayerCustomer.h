#ifndef LAYERCUSTOMER_H
#define LAYERCUSTOMER_H

#include <QWidget>
#include "DialogCustomerEdit.h"
#include "DialogCustomerCostHistory.h"
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

    void setEditType();

private slots:
    void on_btnAdd_clicked();

    void refresh();

    void on_btnEdit_clicked();

    void on_tb_cellClicked(int row, int column);


    void slotClearSearch();

    void on_txSearch_textChanged(const QString &arg1);

private:
    Ui::LayerCustomer *ui;

    QVariantList m_listData;

    void showEvent(QShowEvent *) override;

    bool checkSearch(CustomerData data);

    void keyPressEvent(QKeyEvent *e) override;

signals:
    void into(int iRow);
};

#endif // LAYERCUSTOMER_H
