#ifndef CLISTENAPI_H
#define CLISTENAPI_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"

class CListenApi : public QObject
{
    Q_OBJECT
public:
    explicit CListenApi(QObject *parent = nullptr);

    void listen(QString sPort);

    QByteArray encodeHttp(QString sData);
signals:

public slots:

    void getData(QByteArray dData, uintptr_t handleId);

    void getHttpRequest(QByteArray path, QByteArray method, uintptr_t handleId);

};

#endif // CLISTENAPI_H
