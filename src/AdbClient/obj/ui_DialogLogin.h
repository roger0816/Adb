/********************************************************************************
** Form generated from reading UI file 'DialogLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogLogin
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *txUser;
    QLabel *label_2;
    QLineEdit *txPass;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QPushButton *btnLogin;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lbMsg;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QString::fromUtf8("DialogLogin"));
        DialogLogin->resize(400, 300);
        gridLayout = new QGridLayout(DialogLogin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(DialogLogin);
        widget->setObjectName(QString::fromUtf8("widget"));
        QFont font;
        font.setPointSize(14);
        widget->setFont(font);
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        formLayout = new QFormLayout(widget_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        txUser = new QLineEdit(widget_2);
        txUser->setObjectName(QString::fromUtf8("txUser"));

        formLayout->setWidget(0, QFormLayout::FieldRole, txUser);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        txPass = new QLineEdit(widget_2);
        txPass->setObjectName(QString::fromUtf8("txPass"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txPass);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btnLogin = new QPushButton(widget_3);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));

        gridLayout_2->addWidget(btnLogin, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);


        formLayout->setWidget(3, QFormLayout::FieldRole, widget_3);

        lbMsg = new QLabel(widget_2);
        lbMsg->setObjectName(QString::fromUtf8("lbMsg"));
        lbMsg->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lbMsg);


        gridLayout_3->addWidget(widget_2, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 0, 1, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(DialogLogin);

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QApplication::translate("DialogLogin", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogLogin", "\345\270\263\350\231\237", nullptr));
        label_2->setText(QApplication::translate("DialogLogin", "\345\257\206\347\242\274", nullptr));
        btnLogin->setText(QApplication::translate("DialogLogin", "\347\231\273\345\205\245", nullptr));
        lbMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
