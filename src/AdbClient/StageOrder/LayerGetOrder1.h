#ifndef LAYERGETORDER1_H
#define LAYERGETORDER1_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerSayCost.h"

namespace Ui {
class LayerGetOrder1;
}

class LayerGetOrder1 : public QWidget
{
    Q_OBJECT

public:
    explicit LayerGetOrder1(QWidget *parent = nullptr);
    ~LayerGetOrder1();

    void showEvent(QShowEvent *) override;

private slots:
    void on_tbUser_cellPressed(int row, int column);

    void on_tbOrder_cellPressed(int row, int column);

    void on_btnBackOrder_clicked();

    void on_btnFinish_clicked();

private:
    Ui::LayerGetOrder1 *ui;

    void refreshUser(bool bRe=true);

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    CListPair m_listPayType;

    QVariantMap m_data;

    QVariantMap gameItem(QString sSid);

    QString  m_currentDataKey="";

    LayerSayCost *m_layerCost  = nullptr;
};

#endif // LAYERGETORDER1_H
