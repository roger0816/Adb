#ifndef LAYERDAYREPORT_H
#define LAYERDAYREPORT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerSayCost.h"
#include "DialogCommon.h"
#include <QShowEvent>
#include "DialogDayReportEdit.h"
namespace Ui {
class LayerDayReport;
}


namespace  _LayerDayReport{

struct OrderPayType{

    QString sPaySid;
    QString sPayName;
    int iTotalCount=0;

    QList<int> m_iListCount;

};


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


    void delayRefresh();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_tb_cellEntered(int row, int column);

private:
    Ui::LayerDayReport *ui;

    QList<OrderData> m_listOrder;

    QList<OrderData> m_listInto; //after fitler , display of m_listOrder

    LayerSayCost *m_detialOrder = nullptr;


    _LayerDayReport::OrderPayType getPayCount(OrderData data);

    bool m_bLockDate = false;
};

#endif // LAYERDAYREPORT_H
