#include "CPing.h"

CPing::CPing(QObject *parent)
    : QThread{parent}
{
//    QObject::connect(&pingProcess, &QProcess::readyReadStandardOutput, [&]() {

//        QByteArray output = pingProcess.readAllStandardOutput();

//        qDebug() << output;
//    });


    // 连接QProcess的finished信号，表示进程完成
  //  QObject::connect(&pingProcess, SIGNAL(finished(int, QProcess::ExitStatus)),this, SLOT(slotProcessExit(int , QProcess::ExitStatus )));
}

void CPing::setIp(QString sIp)
{
    QMutex lock;

    lock.lock();
    m_sIp=sIp;

    lock.unlock();
}

void CPing::run()
{
    while(!m_bIsStop)
    {
        qDebug()<<"run";
        ping();
        sleep(1);
    }

}

void CPing::ping()
{

    if(m_sIp=="")
        return;

    // 创建QProcess对象

    // 设置命令行命令和参数
    QStringList arguments;
    arguments << "-c" << "4 " << m_sIp; // 测试用的目标主机


    pingProcess.start("ping", arguments);

    qDebug()<<"ping "<<arguments;


}

void CPing::slotProcessExit(int , QProcess::ExitStatus )
{
    qDebug()<<"do something";
}
