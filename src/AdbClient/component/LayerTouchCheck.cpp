#include "LayerTouchCheck.h"

LayerTouchCheck::LayerTouchCheck(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TransparentForMouseEvents, true);


}

/*
void LayerTouchCheck::mousePressEvent(QMouseEvent *e)
{

       // QObject::event(e);
   //     QApplication::postEvent(this->parent(),e);
    // QWidget::mousePressEvent(e);
}
*/
