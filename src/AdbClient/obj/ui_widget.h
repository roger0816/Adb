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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "StageAccount.h"
#include "StageCustomer.h"
#include "StageHomePage.h"
#include "StageManagerSetting.h"
#include "StageOrder.h"

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
    StageHomePage *pageHome;
    StageCustomer *pageCustomer;
    StageOrder *pageOrder;
    QWidget *page3;
    StageManagerSetting *pageManager;
    StageAccount *pageAccount;
    QWidget *page;
    QWidget *wTop;
    QGridLayout *gridLayout_4;
    QWidget *widget_3;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QPushButton *btnLogout;
    QSpacerItem *verticalSpacer_3;
    QLabel *lbName;
    QWidget *wMenu;
    QVBoxLayout *verticalLayout;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QSpacerItem *verticalSpacer;
    QPushButton *btnTest;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnAccount;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1280, 700);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wBg = new QWidget(Widget);
        wBg->setObjectName(QString::fromUtf8("wBg"));
        wBg->setStyleSheet(QString::fromUtf8("font: 16px \"Microsoft JhengHei UI\";\n"
"\n"
""));
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
        pageHome = new StageHomePage();
        pageHome->setObjectName(QString::fromUtf8("pageHome"));
        stackedWidget->addWidget(pageHome);
        pageCustomer = new StageCustomer();
        pageCustomer->setObjectName(QString::fromUtf8("pageCustomer"));
        pageCustomer->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(pageCustomer);
        pageOrder = new StageOrder();
        pageOrder->setObjectName(QString::fromUtf8("pageOrder"));
        pageOrder->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(pageOrder);
        page3 = new QWidget();
        page3->setObjectName(QString::fromUtf8("page3"));
        page3->setStyleSheet(QString::fromUtf8("background-color: rgb(207, 255, 252);"));
        stackedWidget->addWidget(page3);
        pageManager = new StageManagerSetting();
        pageManager->setObjectName(QString::fromUtf8("pageManager"));
        pageManager->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(pageManager);
        pageAccount = new StageAccount();
        pageAccount->setObjectName(QString::fromUtf8("pageAccount"));
        pageAccount->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(pageAccount);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget_2, 1, 1, 1, 1);

        wTop = new QWidget(wBg);
        wTop->setObjectName(QString::fromUtf8("wTop"));
        wTop->setMinimumSize(QSize(0, 100));
        wTop->setMaximumSize(QSize(16777215, 100));
        wTop->setStyleSheet(QString::fromUtf8("QWidget#wTop{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));}"));
        gridLayout_4 = new QGridLayout(wTop);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widget_3 = new QWidget(wTop);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        widget_3->setFont(font);

        gridLayout_4->addWidget(widget_3, 1, 0, 1, 1);

        widget = new QWidget(wTop);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        btnLogout = new QPushButton(widget);
        btnLogout->setObjectName(QString::fromUtf8("btnLogout"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(true);
        btnLogout->setFont(font1);
        btnLogout->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft JhengHei UI\";\n"
"\n"
"text-decoration: underline;\n"
"\n"
"color: rgb(95, 95, 0);"));
        btnLogout->setFlat(true);

        gridLayout_5->addWidget(btnLogout, 0, 0, 1, 1);


        gridLayout_4->addWidget(widget, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 0, 0, 1, 3);

        lbName = new QLabel(wTop);
        lbName->setObjectName(QString::fromUtf8("lbName"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbName->sizePolicy().hasHeightForWidth());
        lbName->setSizePolicy(sizePolicy1);
        lbName->setFont(font);
        lbName->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(0, 85, 255);"));

        gridLayout_4->addWidget(lbName, 1, 1, 1, 1);


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
"}\n"
"\n"
"QPushButton:disabled { \n"
"border-style: outset; \n"
"bo"
                        "rder-width: 0px; \n"
"font: 700 24px \"Microsoft JhengHei UI\"; \n"
"color: rgb(122, 122, 122);\n"
"}"));
        verticalLayout = new QVBoxLayout(wMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn0 = new QPushButton(wMenu);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setFocusPolicy(Qt::NoFocus);
        btn0->setStyleSheet(QString::fromUtf8(""));
        btn0->setCheckable(true);
        btn0->setChecked(true);
        btn0->setFlat(true);

        verticalLayout->addWidget(btn0);

        btn1 = new QPushButton(wMenu);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setEnabled(true);
        btn1->setFocusPolicy(Qt::NoFocus);
        btn1->setStyleSheet(QString::fromUtf8(""));
        btn1->setCheckable(true);
        btn1->setChecked(false);
        btn1->setFlat(true);

        verticalLayout->addWidget(btn1);

        btn2 = new QPushButton(wMenu);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setFocusPolicy(Qt::NoFocus);
        btn2->setStyleSheet(QString::fromUtf8(""));
        btn2->setCheckable(true);
        btn2->setFlat(true);

        verticalLayout->addWidget(btn2);

        btn3 = new QPushButton(wMenu);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setFocusPolicy(Qt::NoFocus);
        btn3->setCheckable(true);
        btn3->setFlat(true);

        verticalLayout->addWidget(btn3);

        btn4 = new QPushButton(wMenu);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setEnabled(false);
        btn4->setFocusPolicy(Qt::NoFocus);
        btn4->setCheckable(true);
        btn4->setFlat(true);

        verticalLayout->addWidget(btn4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnTest = new QPushButton(wMenu);
        btnTest->setObjectName(QString::fromUtf8("btnTest"));

        verticalLayout->addWidget(btnTest);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnAccount = new QPushButton(wMenu);
        btnAccount->setObjectName(QString::fromUtf8("btnAccount"));
        btnAccount->setFocusPolicy(Qt::NoFocus);
        btnAccount->setCheckable(true);
        btnAccount->setFlat(true);

        verticalLayout->addWidget(btnAccount);


        gridLayout_2->addWidget(wMenu, 1, 0, 1, 1);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        btnLogout->setText(QApplication::translate("Widget", "\347\231\273\345\207\272", nullptr));
        lbName->setText(QString());
        btn0->setText(QApplication::translate("Widget", "\351\246\226\351\240\201", nullptr));
        btn1->setText(QApplication::translate("Widget", "\345\256\242\346\234\215\345\260\210\345\215\200", nullptr));
        btn2->setText(QApplication::translate("Widget", "\350\250\202\345\226\256\347\213\200\346\205\213", nullptr));
        btn3->setText(QApplication::translate("Widget", "\345\240\261\350\241\250\346\252\242\350\246\226", nullptr));
        btn4->setText(QApplication::translate("Widget", "\347\256\241\347\220\206\350\250\255\345\256\232", nullptr));
        btnTest->setText(QApplication::translate("Widget", "Test", nullptr));
        btnAccount->setText(QApplication::translate("Widget", "\345\270\263\350\231\237\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
