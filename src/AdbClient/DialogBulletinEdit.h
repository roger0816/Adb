#ifndef DIALOGBULLETINEDIT_H
#define DIALOGBULLETINEDIT_H

#include <QDialog>
#include "DialogMsg.h"
#include <QVariantMap>
#include <QDebug>
#include <QDateTime>
namespace Ui {
class DialogBulletinEdit;
}

class DialogBulletinEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBulletinEdit(QWidget *parent = nullptr);
    ~DialogBulletinEdit();

    void setReadyOnly();

    void setData(QVariantMap data,QString sName="");

    QVariantMap data();


private slots:
    void on_btnOk_clicked();

    void on_btnDel_clicked();

    void on_btnClose_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogBulletinEdit *ui;

      QVariantMap m_data;
};

#endif // DIALOGBULLETINEDIT_H
