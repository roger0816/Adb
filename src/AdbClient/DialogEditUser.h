#ifndef DIALOGEDITUSER_H
#define DIALOGEDITUSER_H

#include <QDialog>
#include <QDebug>
#include <QVariantMap>
#include "VojData.h"
#include "DEF.h"

namespace Ui {
class DialogEditUser;
}

class DialogEditUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditUser(QWidget *parent = nullptr);
    ~DialogEditUser();

    void setData(QVariantMap data);

    QVariantMap data();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogEditUser *ui;

    UserData m_data;
};

#endif // DIALOGEDITUSER_H
