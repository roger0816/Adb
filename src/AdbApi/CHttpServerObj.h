#ifndef CHTTPSERVEROBJ_H
#define CHTTPSERVEROBJ_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"


class CHttpServerObj : public QObject
{
    Q_OBJECT
public:
    explicit CHttpServerObj(QObject *parent = nullptr);

    void listen(QString sPort);

    virtual QString funcGet(bool bIsBrowser, QString Path, QVariantMap args);

    virtual QString funcPost(bool bIsBrowser,QString Path, QVariantMap args);


    bool dPath(QString sPath,QString sKeyCmd, QString &sSubPath);


    QString toJsonString(QString sKey,QString sValue);

    QString toJsonString(QVariantMap d);

private:

    QByteArray encodeHttp(bool bIsBrowser, QString sData);

    virtual QString implementRecall (bool bIsBrowser, QString method, QString path);

    bool getArgs(QString sOriPath, QVariantMap &reData);

    QString m_sOriPath="";
signals:


private slots:

    void getData(QByteArray dData, uintptr_t handleId);

};

#endif // CHTTPSERVEROBJ_H
