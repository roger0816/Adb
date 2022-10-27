#ifndef DIALOGGAMEEDIT_H
#define DIALOGGAMEEDIT_H

#include <QDialog>
#include <QDebug>
#include "DialogMsg.h"
#include <QRegExpValidator>
#include "Global.h"

namespace Ui {
class DialogGameEdit;
}

class DialogGameEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGameEdit(QWidget *parent = nullptr);
    ~DialogGameEdit();

    void setData(QString sSid,bool bEnable,QString sId,QString sName,double iGameRate);

    bool m_bEnable= false;

    QString m_sSid="";
    QString m_sId;

    QString m_sName;

    double m_iGameRate;

public slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private slots:
    void on_btnDel_clicked();

private:
    Ui::DialogGameEdit *ui;

    bool m_bIsAddType = true;




};

#endif // DIALOGGAMEEDIT_H
