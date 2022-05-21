#ifndef CLISTENCLIENT_H
#define CLISTENCLIENT_H

#include <QThread>
#include <QObject>
#include <QtNetwork>




class CTcpServer : public QThread
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = 0);
    void run();
    void startServer(QString sPort);



private:
        QTcpServer *m_tcpServer;

        QTcpSocket *m_clientConnection;



signals:
        void signalLog(QString st);

        void signalReadAll(QByteArray arrRead);

private slots:
        void slotAcceptConnection();
        void slotReadClient();

public slots:
        void slotRetrun(QByteArray arrReturn);

};

#endif // CLISTENCLIENT_H
