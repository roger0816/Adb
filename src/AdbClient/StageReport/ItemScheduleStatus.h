#ifndef ITEMSCHEDULESTATUS_H
#define ITEMSCHEDULESTATUS_H

#include <QWidget>
#include "GlobalUi.h"
namespace Ui {
class ItemScheduleStatus;
}

class ItemScheduleStatus : public QWidget
{
    Q_OBJECT

public:
    explicit ItemScheduleStatus(QWidget *parent = nullptr);
    ~ItemScheduleStatus();

    QString data();

    void setData(QString sData);

    void setEditMode(bool b);

private:

    void refresh();

    QVariantList m_data;

    bool checkHasTitle(QString sTitle);
signals:

    void sendClicked(QString sText);
private slots:
    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_tbEdit_itemEntered(QTableWidgetItem *item);

    void on_tb_itemClicked(QTableWidgetItem *item);

private:
    Ui::ItemScheduleStatus *ui;

    bool m_bEditMode= false;
};

#endif // ITEMSCHEDULESTATUS_H
