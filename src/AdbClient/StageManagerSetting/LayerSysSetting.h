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


private:
    Ui::LayerSysSetting *ui;

    void showEvent(QShowEvent *) override;

    void refreshBulletin();

    void refreshCustomer();



    QVariantList m_listBulletin;
     QVariantList m_listCustomer;

};

#endif // LAYERSYSSETTING_H
