QT       += core gui
QT += sql network charts

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
              component \
              StageCustomerService \
              StageOrder \
              StageReport \
              StageManagerSetting

SOURCES += \
    StageCustomerService/DialogCustomerCostHistory.cpp \
    StageOrder/ItemOrderSelector.cpp \
    component/CLinkTable.cpp \
    component/CSideMenu.cpp \
    DialogBulletinEdit.cpp \
    DialogCommon.cpp \
    DialogEditUser.cpp \
    DialogInput.cpp \
    DialogLogin.cpp \
    DialogMsg.cpp \
    Global.cpp \
    GlobalUi.cpp \
    component/DialogObj.cpp \
    component/ItemMiniLoadbar.cpp \
    component/ItemPic.cpp \
    component/ItemPicObj.cpp \
    component/Label3.cpp \
    LayerBulletin.cpp \
    LayerOrder.cpp \
    StageAccount.cpp \
    StageCustomerService/LayerSayCost.cpp \
    StageCustomerService/LayerSearchCustomer.cpp \
    StageCustomerService/LayerCustomer.cpp \
    StageCustomerService/DialogCustomerEdit.cpp \
    StageCustomerService/LayerCustomerDetail.cpp \
    StageCustomerService/LayerAddCost.cpp \
    StageCustomerService/StageCustomerService.cpp \
    StageManagerSetting/LayerAccountManager.cpp \
    StageManagerSetting/LayerCustomerSetting.cpp \
    StageOrder/LayerGetOrder2.cpp \
    StageOrder/StageOrder.cpp \
    StageOrder/LayerCostTable.cpp \
    StageOrder/LayerDayReport.cpp \
    StageOrder/LayerGetOrder1.cpp \
    StageHomePage.cpp \
    StageManagerSetting/DialogEditFactory.cpp \
    StageManagerSetting/LayerFactory.cpp \
    StageManagerSetting/LayerPrimeCostRate.cpp \
    StageManagerSetting/StageManagerSetting.cpp \
    StageManagerSetting/LayerCostSetting.cpp \
    StageManagerSetting/LayerAddValueType.cpp \
    StageManagerSetting/LayerSysSetting.cpp \
    StageManagerSetting/DialogGameEdit.cpp \
    StageManagerSetting/DialogEditGameItem.cpp \
    StageManagerSetting/DialogAddValueTypeEdit.cpp \
    StageReport/ItemScheduleStatus.cpp \
    StageReport/LayerSchedule.cpp \
    StageReport/StageReport.cpp \
    StageTest.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    StageCustomerService/DialogCustomerCostHistory.h \
    StageOrder/ItemOrderSelector.h \
    component/CLinkTable.h \
    component/CSideMenu.h \
    DialogBulletinEdit.h \
    DialogCommon.h \
    DialogEditUser.h \
    DialogInput.h \
    DialogLogin.h \
    DialogMsg.h \
    Global.h \
    GlobalUi.h \
    component/DialogObj.h \
    component/ItemMiniLoadbar.h \
    component/ItemPic.h \
    component/ItemPicObj.h \
    component/Label3.h \
    LayerBulletin.h \
    LayerOrder.h \
    StageAccount.h \
    StageCustomerService/LayerSayCost.h \
    StageCustomerService/LayerSearchCustomer.h \
       StageCustomerService/DialogCustomerEdit.h \
    StageCustomerService/LayerCustomer.h \
    StageCustomerService/LayerCustomerDetail.h \
     StageCustomerService/LayerAddCost.h \
    StageCustomerService/StageCustomerService.h \
    StageManagerSetting/LayerAccountManager.h \
    StageManagerSetting/LayerCustomerSetting.h \
    StageOrder/LayerGetOrder2.h \
       StageOrder/StageOrder.h \
       StageOrder/LayerCostTable.h \
       StageOrder/LayerDayReport.h \
       StageOrder/LayerGetOrder1.h \
    StageHomePage.h \
    StageManagerSetting/DialogEditFactory.h \
    StageManagerSetting/LayerFactory.h \
    StageManagerSetting/LayerPrimeCostRate.h \
    StageManagerSetting/StageManagerSetting.h \
    StageManagerSetting/LayerCostSetting.h \
    StageManagerSetting/LayerAddValueType.h \
    StageManagerSetting/LayerSysSetting.h \
    StageManagerSetting/DialogGameEdit.h \
    StageManagerSetting/DialogEditGameItem.h \
    StageManagerSetting/DialogAddValueTypeEdit.h \
    StageReport/ItemScheduleStatus.h \
    StageReport/LayerSchedule.h \
    StageReport/StageReport.h \
    StageTest.h \
    widget.h

FORMS += \
    StageCustomerService/DialogCustomerCostHistory.ui \
    StageOrder/ItemOrderSelector.ui \
    component/CSideMenu.ui \
    DialogBulletinEdit.ui \
    DialogCommon.ui \
    DialogEditUser.ui \
    DialogInput.ui \
    DialogLogin.ui \
    DialogMsg.ui \
    component/ItemMiniLoadbar.ui \
    LayerBulletin.ui \
    LayerOrder.ui \
    StageAccount.ui \
    StageCustomerService/LayerSayCost.ui \
    StageCustomerService/LayerSearchCustomer.ui \
    StageCustomerService/LayerCustomer.ui \
    StageCustomerService/DialogCustomerEdit.ui \
    StageCustomerService/LayerCustomerDetail.ui \
    StageCustomerService/LayerAddCost.ui \
    StageCustomerService/StageCustomerService.ui \
    StageManagerSetting/LayerAccountManager.ui \
    StageManagerSetting/LayerCustomerSetting.ui \
    StageOrder/LayerGetOrder2.ui \
      StageOrder/StageOrder.ui \
      StageOrder/LayerCostTable.ui \
      StageOrder/LayerDayReport.ui \
      StageOrder/LayerGetOrder1.ui \
    StageHomePage.ui \
    StageManagerSetting/DialogEditFactory.ui \
    StageManagerSetting/LayerFactory.ui \
    StageManagerSetting/LayerPrimeCostRate.ui \
    StageManagerSetting/StageManagerSetting.ui \
    StageManagerSetting/LayerCostSetting.ui \
    StageManagerSetting/LayerAddValueType.ui \
    StageManagerSetting/LayerSysSetting.ui \
    StageManagerSetting/DialogGameEdit.ui \
    StageManagerSetting/DialogEditGameItem.ui \
    StageManagerSetting/DialogAddValueTypeEdit.ui \
    StageReport/ItemScheduleStatus.ui \
    StageReport/LayerSchedule.ui \
    StageReport/StageReport.ui \
    StageTest.ui \
    component/ItemPicObj.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include(../Common/Common.pri)

include(../../libs/RpkLib/RpkCore.pri)

RESOURCES += \
    res/res.qrc

win32: TARGET =AdbClientWin
unix: TARGET =AdbClientUnix


include(component/mutiScreen/mutiScreen.pri)




