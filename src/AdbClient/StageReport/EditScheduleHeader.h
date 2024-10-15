#ifndef EDITSCHEDULEHEADER_H
#define EDITSCHEDULEHEADER_H

#include <QWidget>
#include <QDebug>
#include <QShowEvent>
#include <QFocusEvent>
#include <QDialog>
#include <QLineEdit>

namespace Ui {
class EditScheduleHeader;
}

class EditScheduleHeader : public QWidget
{
    Q_OBJECT

public:
    explicit EditScheduleHeader(QWidget *parent = nullptr);
    ~EditScheduleHeader();

    void setData(QStringList list0, QStringList list1);

    void focusInEvent(QFocusEvent *event);


    void focusOutEvent(QFocusEvent *event);


private slots:
    void on_btnCancel_clicked();

    void on_btnSub_clicked();

    void on_btnOk_clicked();

    void on_btnAdd_clicked();

    void on_btnAdd_2_clicked();

    void on_btnSub_2_clicked();

private:
    Ui::EditScheduleHeader *ui;

    void showEvent(QShowEvent * ) override;

    QList<QLineEdit*> m_listTx0,m_listTx1;

    int m_iCount0=1,m_iCount1=1;

    void reCount(int iCount0, int iCount1);

signals:
    void done(QStringList list0,QStringList list1);
};

#endif // EDITSCHEDULEHEADER_H
