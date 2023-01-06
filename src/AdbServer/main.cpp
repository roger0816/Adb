#include <QCoreApplication>
#include "Launch.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString sDbIp="127.0.0.1";
    if(argc>=2)
    {
        sDbIp =QString(argv[1]).toLower();

    }
    Launch l;

    l.startServer(sDbIp);

    return a.exec();
}
