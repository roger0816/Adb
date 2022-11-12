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

    bool checkFilter(OrderData order);

    void refreshTb();
private slots:
    void on_tb_cellPressed(int row, int column);

    void on_cbStep0_clicked();

    void on_cbStep1_clicked();

    void on_cbStep2_clicked();

    void on_cbStep3_clicked();

    void on_cbStep4_clicked();

    void on_cbStep5_clicked();

    void on_tb_cellClicked(int, int);

    void delayRefresh();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_tb_cellEntered(int row, int column);

private:
    Ui::LayerDayReport *ui;

    QList<OrderData> m_listOrder;

    QList<OrderData> m_listInto;

    LayerSayCost *m_detialOrder = nullptr;


    bool m_bLockDate = false;
};

#endif // LAYERDAYREPORT_H
