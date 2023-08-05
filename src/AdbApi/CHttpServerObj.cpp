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

QString CHttpServerObj::funcGet(bool bIsBrowser,QString Path, QVariantMap args)
{
    Q_UNUSED(Path);
    Q_UNUSED(args);
    //override
    return "";
}

QString CHttpServerObj::funcPost(bool bIsBrowser, QString Path, QVariantMap args)
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

    // 判斷是否在瀏覽器上開啟，檢查 User-Agent 標頭
    bool isBrowserRequest = false;
    foreach (QByteArray line, requestLines) {
        if (line.startsWith("User-Agent:")) {
            QString userAgent = line.mid(12).trimmed();
            // 使用正則表達式來判斷是否為瀏覽器請求
            QRegularExpression regex("Mozilla|Chrome|Safari|Edge|Opera");
            QRegularExpressionMatch match = regex.match(userAgent);
            if (match.hasMatch()) {
                isBrowserRequest = true;
                break;
            }
        }
    }


    QString sReply=implementRecall(isBrowserRequest,method,path);

    RPKCORE.network.recallClient(encodeHttp(isBrowserRequest,sReply),handleId,false);

}



QByteArray CHttpServerObj::encodeHttp(bool bIsBrowser,QString sData)
{


#if 1
    bIsBrowser = false;
    // 使用 QJsonDocument::toJson() 獲得壓縮的 JSON 字串
    QJsonDocument jsonDoc=QJsonDocument::fromJson(sData.toUtf8());
    QString jsonData = jsonDoc.toJson(QJsonDocument::Indented);


    QString st;

    if (bIsBrowser) {
        st = "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=utf-8\r\n"
             "Content-Length: %1\r\n"
             "\r\n";

    } else {
        st = "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json; charset=utf-8\r\n"
             "Content-Length: %1\r\n"
             "\r\n";
    }




    QByteArray re;



     QString response = st.arg(jsonData.toUtf8().size())+
             jsonData;
     re.append(response);

//    QByteArray re;
//    re.append(st.arg(sData.length()+50000).arg(jsonData));


//    qDebug()<<"AAAAAA : "<<QString::fromUtf8(re);

    return re;

#else
  bIsBrowser = true;

  // 使用 QJsonDocument::toJson() 獲得壓縮的 JSON 字串
  QJsonDocument jsonDoc = QJsonDocument::fromJson(sData.toUtf8());
  QByteArray jsonData;

  // 如果請求來自瀏覽器，使用 QJsonDocument::toJson(QJsonDocument::Indented) 格式化 JSON 字串
  if (bIsBrowser) {
      jsonData = jsonDoc.toJson(QJsonDocument::Indented);

      QString st = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: text/html; charset=utf-8\r\n"
                   "Content-Length: %1\r\n"
                   "\r\n"
                   "<html><body><pre>%2</pre></body></html>";

      QByteArray re;
      re.append(st.arg(jsonData.length(), 10, 10).arg(QString::fromUtf8(jsonData)));

      qDebug() << "HTTP Response (Browser):\n" << QString::fromUtf8(re);
      return re;
  } else {
      jsonData = jsonDoc.toJson(QJsonDocument::Compact);

      QString st = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: application/json; charset=utf-8\r\n"
                   "Content-Length: %1\r\n"
                   "\r\n"
                   "%2";

      QByteArray re;
      re.append(st.arg(jsonData.length(), 10, 10).arg(QString::fromUtf8(jsonData)));

      qDebug() << "HTTP Response (Non-Browser):\n" << QString::fromUtf8(re);
      return re;
  }

#endif
}

QString CHttpServerObj::implementRecall(bool bIsBrowser,QString method, QString path)
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

        return funcGet(bIsBrowser,sPath,dArgv);
    }

    else if(method.toUpper()=="POST")
    {
        QString sPath = m_sOriPath;

        QVariantMap dArgv;

        bool bHasArgs=getArgs(sPath,dArgv);

        if(bHasArgs)
           sPath = sPath.split("?").first();

        return funcPost(bIsBrowser,sPath,dArgv);
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

    sKeyCmd="/"+sKeyCmd.toLower()+"/";


    sKeyCmd = sKeyCmd.replace("//","/");




    if(sPath.left(1)!="/")
        sPath="/"+sPath;

    if(sPath.right(1)!="/")
        sPath+="/";


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



    return bRe;
}

QString CHttpServerObj::toJsonString(QString sKey,QString sValue)
{

     QVariantMap variantMap;
     variantMap[sKey]=sValue;

    return toJsonString(variantMap);
}

QString CHttpServerObj::toJsonString(QVariantMap d)
{

    // 將 QVariantMap 轉換為 QJsonObject
    QJsonObject jsonObject = QJsonObject::fromVariantMap(d);

    // 使用 QJsonDocument 來創建 JSON 格式的 QByteArray
    QJsonDocument jsonDoc(jsonObject);

    // 使用 toJson 函數將 QJsonDocument 轉換為格式化的 JSON 字串
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // 將 QByteArray 轉換為 QString
    QString jsonString(jsonData);

    return jsonString;
}





