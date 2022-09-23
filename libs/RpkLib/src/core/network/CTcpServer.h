#ifndef CLISTENCLIENT_H
#define CLISTENCLIENT_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include "CTcpServerSubHandler.h"



class CTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = 0);
    ~CTcpServer();

    void startServer(QString sPort);
    void stop();

private:
    QTcpServer *m_tcpServer;

    QList <CTcpServerSubHandler *> handlerList;

signals:
    void signalLog(QString st);
    void signalReadAll(QByteArray data, uintptr_t handlerID);

private slots:
    void handlerQuery(QByteArray data, CTcpServerSubHandler * handler);
    void handlerFinish();

protected:
    void incomingConnection(qintptr socketDescriptor);


public slots:
    void slotRetrun(QByteArray arrReturn, uintptr_t handlerID);

};

#endif // CLISTENCLIENT_H
