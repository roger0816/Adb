#ifndef LAYERSYSSETTING_H
#define LAYERSYSSETTING_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogBulletinEdit.h"

namespace Ui {
class LayerSysSetting;
}

class LayerSysSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSysSetting(QWidget *parent = nullptr);
    ~LayerSysSetting();

private slots:
    void on_btnBulletinAdd_clicked();

    void on_tbBulletin_cellDoubleClicked(int row, int column);

    void on_btnBulletinEdit_clicked();




    void on_btnCusClassAdd_clicked();

    void on_btnCusClassEdit_clicked();

    void on_tbCusClass_cellDoubleClicked(int, int);

    void on_btnFactoryAdd_clicked();

    void on_btnFactoryEdit_clicked();

private:
    Ui::LayerSysSetting *ui;

    void showEvent(QShowEvent *) override;

    void refreshBulletin();

    void refreshCustomer();

    void refreshFactory();

    QVariantList m_listBulletin;
     QVariantList m_listCustomer;
      QVariantList m_listFactory;
};

#endif // LAYERSYSSETTING_H
