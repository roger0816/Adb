#ifndef CTCPSERVERSUBHANDLER_H
#define CTCPSERVERSUBHANDLER_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>

#include "Packager.h"

class CTcpServerSubHandler : public QThread
{
    Q_OBJECT
public:
    explicit CTcpServerSubHandler(qintptr ID,QObject *parent = nullptr);

    //void run();

    void responcesClient(QByteArray data);

    signals:
        void error(QTcpSocket::SocketError socketerror);

        void clientQuery(QByteArray data, CTcpServerSubHandler * self);

    public slots:
        void readyRead();
        void disconnected();

    private:
        QTcpSocket  *socket;
        qintptr     descriptor;

        Packager    packager;
};

#endif // CTCPSERVERSUBHANDLER_H
