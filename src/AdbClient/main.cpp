#include "widget.h"

#include <QApplication>
#include "DialogLogin.h"
#include <QDebug>
#include "Global.h"
#include "GlobalUi.h"
#include "StageTest.h"

typedef enum
{
    _RELEASE=1,
    _LOCAL_SERVER,
    _NO_SERVER,
    _NO_SERVER_NO_DB

}RUN_MODE;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RUN_MODE mode = _RELEASE;

    if(argc>=2)
    {
        QString st=QString(argv[1]).toLower();

        if(st=="local")
        {
            mode = _LOCAL_SERVER;
        }

        else if(st=="noserver")
        {
            mode = _NO_SERVER;
        }

        else if(st=="none")
        {
            mode = _NO_SERVER_NO_DB;
        }

        else{}
    }



    GLOBAL;

    QString sServerIp =GLOBAL.config("ServerIp").toString();


    QString sServerPort = GLOBAL.config("ServerPort").toString();

    bool b = GLOBAL.config("UseServer").toBool();


    switch (mode) {
    case _LOCAL_SERVER :
        ACTION.setServer(true,"127.0.0.1","6000");
        break;
    case _NO_SERVER :
        ACTION.setServer(false);
        ACTION.m_queryObj.setDataBase(true,"167.172.87.35");
        break;

    case _NO_SERVER_NO_DB :
        ACTION.setServer(false);
        ACTION.m_queryObj.setDataBase(false);
        break;


    case _RELEASE:
    default:
        ACTION.setServer(b,sServerIp,sServerPort);

        break;

    }


    qDebug()<<"run mode : "<<mode;

    Widget w;

    DialogLogin login;

    login.setRelease(b);

    UI.m_dialogLogin = &login;

#if 1



    if(login.exec())
    {
        ACTION.reQuerty();

        ACTION.setStartSyanc(true);

        w.show();
    }
    else
    {
        return 0;
    }


#else
    ACTION.m_currentUser.Id="root";
    ACTION.m_currentUser.Name="Test001";
    ACTION.m_currentUser.Lv=99;
    ACTION.m_currentUser.Sid="1";
    w.show();
#endif


    return a.exec();


}
