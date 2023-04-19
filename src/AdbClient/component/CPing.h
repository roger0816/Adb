#ifndef CPING_H
#define CPING_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QThread>
#include <QMutex>

class CPing : public QThread
{
    Q_OBJECT
public:
    explicit CPing(QObject *parent = nullptr);

    bool m_bIsStop = false;

    void setIp(QString sIp);

    void run() override;


    QProcess pingProcess;
private:
    QString m_sIp="";

        void ping();


        QMutex m_lock;
signals:

private slots:
    void slotProcessExit(int, QProcess::ExitStatus);


};

#endif // CPING_H
