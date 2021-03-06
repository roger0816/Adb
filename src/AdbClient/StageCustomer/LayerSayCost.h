#ifndef LAYERSAYCOST_H
#define LAYERSAYCOST_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QSpinBox>
#include <QClipboard>

namespace Ui {
class LayerSayCost;
}

class LayerSayCost : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSayCost(QWidget *parent = nullptr);
    ~LayerSayCost();

        void orderMode();

     void setCustomer(QVariantMap data,QString sOrderSid="");

     void setReadOnly();

     void showEvent(QShowEvent *) override;
     void refreshInfo();
     Ui::LayerSayCost *ui;
     bool m_bOrderMode = false;

private:

    CustomerData m_dataCustomer;

    QVariantList m_listGameInfo;

    QString m_sCurrentGameSid="";

    QVariantList m_listGameItem;

    QVariantList m_listInto;

    QList<QSpinBox*> m_listSp;

    double checkTotal();

    QList<UserData> m_listOwnerUser;


    OrderData m_order;

    QDateTime m_date;

    double m_iTotal=0.0;

    double m_iBouns=0.0;

    QString m_sLoadOrderSid="";

    QString m_sLoadRateSid="";

    bool m_bReadOnly = false;
protected:


    QString getNewOrderId();

    QString getNewOrderName();

signals:
    void back();
public slots:

    void on_btnSayCostBack_clicked();

    void spValue(int i);
private slots:
    void on_cbGame_currentTextChanged(const QString &arg1);
    void on_cbAccount_currentTextChanged(const QString &arg1);
    void on_cbServer_currentTextChanged(const QString &arg1);
    void on_cbChr_currentTextChanged(const QString &arg1);
    void on_tbGameItem_cellClicked(int row, int column);
    void on_tbInfo_cellPressed(int row, int column);
    void on_btnCopy_clicked();
    void on_btnSayClose_clicked();

public slots:
    void on_btnSayOk_clicked();
};

#endif // LAYERSAYCOST_H
