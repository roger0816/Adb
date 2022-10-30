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

#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    CSideMenu * m_menu;
private slots:
    void slotPage(int iIdx);
    void on_btnTest_clicked();


    void on_btnLogout_clicked();
public slots:
    void slotLogin();
private:
    Ui::Widget *ui;
    QButtonGroup m_btns;

    void showEvent(QShowEvent *) override;

    void resizeEvent(QResizeEvent *) override;


    void checkUserLv();

};
#endif // WIDGET_H
