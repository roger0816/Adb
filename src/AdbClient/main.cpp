#include "widget.h"

#include <QApplication>
#include "DialogLogin.h"
#include <QDebug>
#include "Global.h"
#include "GlobalUi.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLOBAL;

    QString sServerIp =GLOBAL.config("ServerIp").toString();


    QString sServerPort = GLOBAL.config("ServerPort").toString();

    bool b = GLOBAL.config("UseServer").toBool();

    ACTION.setDataFromServer(b,sServerIp,sServerPort);
//    ACTION.setDataBase(true,sServerIp,"3306");
    if(!b)
        ACTION.setDataBase(false);

    ACTION.reQuerty();

    Widget w;
    DialogLogin login;

    login.setRelease(b);

    UI.m_dialogLogin = &login;


    w.connect(&login,SIGNAL(signalLogin()),&w,SLOT(show()));
#if 1


   login.exec();

#else
     ACTION.m_currentUser.Id="root";
     ACTION.m_currentUser.Name="Test001";
      ACTION.m_currentUser.Lv=99;
      ACTION.m_currentUser.Sid="1";
     w.show();
#endif



    return a.exec();
}
