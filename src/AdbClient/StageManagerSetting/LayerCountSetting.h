#ifndef LAYERCOUNTSETTING_H
#define LAYERCOUNTSETTING_H

#include <QWidget>
#include <QDebug>
#include <QShowEvent>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerCountSetting;
}

struct DataCount{
   QString GameSid;
   QString GameItemSid;
   QString Name;
   int CurrentCount;
   int TotalSell;
   int TotalCount;

};

class LayerCountSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCountSetting(QWidget *parent = nullptr);
    ~LayerCountSetting();
    void showEvent(QShowEvent *) override;

    QList<DataGameList> m_listGame;
     QMap<QString,DataCount> m_countData;
private slots:

    void slotCbChangeIdx(int idx);

    void on_tb_cellClicked(int row, int column);
private:
    Ui::LayerCountSetting *ui;

    QMap<QString,DataCount > getDataCount(QString sGameSid);

    void refresh();
};

#endif // LAYERCOUNTSETTING_H
