#include "CHttpServerObj.h"

CHttpServerObj::CHttpServerObj(QObject *parent)
    : QObject{parent}
{
    RPKCORE;

    connect(&RPKCORE.network,SIGNAL(signalReadOrigin(QByteArray,uintptr_t)),this,SLOT(getData(QByteArray,uintptr_t)));


}

void CHttpServerObj::listen(QString sPort)
{
    RPKCORE.network.runTcpServer(sPort);
}


void CHttpServerObj::getData(QByteArray dData, uintptr_t handleId)
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

    QString method = methodAndPath[0];
    QString path = methodAndPath[1];

    QString args ="";

    if(path.contains("?"))
    {
        path =path.split("?").first();

        args =path.split("?").last();
    }


    QString sReply=query(method,path,args);

    RPKCORE.network.recallClient(encodeHttp(sReply),handleId,false);

}



QByteArray CHttpServerObj::encodeHttp(QString sData)
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

QString CHttpServerObj::query(QString method, QString path, QString args)
{

    qDebug()<<" method : "<<method<<" ,ori path : "<<path<<" , args : "<<args;

    QString sSendData ="test data!";

    path.replace("/api","/");
    path.replace("/apiTest","/");

	qDebug()<<"path: "<<path;


    if(path=="/test" && method.toUpper()=="GET")
    {
        qDebug()<<"reply : "<<sSendData;



    }
    else
    {
        sSendData="400 Bad Request";

        // 不知哪來的/favicon.ico  不處理


    }

    return sSendData;
}



