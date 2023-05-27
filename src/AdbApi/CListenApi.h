#ifndef CLISTENAPI_H
#define CLISTENAPI_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"
#include "CHttpServerObj.h"

class CHttpServer : public CHttpServerObj
{
    Q_OBJECT
public:

    QString query(QString method, QString path, QString args) override;


};




class CListenApi : public QObject
{
    Q_OBJECT
public:
    explicit CListenApi(QObject *parent = nullptr);

    void startRESTfulApi(QString sPort);

private:

    CHttpServer m_httpServer;



signals:

public slots:



};

#endif // CLISTENAPI_H
