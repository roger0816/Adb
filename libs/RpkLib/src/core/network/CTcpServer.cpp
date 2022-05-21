#include "CTcpServer.h"
#include "Packager.h"

#include <QList>
#include <QMap>

QMap <QTcpSocket*, Packager*> SocketMap;

CTcpServer::CTcpServer(QObject *parent) :
    QThread(parent)
{


}

void CTcpServer::run()
{


}

void CTcpServer::startServer(QString sPort)
{

    //m_clientConnection=NULL;

    m_tcpServer = new QTcpServer(this);

    m_tcpServer->listen(QHostAddress::Any, sPort.toInt());

    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotAcceptConnection()));

    emit signalLog("TCP SERVER CREAT");

}

void CTcpServer::slotAcceptConnection()
{

    emit signalLog("get client link");

#if 1
    static quint64 connectID = 0;

    QTcpSocket * sp = m_tcpServer->nextPendingConnection();

    sp->setObjectName(QString("connect_%1").arg(++connectID));

    Packager * pp = new Packager();

    QObject::connect(sp, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    SocketMap.insert(sp,pp);
#else
    if(m_clientConnection!=NULL)
    {
        m_clientConnection->abort();

        m_clientConnection->disconnect();
    }

    m_clientConnection = m_tcpServer->nextPendingConnection();

    m_clientConnection->connect(m_clientConnection, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
#endif

}

void CTcpServer::slotReadClient()
{
#if 1

    QTcpSocket *pSenderSocket = qobject_cast<QTcpSocket*>(sender());

    //qDebug()<<  pSenderSocket->objectName();

    Packager * pp = SocketMap.value(pSenderSocket);

    pp->insert(pSenderSocket->readAll());

    if(pp->isPackageComplete())
    {
        QByteArray readdate = pp->unPackage();

        QString str =readdate;

        emit signalLog("read client : "+str);

        emit signalReadAll(readdate);


        if(readdate=="test")
        {
            slotRetrun(QByteArray("testOk"));
        }

        pp->clear();
    }

#else
    static Packager pp;

    pp.insert(m_clientConnection->readAll());

    if(pp.isPackageComplete())
    {
        QByteArray readdate = pp.unPackage();

        //qDebug() << "slotReadClient" << QString(readdate);

        QString str =readdate;

        emit signalLog("read client : "+str);

        emit signalReadAll(readdate);

        pp.clear();
    }
    //    QString sReClient;

    //    emit signalLog(sReClient);

    //    QByteArray tmp;

    //    tmp.append(sReClient);

    //    QTcpSocket *pSenderSocket = qobject_cast<QTcpSocket*>(sender());

    //    pSenderSocket->write(tmp);
#endif

}

void CTcpServer::slotRetrun(QByteArray arrReturn)
{
    Packager pp;

    QTcpSocket *pSenderSocket = qobject_cast<QTcpSocket*>(sender());

    //qDebug() << "slotRetrun" << arrReturn;

    pp.insert(arrReturn);

    pSenderSocket->write(pp.package());

    QString sReClient=arrReturn;

    emit signalLog("return client : "+sReClient);

    Packager * oldpp = SocketMap.value(pSenderSocket);

    oldpp->clear();

    delete oldpp;

    SocketMap.remove(pSenderSocket);
}




