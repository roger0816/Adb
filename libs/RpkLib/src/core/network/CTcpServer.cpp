#include "CTcpServer.h"
#include "Packager.h"
#include "CTcpServerSubHandler.h"
#include <QList>
#include <QMap>



CTcpServer::CTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    handlerList.clear();
}

CTcpServer::~CTcpServer()
{
    while(handlerList.length())
    {
        CTcpServerSubHandler *handler =  handlerList.takeFirst();

        qDebug() << "CTcpServer remove handler";

        handler->exit(0);

        delete handler;
    }
    qDebug() << "CTcpServer done";

    //exit(0);
}



void CTcpServer::startServer(QString sPort)
{

    if(!this->listen(QHostAddress::Any, sPort.toInt()))
    {
        qDebug() << "CTcpServer Could not start server";
    }
    else
    {
        qDebug() << "CTcpServer Listening to port " << sPort << "...";
    }

}

void CTcpServer::stop()
{

    if(!this->isListening())
        return;

    this->close();

}


void CTcpServer::handlerQuery(QByteArray data, CTcpServerSubHandler *handler)
{
     uintptr_t h =  (uintptr_t)handler;

     emit signalReadAll(data, h);

}
void CTcpServer::handlerFinish()
{
    CTcpServerSubHandler *handler = qobject_cast<CTcpServerSubHandler *>(sender());

//    qDebug() << "CTcpServer handler" <<  (uintptr_t)handler << "finish";

//    foreach(CTcpServerSubHandler* h  ,handlerList)
//    {
//        qDebug() << (uintptr_t)h;
//    }

    if(handlerList.contains(handler))
    {
        handlerList.removeOne(handler);

        //qDebug() << "CTcpServer handler" <<  (uintptr_t)handler  << "remove form list" << handlerList.contains(handler);
    }

//    foreach(CTcpServerSubHandler *h  ,handlerList)
//    {
//        qDebug() << (uintptr_t)h;
//    }



    handler->deleteLater();

}


void CTcpServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << "CTcpServer " << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    CTcpServerSubHandler *handler = new CTcpServerSubHandler(socketDescriptor, this);

    handlerList << handler;

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(handler, SIGNAL(finished()), this, SLOT(handlerFinish()));
    connect(handler, SIGNAL(clientQuery(QByteArray, CTcpServerSubHandler *)), this,SLOT(handlerQuery(QByteArray, CTcpServerSubHandler *)));

    handler->start();
}

void CTcpServer::slotRetrun(QByteArray arrReturn, uintptr_t handlerID)
{
    CTcpServerSubHandler *handler = (CTcpServerSubHandler *)handlerID;

    qDebug() << "CTcpServer handler" <<  (uintptr_t)handler << "responcesClient";

    if(handlerList.contains(handler))
        handler->responcesClient(arrReturn);
}






