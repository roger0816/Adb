#ifndef GLOBALUI_H
#define GLOBALUI_H

#include <QObject>
#include <QShowEvent>
#include "DialogMsg.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QDateTime>
#include "DialogLogin.h"
#include "DialogInput.h"

#define UI GlobalUi::Instance()

class GlobalUi : public QObject
{
    Q_OBJECT
public:
    explicit GlobalUi(QObject *parent = nullptr);
    static GlobalUi& Instance();

    int showMsg(QString sTitle,QString sMsg,QStringList listBtn);

    int showMsg(QString sTitle,QString sMsg,QString btn);

    QTableWidgetItem * tbItem(QVariant var);

    DialogLogin *m_dialogLogin = nullptr;

private:
    static GlobalUi *m_pInstance;


signals:

};

#endif // GLOBALUI_H
