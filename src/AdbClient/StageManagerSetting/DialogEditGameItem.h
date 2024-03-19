#ifndef DIALOGEDITGAMEITEM_H
#define DIALOGEDITGAMEITEM_H

#include <QDialog>
#include <QDebug>
#include <QComboBox>
#include "Common.h"
#include "Global.h"
#include "GlobalUi.h"
#include <QVariantMap>
#include "DialogMsg.h"
#include <QToolTip>
#include "VojData.h"
#include <QDoubleSpinBox>
#include <QCompleter>
#include <QWheelEvent>
namespace Ui {
class DialogEditGameItem;
}


namespace _DialogEditGameItem
{
    class DoubleSpinBox:public QDoubleSpinBox
    {
    public:
        DoubleSpinBox(QWidget *parent=nullptr):QDoubleSpinBox(parent){}

        void wheelEvent(QWheelEvent *) override{};
    };
}


class DialogEditGameItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditGameItem(QWidget *parent = nullptr);
    ~DialogEditGameItem();

    void setRate(QString sTitle,DataRate rate);
    void setData(double iGameRate, QVariantMap data);

    void setEanbleCount(bool bShowCountEdit =true);
    bool isEnableCount();
    QVariantMap data();

    //DataExchange::Rate m_rate;

    DataRate m_rate;
private :
    bool m_bLock = false;

    double m_iGameRate=1.00;

    void appendCb(int iCbIdx=0, double cost=100.00);

    enum{_Sort=0,_Sid,_Name,_PrimeCount};
private slots:
    void on_btnCostAdd_clicked();

    void on_btnCostSub_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_sbNTD_valueChanged(double arg1);


    void on_btnGameEditDel_clicked();

    void valueChange(double arg);

    double valueToUp(double d, int decimals);

    void on_sbOrderBouns_valueChanged(double arg1);

    void on_btnCopy_clicked();

    void on_btnPaste_clicked();

private:
    Ui::DialogEditGameItem *ui;

    QVariantMap m_data;

    void refreshCb();


};

#endif // DIALOGEDITGAMEITEM_H
