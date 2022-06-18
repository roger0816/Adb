#ifndef DIALOGEDITFACTORY_H
#define DIALOGEDITFACTORY_H

#include <QDialog>
#include "Global.h"
#include "GlobalUi.h"
#include <QCheckBox>

namespace Ui {
class DialogEditFactory;
}

class DialogEditFactory : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditFactory(QWidget *parent = nullptr);
    ~DialogEditFactory();
    void setData(QVariantMap data);

    QVariantMap data();
private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnDel_clicked();

    void on_tb_cellClicked(int row, int column);

private:
    Ui::DialogEditFactory *ui;

    QVariantMap m_data;

    PrimeRate m_rate;
};

#endif // DIALOGEDITFACTORY_H
