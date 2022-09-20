#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QShowEvent>
#include "RpkCore.h"
#include "CSideMenu.h"
#include <QButtonGroup>
#include "DEF.h"
#include "GlobalUi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString sAA;

    CSideMenu * m_menu;
private slots:
    void slotPage(int iIdx);
    void on_btnTest_clicked();


    void on_btnLogout_clicked();

private:
    Ui::Widget *ui;
    QButtonGroup m_btns;

    void showEvent(QShowEvent *) override;

    void setLv(int iLv);

};
#endif // WIDGET_H
