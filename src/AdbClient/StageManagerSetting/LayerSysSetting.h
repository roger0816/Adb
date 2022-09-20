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





private:
    Ui::LayerSysSetting *ui;

    void showEvent(QShowEvent *) override;

    void refreshBulletin();




    QVariantList m_listBulletin;


};

#endif // LAYERSYSSETTING_H
