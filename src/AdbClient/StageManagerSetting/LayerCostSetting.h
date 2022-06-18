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


    void on_tbGame_cellClicked(int row, int);

    void on_btnItemEdit_clicked();

    void on_tbGame_cellDoubleClicked(int row, int);

    void on_tbGameItem_cellDoubleClicked(int row, int);

private:
    Ui::LayerCostSetting *ui;

    void showEvent(QShowEvent *) override;


    void refreshGameList();

    void refreshItemList();






    GameList m_gameList;

    QVariantList m_listItem;

    int m_iCurrentGameSid = -1;


};

#endif // LAYERCOSTSETTING_H
