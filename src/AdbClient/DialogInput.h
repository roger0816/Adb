#ifndef DIALOGINPUT_H
#define DIALOGINPUT_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "DialogMsg.h"

namespace Ui {
class DialogInput;
}

class DialogInputItem : public QWidget
{
    Q_OBJECT
public:
    explicit DialogInputItem(QWidget *parent = nullptr);

    void setData(QString title,QVariantMap data);
    QVariantMap data();
private:
    QLabel *lb;

    QLineEdit *txt;

    QVariantMap m_data;
};

class DialogInput : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInput(QWidget *parent = nullptr);
    ~DialogInput();

    void setTitle(QString sTitle);

    void addInput(QString sLb, QVariantMap input);

    QVariantMap data();

private slots:

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnDel_clicked();

private:
    Ui::DialogInput *ui;

    QList<DialogInputItem*> m_listW;

    QVBoxLayout *lay;

};

#endif // DIALOGINPUT_H
