#ifndef GLOBALUI_H
#define GLOBALUI_H

#include <QObject>
#include <QApplication>
#include <QClipboard>
#include <QToolTip>
#include <QShowEvent>
#include "DialogMsg.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>
#include "DialogLogin.h"
#include "DialogInput.h"

#define PX_SIZE 16

#define UI GlobalUi::Instance()

class GlobalUi : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUi(QObject *parent = nullptr);
    static GlobalUi& Instance();

    int showMsg(QString sTitle,QString sMsg,QStringList listBtn);

    int showMsg(QString sTitle,QString sMsg,QString btn);

    enum tbItemType{_def=0,_txt,_btn,_double2,_double3,_cb_split1};

    void setTbData(QTableWidget *tb, QVariantList data, QStringList listHeader, bool reTb=false, QList<int> listType=QList<int>());

    enum _tbItemType{_AUTO=0,_TXT,_BOOL,_DOUBLE,_TOOLTIP,_BUTTON,_DATE,_DATETIME};
    QTableWidgetItem * tbItem(QVariant var,int iType=0,int iPixSize=PX_SIZE);

    QFont font(int iPixSize=20);

    void copyMsg(QString sMsg);
    DialogLogin *m_dialogLogin = nullptr;

private:
    static GlobalUi *m_pInstance;


signals:

};

#endif // GLOBALUI_H
