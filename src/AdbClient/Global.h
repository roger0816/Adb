#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include "Action.h"
#include "VojData.h"
#include "DataSync.h"
#include "CPing.h"
#include "UpdateData.h"
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QFuture>

#define GLOBAL Global::Instance()

#define ACTION Global::Instance().m_action

#define QUERY Global::Instance().m_action.m_queryObj



#include <QThread>
#include <QDebug>
#include <QElapsedTimer>






class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    ~Global();

//    GLOBAL_DATA::Data m_data;

    void setServer(bool b = true,QString sIp="127.0.0.1",QString sPort="6000");

    QStringList listMapToList(const QVariantList list,QString sKey);

    bool isDiff(QStringList listKey, QVariantMap pre, QVariantMap current);

    QString displayCurrency(QString st);

    QString originCurrency(QString st);

    QString displayCustomerLv(QString iLv);

    QString sidAdd(QString last);

//    QString addFlow(QString st,QString currency);

//    QString addFlow(QString sDouble,int flowCount);

//    double addFlow(double value, int flowCount=0);

    QVariantList reData(QVariantList data,QStringList listKey);

    QStringList toList(QString sData);

    QString toString(QStringList list);

    QString toString(CListPair listPair);

    CListPair toListPair(QString st);

    QStringList mapping(CListPair listData, QStringList listKey, bool bMappingFirst = true);

    void loadConfig();

    static Global& Instance();

    Action m_action;


    QVariant config(QString st);

    QDateTime dateTimeUtc8();

    QString userLvToStr(int iLv);

    QString encryptSt(const QString &st, const QByteArray &key);

    QString decryptSt(const QString &st, const QByteArray &key) ;

    int m_virtualSec=0;

    bool checkSearch(QString sFilterStr,QVariantMap dTarget,bool caseNeedDiff=false);

    QVariantMap m_copyGameItem;

    QString currencyStr(QString st);

    QString license="";
    QString titleName="";
    QString color1="";
    QString txtColor="";



    void ping(QString sIp);

    bool m_bRootLogin= false;

    QString printTime(QString st);

    void Debug(QString st);

    // 定義通用的函數，接受任務函數和最大等待時間（毫秒）作為參數
    template<typename Func>
    bool runTaskWithTimeout(Func taskFunction, int timeout)
    {
        // 在主線程中初始化 QFutureWatcher
        QFutureWatcher<void> watcher;

        QEventLoop loop;

        // 將 QFutureWatcher 的 finished() 信號連接到事件循環的 quit() 槽
        QObject::connect(&watcher, &QFutureWatcher<void>::finished, &loop, &QEventLoop::quit);

        // 启动任務
        QFuture<void> future = QtConcurrent::run([=, &watcher]() {
            // 在這個線程中執行任務
            taskFunction();
        });

        // 將 QFutureWatcher 與任務關聯起來
        watcher.setFuture(future);

        // 啟動計時器，設置最大等待時間
        QTimer timer;
        timer.setSingleShot(true);
        QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(timeout);

        // 開始事件循環，等待任務完成或超時
        loop.exec();

        // 檢查計時器是否超時
        if (timer.isActive()) {
            // 計時器沒有超時，任務已完成
            timer.stop();
            return true;
        } else {
            // 計時器已超時，任務未能在指定時間內完成
            watcher.cancel(); // 取消任務
            watcher.waitForFinished(); // 等待取消完成
            return false;
        }
    }
    void runWorkerThreadWithTimeout(const std::function<void()> &taskFunction, int timeout) {
        QThread* thread = new QThread;
        QObject::connect(thread, &QThread::started, [=]() {
            // 在新的線程中執行任務
            taskFunction();
            // 任務完成後退出線程
            thread->quit();
            thread->deleteLater();
        });
        // 啟動線程
        thread->start();

        // 設置超時計時器，超時後退出線程
//        QTimer::singleShot(timeout, [=]() {
//            if (thread!=nullptr &&thread->isRunning()) {
//                thread->quit();
//                thread->deleteLater();
//            }
//        });
    }


    void runWorkerThreadWithTimeout2(const std::function<void()> &taskFunction, int timeout) {
        QThread* thread = new QThread;

               QEventLoop loop;
        QObject::connect(thread, &QThread::started, [=,&loop]() {
            // 在新的線程中執行任務
            taskFunction();
            loop.quit();
        });

        // 當任務完成後，退出線程
        QObject::connect(thread, &QThread::finished, thread, &QThread::quit);

        // 啟動線程
        thread->start();


        loop.exec();


        // 設置超時計時器，超時後退出線程
        QTimer::singleShot(timeout, thread, &QThread::quit);
    }

private:
    static Global *m_pInstance;


    QString strNumber(double number);

    QMap<QString,QVariant> m_config;

    CPing m_ping;

    // TimerThread timerThread;
  //  DataSync m_dataSync;




signals:

};

#endif // GLOBAL_H
