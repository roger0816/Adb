#ifndef LAYERGETORDER2_H
#define LAYERGETORDER2_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogNote.h"
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

    void init();

private slots:
    void on_tbUser_cellPressed(int row, int column);

    void on_tbOrder_cellPressed(int row, int column);

    void on_btnBackOrder_clicked();

    void on_btnFinish_clicked();

    void refresh();

    void on_btnOrder2Copy_clicked();

    void on_btnNoteChange_clicked();

private:
    Ui::LayerGetOrder2 *ui;

    enum _tbHeader{
        _User=0,
        _Name,
        _Id,
        _CustomerId,
        _CustomerName,
        _GameName,
        _Bouns,
        _Status,
        _Action,
        _Note

    };

    void refreshUser(bool bRe=true);

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    QVariantMap m_data;

    QVariantMap gameItem(QString sSid);

    QString  m_currentDataKey="";

    LayerSayCost *m_layerCost  = nullptr;
    int m_iPreUserRow=-1;
    int m_iPreUserCol=-1;

    bool m_bLockLoading = false;
};

#endif // LAYERGETORDER2_H
