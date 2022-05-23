QT       += core gui
QT += sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
DESTDIR =$$PWD/../../bin/

SOURCES += \
    CSideMenu.cpp \
    DialogAddValueTypeEdit.cpp \
    DialogBulletinEdit.cpp \
    DialogCommon.cpp \
    DialogCustomerEdit.cpp \
    DialogEditGameItem.cpp \
    DialogEditUser.cpp \
    DialogGameEdit.cpp \
    DialogInput.cpp \
    DialogLogin.cpp \
    DialogMsg.cpp \
    Global.cpp \
    GlobalUi.cpp \
    LayerAddCost.cpp \
    LayerAddValueType.cpp \
    LayerBulletin.cpp \
    LayerCostSetting.cpp \
    LayerCostTable.cpp \
    LayerCustomer.cpp \
    LayerCustomerDetail.cpp \
    LayerDayReport.cpp \
    LayerExchangeRate.cpp \
    LayerGetOrder1.cpp \
    LayerOrder.cpp \
    LayerSayCost.cpp \
    LayerSearchCustomer.cpp \
    LayerSysSetting.cpp \
    StageAccount.cpp \
    StageCustomer.cpp \
    StageHomePage.cpp \
    StageManagerSetting.cpp \
    StageOrder.cpp \
    StageTest.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    CSideMenu.h \
    DialogAddValueTypeEdit.h \
    DialogBulletinEdit.h \
    DialogCommon.h \
    DialogCustomerEdit.h \
    DialogEditGameItem.h \
    DialogEditUser.h \
    DialogGameEdit.h \
    DialogInput.h \
    DialogLogin.h \
    DialogMsg.h \
    Global.h \
    GlobalUi.h \
    LayerAddCost.h \
    LayerAddValueType.h \
    LayerBulletin.h \
    LayerCostSetting.h \
    LayerCostTable.h \
    LayerCustomer.h \
    LayerCustomerDetail.h \
    LayerDayReport.h \
    LayerExchangeRate.h \
    LayerGetOrder1.h \
    LayerOrder.h \
    LayerSayCost.h \
    LayerSearchCustomer.h \
    LayerSysSetting.h \
    StageAccount.h \
    StageCustomer.h \
    StageHomePage.h \
    StageManagerSetting.h \
    StageOrder.h \
    StageTest.h \
    widget.h

FORMS += \
    CSideMenu.ui \
    DialogAddValueTypeEdit.ui \
    DialogBulletinEdit.ui \
    DialogCommon.ui \
    DialogCustomerEdit.ui \
    DialogEditGameItem.ui \
    DialogEditUser.ui \
    DialogGameEdit.ui \
    DialogInput.ui \
    DialogLogin.ui \
    DialogMsg.ui \
    LayerAddCost.ui \
    LayerAddValueType.ui \
    LayerBulletin.ui \
    LayerCostSetting.ui \
    LayerCostTable.ui \
    LayerCustomer.ui \
    LayerCustomerDetail.ui \
    LayerDayReport.ui \
    LayerExchangeRate.ui \
    LayerGetOrder1.ui \
    LayerOrder.ui \
    LayerSayCost.ui \
    LayerSearchCustomer.ui \
    LayerSysSetting.ui \
    StageAccount.ui \
    StageCustomer.ui \
    StageHomePage.ui \
    StageManagerSetting.ui \
    StageOrder.ui \
    StageTest.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include(../Common/Common.pri)

win32: LIBS += -L$$PWD/../../libs/RpkLib/ -lRpkCore

INCLUDEPATH += $$PWD/../../libs/RpkLib/include
DEPENDPATH += $$PWD/../../libs/RpkLib/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RpkLib/RpkCore.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RpkLib/libRpkCore.a


include(../../libs/RpkLib/RpkCore.pri)

RESOURCES += \
    res/res.qrc
