#ifndef CLISTENAPI_H
#define CLISTENAPI_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"
#include "CHttpServerObj.h"
#include "CRequestData.h"



class CListenApi : public CHttpServerObj
{
    Q_OBJECT
public:
    explicit CListenApi(QObject *parent = nullptr);

    void startRESTfulApi(QString sPort);

    QString funcGet(bool bIsBrowser,QString path, QVariantMap args) override;
    QString funcPost(bool bIsBrowser,QString path, QVariantMap args) override;


    QString func(bool bIsBrowser,QString path, QVariantMap args) ;

    CRequestData m_request;

private:





signals:

public slots:



};

#endif // CLISTENAPI_H
