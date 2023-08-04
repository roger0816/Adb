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

QString CHttpServerObj::funcGet(QString Path, QVariantMap args)
{
    Q_UNUSED(Path);
    Q_UNUSED(args);
    //override
    return "";
}

QString CHttpServerObj::funcPost(QString Path, QVariantMap args)
{
    Q_UNUSED(Path);
    Q_UNUSED(args);
    //override
    return "";
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

    //    QString args ="";

    //    if(path.contains("?"))
    //    {
    //        path =path.split("?").first();

    //        args =path.split("?").last();
    //    }


    QString sReply=implementRecall(method,path);

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

QString CHttpServerObj::implementRecall(QString method, QString path)
{

    if(path.toLower().contains("favicon.ico"))
        return "";

    m_sOriPath = path;



    if(method.toUpper()=="GET")
    {
        QString sPath = m_sOriPath;

        QVariantMap dArgv;

        bool bHasArgs=getArgs(sPath,dArgv);

        if(bHasArgs)
           sPath = sPath.split("?").first();

        return funcGet(sPath,dArgv);
    }

    else if(method.toUpper()=="POST")
    {
        QString sPath = m_sOriPath;

        QVariantMap dArgv;

        bool bHasArgs=getArgs(sPath,dArgv);

        if(bHasArgs)
           sPath = sPath.split("?").first();

        return funcPost(sPath,dArgv);
    }




}

bool CHttpServerObj::getArgs(QString sOriPath, QVariantMap &reData)
{
    bool bRe= false;

    reData.clear();
    if(sOriPath.split("?").length()>1)
    {
        QString sTmp = sOriPath.split("?").last();

        QStringList list = sTmp.split("&");

        foreach (QString v,list)
        {
            if(v.split("=").length()>1)
            {
                reData[v.split("=").at(0)]=v.split("=").at(1);
            }
        }

    }

    return reData.keys().length()>0;
}

bool CHttpServerObj::dPath(QString sPath, QString sKeyCmd, QString &sSubPath)
{
    qDebug()<<"a "<<sKeyCmd;
    sKeyCmd="/"+sKeyCmd.toLower()+"/";

    qDebug()<<"b "<<sKeyCmd;

    sKeyCmd = sKeyCmd.replace("//","/");




    if(sPath.left(1)!="/")
        sPath="/"+sPath;

    if(sPath.right(1)!="/")
        sPath+="/";

    qDebug()<<"c "<<sKeyCmd<<" , "<<sPath;
    bool bRe = false;


    if(sPath.toLower().contains(sKeyCmd))
    {
        bRe = true;

        sSubPath="";

        if(sPath.split(sKeyCmd).length()>1)
        {
            sSubPath=sPath.split(sKeyCmd).last();
        }
    }

    qDebug()<<"BRE : "<<bRe;

    return bRe;
}





