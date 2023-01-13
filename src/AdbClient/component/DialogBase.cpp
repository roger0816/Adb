#include "DialogBase.h"

DialogBase::DialogBase(QWidget *parent)
    : QDialog{parent}
{
   m_wMask= new QWidget(this);

   m_wMask->hide();

   m_wMask->setStyleSheet("background-color:red;");
}

void DialogBase::slotMask(bool b)
{
    m_wMask->setGeometry(0,0,size().width(),size().height());

    m_wMask->raise();
    m_wMask->setVisible(b);
}
