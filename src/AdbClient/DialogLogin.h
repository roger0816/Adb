#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QPaintEvent>
#include <QPainter>
#include "Global.h"
#include <QCloseEvent>
#include <QBitmap>
#include <QButtonGroup>
#include <QSettings>
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

    void setReleaseIp(QString sIp,QString sPort);

    void setTestIp(QString sIp,QString sPort);
    void loginTarget(QString sSid);

    bool bMLogin= false;

private:

    void showEvent(QShowEvent *) override;

    void timerEvent(QTimerEvent *) override;

    QString m_sIp,m_sPort;

    QString m_sTestIp,m_sTestPort;

    void preload(bool bTrue);

    int m_iTimerCount=0;

    bool m_bPreLock= true;

    QButtonGroup m_btns;

    void loadServerConf();

private slots:
    void on_btnLogin_clicked();


    void doLogin(bool bIsTestMode=false);

    void slotBtnClicked(int iId);


signals:
    void signalLogin();
private:
    Ui::DialogLogin *ui;
private:

    ItemMiniLoadbar *m_loading=new ItemMiniLoadbar(this);

    QVariantList m_listServer;
};

#endif // DIALOGLOGIN_H
