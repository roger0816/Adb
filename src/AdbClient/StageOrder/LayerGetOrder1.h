#ifndef LAYERGETORDER1_H
#define LAYERGETORDER1_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogNote.h"
#include <QCompleter>
#include <QStringListModel>
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

    void init();

private slots:
    void on_tbUser_cellPressed(int row, int column);

    void on_tbOrder_cellPressed(int row, int column);

    void on_btnBackOrder_clicked();

    void on_btnFinish_clicked();

    void refresh();

    void on_btnChangeNote_clicked();

    void slotCancel();



    void on_btnDelayOrder_clicked();

private:
    Ui::LayerGetOrder1 *ui;

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
        _Note1,
        _Note2

    };

    void refreshUser(bool bRe=true);

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    CListPair m_listPayType;

    QVariantMap m_data;

    QVariantMap gameItem(QString sSid);

    QString  m_currentDataKey="";

    LayerSayCost *m_layerCost  = nullptr;

private:

    int m_iPreUserRow=-1;
    int m_iPreUserCol=-1;

    bool m_bLockLoading = false;

};

#endif // LAYERGETORDER1_H
