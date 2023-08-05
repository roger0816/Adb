QT -= gui
QT+=network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
DESTDIR =$$PWD/../../bin/

SOURCES += \
        CHttpServerObj.cpp \
        CListenApi.cpp \
        CRequestData.cpp \
        main.cpp

include(../Common/Common.pri)

include(../../libs/RpkLib/RpkCore.pri)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CHttpServerObj.h \
    CListenApi.h \
    CRequestData.h
