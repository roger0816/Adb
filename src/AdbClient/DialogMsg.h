#ifndef DIALOGMSG_H
#define DIALOGMSG_H

#include <QDialog>
#include "DialogBase.h"

namespace Ui {
class DialogMsg;
}

#define DMSG DialogMsg::Instance()

class DialogMsg : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogMsg(QWidget *parent = nullptr);
    ~DialogMsg();

    int showMsg(QString sTitle,QString sMsg,QStringList listBtn);

    int showMsg(QString sTitle,QString sMsg,QString btnName);


    void setDialogInfo(QString sMsg,QStringList listBtnText);

    void setInput(QString sTitle, QString sPreInplut, QStringList listBtnName);

    void setButton(QStringList listName);

    QString getInput();

    static DialogMsg& Instance();

private slots:
    void on_btnCancel_clicked();
public slots:
    void on_btnOk_clicked();

private:
    Ui::DialogMsg *ui;

    static DialogMsg *m_pInstance;
};

#endif // DIALOGMSG_H
