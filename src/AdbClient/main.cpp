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

    ACTION.reQuerty();

    Widget w;
    DialogLogin login;

    UI.m_dialogLogin = &login;


    w.connect(&login,SIGNAL(signalLogin()),&w,SLOT(show()));
#if 0


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
