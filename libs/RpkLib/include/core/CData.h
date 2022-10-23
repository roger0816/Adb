#ifndef CDATA_H
#define CDATA_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonDocument>


#define END_DATA "::ENDX::"

#define ACT_SEND 0
#define ACT_RECALL 1

class CData
{

public:
    explicit CData();

    explicit CData(QByteArray data);

    int iAciton=0;

    QString sUser;

    QString sMsg;


    QString sTrigger;


    bool bOk =false;

    int iState = ACT_SEND;

    QVariantList listName;

    QVariantList listData;

    QVariantMap dData;



    QByteArray enCodeJson()
    {

        QVariantMap d;

        d.insert("action",iAciton);
        d.insert("user",sUser);

        d.insert("msg",sMsg);

        d.insert("data",dData);

        d.insert("listName",listName);

        d.insert("listData",listData);

        d.insert("ok",bOk);

        d.insert("status",iState);

        d.insert("trigger",sTrigger);


        QJsonObject obj;

        obj = QJsonObject(QJsonDocument::fromJson(QJsonDocument::fromVariant(QVariant(d)).toJson()).object());

        QByteArray re = QJsonDocument(obj).toJson();

        re.append(QString(END_DATA).toLatin1());

        return   re;


    }

    bool deCodeJson(QByteArray jsonData)
    {
        if(jsonData.length()==0)
            return false;

        QByteArray tmp = QString(END_DATA).toLatin1();

        QByteArray d =jsonData.remove(jsonData.length()-tmp.length(),tmp.length());

        QVariantMap map= QJsonDocument::fromJson(d).toVariant().toMap();


        if(!map["action"].isValid())
            return false;

        iAciton = map["action"].toInt();

        sUser = map["user"].toString();

        sMsg = map["msg"].toString();

        bOk = map["ok"].toBool();

        iState = map["status"].toInt();

        dData = map["data"].toMap();

        listName = map["listName"].toList();

        listData = map["listData"].toList();

        sTrigger = map["trigger"].toString();


        return true;

    };


signals:

};






#endif // CDATA_H
