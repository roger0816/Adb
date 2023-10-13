#ifndef DIALOGCOUNTHISOTRY_H
#define DIALOGCOUNTHISOTRY_H

#include <QDialog>
#include "Global.h"
#include "GlobalUi.h"
namespace Ui {
class DialogCountHisotry;
}

class DialogCountHisotry : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCountHisotry(QWidget *parent = nullptr);
    ~DialogCountHisotry();

    void setTitle(QString sItemSid,QString sGameName,QString sItemName,QString sCount);

    void refresh();
private:
    QString m_sItemSid;
    QList<DataItemCount> m_listData;
private:
    Ui::DialogCountHisotry *ui;
};

#endif // DIALOGCOUNTHISOTRY_H
