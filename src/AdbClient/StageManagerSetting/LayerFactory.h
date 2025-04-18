#ifndef LAYERFACTORY_H
#define LAYERFACTORY_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogEditFactory.h"
namespace Ui {
class LayerFactory;
}

class LayerFactory : public QWidget
{
    Q_OBJECT

public:
    explicit LayerFactory(QWidget *parent = nullptr);
    ~LayerFactory();



private slots:
    void on_btnFactoryEdit_clicked();

    void on_btnFactoryAdd_clicked();

    void refresh();

    void on_tbFactory_itemEntered(QTableWidgetItem *item);

private:
    Ui::LayerFactory *ui;

       QList<DataFactory> m_listFactory;

       void showEvent(QShowEvent *) override;

 private slots:
    void slotBtnSortUp();
    void slotBtnSortDown();
    void slotBtnSortTop();
    void slotBtnSortSave();

};

#endif // LAYERFACTORY_H
