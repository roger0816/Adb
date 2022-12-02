#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QPaintEvent>
#include <QPainter>
#include "Global.h"
#include <QCloseEvent>
#include <QBitmap>
#include "ItemMiniLoadbar.h"

namespace Ui {
class DialogLogin;
}


namespace _DialogLogin {
enum{ _Close=-1,_LoginFail, _LoginOk=1};
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = nullptr);
    ~DialogLogin();

    void init(QString sMsg="");

    void setRelease(bool b);

    void closeEvent(QCloseEvent *) override;

    void paintEvent(QPaintEvent *) override;

    void setVer(QString sVer);


private slots:
    void on_btnLogin_clicked();

signals:
    void signalLogin();
private:
    Ui::DialogLogin *ui;
private:

    ItemMiniLoadbar *m_loading=new ItemMiniLoadbar(this);

};

#endif // DIALOGLOGIN_H
