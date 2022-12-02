#ifndef LAYERCOSTSETTING_H
#define LAYERCOSTSETTING_H

#include <QWidget>
#include "DialogGameEdit.h"
#include "DialogEditGameItem.h"
#include "Global.h"
#include "GlobalUi.h"
#include "DialogMsg.h"
#include <QShowEvent>
#include <QTableWidgetItem>
#include <QToolTip>
namespace Ui {
class LayerCostSetting;
}

class LayerCostSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCostSetting(QWidget *parent = nullptr);
    ~LayerCostSetting();


private slots:

    void on_btnGameAdd_clicked();


    void on_btnGameEdit_clicked();

    void on_btnItemAdd_clicked();


    void on_tbGame_cellClicked(int, int);

    void on_btnItemEdit_clicked();

    void on_tbGame_cellDoubleClicked(int row, int);

    void on_tbGameItem_cellDoubleClicked(int row, int);

    void on_tbGameItem_itemEntered(QTableWidgetItem *);

    void on_tbGameItem_cellEntered(int row, int column);

private:
    Ui::LayerCostSetting *ui;

    void showEvent(QShowEvent *) override;



    void refreshItemList();

    bool checkSearch(QVariantMap data);

    QVariantList m_listTipData;

    QVariantList m_gameData;

    QVariantList m_gameDisplayData;



    QVariantList m_listItem;

    int m_iCurrentGameSid = -1;

private slots:

    void refreshGameList();

     void refresh();

     void on_txSearch_textChanged(const QString &);
};

#endif // LAYERCOSTSETTING_H
