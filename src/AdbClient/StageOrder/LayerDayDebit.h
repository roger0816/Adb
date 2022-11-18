#ifndef LAYERDAYDEBIT_H
#define LAYERDAYDEBIT_H

#include <QWidget>
#include "GlobalUi.h"
#include "Global.h"

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


    QVariantList m_listDebit;

    QVariantList m_listCustomerCost;

    bool checkData(CustomerCost data);


private slots:
    void refresh();

    void refreshTb();

    void on_cbDebit_currentIndexChanged(int index);
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_timeStart_userTimeChanged(const QTime &time);
    void on_timeEnd_userTimeChanged(const QTime &time);
};

#endif // LAYERDAYDEBIT_H
