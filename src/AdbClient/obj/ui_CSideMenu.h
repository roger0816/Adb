/********************************************************************************
** Form generated from reading UI file 'CSideMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSIDEMENU_H
#define UI_CSIDEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSideMenu
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;

    void setupUi(QWidget *CSideMenu)
    {
        if (CSideMenu->objectName().isEmpty())
            CSideMenu->setObjectName(QString::fromUtf8("CSideMenu"));
        CSideMenu->resize(192, 400);
        gridLayout = new QGridLayout(CSideMenu);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CSideMenu);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(CSideMenu);

        QMetaObject::connectSlotsByName(CSideMenu);
    } // setupUi

    void retranslateUi(QWidget *CSideMenu)
    {
        CSideMenu->setWindowTitle(QCoreApplication::translate("CSideMenu", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSideMenu: public Ui_CSideMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSIDEMENU_H
