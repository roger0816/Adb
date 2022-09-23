#include "CTcpClient.h"
#include "Packager.h"
#include <QDateTime>
#include <QTimer>
#include <QEventLoop>

QMap<QString,Packager > m_kPackger;

namespace  CTcp{
const char *id= "id";
const char *inputData ="input";
const char *outputData ="output";
}

bool bSendSignal = true;

CTcpClient::CTcpClient(QObject *parent) : QObject(parent)
{
    m_socket=NULL;
}


int CTcpClient::connectHost(QString sIp, QString sPort, QByteArray arrInput, QByteArray &arrOutput, int iWaitMsec)
{

    int iRe=0;

    QString sId =QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");

    bSendSignal = false;

    connectHost(sId,sIp,sPort,arrInput,iWaitMsec);

    bSendSignal = true;
    QEventLoop *loop= new QEventLoop(this);

    connect(this,&CTcpClient::signalReply,this,[=,&arrOutput,&iRe](QString id,QByteArray data,int error)
    {
        if(sId==id)
        {
            loop->quit();

            loop->deleteLater();

            arrOutput =data;

            iRe = error;
        }

    });


    loop->exec();


    return iRe;

    /*
    int iRe=0;

    QTcpSocket tcp;

    tcp.connectToHost(sIp,sPort.toInt());

    Packager pp(arrInput);

    if(tcp.waitForConnected(iWaitTimer))
    {

        emit signalLog("Connected "+sIp+" : "+sPort);
        tcp.write(pp.package());
        //   m_socket->bytesWritten(inBuffer);
        tcp.waitForBytesWritten(iWaitTimer);
        emit signalLog("socket written ok");

        pp.clear();
        while (true)
        {
            if(tcp.waitForReadyRead(30000) == false)
            {
                break;
            }

            pp.insert(tcp.readAll());

            if(pp.isPackageComplete())
            {
                break;
            }
        }

        arrOutput.append(pp.unPackage());

        //qDebug() << QString(arrOutput);

        QString sTmp="Reading : "+arrOutput;

        emit signalLog(sTmp);

        tcp.close();
    }
    else
    {
        emit signalLog("Not connected!");
        iRe= 999;
    }



    if(arrOutput.length()-arrInput.length()<1)
        iRe=998;
    return iRe;

    */
}

int CTcpClient::connectHost(QString sId, QString sIp, QString sPort, QByteArray arrInput, int iWaitMsec)
{

    qDebug()<<"unblock";

    if(sId.trimmed()=="")
        sId =QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    QTcpSocket *tcp = new QTcpSocket(this);


    tcp->setProperty(CTcp::id,sId);

    tcp->setProperty(CTcp::inputData,arrInput);

    tcp->setProperty(CTcp::outputData,QByteArray());


    tcp->connect(tcp,SIGNAL(connected()),this,SLOT(slotConnected()));

    tcp->connect(tcp,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    tcp->connect(tcp,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

    QTimer timer;

    connect(&timer,&QTimer::timeout,[=]
    {
        if(tcp && tcp->isOpen())
            tcp->close();

        this->error(QAbstractSocket::SocketTimeoutError);
    });

    timer.start(iWaitMsec);

#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
    tcp->connect(tcp,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
#else
    tcp->connect(tcp,SIGNAL(errorOccurred(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
#endif

    /* 累堆疊check要能帶到readyread()，需要存map、清map，有點麻煩
    Packager pp;

    m_kPackger.insert(sId,pp);
    */


    tcp->connectToHost(sIp,sPort.toInt());

    qDebug()<<"return fn";
    return 1;
}


void CTcpClient::error(QAbstractSocket::SocketError error)
{
    qDebug()<<"error : "<<error;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());


    QString sId = tcp->property(CTcp::id).toString();

    if(bSendSignal)
        emit signalReply(sId,QByteArray(),error);
    else
        emit finished(sId,QByteArray(),error);
}

void CTcpClient::slotConnected()
{
    qDebug()<<"connected ";

    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());

    QByteArray data = tcp->property(CTcp::inputData).toByteArray();

    Packager pp(data);

    tcp->write(pp.package());


}

void CTcpClient::slotDisconnected()
{
    qDebug()<<"disconnected";
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());
    tcp->disconnect();
    tcp->deleteLater();
}

void CTcpClient::slotReadyRead()
{
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());

    QString sId = tcp->property(CTcp::id).toString();

    QByteArray readData = tcp->readAll();
    qDebug()<<"ready read len : "<<readData.length();
    bool bOk = false;

    /*
    Packager *pp=&m_kPackger[sId];

    pp->insert(readData);

    bOk =pp->isPackageComplete();
    */

    QByteArray out= tcp->property(CTcp::outputData).toByteArray();

    out.append(readData);

    tcp->setProperty(CTcp::outputData,out);

    Packager check(out);

    bOk = check.isPackageComplete();

    if(bOk)
    {
        tcp->close();

        QByteArray re =check.unPackage();

        qDebug()<<"send len : "<<re.length();

        if(bSendSignal)
            emit signalReply(sId,re,1);
        else
            emit finished(sId,re,1);

    }
}


