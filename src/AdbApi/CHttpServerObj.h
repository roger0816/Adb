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

    virtual QString query(QString method, QString path, QString args);



private:

    QByteArray encodeHttp(QString sData);

signals:


private slots:

    void getData(QByteArray dData, uintptr_t handleId);

};

#endif // CHTTPSERVEROBJ_H
