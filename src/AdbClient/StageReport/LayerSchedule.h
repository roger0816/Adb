#ifndef LAYERSCHEDULE_H
#define LAYERSCHEDULE_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QShowEvent>
#include <QButtonGroup>
#include <QSpinBox>
#include <QMouseEvent>

namespace Ui {
class LayerSchedule;
}


class CLineEditClick : public QLineEdit
{
    Q_OBJECT
public:
    void mousePressEvent(QMouseEvent *) override
    {
        emit clicked();
    }

 signals:
    void clicked();

};


class LayerSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSchedule(QWidget *parent = nullptr);
    ~LayerSchedule();


    void showEvent(QShowEvent*) override;

    void refresh();


    QButtonGroup m_group;


    QString sDataUserSid[52][7];
    QString sDataCost[52][7];
    QString sDataCheck[52][7];
    QString sTb0Note[52][7];

private slots:
    void on_btnSave_clicked();

    void on_btnName_clicked();

    void on_btnCost_clicked();

    void on_tb2_itemClicked(QTableWidgetItem *item);

    void on_tb1_itemChanged(QTableWidgetItem *item);

    void on_tb0_itemChanged(QTableWidgetItem *item);

    void on_btnChangeBtn_clicked();

    void btnsClicked();
    void on_tb1_cellChanged(int row, int column);

private:
    Ui::LayerSchedule *ui;

    void changeTb();

    QList<QPushButton*> m_listBtn;

    void refreshCb();


    void write();

    void read();
};

#endif // LAYERSCHEDULE_H
