#ifndef LAYERDAYREPORT_H
#define LAYERDAYREPORT_H

#include <QWidget>
#include <QDir>
#include <QDesktopServices>
#include "DialogNote.h"
#include "Global.h"
#include "GlobalUi.h"
#include "LayerOrder.h"
#include "DialogCommon.h"
#include <QShowEvent>
#include "DialogDayReportEdit.h"

#include "CExcelExport.h"
#include "CObjectExcel.h"
#include "xlsxdocument.h"
#include "ItemPic.h"
#include <QFileDialog>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

namespace Ui {
class LayerDayReport;
}


namespace  _LayerDayReport{

struct OrderPayType{

    QString sPaySid;
    QString sPayName;
    double iTotalCount=0.00;

    QList<int> m_iListCount;

};

enum tbHeader
{
    _Sid=0,
    _OderId=1,      //訂單編號
    _Name,        //序號
    _CheckNum,      //核對單位
    _DateTime,    //成立時間
    _User,        //專員代碼
    _Customer,    //客戶編號
    _Status,        //訂單狀態
    _Bonus,         //業績
    _GameName,      //遊戲名稱
    _GameItem,    //訂單項目
    _PayType,    //儲值方式
    _PayCount,  //單位
    _Currency,      //幣別
    _TodayCost,     //今日應收
    _ExRate,        //售價匯率
    _Cost,          //應收(台幣)
    _PrimeRate,      //成本匯率
    _Prime,         //成本(台幣)
    _Profit,        //利潤(台幣
    _ProfitForOne,  //每業績利潤
    _PayRate,       //成本參數
    _Pic1,           //回報圖
    _Pic0,          //儲值圖

    _Note,
    _Note1,

    _TB_COL_COUNT
};


}


class LayerDayReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerDayReport(QWidget *parent = nullptr);
    ~LayerDayReport();

    void init();

    bool checkFilter(OrderData order);

    virtual void refreshTb(bool bRequery=true,bool bResetCb=true);
private slots:



    void on_tb_cellPressed(int row, int column);


    void on_cbStep0_1_clicked();

    void on_cbStep0_clicked();

    void on_cbStep1_clicked();

    void on_cbStep2_clicked();

    void on_cbStep3_clicked();

    void on_cbStep4_clicked();

    void on_cbStep5_clicked();

    void on_btnFilter_clicked();
    void on_btnFilterClear_clicked();


    void delayRefresh();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_tb_cellEntered(int row, int column);

    void on_btnExcel_clicked();

    void on_cbShowBonus_clicked();

    void on_cbShowPic_clicked();

    void on_cbShowCost_clicked();

    void on_btnChangeDate_clicked();




    void on_cbFilter_currentIndexChanged(int index);

    void on_cbShowGameItem_clicked();

public:
    Ui::LayerDayReport *ui;

    QList<OrderData> m_listOrder;

   // QList<OrderData> m_listInto; //after fitler , display of m_listOrder

        QVariantMap m_mappingData;

    LayerOrder *m_detialOrder = nullptr;


    _LayerDayReport::OrderPayType getPayCount(OrderData data);

    bool m_bLockDate = false;

    QDialog *m_dialogPic = new QDialog();
    ItemPic *m_itemPic  = new ItemPic(m_dialogPic);

    void changeVisable();

    bool m_bLockLoading=false;

    void updateOrderData(bool bUpdate,bool bStrong=false);

    QString m_sFilterKey="";

    QString statusString(QString sStep);

    QString getGameItemStr(QString items);

    bool bIsFirst = true;

};

#endif // LAYERDAYREPORT_H
