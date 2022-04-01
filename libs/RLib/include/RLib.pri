
QT       += network sql testlib



win32{
OS=Win

}
unix:!macx{

#linux-arm-gnueabi {
#    //ARM stuff here
#}

OS=Linux
}
mac:!macx{
OS=Ios
}
macx{
QMAKE_MAC_SDK = macosx10.12
OS=Osx
}
android{
OS=Android
}



#DESTDIR = $$PWD/../bin/
MOC_DIR = $$PWD/../build/moc/
OBJECTS_DIR = $$PWD/../build/obj/
RCC_DIR = $$PWD/../build/rc/
UI_DIR = $$PWD/../build/ui/


RLIB=libRLibQt$$QT_MAJOR_VERSION$${OS}.a


#Use EX
#LIBS += -L$$PWD/../lib/ -lRLibQt$$QT_MAJOR_VERSION$${OS}
#INCLUDEPATH += $$PWD/../lib/include
#DEPENDPATH += $$PWD/../lib/include
#INCLUDEPATH += $$PWD/../lib/include/ui
#DEPENDPATH += $$PWD/../lib/include/ui
#PRE_TARGETDEPS += $$PWD/../lib/libRLibQt$$QT_MAJOR_VERSION$${OS}.a



INCLUDEPATH+= \
            $$PWD


HEADERS += \
    $$PWD/Network.h \
    $$PWD/DataBase.h \
    $$PWD/Ipc.h \
    $$PWD/Packager.h \
    $$PWD/Utility.h \
    $$PWD/Library.h
#    $$PWD/Ui.h \
#    $$PWD/ui/LayerWheel.h \
#    $$PWD/ui/LayerScrollView.h \
#    $$PWD/ui/ItemSelectNumber.h \
#    $$PWD/ui/LayerKeyborad.h \
#    $$PWD/ui/ItemLineEdit.h \
#    $$PWD/GlobalBase.h \
#    $$PWD/ui/LayerBlock.h \
#    $$PWD/ui/ItemLoadingBarA.h

RESOURCES += \
    $$PWD/res/res.qrc






