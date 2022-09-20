#ifndef LAYERDAYREPORT_H
#define LAYERDAYREPORT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerSayCost.h"
#include "DialogCommon.h"
#include <QShowEvent>
namespace Ui {
class LayerDayReport;
}

class LayerDayReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerDayReport(QWidget *parent = nullptr);
    ~LayerDayReport();

    void showEvent(QShowEvent *) override;
    void refreshTb();

    bool checkFilter(OrderData order);
private slots:
    void on_tb_cellPressed(int row, int column);

    void on_cbStep0_clicked();

    void on_cbStep1_clicked();

    void on_cbStep2_clicked();

    void on_cbStep3_clicked();

    void on_cbStep4_clicked();

    void on_cbStep5_clicked();

    void on_tb_cellClicked(int row, int column);

private:
    Ui::LayerDayReport *ui;

    QList<OrderData> m_listOrder;

    QList<OrderData> m_listInto;

    LayerSayCost *m_detialOrder = nullptr;

    void checkMoney(int iRow, OrderData order, CustomerData customer);


};

#endif // LAYERDAYREPORT_H
