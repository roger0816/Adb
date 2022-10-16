#ifndef LAYERPRIMECOSTRATE_H
#define LAYERPRIMECOSTRATE_H

#include <QWidget>
#include <QRegExpValidator>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerPrimeCostRate;
}

class LayerPrimeCostRate : public QWidget
{
    Q_OBJECT

public:
    explicit LayerPrimeCostRate(QWidget *parent = nullptr);
    ~LayerPrimeCostRate();

    void showEvent(QShowEvent* )override;

    void setExchangeType();

private slots:
    void on_btnAdd_clicked();

    void on_btnSub_clicked();

    void on_btnSave_clicked();

    void on_tb1_itemEntered(QTableWidgetItem *item);

    void refresh();

private:
    Ui::LayerPrimeCostRate *ui;

    void reLineEdit();

    void refreshRate();

    void refreshTbDetail();

     QList<DataRate> m_listRate;

     bool m_bExchangeType = false;

};

#endif // LAYERPRIMECOSTRATE_H
