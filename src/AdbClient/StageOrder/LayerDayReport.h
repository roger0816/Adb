#ifndef LAYERDAYREPORT_H
#define LAYERDAYREPORT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerSayCost.h"
#include "DialogCommon.h"
#include <QShowEvent>
#include "DialogDayReportEdit.h"
#include "CExcelExport.h"
#include "CObjectExcel.h"
#include "xlsxdocument.h"
#include "ItemPic.h"
#include <QFileDialog>
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

enum tbHeader
{
    _OderId=0,      //訂單編號
    _Name=1,        //序號
    _DateTime=2,    //成立時間
    _User=3,        //專員代碼
    _Customer=4,    //客戶編號
    _Content=5,     //訂單內容
    _Status=6,
    _Bonus=7,
    _Check=8,
    _Currency=9,
    _TodayCost=10,
    _Cost=11,
    _Prime=12,
    _Profit=13,
    _ProfitForOne=14,
    _PayType = 15,
    _PayCount=16,
    _PayRate=17,
    _Pic0=18,
    _Pic1=19


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


    void on_cbStep0_1_clicked();

    void on_cbStep0_clicked();

    void on_cbStep1_clicked();

    void on_cbStep2_clicked();

    void on_cbStep3_clicked();

    void on_cbStep4_clicked();

    void on_cbStep5_clicked();


    void delayRefresh();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_tb_cellEntered(int row, int column);

    void on_btnExcel_clicked();

private:
    Ui::LayerDayReport *ui;

    QList<OrderData> m_listOrder;

    QList<OrderData> m_listInto; //after fitler , display of m_listOrder

    LayerSayCost *m_detialOrder = nullptr;


    _LayerDayReport::OrderPayType getPayCount(OrderData data);

    bool m_bLockDate = false;

    QDialog *m_dialogPic = new QDialog();
    ItemPic *m_itemPic  = new ItemPic(m_dialogPic);

};

#endif // LAYERDAYREPORT_H
