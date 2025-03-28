#ifndef LAYERGETORDER2_H
#define LAYERGETORDER2_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogNote.h"
#include "LayerOrder.h"
#include <QTimerEvent>
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

    void on_pushButton_clicked();

private:
    Ui::LayerGetOrder2 *ui;

    typedef enum{
        _NONE,
        _TIMEOUT,   //等待逾時
        _CHECK,    //鎖單
        _NO_CHECK, //解除鎖單(返回未處理)
        _NOTE,     //更改備註
        _FINISH    //完成送單

    }_LockStatus;

    _LockStatus m_uiLockStatus=_NONE;
    QString m_sUnLockMsg="";

    void uiWait(_LockStatus iType=_NONE,QString sMsg="");

    int m_iUiLockTimeSec=0;
    QString m_sWaitSid="";
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
        _Note

    };

    void refreshUser(bool bRe=true);

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    QVariantMap m_data;


    QString  m_currentDataKey="";

    LayerOrder *m_layerCost  = nullptr;

    QString m_sPreSid="";

    bool m_bLockLoading = false;


    int iTesetCount =0;

signals:
    void dataUpdate();

};

#endif // LAYERGETORDER2_H
