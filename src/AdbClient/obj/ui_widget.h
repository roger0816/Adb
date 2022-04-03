/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "StageCustomer.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QWidget *wBg;
    QGridLayout *gridLayout_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    StageCustomer *page;
    QWidget *page_2;
    QWidget *page_3;
    QWidget *page_4;
    QWidget *page_5;
    QWidget *wTop;
    QWidget *wMenu;
    QVBoxLayout *verticalLayout;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSpacerItem *verticalSpacer;
    QPushButton *btnAccount;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1280, 660);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wBg = new QWidget(Widget);
        wBg->setObjectName(QString::fromUtf8("wBg"));
        gridLayout_2 = new QGridLayout(wBg);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(wBg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new StageCustomer();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 237, 211);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setStyleSheet(QString::fromUtf8("background-color: rgb(207, 255, 252);"));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 215, 255);"));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 108, 240);"));
        stackedWidget->addWidget(page_5);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget_2, 1, 1, 1, 1);

        wTop = new QWidget(wBg);
        wTop->setObjectName(QString::fromUtf8("wTop"));
        wTop->setMinimumSize(QSize(0, 100));
        wTop->setMaximumSize(QSize(16777215, 100));
        wTop->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(wTop, 0, 0, 1, 2);

        wMenu = new QWidget(wBg);
        wMenu->setObjectName(QString::fromUtf8("wMenu"));
        wMenu->setMinimumSize(QSize(140, 0));
        wMenu->setMaximumSize(QSize(140, 16777215));
        wMenu->setStyleSheet(QString::fromUtf8("QWidget#wMenu{\n"
"\n"
"background-color: rgb(0, 37, 88);\n"
"}\n"
"\n"
"QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"	font: 700 20pt \"Microsoft JhengHei UI\";\n"
"}\n"
"\n"
"QPushButton { \n"
"	border:none; \n"
"/*    border-radius: 6px;*/ \n"
"    border-color: beige; \n"
"	font: 700 22px \"Microsoft JhengHei UI\"; \n"
"    min-width: 4em; \n"
"    min-height:1.2em; \n"
"	padding: 6px; \n"
"	color: rgb(255, 255, 255); \n"
"	}\n"
"\n"
"QPushButton:hover \n"
"{ \n"
"background-color: rgb(198, 200, 223); \n"
"border-style: outset; \n"
"border-width: 2px; \n"
"font: 700 24px \"Microsoft JhengHei UI\"; \n"
"}\n"
"QPushButton:pressed { \n"
"border-style: outset; \n"
"border-width: 2px; \n"
"font: 700 24px \"Microsoft JhengHei UI\"; \n"
"background-color: rgb(67, 67, 67);\n"
"}\n"
" QPushButton:checked { \n"
"background-color: rgb(67, 67, 67);\n"
"border-style: outset; \n"
"border-width: 0px; \n"
"font: 700 24px \"Microsoft JhengHei UI\"; \n"
"}"));
        verticalLayout = new QVBoxLayout(wMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn0 = new QPushButton(wMenu);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setStyleSheet(QString::fromUtf8(""));
        btn0->setCheckable(true);
        btn0->setChecked(true);
        btn0->setFlat(true);

        verticalLayout->addWidget(btn0);

        btn1 = new QPushButton(wMenu);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setStyleSheet(QString::fromUtf8(""));
        btn1->setCheckable(true);
        btn1->setFlat(true);

        verticalLayout->addWidget(btn1);

        btn2 = new QPushButton(wMenu);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setCheckable(true);
        btn2->setFlat(true);

        verticalLayout->addWidget(btn2);

        btn3 = new QPushButton(wMenu);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setCheckable(true);
        btn3->setFlat(true);

        verticalLayout->addWidget(btn3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnAccount = new QPushButton(wMenu);
        btnAccount->setObjectName(QString::fromUtf8("btnAccount"));
        btnAccount->setCheckable(true);
        btnAccount->setFlat(true);

        verticalLayout->addWidget(btnAccount);


        gridLayout_2->addWidget(wMenu, 1, 0, 1, 1);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        btn0->setText(QApplication::translate("Widget", "\345\256\242\346\234\215\345\260\210\345\215\200", nullptr));
        btn1->setText(QApplication::translate("Widget", "\350\250\202\345\226\256\347\213\200\346\205\213", nullptr));
        btn2->setText(QApplication::translate("Widget", "\346\234\203\350\250\210\346\252\242\350\246\226", nullptr));
        btn3->setText(QApplication::translate("Widget", "\347\256\241\347\220\206\350\250\255\345\256\232", nullptr));
        btnAccount->setText(QApplication::translate("Widget", "\345\270\263\350\231\237\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
