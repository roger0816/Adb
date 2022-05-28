#ifndef DIALOGCOMMON_H
#define DIALOGCOMMON_H

#include <QDialog>
#include <QGridLayout>
namespace Ui {
class DialogCommon;
}

class DialogCommon : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCommon(QWidget *parent = nullptr);
    ~DialogCommon();

    void setWidget(QWidget * w);

private slots:
    void on_btnOk_clicked();

private:
    Ui::DialogCommon *ui;
};

#endif // DIALOGCOMMON_H
