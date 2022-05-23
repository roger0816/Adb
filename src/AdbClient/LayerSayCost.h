#ifndef LAYERSAYCOST_H
#define LAYERSAYCOST_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QSpinBox>

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

     void setCustomer(QVariantMap data);

     void showEvent(QShowEvent *) override;
     void refreshInfo();
     Ui::LayerSayCost *ui;

private:

    QVariantMap m_dataCustomer;

    QVariantList m_listGameInfo;

    QString m_sCurrentGameSid="";

    QVariantList m_listGameItem;

    QVariantList m_listInto;

    QList<QSpinBox*> m_listSp;

    double checkTotal();
signals:
    void back();
public slots:

    void on_btnSayCostBack_clicked();

    void spValue(int i);
private slots:
    void on_cbGame_currentTextChanged(const QString &arg1);
    void on_cbAccount_currentTextChanged(const QString &arg1);
    void on_tbGameItem_cellClicked(int row, int column);
    void on_tbInfo_cellPressed(int row, int column);
};

#endif // LAYERSAYCOST_H
