#ifndef LAYERUSERREPORT_H
#define LAYERUSERREPORT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "ModelUserReport.h"

namespace Ui {
class LayerUserReport;
}

class LayerUserReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerUserReport(QWidget *parent = nullptr);
    ~LayerUserReport();

    void refresh();

private:
    Ui::LayerUserReport *ui;

    ModelUserReport m_model;

    QButtonGroup m_btns;



private slots:
    void slotBtnDate(int iId);
    void on_dateEdit_dateChanged(const QDate &date);
    void on_btnUserReport_clicked();
};

#endif // LAYERUSERREPORT_H
