/********************************************************************************
** Form generated from reading UI file 'DialogLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
    QWidget *wBg;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
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
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QString::fromUtf8("DialogLogin"));
        DialogLogin->resize(400, 300);
        gridLayout = new QGridLayout(DialogLogin);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wBg = new QWidget(DialogLogin);
        wBg->setObjectName(QString::fromUtf8("wBg"));
        QFont font;
        font.setPointSize(14);
        wBg->setFont(font);
        wBg->setStyleSheet(QString::fromUtf8("QWidget#wBg{background-color: rgb(255, 255, 255);}"));
        gridLayout_3 = new QGridLayout(wBg);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 1, 1, 1, 1);

        widget_2 = new QWidget(wBg);
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
        txPass->setEchoMode(QLineEdit::Password);

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


        formLayout->setWidget(4, QFormLayout::FieldRole, widget_3);

        lbMsg = new QLabel(widget_2);
        lbMsg->setObjectName(QString::fromUtf8("lbMsg"));
        lbMsg->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lbMsg);

        checkBox = new QCheckBox(widget_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, checkBox);


        gridLayout_3->addWidget(widget_2, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        label_3 = new QLabel(wBg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 40));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(109, 109, 109);\n"
"font: 700 28pt \"Microsoft JhengHei UI\";"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 1, 1, 1);


        gridLayout->addWidget(wBg, 0, 0, 1, 1);


        retranslateUi(DialogLogin);

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QCoreApplication::translate("DialogLogin", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DialogLogin", "\345\270\263\350\231\237", nullptr));
        label_2->setText(QCoreApplication::translate("DialogLogin", "\345\257\206\347\242\274", nullptr));
        btnLogin->setText(QCoreApplication::translate("DialogLogin", "\347\231\273\345\205\245", nullptr));
        lbMsg->setText(QString());
        checkBox->setText(QCoreApplication::translate("DialogLogin", "\345\204\262\345\255\230\345\270\263\350\231\237", nullptr));
        label_3->setText(QCoreApplication::translate("DialogLogin", "\350\211\276\346\257\224\344\273\243\347\256\241\347\220\206\347\263\273\347\265\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
