#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QStringList>
#include "CData.h"



class Network :public QObject
{
    Q_OBJECT
public:
    Network(QObject *parent = 0);

    ~Network();

    /** tcpip server
     * @brief startServer
     * @param sPort
     */


    void runTcpServer(QString sPort);

    void stopTcpServer();

    void recallClient(QByteArray arrReturn, uintptr_t handlerID,bool bUsePackage=true);


    /** block tcpip client
     * @brief connectHost
     * @param sIp
     * @param sPort
     * @param arrInput
     * @param arrOutput
     * @param iWaitTimer
     * @return
     */
    int connectHost(QString sIp, QString sPort, QByteArray arrInput, QByteArray &arrOutput, int iWaitTimer=300);

    //Id =""  is Auto
    int connectHost(QString sId,QString sIp, QString sPort, QByteArray arrInput, int iWaitTimer=3000);


signals:
    void signalLog(QString st);

    /** tcpip server
     * @brief signalReadAll
     * @param arrRead
     */
    void signalReadAll(QByteArray arrRead, uintptr_t handlerID);
     void signalReadOrigin(QByteArray arrRead, uintptr_t handlerID);


    void replyFromServer(QString sId,QByteArray data,int error);


};

#endif // NETWORK_H
