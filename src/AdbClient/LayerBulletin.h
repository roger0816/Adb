#ifndef LAYERBULLETIN_H
#define LAYERBULLETIN_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QDateTime>
#include "DialogBulletinEdit.h"

namespace Ui {
class LayerBulletin;
}

class LayerBulletin : public QWidget
{
    Q_OBJECT

public:
    explicit LayerBulletin(QWidget *parent = nullptr);
    ~LayerBulletin();

private slots:
    void on_tbSys_cellDoubleClicked(int row, int);

    void on_tbTop_cellDoubleClicked(int row, int);

private:
    Ui::LayerBulletin *ui;

    void showEvent(QShowEvent * ) override;

    void refresh(bool bRequery=true);

    QList<UserData> m_listUser;

    QVariantList m_listData;

    void intoTopTb(QVariantMap data);

     void intoSysTb(QVariantMap data);

     QString userName(QString sId);
};

#endif // LAYERBULLETIN_H
