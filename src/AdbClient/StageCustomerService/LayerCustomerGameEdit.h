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

    void refresh();

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
