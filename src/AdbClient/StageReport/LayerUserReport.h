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



};

#endif // LAYERUSERREPORT_H
