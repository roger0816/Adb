#ifndef LAUNCH_H
#define LAUNCH_H

#include <QObject>
#include <QDebug>
#include "RpkCore.h"

class Launch : public QObject
{
    Q_OBJECT
public:
    explicit Launch(QObject *parent = nullptr);


signals:

public slots:

    void getData(QByteArray dData);

};

#endif // LAUNCH_H
