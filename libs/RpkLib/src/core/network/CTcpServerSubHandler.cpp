#include "CTcpServerSubHandler.h"



CTcpServerSubHandler::CTcpServerSubHandler(qintptr ID, QObject *parent) : QThread(parent)
{
    this->descriptor = ID;
    packager.clear();

    this->socket = new QTcpSocket();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // set the ID
    if(!socket->setSocketDescriptor(this->descriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }
}


void CTcpServerSubHandler::responcesClient(QByteArray data)
{
    Packager psend;

    psend.insert(data);

    qDebug() << "CTcpServerSubHandler" <<  (uintptr_t)this << "responces";

    this->socket->write(psend.package());

}

void CTcpServerSubHandler::readyRead()
{
    packager.insert(socket->readAll());

    //qDebug() << QString(packager.raw());

    if(packager.isPackageComplete())
    {
        QByteArray readdate = packager.unPackage();

        emit clientQuery(readdate,this);

        packager.clear();
    }

}

void CTcpServerSubHandler::disconnected()
{
    qDebug() << descriptor << " Disconnected";

    socket->deleteLater();

    exit(0);
}
