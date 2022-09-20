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



    void on_tbFactory_itemEntered(QTableWidgetItem *item);

private:
    Ui::LayerFactory *ui;

    void refresh();

       QVariantList m_listFactory;

       void showEvent(QShowEvent *) override;
};

#endif // LAYERFACTORY_H
