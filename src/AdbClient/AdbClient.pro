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

INCLUDEPATH+= \
              StageCustomer \
              StageOrder \
              StageReport \
              StageManagerSetting

SOURCES += \
    CSideMenu.cpp \
    DialogAddValueTypeEdit.cpp \
    DialogBulletinEdit.cpp \
    DialogCommon.cpp \
    DialogCustomerEdit.cpp \
    DialogEditUser.cpp \
    DialogInput.cpp \
    DialogLogin.cpp \
    DialogMsg.cpp \
    Global.cpp \
    GlobalUi.cpp \
    LayerBulletin.cpp \
    LayerOrder.cpp \
    StageAccount.cpp \
    StageCustomer/StageCustomer.cpp \
    StageCustomer/LayerSayCost.cpp \
    StageCustomer/LayerSearchCustomer.cpp \
    StageCustomer/LayerCustomer.cpp \
    StageCustomer/LayerCustomerDetail.cpp \
    StageCustomer/LayerAddCost.cpp \
    StageOrder/LayerGetOrder2.cpp \
    StageOrder\StageOrder.cpp \
    StageOrder\LayerCostTable.cpp \
    StageOrder\LayerDayReport.cpp \
    StageOrder\LayerGetOrder1.cpp \
    StageHomePage.cpp \
    StageManagerSetting/DialogEditFactory.cpp \
    StageManagerSetting/LayerFactory.cpp \
    StageManagerSetting/LayerPrimeCostRate.cpp \
    StageManagerSetting/StageManagerSetting.cpp \
    StageManagerSetting/LayerExchangeRate.cpp \
    StageManagerSetting/LayerCostSetting.cpp \
    StageManagerSetting/LayerAddValueType.cpp \
    StageManagerSetting/LayerSysSetting.cpp \
    StageManagerSetting/DialogGameEdit.cpp \
    StageManagerSetting/DialogEditGameItem.cpp \
    StageTest.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    CSideMenu.h \
    DialogAddValueTypeEdit.h \
    DialogBulletinEdit.h \
    DialogCommon.h \
    DialogCustomerEdit.h \
    DialogEditUser.h \
    DialogInput.h \
    DialogLogin.h \
    DialogMsg.h \
    Global.h \
    GlobalUi.h \
    LayerBulletin.h \
    LayerOrder.h \
    StageAccount.h \
    StageCustomer/StageCustomer.h \
    StageCustomer/LayerSayCost.h \
    StageCustomer/LayerSearchCustomer.h \
    StageCustomer/LayerCustomer.h \
    StageCustomer/LayerCustomerDetail.h \
     StageCustomer/LayerAddCost.h \
    StageOrder/LayerGetOrder2.h \
       StageOrder\StageOrder.h \
       StageOrder\LayerCostTable.h \
       StageOrder\LayerDayReport.h \
       StageOrder\LayerGetOrder1.h \
    StageHomePage.h \
    StageManagerSetting/DialogEditFactory.h \
    StageManagerSetting/LayerFactory.h \
    StageManagerSetting/LayerPrimeCostRate.h \
    StageManagerSetting/StageManagerSetting.h \
    StageManagerSetting/LayerExchangeRate.h \
    StageManagerSetting/LayerCostSetting.h \
    StageManagerSetting/LayerAddValueType.h \
    StageManagerSetting/LayerSysSetting.h \
    StageManagerSetting/DialogGameEdit.h \
    StageManagerSetting/DialogEditGameItem.h \
    StageTest.h \
    widget.h

FORMS += \
    CSideMenu.ui \
    DialogAddValueTypeEdit.ui \
    DialogBulletinEdit.ui \
    DialogCommon.ui \
    DialogCustomerEdit.ui \
    DialogEditUser.ui \
    DialogInput.ui \
    DialogLogin.ui \
    DialogMsg.ui \
    LayerBulletin.ui \
    LayerOrder.ui \
    StageAccount.ui \
    StageCustomer/StageCustomer.ui \
    StageCustomer/LayerSayCost.ui \
    StageCustomer/LayerSearchCustomer.ui \
    StageCustomer/LayerCustomer.ui \
    StageCustomer/LayerCustomerDetail.ui \
    StageCustomer/LayerAddCost.ui \
    StageOrder/LayerGetOrder2.ui \
      StageOrder\StageOrder.ui \
      StageOrder\LayerCostTable.ui \
      StageOrder\LayerDayReport.ui \
      StageOrder\LayerGetOrder1.ui \
    StageHomePage.ui \
    StageManagerSetting/DialogEditFactory.ui \
    StageManagerSetting/LayerFactory.ui \
    StageManagerSetting/LayerPrimeCostRate.ui \
    StageManagerSetting/StageManagerSetting.ui \
    StageManagerSetting/LayerExchangeRate.ui \
    StageManagerSetting/LayerCostSetting.ui \
    StageManagerSetting/LayerAddValueType.ui \
    StageManagerSetting/LayerSysSetting.ui \
    StageManagerSetting/DialogGameEdit.ui \
    StageManagerSetting/DialogEditGameItem.ui \
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
