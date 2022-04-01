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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QWidget *wBg;
    QGridLayout *gridLayout_2;
    QWidget *wMenu;
    QVBoxLayout *verticalLayout;
    QPushButton *btnOrder;
    QPushButton *btnStock;
    QPushButton *btnDispatching;
    QPushButton *btnQueryOrder;
    QPushButton *btnReport;
    QPushButton *btnFinance;
    QPushButton *btnManager;
    QSpacerItem *verticalSpacer;
    QPushButton *btnAccount;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTextEdit *textEdit;
    QWidget *page_2;
    QWidget *widget_3;

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
"}"));
        verticalLayout = new QVBoxLayout(wMenu);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnOrder = new QPushButton(wMenu);
        btnOrder->setObjectName(QString::fromUtf8("btnOrder"));
        btnOrder->setStyleSheet(QString::fromUtf8(""));
        btnOrder->setFlat(true);

        verticalLayout->addWidget(btnOrder);

        btnStock = new QPushButton(wMenu);
        btnStock->setObjectName(QString::fromUtf8("btnStock"));
        btnStock->setFlat(true);

        verticalLayout->addWidget(btnStock);

        btnDispatching = new QPushButton(wMenu);
        btnDispatching->setObjectName(QString::fromUtf8("btnDispatching"));
        btnDispatching->setFlat(true);

        verticalLayout->addWidget(btnDispatching);

        btnQueryOrder = new QPushButton(wMenu);
        btnQueryOrder->setObjectName(QString::fromUtf8("btnQueryOrder"));
        btnQueryOrder->setFlat(true);

        verticalLayout->addWidget(btnQueryOrder);

        btnReport = new QPushButton(wMenu);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));
        btnReport->setFlat(true);

        verticalLayout->addWidget(btnReport);

        btnFinance = new QPushButton(wMenu);
        btnFinance->setObjectName(QString::fromUtf8("btnFinance"));
        btnFinance->setFlat(true);

        verticalLayout->addWidget(btnFinance);

        btnManager = new QPushButton(wMenu);
        btnManager->setObjectName(QString::fromUtf8("btnManager"));
        btnManager->setFlat(true);

        verticalLayout->addWidget(btnManager);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnAccount = new QPushButton(wMenu);
        btnAccount->setObjectName(QString::fromUtf8("btnAccount"));
        btnAccount->setFlat(true);

        verticalLayout->addWidget(btnAccount);


        gridLayout_2->addWidget(wMenu, 1, 0, 1, 1);

        widget_2 = new QWidget(wBg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        textEdit = new QTextEdit(page);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(310, 120, 371, 261));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(widget_2, 1, 1, 1, 1);

        widget_3 = new QWidget(wBg);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 120));
        widget_3->setMaximumSize(QSize(16777215, 120));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(widget_3, 0, 0, 1, 2);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        btnOrder->setText(QApplication::translate("Widget", "\345\273\272\347\253\213\350\250\202\345\226\256", nullptr));
        btnStock->setText(QApplication::translate("Widget", "\345\272\253\345\255\230\347\256\241\347\220\206", nullptr));
        btnDispatching->setText(QApplication::translate("Widget", "\346\264\276\345\267\245\347\256\241\347\220\206", nullptr));
        btnQueryOrder->setText(QApplication::translate("Widget", "\346\237\245\347\234\213\350\250\202\345\226\256", nullptr));
        btnReport->setText(QApplication::translate("Widget", "\346\237\245\347\234\213\345\240\261\350\241\250", nullptr));
        btnFinance->setText(QApplication::translate("Widget", "\346\234\203\350\250\210\350\250\230\345\270\263", nullptr));
        btnManager->setText(QApplication::translate("Widget", "\347\256\241\347\220\206\347\266\255\350\255\267", nullptr));
        btnAccount->setText(QApplication::translate("Widget", "\345\270\263\350\231\237\350\250\255\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
