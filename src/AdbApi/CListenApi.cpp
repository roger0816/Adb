#include "CListenApi.h"

CListenApi::CListenApi(QObject *parent)
    : QObject{parent}
{

    RPKCORE;

    connect(&RPKCORE.network,SIGNAL(signalReadOrigin(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));



}

void CListenApi::listen(QString sPort)
{
    RPKCORE.network.runTcpServer(sPort);
}

QByteArray CListenApi::encodeHttp(QString sData)
{
    QString st = "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: %1\r\n"
                 "\r\n"
                 "%2";

    st =st.arg(sData.length()).arg(sData);

    QByteArray re;
    re.append(st.toUtf8());

    return re;
}

void CListenApi::getData(QByteArray dData, uintptr_t handleId)
{

    qDebug()<<"raw data : "<<dData.toStdString().c_str();

    // 解析請求
    QList<QByteArray> requestLines = dData.split('\r\n');
    if (requestLines.isEmpty())
        return;

    // 取得 HTTP 方法和路徑
    QList<QByteArray> methodAndPath = requestLines.first().split(' ');
    if (methodAndPath.size() < 2)
        return;

    QByteArray method = methodAndPath[0];
    QByteArray path = methodAndPath[1];

    getHttpRequest(path,method,handleId);



}

void CListenApi::getHttpRequest(QByteArray path, QByteArray method,uintptr_t handleId)
{
    qDebug()<<"path : "<<path<<" , method : "<<method;

    QString sSendData ="test data!";



    if(path=="/test" && method.toUpper()=="GET")
    {
            qDebug()<<"reply : "<<sSendData;
        RPKCORE.network.recallClient(encodeHttp(sSendData),handleId,false);
    }
    else
    {
        // 不知哪來的/favicon.ico  不處理


    }
}


