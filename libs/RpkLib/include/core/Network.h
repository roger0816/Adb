#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QStringList>
#include "CData.h"
//#include <QVariantMap>
//#include <QJsonObject>
//#include <QJsonDocument>

//#define END_DATA "::ENDX::"

//#define ACT_SEND 0
//#define ACT_RECALL 1

//struct CData
//{
//    int iAciton;

//    QString sUser;

//    QString sMsg;

//    bool bOk;

//    int iState = ACT_SEND;

//    QVariantList listName;

//    QVariantList listData;

//    QVariantMap dData;

//    QByteArray enCodeJson()
//    {

//        QVariantMap d;

//        d.insert("action",iAciton);
//        d.insert("user",sUser);

//        d.insert("msg",sMsg);

//        d.insert("data",dData);

//        d.insert("listName",listName);

//        d.insert("listData",listData);

//        QJsonObject obj;

//        obj = QJsonObject(QJsonDocument::fromJson(QJsonDocument::fromVariant(QVariant(d)).toJson()).object());

//        QByteArray re = QJsonDocument(obj).toJson();

//        re.append(QString(END_DATA).toLatin1());

//        return   re;


//    }

//    bool deCodeJson(QByteArray jsonData)
//    {
//        QByteArray tmp = QString(END_DATA).toLatin1();

//        QByteArray d =jsonData.remove(jsonData.length()-tmp.length(),tmp.length());

//        QVariantMap map= QJsonDocument::fromJson(d).toVariant().toMap();


//        if(!map["action"].isValid())
//            return false;

//        iAciton = map["action"].toInt();

//        sUser = map["user"].toString();

//        sMsg = map["msg"].toString();

//        dData = map["data"].toMap();

//        listName = map["listName"].toList();

//        listData = map["listData"].toList();


//        return true;

//    };



//};



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

    void recallClient(QByteArray arrReturn, uintptr_t handlerID);


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


    void replyFromServer(QString sId,QByteArray data,int error);


};

#endif // NETWORK_H
