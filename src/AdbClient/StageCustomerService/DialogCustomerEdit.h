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


    void setData(QVariantList listClass, QVariantList listGame, QVariantList listGameInfo, QVariantMap data);

    void setData(QString sCustomerSid);

    void setReadOnly(bool bReadOnly=true);
    QVariantMap data();

    QVariantList dataGameInfo();
    QVariantList deleteGameInfo();

    void setCb(QVariantList listClass, QVariantList listGame);


private slots:
    void on_btnAddGame_clicked();


    void on_tbGameList_cellClicked(int row, int col);

    void on_cbClass_currentIndexChanged(int index);

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnDel_clicked();

private:
    Ui::DialogCustomerEdit *ui;

    QVariantMap m_data;

    QVariantList m_listClass;

    QVariantList m_listGame;

    QStringList mapToList(QVariantList list,QString sKey);

    QVariantList m_listGameInfo;

    QVariantList m_listDeleteInfo;



    QString checkId(int cbIdx);


    void refresh();

    QString gameToName(QString sSid);

    QString gameToSid(QString sName);


    DataRate m_lastPrimeRate;

    QString m_sOriginCurrency; //辨別它是否改幣別
};

#endif // DIALOGCUSTOMEREDIT_H
