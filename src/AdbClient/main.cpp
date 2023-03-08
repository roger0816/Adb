#include "widget.h"

#include <QApplication>
//#include "DialogLogin.h"
//#include <QDebug>
//#include "Global.h"
//#include "GlobalUi.h"
//#include "StageTest.h"

#include <QFileDialog>
typedef enum
{
    _RELEASE=1,
    _LOCAL_SERVER,
    _NO_SERVER,
    _NO_SERVER_NO_DB,
    _TEST

}RUN_MODE;



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


#if 1
    //

    QString st=argv[0];


    RUN_MODE mode = _RELEASE;

    QString sArg=st.split("\\").last().trimmed().mid(0,9).toUpper();


    if(sArg.contains("ADBLOCAL"))
    {
        mode=_LOCAL_SERVER;
    }
    else if(sArg.contains("ADBTEST"))
    {
        ACTION.m_bTest = true;
         mode = _TEST;
    }





    qDebug()<<"test mode : "<<ACTION.m_bTest;


   // mode = _LOCAL_SERVER;

    if(argc>1)
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
        else if(st=="test")
        {
            mode = _TEST;

            ACTION.m_bTest = true;
        }

        else{}
    }

    QString sPort="6000";


    if(argc>2)
    {
        sPort=argv[2];
    }



    GLOBAL;


    QString sServerIp =GLOBAL.config("ServerIp").toString();


    QString sTestIp =GLOBAL.config("TestIp").toString();

    QString sServerPort = GLOBAL.config("ServerPort").toString();


    QString sTestPort = GLOBAL.config("TestPort").toString();

    bool b = GLOBAL.config("UseServer").toBool();


    switch (mode) {
    case _LOCAL_SERVER :
        GLOBAL.setServer(true,"127.0.0.1","6000");
        break;
    case _NO_SERVER :
        GLOBAL.setServer(false);
        ACTION.m_queryObj.setDataBase(true,"167.172.87.35");
        break;

    case _NO_SERVER_NO_DB :
        GLOBAL.setServer(false);
        ACTION.m_queryObj.setDataBase(false);
        break;


    case _RELEASE:
    default:
    {
        if(!ACTION.m_bTest)
            GLOBAL.setServer(b,sServerIp,sPort);
        else
            GLOBAL.setServer(b,sTestIp,sPort);


        break;
    }
    }


    qDebug()<<"run mode : "<<mode;

    Widget w;

    UI.m_mainWidget=&w;

    DialogLogin login;

    login.setReleaseIp(sServerIp,sServerPort);

    login.setTestIp(sTestIp,sTestPort);


    login.setVer(ADP_VER);

    login.connect(&login,&DialogLogin::signalLogin,&w,&Widget::slotLogin);

    login.setRelease(!ACTION.m_bTest);

    UI.m_dialogLogin = &login;

#if 1

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
    login.loginTarget("21");
#endif


    return a.exec();
#endif

}
