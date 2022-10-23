#ifndef DIALOGEDITGAMEITEM_H
#define DIALOGEDITGAMEITEM_H

#include <QDialog>
#include <QDebug>
#include <QComboBox>
#include "Global.h"
#include "GlobalUi.h"
#include <QVariantMap>
#include "DialogMsg.h"
#include <QToolTip>
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

    void setRate(QString sTitle,DataRate rate);
    void setData(double iGameRate, QVariantMap data);

    QVariantMap data();

    //DataExchange::Rate m_rate;

    DataRate m_rate;
private :
    bool m_bLock = false;

    double m_iGameRate=1.00;

    void appendCb(int iCbIdx=0, double cost=1.00);
private slots:
    void on_btnCostAdd_clicked();

    void on_btnCostSub_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_sbNTD_valueChanged(double arg1);


    void on_btnGameEditDel_clicked();

    void valueChange(double arg);

    double valueToUp(double d, int decimals);

    void on_sbOrderUSD_valueChanged(double arg1);

private:
    Ui::DialogEditGameItem *ui;

    QVariantMap m_data;


};

#endif // DIALOGEDITGAMEITEM_H
