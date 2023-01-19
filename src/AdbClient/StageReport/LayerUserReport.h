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


private:
    Ui::LayerUserReport *ui;

    ModelUserReport m_model;

    QButtonGroup m_btns;

    void showEvent(QShowEvent *) override;


private slots:
    void slotBtnDate(int iId);

    void refresh();


    void on_btnOk_clicked();
};

#endif // LAYERUSERREPORT_H
