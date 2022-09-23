#include "Packager.h"
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

QByteArray Uint32ToByteArray(quint32 somevalue)
{
    quint32 value = somevalue;
    QByteArray tag;
    QDataStream s(&tag,QIODevice::ReadWrite);
    s << value;
    return tag;
}

quint32 ByteArrayToUint32(QByteArray bytes)
{
    QByteArray tag = bytes;
    quint32 value;
    QDataStream s(&tag,QIODevice::ReadWrite);
    s >> value;
    return value;
}

QByteArray headerbyte()
{
    const char header[] ={'@','A','K','A','4','0','4','@'};
    QByteArray hbyte(header,8);
    return hbyte;
}

QByteArray footbyte()
{
    const char footer[] ={'@','4','0','4','A','K','A','@'};
    QByteArray fbyte(footer,8);
    return fbyte;
}

Packager::Packager()
{
    m_data.clear();
}

Packager::Packager(QByteArray data):Packager()
{
    insert(data);
}

void Packager::insert(QByteArray dat)
{
    m_data.append(dat);
}

void Packager::clear()
{
    m_data.clear();
}

bool Packager::isPackaged()
{
    int sp = m_data.indexOf(headerbyte());

    if(sp < 0)
        return false;

    return true;
}

bool Packager::isPackageComplete()
{
    QByteArray hb = headerbyte();
    QByteArray ft = headerbyte();

    int sp = m_data.indexOf(hb);

    if(sp < 0)
    {
        //qDebug() << "isPackageComplete :No header" << QString(m_data);
        return false;
    }


    int ep = m_data.indexOf(ft);

    if(ep < 0)
    {
        //qDebug() << "isPackageComplete :No footer" << QString(m_data);
        return false;
    }

    uint datavlen = ByteArrayToUint32(m_data.mid(sp+8,4));

    if(datavlen == uint(m_data.length()-sp))
    {
        //qDebug() << "Package is Complete";
        return true;
    }

    return false;
}

QByteArray Packager::package()
{
    QByteArray pdata;

    pdata.append(headerbyte());
    pdata.append(Uint32ToByteArray(m_data.length()+20));
    pdata.append(m_data);
    pdata.append(footbyte());

    //qDebug() << "data size " << m_data.length() << "package" << pdata.length();

    return pdata;
}

QByteArray Packager::unPackage()
{

    QByteArray hb = headerbyte();
    QByteArray ft = headerbyte();

    int sp = m_data.indexOf(hb);

    if(sp < 0)
    {
        //qDebug() << "unPackage:No header" << QString(m_data);
        return QByteArray();
    }

    int ep = m_data.indexOf(ft);

    if(ep < 0)
    {
        //qDebug() << "unPackage:No footer" << QString(m_data);
        return QByteArray();
    }

    uint datavlen = ByteArrayToUint32(m_data.mid(sp+8,4));

    QByteArray rdata =m_data.mid(sp+12,datavlen-20);

    //qDebug() << "unPackage" << QString(rdata);

    m_data.remove(sp,datavlen);

    return rdata;
}


