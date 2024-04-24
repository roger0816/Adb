#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QEventLoop>

class CTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = 0);
    //once connect
    int connectHost(QString sIp,QString sPort,QByteArray arrInput,QByteArray &arrOutput,int iWaitMsec=3000);

    int connectHost(QString sId,QString sIp, QString sPort, QByteArray arrInput, int iWaitMsec=3000);

    // long connect
    bool openConnect(QString sIp,QString sPort);

    bool sendData(QString sId,QByteArray arrInput, QString sIp="",QString sPort="");

    bool connectIsOpen(QString sIp,QString sPort);

    void closeConnect(QString sIp,QString sPort);
    //
signals:
    void signalLog(QString st);

    void signalReply(QString sId,QByteArray data,int Error);

    void singalLongConnect(QString sConnect, QString sId,QByteArray data,int Error);

    void finished(QString sId,QByteArray data,int Error);
public slots:

    void error(QAbstractSocket::SocketError error);

    void slotConnected();

    void slotDisconnected();

    void slotReadyRead();

    void slotLongRead();
private:

        QEventLoop *loop=new QEventLoop(this);
};

#endif // CTCPCLIENT_H
