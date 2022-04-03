#include "widget.h"

#include <QApplication>
#include "DialogLogin.h"
#include <QDebug>
#include "Global.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLOBAL;
    DialogLogin login;
        Widget w;
   // if(login.exec() ==1)
      w.show();


    return a.exec();
}
