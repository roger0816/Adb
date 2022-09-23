QT+= network sql

LIB_PATH=$$PWD

message($$LIB_PATH)

INCLUDEPATH+=$$PWD \
             $$PWD/include \
             $$PWD/include/core \
             $$PWD/include/core/abstract

HEADERS += \
    $$PWD/include/core/CData.h \
    $$PWD/include/core/abstract/CAction.h \
    $$PWD/include/RpkCore.h \
    $$PWD/include/core/DataBase.h \
    $$PWD/include/core/Network.h \
    $$PWD/include/core/abstract/CGlobal.h







contains(DEFINES,BUILD_PRK){
    message("Build RPKLib")

MOC_DIR =$$PWD/obj
OBJECTS_DIR =$$PWD/obj
UI_DIR =$$PWD/obj
#DESTDIR =$$PWD/../../bin/

}
else{
     message("Use RPKLib")

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32: LIBS += -L$$PWD/ -lRpkCoreWin
unix: LIBS += -L$$PWD/ -lRpkCoreUnix


win32:!win32-g++: PRE_TARGETDEPS += $$PWD/RpkCoreWin.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libRpkCoreWin.a
else:unix: PRE_TARGETDEPS += $$PWD/libRpkCoreUnix.a

}
