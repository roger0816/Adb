#ifndef LAYERTOUCHCHECK_H
#define LAYERTOUCHCHECK_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QPushButton>
class LayerTouchCheck : public QWidget
{
    Q_OBJECT
public:
    explicit LayerTouchCheck(QWidget *parent = nullptr);

   // void mousePressEvent(QMouseEvent *e) override;

signals:

};

#endif // LAYERTOUCHCHECK_H
