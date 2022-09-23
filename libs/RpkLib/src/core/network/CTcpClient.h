#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>


class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = 0);
    QTcpSocket *m_socket;
    int connectHost(QString sIp,QString sPort,QByteArray arrInput,QByteArray &arrOutput,int iWaitMsec=3000);

    int connectHost(QString sId,QString sIp, QString sPort, QByteArray arrInput, int iWaitMsec=3000);

signals:
    void signalLog(QString st);

    void signalReply(QString sId,QByteArray data,int Error);

    void finished(QString sId,QByteArray data,int Error);
public slots:

    void error(QAbstractSocket::SocketError error);

    void slotConnected();

    void slotDisconnected();

    void slotReadyRead();


};

#endif // CTCPCLIENT_H
