#ifndef LAYERGAMEREPORT_H
#define LAYERGAMEREPORT_H

#include <QWidget>

#include "Global.h"
#include "GlobalUi.h"
#include "ModelGameReport.h"
#include <QShowEvent>

namespace Ui {
class LayerGameReport;
}

class LayerGameReport : public QWidget
{
    Q_OBJECT

public:
    explicit LayerGameReport(QWidget *parent = nullptr);
    ~LayerGameReport();



    void showEvent(QShowEvent *) override;

private:
    Ui::LayerGameReport *ui;

    QButtonGroup m_btns;

    ModelGameReport m_model;

private slots:
    void slotBtnDate(int iId);
    void refresh();

    void on_btnOk_clicked();
};

#endif // LAYERGAMEREPORT_H
