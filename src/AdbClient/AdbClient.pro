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
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../libs/RLib/ -lRLibQt5Win

INCLUDEPATH += $$PWD/../../libs/RLib/include
DEPENDPATH += $$PWD/../../libs/RLib/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RLib/RLibQt5Win.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../libs/RLib/libRLibQt5Win.a

include(../Common/Common.pri)