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


    void setServer(bool b = true,QString sIp="127.0.0.1",QString sPort="6000");

private:
    QTimer m_timer;

    Action m_act;

    QString m_actId="";

    QString m_sIp;

    QString m_sPort;

signals:

private slots:

    void slotTimer();

    void slotServerRecv(QString sId,QByteArray data,int error);


};

#endif // DATASYNC_H
