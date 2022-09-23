#include "DataBase.h"
#include "CSql.h"

CSql *sql=nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    sql=new CSql(this);
    sql->connect(sql,SIGNAL(signalLog(QString)),this,SIGNAL(signalLog(QString)));
}

bool DataBase::openDb(QString sDbName, QString sUser, QString sPassword,QString sIp, QString sPort,_db_type type)
{
    QString sSqldrive="QSQLITE";

    if(type==_mysql)
        sSqldrive="QMYSQL";



    return sql->openDb(sDbName,sUser,sPassword,sIp,sPort,sSqldrive);
}

bool DataBase::openDb(QString sDbName)
{
    return openDb(sDbName,"","","","",_sql_lite);
}



void DataBase::closeDb()
{
    sql->closeDB();
}

bool DataBase::dbCmd(QString st)
{
    return sql->dbCmd(st);
}


QSqlDatabase &DataBase::getDb(int idx)
{
    int i= qBound(0,idx,sql->m_listDb.length()-1);
    return sql->m_listDb[i];
}

QList<QVariantList> DataBase::getTable(QString sTableName, int idx)
{
    QList<QVariantList> dRe;
    dRe=sql->getTable(sTableName,idx);
    return dRe;
}

void DataBase::insertDb(QString sTableName, QMap<QString, QString> data,int idx)
{
    sql->insertDb(sTableName,data,idx);
}

bool DataBase::updateKeyPair(QString sKey, QString sValue, int idx)
{
    return sql->updateKeyPair(sKey,sValue,idx);
}

bool DataBase::insertKeyPair(QString sKey, QString sValue, int idx, bool isHaveKeyDoUpdate)
{
    return sql->insertKeyPair(sKey,sValue,isHaveKeyDoUpdate,idx);
}

QString DataBase::getKeyPair(QString sKey, int idx)
{
    return sql->getKeyPair(sKey,idx);
}
