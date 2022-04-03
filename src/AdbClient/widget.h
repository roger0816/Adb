#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

#include "Library.h"
#include "CSideMenu.h"
#include <QButtonGroup>
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
private:
    Ui::Widget *ui;
    QButtonGroup m_btns;



};
#endif // WIDGET_H
