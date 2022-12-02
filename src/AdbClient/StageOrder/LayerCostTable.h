#ifndef LAYERCOSTTABLE_H
#define LAYERCOSTTABLE_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QDoubleSpinBox>

namespace Ui {
class LayerCostTable;
}

class LayerCostTable : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCostTable(QWidget *parent = nullptr);
    ~LayerCostTable();


    QList<DataGameList> m_listGame;

    QList<DataGameList> m_listGameDisplay;



    QList<DataGameItem> m_currentItems;

    void showEvent(QShowEvent * ) override;


private slots:
    void on_tbGame_cellPressed(int row, int);

    void on_btnSearch_clicked();

    void on_btnClear_clicked();

    void on_btnCopy_clicked();

    void refreshGameList();

    void slotTabCurrentChanged(int index);

    void on_btnSaveText_clicked();

    void on_txEdit_textChanged();


    void on_txSearch_textChanged(const QString &);

private:
    Ui::LayerCostTable *ui;

    QString trText();

    bool checkSearch(QVariantMap data);

};

#endif // LAYERCOSTTABLE_H
