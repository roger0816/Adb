#include <QCoreApplication>
#include "CListenApi.h"
#include <QDataStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //chencan.info
    //adp.idv.tw
    CListenApi api;

    QString sListenPort="81";

    QString sServerIp="127.0.0.1";
    QString sServerPort="6005";

    if(argc>3)
    {
        sServerPort=argv[3];
    }

    if(argc>2)
    {
        sServerIp=argv[2];
    }

    if(argc>1)
    {
        sListenPort=argv[1];
    }

    api.m_request.setServer(sServerIp,sServerPort);

    api.startRESTfulApi(sListenPort);



    return a.exec();
}
