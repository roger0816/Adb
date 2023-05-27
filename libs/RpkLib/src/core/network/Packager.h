#ifndef NETWORKTOOL_H
#define NETWORKTOOL_H
#include <QByteArray>

//typedef struct _package_network_
//{
//    QByteArray packeageHeader; // "@#$%+-*/"
//    quint32    packeageLength; // package lenght
//    QByteArray packedate;      // data
//    QByteArray packeageFoot;   // "/*-+%$#@"
//}package_network;

class Packager
{
public:
    Packager();
    Packager(QByteArray data);
    void insert(QByteArray dat);
    void clear();
    bool isPackaged();
    bool isPackageComplete();
    QByteArray package();
    QByteArray unPackage();



private:
    QByteArray m_data;
};

#endif // NETWORKTOOL_H
