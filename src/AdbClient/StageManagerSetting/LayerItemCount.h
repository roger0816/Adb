#ifndef LAYERITEMCOUNT_H
#define LAYERITEMCOUNT_H

#include <QWidget>
#include <QShowEvent>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerItemCount;
}

class LayerItemCount : public QWidget
{
    Q_OBJECT

public:
    explicit LayerItemCount(QWidget *parent = nullptr);
    ~LayerItemCount();

    void refresh();
private slots:
    void on_cbGame_currentIndexChanged(int index);

    void on_tb_cellClicked(int row, int column);

private:
    void showEvent(QShowEvent *) override;

    QPair<int,int> checkCount(QString itemSid);

    void updateTb();


    QList<DataGameList> m_listGame;

   QList<DataGameItem> m_listGameItem;

   int m_iCbGame=0;



    QVariantList m_listData;
private:
    Ui::LayerItemCount *ui;
};

#endif // LAYERITEMCOUNT_H
