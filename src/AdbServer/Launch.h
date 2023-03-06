#ifndef LAUNCH_H
#define LAUNCH_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"
#include "Query.h"

class Launch : public QObject
{
    Q_OBJECT
public:
    explicit Launch(QObject *parent = nullptr);

    void setDb(QString sDbIp,QString sDbName="adp");

    void startServer(QString sListenPort="6000");
private:
    Query queryObj;
signals:

public slots:

    void getData(QByteArray dData,uintptr_t handleId);

};

#endif // LAUNCH_H
