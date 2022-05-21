#include "Network.h"

#include "CTcpClient.h"
#include "CTcpServer.h"





CTcpServer *g_tcpServer=0;

CTcpClient *g_tcpClient=0;


typedef void (CTcpClient::*tcpConnect)(QString sIp, QString sPort, QByteArray arrInput, QByteArray &arrOutput, int iWaitTimer);


Network::Network(QObject *parent):
    QObject(parent)
{
    g_tcpClient=new CTcpClient(this);
    g_tcpClient->connect(g_tcpClient,SIGNAL(signalLog(QString)),this,SIGNAL(signalLog(QString)));

    g_tcpServer=new CTcpServer(this);
    g_tcpServer->connect(g_tcpServer,SIGNAL(signalLog(QString)),this,SIGNAL(signalLog(QString)));
    g_tcpServer->connect(g_tcpServer,SIGNAL(signalReadAll(QByteArray)),this,SIGNAL(signalReadAll(QByteArray)));
}

Network::~Network()
{

}

void Network::runTcpServer(QString sPort)
{
    g_tcpServer->startServer(sPort);
}

void Network::recallClient(QByteArray arrReturn)
{
    g_tcpServer->slotRetrun(arrReturn);
}

int Network::connectHost(QString sIp, QString sPort, QByteArray arrInput, QByteArray &arrOutput, int iWaitTimer)
{
    return g_tcpClient->connectHost(sIp,sPort,arrInput,arrOutput,iWaitTimer);
}




