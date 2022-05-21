#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include "Global.h"
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

private slots:
    void on_btnLogin_clicked();

signals:
    void signalLogin();
private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
