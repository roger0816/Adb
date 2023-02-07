#ifndef LAYERDAYDEBIT_H
#define LAYERDAYDEBIT_H

#include <QWidget>
#include "GlobalUi.h"
#include "Global.h"
#include "ItemPic.h"
#include "xlsxdocument.h"
namespace Ui {
class LayerDayDebit;
}

class LayerDayDebit : public QWidget
{
    Q_OBJECT

public:
    explicit LayerDayDebit(QWidget *parent = nullptr);
    ~LayerDayDebit();
    void init();
private:
    Ui::LayerDayDebit *ui;

    enum tbHeader
    {
        _OrderId=0,
        _DebitSid,

        _CusSid,
        _CusName,
        _CusCurrency,
        _CusTotal,
        _DebitNote,
        _ChangeValue,
        _OriValue,
        _OriCurrency,

        _Note0,
        _OrderTime,
        _UserName,
        _Pic0,
        _Pic1,

        _Note1,
        _ColCount

    };


    QVariantList m_allDebit;


    QVariantList m_listDebit;


    QVariantList m_listCustomerCost;

    QVariantList m_listDisplayCustomerCost;


    bool checkData(CustomerCost data);

    QDialog *m_dialogPic = new QDialog();
    ItemPic *m_itemPic  = new ItemPic(m_dialogPic);

    void setCb(bool bRe= true);

    bool m_bLockRe = false;

    QString getDebitName(QString debitSid);

private slots:
    void refresh(bool bRe=true);

    void refreshTb();

    void on_cbDebit_currentIndexChanged(int index);
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_timeStart_userTimeChanged(const QTime &time);
    void on_timeEnd_userTimeChanged(const QTime &time);
    void on_tb_cellPressed(int row, int column);
    void slotBtnDebitExport();
    void on_btnChangeDate_clicked();
};

#endif // LAYERDAYDEBIT_H
