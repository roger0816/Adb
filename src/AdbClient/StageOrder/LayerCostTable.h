#ifndef LAYERCOSTTABLE_H
#define LAYERCOSTTABLE_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"


namespace Ui {
class LayerCostTable;
}

class LayerCostTable : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCostTable(QWidget *parent = nullptr);
    ~LayerCostTable();

    GameList m_gameList;

    void showEvent(QShowEvent * ) override;

    bool check(GameList::GameData data);

private slots:
    void on_tbGame_cellPressed(int row, int);

    void on_btnSearch_clicked();

    void on_btnClear_clicked();

    void on_btnCopy_clicked();

    void refreshGameList();

private:
    Ui::LayerCostTable *ui;
};

#endif // LAYERCOSTTABLE_H
