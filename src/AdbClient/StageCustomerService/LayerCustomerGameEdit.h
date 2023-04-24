#ifndef LAYERCUSTOMERGAMEEDIT_H
#define LAYERCUSTOMERGAMEEDIT_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"

namespace Ui {
class LayerCustomerGameEdit;
}

class LayerCustomerGameEdit : public QWidget
{
    Q_OBJECT

public:
    explicit LayerCustomerGameEdit(QWidget *parent = nullptr);
    ~LayerCustomerGameEdit();

    void setCustomer(QString sSid, QString sId);

    void setReadOnly(bool bReadOnly);
    void refresh();

    bool m_bAddMode = true;  //新增客戶時還沒送出新增，未獲得客戶sid

    QVariantList queeList(QString sCustomerSid);  //已獲得客戶sid時再補送


    void setCb(QVariantList outGame);
private slots:
    void on_tbCusGameInfo_cellClicked(int row, int col);

        void slotAdd();
    void slotChange();
private:
    Ui::LayerCustomerGameEdit *ui;

    QString m_sCustomerSid;

    QString m_sCustomerId;

    QVariantList m_listGame;

    QVariantList m_listCustomerInfo;



};

#endif // LAYERCUSTOMERGAMEEDIT_H
