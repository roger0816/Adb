#ifndef DIALOGDAYREPORTEDIT_H
#define DIALOGDAYREPORTEDIT_H

#include <QDialog>
#include "Global.h"
#include "GlobalUi.h"
namespace Ui {
class DialogDayReportEdit;
}

class DialogDayReportEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDayReportEdit(QWidget *parent = nullptr);
    ~DialogDayReportEdit();
    void setData(OrderData data);

    QString data();
private:
    Ui::DialogDayReportEdit *ui;

    OrderData m_data;

    QStringList m_listPayTypeSid;
private slots:
    void refresh();

};

#endif // DIALOGDAYREPORTEDIT_H
