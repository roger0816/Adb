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
    int connectHost(QString sIp,QString sPort,QByteArray arrInput,QByteArray &arrOutput,int iWaitTimer=300);

signals:
    void signalLog(QString st);
public slots:
};

#endif // CTCPCLIENT_H
