#ifndef DIALOGADDVALUETYPEEDIT_H
#define DIALOGADDVALUETYPEEDIT_H

#include <QDialog>
#include <QDoubleSpinBox>
#include "GlobalUi.h"
#include "Global.h"
#include <QPair>
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

    void setRate(QStringList sName,QStringList sRate);

   // void setData(QStringList list);

    void setData(QVariantMap data);

  //  QStringList data();

    QVariantMap data();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnDel_clicked();

    void on_comboBox_currentIndexChanged(int index);


    void updateTotal(double=0);
    void on_spOrigin_valueChanged(double);

    void on_spPrime_valueChanged(double);

private:
    Ui::DialogAddValueTypeEdit *ui;

    QList<QDoubleSpinBox*> m_listItem;


    QStringList m_listRateName;

    QStringList m_listRate;


    double m_iTotal;

};

#endif // DIALOGADDVALUETYPEEDIT_H
