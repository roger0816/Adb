QT -= gui

QT += sql network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Launch.cpp \
        main.cpp

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
DESTDIR =$$PWD/../../bin/


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Launch.h


include(../Common/Common.pri)

#unix:!macx|win32: LIBS += -L$$PWD/../../libs/RpkLib/ -lRpkCore

#INCLUDEPATH += $$PWD/../../libs/RpkLib/include
#DEPENDPATH += $$PWD/../../libs/RpkLib/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RpkLib/RpkCore.lib
#else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RpkLib/libRpkCore.a

include(../../libs/RpkLib/RpkCore.pri)

win32: TARGET =AdbServerWin

unix: TARGET =AdbServerUnix
