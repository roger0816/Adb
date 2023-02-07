#ifndef DIALOGINPUT_H
#define DIALOGINPUT_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "DialogMsg.h"
#include <QRegExpValidator>

namespace Ui {
class DialogInput;
}




class DialogInputItem : public QWidget
{
    Q_OBJECT
public:
    explicit DialogInputItem(QWidget *parent = nullptr);
    void initInput();
    void setInputData(QString title,QVariantMap data);
    void initComboBox();
    void setComboData(QString title,QVariantMap data);
    virtual QVariantMap data();
private:
    QLabel *lb;

    QComboBox *cb=nullptr;

    QLineEdit *txt=nullptr;

    QVariantMap m_data;
};


class DialogInput : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInput(QWidget *parent = nullptr);
    ~DialogInput();
    //a.  設標題
    void setTitle(QString sTitle);
    //b1.  用法1 設文字
    void setText(QString sText);
    QString text();

    //b2.  用法2 加元件
    void addComboBox(QString sLb, QVariantMap input);

    void addInput(QString sLb, QVariantMap input);

    QVariantMap data();

    //c. btn不要有delete
    void hideDelete();



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
