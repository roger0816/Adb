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

    void refreshBulletin();



private:
    Ui::LayerSysSetting *ui;

    void showEvent(QShowEvent *) override;


    QVariantList m_listBulletin;


};

#endif // LAYERSYSSETTING_H
