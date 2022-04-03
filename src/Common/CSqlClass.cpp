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

    if(bOk)
        createTable();

    qDebug()<<"db open : "<<bOk;
}

bool CSqlClass::checkLogin(QString sUser, QString sPass, QString &sError)
{
    bool bRe = false;


    QSqlQuery query(m_db);

    query.prepare("SELECT * FROM UserData WHERE Id=:id AND Password =:pass;");

    query.bindValue(":id", sUser.trimmed());
    query.bindValue(":pass",sPass.trimmed());

    query.exec();

    bRe = query.next();

    return bRe;
}

void CSqlClass::createTable()
{

    QSqlQuery sql(m_db);

    sql.exec("CREATE TABLE 'UserData' ( \
              'Sid'	INTEGER, \
              'Id'	TEXT NOT NULL, \
              'Password'	TEXT NOT NULL, \
              'DisplayName'	TEXT, \
              'AccessLv'	INTEGER DEFAULT 0, \
              'ParentId'	TEXT, \
              'CreateTime'	TEXT, \
              'UpdateTime'	TEXT, \
              PRIMARY KEY('Sid' AUTOINCREMENT) \
         );");

    sql.clear();
}
