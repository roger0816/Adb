/********************************************************************************
** Form generated from reading UI file 'StageOrder.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEORDER_H
#define UI_STAGEORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageOrder
{
public:
    QGridLayout *gridLayout;
    QWidget *wBg;
    QGridLayout *gridLayout_2;
    QWidget *wMenu;
    QVBoxLayout *verticalLayout;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *StageOrder)
    {
        if (StageOrder->objectName().isEmpty())
            StageOrder->setObjectName(QString::fromUtf8("StageOrder"));
        StageOrder->resize(594, 437);
        gridLayout = new QGridLayout(StageOrder);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wBg = new QWidget(StageOrder);
        wBg->setObjectName(QString::fromUtf8("wBg"));
        gridLayout_2 = new QGridLayout(wBg);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
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
        btn2->setChecked(false);
        btn2->setFlat(true);

        verticalLayout->addWidget(btn2);

        btn3 = new QPushButton(wMenu);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        sizePolicy.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy);
        btn3->setCheckable(true);
        btn3->setFlat(true);

        verticalLayout->addWidget(btn3);

        verticalSpacer = new QSpacerItem(20, 288, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_2->addWidget(wMenu, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(wBg);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 1, 1, 1);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(StageOrder);

        QMetaObject::connectSlotsByName(StageOrder);
    } // setupUi

    void retranslateUi(QWidget *StageOrder)
    {
        StageOrder->setWindowTitle(QCoreApplication::translate("StageOrder", "Form", nullptr));
        btn0->setText(QCoreApplication::translate("StageOrder", "\345\203\271\347\233\256\350\241\250", nullptr));
        btn1->setText(QCoreApplication::translate("StageOrder", "\346\216\245\345\226\256\345\204\262\345\200\274", nullptr));
        btn2->setText(QCoreApplication::translate("StageOrder", "\350\250\202\345\226\256\345\233\236\345\240\261", nullptr));
        btn3->setText(QCoreApplication::translate("StageOrder", "\346\257\217\346\227\245\345\240\261\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageOrder: public Ui_StageOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEORDER_H
