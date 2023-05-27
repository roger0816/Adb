#include <QCoreApplication>
#include "CListenApi.h"
#include <QDataStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CListenApi api;

    api.startRESTfulApi("81");

    return a.exec();
}
