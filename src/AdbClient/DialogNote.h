#ifndef DIALOGNOTE_H
#define DIALOGNOTE_H

#include <QDialog>
#include <QClipboard>
#include <QApplication>
namespace Ui {
class DialogNote;
}

class DialogNote : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNote(QWidget *parent = nullptr);
    ~DialogNote();

    void setUser(QStringList list);

    void setId(QString sId);

    void setData(QStringList list);

    void setReportCost(QString st);

    void hideReport();

private slots:
    void on_btnCopyReport_clicked();

private:
    Ui::DialogNote *ui;
};

#endif // DIALOGNOTE_H
