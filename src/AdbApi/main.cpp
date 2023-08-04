#include <QCoreApplication>
#include "CListenApi.h"
#include <QDataStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CListenApi api;

    QString sPort="81";

    if(argc>1)
    {
        sPort=argv[1];
    }

    api.startRESTfulApi(sPort);

    return a.exec();
}
