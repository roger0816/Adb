#ifndef LAYERGETORDER1_H
#define LAYERGETORDER1_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogNote.h"
#include <QCompleter>
#include <QStringListModel>
#include "LayerOrder.h"
#include <QTimerEvent>

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

    void on_btnFacChange_clicked();

    void on_btnFacCancel_clicked();





private:
    Ui::LayerGetOrder1 *ui;

    typedef enum{
        _NONE,
        _TIMEOUT,   //等待逾時
        _CANCEL,    //取消
        _API_SET,   //API訂單取置負責人
        _API_CANCEL,//API訂單取消
        _CHECK,    //鎖單
        _NO_CHECK, //解除鎖單(返回未處理)
        _NOTE,     //更改備註
        _FINISH    //完成送單

    }_LockStatus;

    _LockStatus m_uiLockStatus=_NONE;
    QString m_sUnLockMsg="";
    QString m_sWaitSid="";

    void uiWait(_LockStatus iType=_NONE,QString sMsg="");

    int m_iUiLockTimeSec=0;

    void timerEvent(QTimerEvent *) override;

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

    void refreshUser();

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    CListPair m_listPayType;

    QVariantMap m_data;


    QString  m_currentDataKey="";

    LayerOrder *m_layerCost  = nullptr;

private:


    QString m_sPreSid="";

    bool m_bLockLoading = false;



signals:
    void dataUpdate();

};

#endif // LAYERGETORDER1_H
