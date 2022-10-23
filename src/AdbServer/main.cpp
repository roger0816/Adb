#include <QCoreApplication>
#include "Launch.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Launch l;

    return a.exec();
}
