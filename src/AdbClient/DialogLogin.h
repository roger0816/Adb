#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include "Global.h"
#include <QCloseEvent>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

    void init();

    void setRelease(bool b);

    void closeEvent(QCloseEvent *) override;

private slots:
    void on_btnLogin_clicked();

signals:
  //  void signalLogin();
private:
    Ui::DialogLogin *ui;
private:
    int m_iRec=-1;
};

#endif // DIALOGLOGIN_H
