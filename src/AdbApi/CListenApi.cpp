#include "CListenApi.h"

CListenApi::CListenApi(QObject *parent)
    : QObject{parent}
{



}

void CListenApi::startRESTfulApi(QString sPort)
{
    m_httpServer.listen(sPort);
}



//===============================================

QString CHttpServer::query(QString method, QString path, QString args)
{
    qDebug()<<" method : "<<method<<" , path : "<<path<<" , args : "<<args;

    QString sSendData ="test data!";


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
