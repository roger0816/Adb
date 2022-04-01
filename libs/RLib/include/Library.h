#ifndef LIBRARY_H
#define LIBRARY_H
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QVariantList>
#include "Network.h"
#include "DataBase.h"
#include "Ipc.h"
#include "Utility.h"


#define LIB Library::Instance()


using namespace _db;

class Library :public QObject
{
Q_OBJECT
public:
    Library();
    QString LibTest();

    Network *network();

    DataBase *database();

    Ipc *ipc();

    Utility utility;

    /**
     * @brief Instance singleton design pattern
     * @return
     */
    static Library& Instance()
    {
        if(m_pInstance==0)
            m_pInstance=new Library();
        return *m_pInstance;
    }



private:
    static Library* m_pInstance;

    Network *m_network;

    DataBase *m_database;

    Ipc *m_ipc;

signals:
    void signalLog(QString st);


   // void signalTcpServerReadAll(QByteArray arr);



};

#endif // LIBRARY_H
