#ifndef DATASYNC_H
#define DATASYNC_H

#include <QObject>
#include <QTimer>
#include "Action.h"

class DataSync : public QObject
{
    Q_OBJECT
public:
    explicit DataSync(QObject *parent = nullptr);


signals:

private slots:


};

#endif // DATASYNC_H
