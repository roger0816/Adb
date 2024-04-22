#include "CTcpClient.h"
#include "Packager.h"
#include <QDateTime>
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>
static QMap<QString,Packager > m_kPackger;

static QMap<QString,QTcpSocket* > m_kLongConnect;


namespace  CTcp{
const char *id= "id";
const char *inputData ="input";
const char *outputData ="output";
const char *ppKey ="ppKey";
}

bool bSendSignal = true;

CTcpClient::CTcpClient(QObject *parent) : QObject(parent)
{

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

            arrOutput =data;

            iRe = error;
        }

    });


    loop->exec();


    loop->deleteLater();



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


    if(sId.trimmed()=="")
        sId =QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmsszzz");
    QTcpSocket *tcp = new QTcpSocket(this);


    tcp->setProperty(CTcp::id,sId);

    QString sPpKey=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("MMddhhmmsszzz");
    Packager pp;
    m_kPackger.insert(sPpKey,pp);

    tcp->setProperty(CTcp::ppKey,sPpKey);

    tcp->setProperty(CTcp::inputData,arrInput);

    tcp->setProperty(CTcp::outputData,QByteArray());


    tcp->connect(tcp,SIGNAL(connected()),this,SLOT(slotConnected()));

    tcp->connect(tcp,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    tcp->connect(tcp,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

    QTimer timer;

    connect(&timer,&QTimer::timeout,[=]
    {

        this->error(QAbstractSocket::SocketTimeoutError);

        if(tcp && tcp->isOpen())
            tcp->close();

        tcp->disconnect();

        tcp->deleteLater();
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


    return 1;
}

bool CTcpClient::openConnect(QString sIp, QString sPort)
{

    //    QString sConnect = QString::number(QDateTime::currentMSecsSinceEpoch(), 16);

    bool bConnected = false;


    QTcpSocket *tcp = new QTcpSocket(this);


    tcp->setProperty(CTcp::outputData,QByteArray());

    tcp->setProperty("ip",sIp);
    tcp->setProperty("port",sPort);



    connect(tcp, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this,[&bConnected](QAbstractSocket::SocketError socketError) {
        //  qDebug() << "Socket error:" << socketError << "-" << socket->errorString();
        bConnected = false;
    });

    connect(tcp,&QTcpSocket::disconnected,this,[=](){

        if(qobject_cast<QTcpSocket*>(sender())==0)
            return;
        qDebug()<<"disconnected event";
        //    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());
        //QString sKey = tcp->property("ip").toString()+":"+tcp->property("port").toString();
        // m_kLongConnect.remove(sKey);
        //        tcp->disconnect();
        //        tcp->close();
        //        tcp->deleteLater();

    });

    tcp->connect(tcp,&QTcpSocket::readyRead,this,&CTcpClient::slotLongRead);


    tcp->connectToHost(sIp, sPort.toInt());

    QTimer timer;
    timer.setInterval(100); // 100ms 的計時器間隔

    connect(tcp, &QTcpSocket::connected,this, [&bConnected, tcp, &timer]() {
        if (tcp->state() == QAbstractSocket::ConnectedState) {
            qDebug() << "Connected to host.";
            bConnected = true;
            timer.stop();
        }
    });
    timer.start();
    // 等待連接成功或超時
    QEventLoop loop;
    connect(tcp, &QTcpSocket::connected, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    loop.exec();


    if(bConnected)
    {
        m_kLongConnect.insert(sIp+":"+sPort,tcp);
    }

    return bConnected;
}

bool CTcpClient::sendData(QString sId, QByteArray arrInput, QString sIp, QString sPort)
{
    if(m_kLongConnect.isEmpty())
        return false;

    if(sId.trimmed()=="")
        sId =QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmsszzz");


    if(sIp=="" || sPort=="")
    {
        sIp = m_kLongConnect.firstKey().split(":").first();
        sPort = m_kLongConnect.firstKey().split(":").last();
    }

    QTcpSocket *tcp=nullptr;

    if(!m_kLongConnect.contains(sIp+":"+sPort))
        return false;

    tcp = m_kLongConnect.value(sIp+":"+sPort);


    // 確保 QTcpSocket 是處於 ConnectedState 狀態
    if (tcp->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "Socket is not in connected state.";

        // 如果不是，嘗試重新建立連接
        if (!openConnect(sIp, sPort))
        {
            qDebug() << "Failed to reconnect.";
            return false;
        }

        return false;
    }

    tcp->setProperty(CTcp::id,sId);
    tcp->setProperty(CTcp::inputData,arrInput);


    QString sPpKey=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("MMddhhmmsszzz");
    Packager pp(arrInput);
    m_kPackger.insert(sPpKey,pp);

    tcp->setProperty(CTcp::ppKey,sPpKey);


    tcp->write(pp.package());


    return true;
}

bool CTcpClient::connectIsOpen(QString sIp, QString sPort)
{
    return m_kLongConnect.contains(sIp+":"+sPort);
}

void CTcpClient::closeConnect(QString sIp,QString sPort)
{
    QString sConnect = sIp+":"+sPort;
    QTcpSocket *tcp=nullptr;

    if(sConnect=="" && !m_kLongConnect.isEmpty())
    {
        tcp = m_kLongConnect.first();
    }
    else
    {
        if(connectIsOpen(sIp,sPort))
        {
            tcp = m_kLongConnect.value(sConnect);
        }

    }

    if(tcp!=nullptr)
    {
        m_kLongConnect.remove(sConnect);
        tcp->disconnected();
        tcp->close();
        tcp->deleteLater();

    }
}


void CTcpClient::error(QAbstractSocket::SocketError error)
{
    qDebug()<<"error : "<<error;
    if(qobject_cast<QTcpSocket*>(sender())==0)
        return;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());


    QString sId = tcp->property(CTcp::id).toString();

    if(bSendSignal)
        emit signalReply(sId,QByteArray(),error);
    else
        emit finished(sId,QByteArray(),error);

    if(tcp && tcp->isOpen())
        tcp->close();

    tcp->disconnect();

    tcp->deleteLater();
}

void CTcpClient::slotConnected()
{
    if(qobject_cast<QTcpSocket*>(sender())==0)
        return;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());

    QByteArray data = tcp->property(CTcp::inputData).toByteArray();

    Packager pp(data);

    tcp->write(pp.package());


}

void CTcpClient::slotDisconnected()
{
    if(qobject_cast<QTcpSocket*>(sender())==0)
        return;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());
    tcp->disconnect();
    tcp->close();
    tcp->deleteLater();
}

void CTcpClient::slotReadyRead()
{
    if(qobject_cast<QTcpSocket*>(sender())==0)
        return;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());

    QString sId = tcp->property(CTcp::id).toString();

    QByteArray readData = tcp->readAll();

    // qDebug()<<"ready read len : "<<readData.length();
    bool bOk = false;




    QByteArray out= tcp->property(CTcp::outputData).toByteArray();

    out.append(readData);

    tcp->setProperty(CTcp::outputData,out);


    QString sPpKey =tcp->property(CTcp::ppKey).toString();

    Packager *pp=&m_kPackger[sPpKey];

    pp->insert(readData);

    bOk =pp->isPackageComplete();

    if(bOk)
    {
        // tcp->close();

        QByteArray re =pp->unPackage();

        //  qDebug()<<"send len : "<<re.length();

        if(bSendSignal)
        {
            // qDebug()<<"rpk lib send siganl : "<<sId<<" , "<<re;
            emit signalReply(sId,re,1);
        }
        else
            emit finished(sId,re,1);


        m_kPackger.remove(sPpKey);

        if(tcp && tcp->isOpen())
            tcp->close();

        tcp->disconnect();

        tcp->deleteLater();
    }
}

void CTcpClient::slotLongRead()
{

    if(qobject_cast<QTcpSocket*>(sender())==0)
        return;
    QTcpSocket *tcp = dynamic_cast<QTcpSocket*>(sender());

    QString sId = tcp->property(CTcp::id).toString();

    QByteArray readData = tcp->readAll();

    // qDebug()<<"ready read len : "<<readData.length();
    bool bOk = false;



    QByteArray out= tcp->property(CTcp::outputData).toByteArray();

    out.append(readData);

    tcp->setProperty(CTcp::outputData,out);


    QString sPpKey =tcp->property(CTcp::ppKey).toString();

    Packager *pp=&m_kPackger[sPpKey];

    pp->insert(readData);

    bOk =pp->isPackageComplete();

    if(bOk)
    {
        // tcp->close();

        QByteArray re =pp->unPackage();

        //  qDebug()<<"send len : "<<re.length();

        QString sConnect = tcp->property("ip").toString()+":"+tcp->property("port").toString();

        emit singalLongConnect(sConnect, sId,re,1);


        m_kPackger.remove(sPpKey);


    }
}


