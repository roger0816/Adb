#ifndef LAYERACCOUNTMANAGER_H
#define LAYERACCOUNTMANAGER_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogEditUser.h"
namespace Ui {
class LayerAccountManager;
}

class LayerAccountManager : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAccountManager(QWidget *parent = nullptr);
    ~LayerAccountManager();

    void showEvent(QShowEvent * ) override;
private:
    Ui::LayerAccountManager *ui;

    void refresh();

         QList<UserData> m_listUser;


         bool checkRule(QString &sErrorMsg);


private slots:
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_btnDel_clicked();

};

#endif // LAYERACCOUNTMANAGER_H
