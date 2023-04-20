#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
class DialogBase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogBase(QWidget *parent = nullptr);

    int exec() override;
signals:

};

#endif // DIALOGBASE_H
