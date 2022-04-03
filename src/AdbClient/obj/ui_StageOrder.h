/********************************************************************************
** Form generated from reading UI file 'StageOrder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEORDER_H
#define UI_STAGEORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageOrder
{
public:

    void setupUi(QWidget *StageOrder)
    {
        if (StageOrder->objectName().isEmpty())
            StageOrder->setObjectName(QString::fromUtf8("StageOrder"));
        StageOrder->resize(400, 300);

        retranslateUi(StageOrder);

        QMetaObject::connectSlotsByName(StageOrder);
    } // setupUi

    void retranslateUi(QWidget *StageOrder)
    {
        StageOrder->setWindowTitle(QApplication::translate("StageOrder", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageOrder: public Ui_StageOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEORDER_H
