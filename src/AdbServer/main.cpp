#include <QCoreApplication>
#include "Launch.h"
#include <QSettings>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     QString sListenPort ="6000";
     QString sDbName ="adp";


    if(argc>1)
    {
        sListenPort = argv[1];
    }


    if(argc>2)
    {
        sDbName =argv[2];
    }




    QString sDbIp="10.130.0.8";
	sDbIp="127.0.0.1";

    if(argc>2)
    {
        sDbIp =QString(argv[2]).toLower();

    }

    if(argc>3)
    {
        sDbName =argv[3];

    }
    Launch l;

    l.setDb(sDbIp);

    l.startServer(sListenPort);

    return a.exec();
}
