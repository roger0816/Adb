#ifndef DIALOGADDVALUETYPEEDIT_H
#define DIALOGADDVALUETYPEEDIT_H

#include <QDialog>
#include <QDoubleSpinBox>
#include "GlobalUi.h"
namespace Ui {
class DialogAddValueTypeEdit;
}

class DialogAddValueTypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddValueTypeEdit(QWidget *parent = nullptr);
    ~DialogAddValueTypeEdit();

    void setName(QString sName);

    QString Name();
    void setData(QStringList list);

    QStringList data();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnDel_clicked();

private:
    Ui::DialogAddValueTypeEdit *ui;

    QList<QDoubleSpinBox*> m_listItem;
};

#endif // DIALOGADDVALUETYPEEDIT_H
