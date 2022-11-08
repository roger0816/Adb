#ifndef LAYERGAMEREPORT_H
#define LAYERGAMEREPORT_H

#include <QWidget>

#include "Global.h"
#include "GlobalUi.h"
#include "ModelGameReport.h"


namespace Ui {
class LayerGameReport;
}

class LayerGameReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerGameReport(QWidget *parent = nullptr);
    ~LayerGameReport();

    void refresh();

private:
    Ui::LayerGameReport *ui;

    QButtonGroup m_btns;

    ModelGameReport m_model;

private slots:
    void slotBtnDate(int iId);


};

#endif // LAYERGAMEREPORT_H
