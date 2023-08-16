#ifndef DIALOGCUSTOMEREDIT_H
#define DIALOGCUSTOMEREDIT_H

#include <QDialog>

#include <QDebug>
#include "Global.h"
#include "GlobalUi.h"
#include "QButtonGroup"


struct DialogCustomerGameInfo
{
    QString sGameId;




};

namespace Ui {
class DialogCustomerEdit;
}

class DialogCustomerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCustomerEdit(QWidget *parent = nullptr);
    ~DialogCustomerEdit();


    void setData(QVariantList listClass, QVariantList listGame, QVariantList listCustomerInfo, QVariantMap data);

    void setData(QString sCustomerSid);

    void setAddMode();


    void setReadOnly(bool bReadOnly=true);
    QVariantMap data();

    QVariantList dataGameInfo(QString sCustomerSid);
    QVariantList deleteGameInfo();

    void setCb(QVariantList listClass, QVariantList listGame);

    bool checkHasChange();//有可能只改客戶遊戲資料，沒有更動客戶資料

    void setRoot(bool b);

private:
      bool m_bIsAdd= false;
private slots:

    void on_cbClass_currentIndexChanged(int index);

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnDel_clicked();

private:
    Ui::DialogCustomerEdit *ui;

    QString m_sCustomerSid="";

    QVariantMap m_data;

    bool m_bHasHistoryOrder = false;
    QString m_lastOrderDate="";

    QVariantList m_listClass;

    QVariantList m_listGame;

    QStringList mapToList(QVariantList list,QString sKey);

   // QVariantList m_listGameInfo;

    QVariantList m_listCustomerInfo;

    QVariantList m_listDeleteInfo;

    QVariantMap m_originData;

    bool m_bIsRoot=false;


/*
    QString checkId(int cbIdx);


    QString strAdd1(QString st);
*/


    QString gameToName(QString sSid);

    QString gameToSid(QString sName);


    DataRate m_lastPrimeRate;

    QString m_sOriginCurrency; //辨別它是否改幣別
};

#endif // DIALOGCUSTOMEREDIT_H
