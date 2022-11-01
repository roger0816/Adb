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

    UI.m_mainWidget=&w;

    DialogLogin login;

    login.setVer(ADP_VER);

    login.connect(&login,&DialogLogin::signalLogin,&w,&Widget::slotLogin);

    login.setRelease(b);

    UI.m_dialogLogin = &login;

#if 0

    int iRet =login.exec();

    if(iRet==_DialogLogin::_LoginOk)
    {
        //is signal slot done
    }
    else if(iRet==_DialogLogin::_Close)
    {
        return 0;
    }


#else
    ACTION.m_currentUser.Id="sysroot";
    ACTION.m_currentUser.Name="sysroot";
    ACTION.m_currentUser.Lv=99;
    ACTION.m_currentUser.Sid="0";
    ACTION.m_currentUser.Cid="R00";
    w.slotLogin();
#endif


    return a.exec();


}
