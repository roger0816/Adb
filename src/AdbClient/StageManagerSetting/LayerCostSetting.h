#ifndef LAYERCOSTSETTING_H
#define LAYERCOSTSETTING_H

#include <QWidget>
#include "DialogGameEdit.h"
#include "DialogEditGameItem.h"
#include "Common.h"
#include "Global.h"
#include "GlobalUi.h"
#include "DialogMsg.h"
#include <QShowEvent>
#include <QTableWidgetItem>
#include <QToolTip>
#include "Action.h"


namespace Ui {
class LayerCostSetting;
}

class LayerCostSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCostSetting(QWidget *parent = nullptr);
    ~LayerCostSetting();

   private:
    enum header
    {
        _Sid=0,
        _Name,
        _Enable,
        _OrderNTD,
        _ForApi,
        _Bonus,
        _Cost,
        _PayType

    } m_header;


private slots:

    void on_btnGameAdd_clicked();


    void on_btnGameEdit_clicked();

    void on_btnItemAdd_clicked();


    void on_tbGame_cellClicked(int row, int);

    void on_btnItemEdit_clicked();

   // void on_tbGame_cellDoubleClicked(int row, int);

    void on_tbGameItem_cellDoubleClicked(int row, int);

    void on_tbGameItem_itemEntered(QTableWidgetItem *);

    void on_tbGameItem_cellEntered(int row, int column);

private:
    Ui::LayerCostSetting *ui;

    void showEvent(QShowEvent *) override;



    void refreshItemList();

    bool checkSearch(DataGameList gameData);

    QVariantList m_listTipData;


    QList<DataGameList> m_listGame;

    QVariantList m_gameDisplayData;


    QList<DataGameItem> m_listGameItem;

    QString m_sCurrentGameSid = "";

    QString m_sPreGameSid="";
    QString m_sPreGameItemSid="";

private slots:

    void refreshGameList();

     void refresh();

     void on_txSearch_textChanged(const QString &);

     void on_btnSortUp();
     void on_btnSortTop();
     void on_btnSortDown();
     void on_btnSortSave();

};

#endif // LAYERCOSTSETTING_H
