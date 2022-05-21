QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



DESTDIR = $$PWD/../..
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/obj
UI_DIR = $$PWD/obj/ui_header

INCLUDEPATH += $$PWD/network \
               $$PWD/database

SOURCES += \
    RpkCore.cpp \
    database/CSql.cpp \
    database/DataBase.cpp \
    network/CTcpClient.cpp \
    network/CTcpServer.cpp \
    network/Network.cpp \
    network/Packager.cpp


HEADERS += \
    RpkCore.h \
    database/CSql.h \
    network/CTcpClient.h \
    network/CTcpServer.h \
    network/Packager.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

include(../../RpkCore.pri)




