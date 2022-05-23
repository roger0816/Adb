/********************************************************************************
** Form generated from reading UI file 'StageCustomer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGECUSTOMER_H
#define UI_STAGECUSTOMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LayerCustomer.h"
#include "LayerSearchCustomer.h"

QT_BEGIN_NAMESPACE

class Ui_StageCustomer
{
public:
    QGridLayout *gridLayout;
    QWidget *wBg;
    QHBoxLayout *horizontalLayout;
    QWidget *wMenu;
    QVBoxLayout *verticalLayout;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    LayerSearchCustomer *page;
    LayerCustomer *page_3;
    QWidget *page_2;

    void setupUi(QWidget *StageCustomer)
    {
        if (StageCustomer->objectName().isEmpty())
            StageCustomer->setObjectName(QString::fromUtf8("StageCustomer"));
        StageCustomer->resize(471, 402);
        gridLayout = new QGridLayout(StageCustomer);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wBg = new QWidget(StageCustomer);
        wBg->setObjectName(QString::fromUtf8("wBg"));
        horizontalLayout = new QHBoxLayout(wBg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wMenu = new QWidget(wBg);
        wMenu->setObjectName(QString::fromUtf8("wMenu"));
        wMenu->setMinimumSize(QSize(120, 0));
        wMenu->setMaximumSize(QSize(120, 16777215));
        QFont font;
        font.setPointSize(16);
        wMenu->setFont(font);
        wMenu->setStyleSheet(QString::fromUtf8("QWidget#wMenu{\n"
"background-color: rgb(244, 244, 244);\n"
"\n"
"}\n"
"\n"
"QPushButton { \n"
"	border:none; \n"
"	background-color: rgba(255, 255, 255,0);\n"
"	font: 700 16px \"Microsoft JhengHei UI\"; \n"
"    min-width: 4em; \n"
"    min-height:1.2em; \n"
"	padding: 6px; \n"
"	color: gray;\n"
"	}\n"
"\n"
"QPushButton:hover \n"
"{ \n"
"background-color: rgb(198, 200, 223); \n"
"border-style: outset; \n"
"border-width: 2px; \n"
"font: 700 18px \"Microsoft JhengHei UI\"; \n"
"}\n"
"QPushButton:pressed { \n"
"border-style: outset; \n"
"border-width: 0px; \n"
"font: 700 18px \"Microsoft JhengHei UI\"; \n"
"background-color: rgb(67, 67, 67);\n"
"}\n"
" QPushButton:checked { \n"
"color:rgb(255,255,255);\n"
"background-color: rgb(67, 67, 67);\n"
"border-style: outset; \n"
"border-width: 0px; \n"
"font: 700 18px \"Microsoft JhengHei UI\"; \n"
"}"));
        verticalLayout = new QVBoxLayout(wMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn0 = new QPushButton(wMenu);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn0->sizePolicy().hasHeightForWidth());
        btn0->setSizePolicy(sizePolicy);
        btn0->setCheckable(true);
        btn0->setChecked(true);
        btn0->setFlat(true);

        verticalLayout->addWidget(btn0);

        btn1 = new QPushButton(wMenu);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        sizePolicy.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy);
        btn1->setCheckable(true);
        btn1->setFlat(true);

        verticalLayout->addWidget(btn1);

        btn2 = new QPushButton(wMenu);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        sizePolicy.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy);
        btn2->setCheckable(true);
        btn2->setFlat(true);

        verticalLayout->addWidget(btn2);

        verticalSpacer = new QSpacerItem(20, 288, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(wMenu);

        widget_2 = new QWidget(wBg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new LayerSearchCustomer();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(page);
        page_3 = new LayerCustomer();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget_2);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(StageCustomer);

        QMetaObject::connectSlotsByName(StageCustomer);
    } // setupUi

    void retranslateUi(QWidget *StageCustomer)
    {
        StageCustomer->setWindowTitle(QCoreApplication::translate("StageCustomer", "Form", nullptr));
        btn0->setText(QCoreApplication::translate("StageCustomer", "\346\245\255\345\213\231\345\212\237\350\203\275", nullptr));
        btn1->setText(QCoreApplication::translate("StageCustomer", "\345\256\242\346\210\266\350\263\207\346\226\231", nullptr));
        btn2->setText(QCoreApplication::translate("StageCustomer", "\345\203\271\347\233\256\350\241\250\346\252\242\350\246\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageCustomer: public Ui_StageCustomer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGECUSTOMER_H
