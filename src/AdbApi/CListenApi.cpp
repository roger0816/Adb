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



QString CHttpServer::funcGet(QString path, QVariantMap args)
{
    qDebug()<<" ori path : "<<path<<" , args : "<<args;

    QString sSendData ="";

    QString sSubPath;

    if(dPath(path,"test",sSubPath))
    {

        qDebug()<<"cmd : test , subPath : "<<sSubPath<<" , args: "<<args;

        QStringList listKey = args.keys();

        foreach(QString sKey,listKey)
            sSendData+=sKey+":"+args[sKey].toString()+"\n";

        sSendData+="\n GET Test ok";


        qDebug()<<"reply : "<<sSendData;


    }
    else
    {
        sSendData="400 Bad Request";

        // 不知哪來的/favicon.ico  不處理


    }

    return sSendData;
}
