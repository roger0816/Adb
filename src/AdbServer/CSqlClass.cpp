#include "CSqlClass.h"

CSqlClass::CSqlClass(QObject *parent)
    : QObject{parent}
{
#if 0
    m_db =QSqlDatabase::addDatabase("QMYSQL");

    m_db.setHostName("127.0.0.1");

    m_db.setPort(3306);

    m_db.setUserName("root");

    m_db.setPassword("Aa111111");
#else

    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName("ADB.db");



#endif
    bool bOk = m_db.open();

    qDebug()<<"db open : "<<bOk;
}
