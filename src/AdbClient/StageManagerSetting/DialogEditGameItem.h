#ifndef DIALOGEDITGAMEITEM_H
#define DIALOGEDITGAMEITEM_H

#include <QDialog>
#include <QDebug>
#include <QVariantMap>
#include "DialogMsg.h"
#include "VojData.h"
#include <QDoubleSpinBox>
namespace Ui {
class DialogEditGameItem;
}

class DialogEditGameItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditGameItem(QWidget *parent = nullptr);
    ~DialogEditGameItem();

    void setRate(QString sTitle,PrimeRate rate);
    void setData(QVariantMap data);

    QVariantMap data();

    //DataExchange::Rate m_rate;

    PrimeRate m_rate;
private :
    bool m_bLock = false;
private slots:
    void on_btnCostAdd_clicked();

    void on_btnCostSub_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_sbNTD_valueChanged(double arg1);


    void on_btnGameEditDel_clicked();

    void valueChange(double arg);

private:
    Ui::DialogEditGameItem *ui;

    QVariantMap m_data;


};

#endif // DIALOGEDITGAMEITEM_H
