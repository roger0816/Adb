#ifndef LAUNCH_H
#define LAUNCH_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"
#include "Action.h"

class Launch : public QObject
{
    Q_OBJECT
public:
    explicit Launch(QObject *parent = nullptr);

private:
    Action act;
signals:

public slots:

    void getData(QByteArray dData,uintptr_t handleId);

};

#endif // LAUNCH_H
