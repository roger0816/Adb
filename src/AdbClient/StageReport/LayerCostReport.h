#ifndef LAYERCOSTREPORT_H
#define LAYERCOSTREPORT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerOrder.h"
#include "DialogCustomerCostHistory.h"
#include "DialogCustomerEdit.h"
#include "CExcelExport.h"
#include "CObjectExcel.h"
#include "xlsxdocument.h"
#include "ItemPic.h"
#include <QFileDialog>
#include <QDesktopServices>

namespace Ui {
class LayerCostReport;
}

class LayerCostReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCostReport(QWidget *parent = nullptr);
    ~LayerCostReport();

    void init();

    void refresh(bool bRequest=false);

private slots:
    void on_btnChangeDate_clicked();

    void on_chOrder_clicked();

    void on_chAddCost_clicked();

    void on_chMix_clicked();

    void on_tb_cellClicked(int row, int column);

    void on_btnFilter_clicked();

    void on_btnFilterClear_clicked();

    void on_btnExcel_clicked();

private:
    Ui::LayerCostReport *ui;

    enum {_Sid=0,_OrderId,_CusId,_CusName,_Currency,_Cost,_User,_Note1};

    QVariantList m_listOrigin;

    QVariantList m_listMix;//只想顯示最終餘額需過濾重複訂單

    QVariantList m_listDisplay;

    bool checkFilter(CustomerData cus,CustomerCost cos);

    void reMix();

   LayerOrder *m_detialOrder = nullptr;

};

#endif // LAYERCOSTREPORT_H
