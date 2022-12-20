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

private:
    Ui::LayerDayDebit *ui;

    void showEvent(QShowEvent*) override;


    QVariantList m_allDebit;


    QVariantList m_listDebit;


    QVariantList m_listCustomerCost;

    QVariantList m_listDisplayCustomerCost;


    bool checkData(CustomerCost data);

    QDialog *m_dialogPic = new QDialog();
    ItemPic *m_itemPic  = new ItemPic(m_dialogPic);

    void setCb();

    bool m_bLockRe = false;

    QString getDebitName(QString debitSid);

private slots:
    void refresh();

    void refreshTb();

    void on_cbDebit_currentIndexChanged(int index);
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_timeStart_userTimeChanged(const QTime &time);
    void on_timeEnd_userTimeChanged(const QTime &time);
    void on_tb_cellPressed(int row, int column);
    void slotBtnDebitExport();
};

#endif // LAYERDAYDEBIT_H
