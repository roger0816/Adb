#ifndef IPC_H
#define IPC_H

#include <QObject>
#include <QStringList>


class Ipc : public QObject
{
    Q_OBJECT
public:
    explicit Ipc(QObject *parent = 0);

    ~Ipc();

    /** tcpip server
     * @brief startServer
     * @param sPort
     */
    void runServer(QString sName);

    void recallClient(QByteArray arrReturn);


    /** block local client
     * @brief connectHost
     * @param sServerName
     * @param arrInput
     * @param arrOutput
     * @param iWaitTimer
     * @return
     */
    int connectHost(QString sServerName,QByteArray arrInput, QByteArray &arrOutput, int iWaitTimer=300);




signals:
    void signalLog(QString st);

    /** server
     * @brief signalReadAll
     * @param arrRead
     */
    void signalReadAll(QByteArray arrRead);
public slots:
};

#endif // IPC_H
