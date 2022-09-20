#ifndef LAYERGETORDER2_H
#define LAYERGETORDER2_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "LayerSayCost.h"

namespace Ui {
class LayerGetOrder2;
}

class LayerGetOrder2 : public QWidget
{
    Q_OBJECT

public:
    explicit LayerGetOrder2(QWidget *parent = nullptr);
    ~LayerGetOrder2();

    void showEvent(QShowEvent *) override;

private slots:
    void on_tbUser_cellPressed(int row, int column);

    void on_tbOrder_cellPressed(int row, int column);

    void on_btnBackOrder_clicked();

    void on_btnFinish_clicked();

private:
    Ui::LayerGetOrder2 *ui;

    void refreshUser(bool bRe=true);

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    QVariantMap m_data;

    QVariantMap gameItem(QString sSid);

    QString  m_currentDataKey="";

    LayerSayCost *m_layerCost  = nullptr;
};

#endif // LAYERGETORDER2_H
