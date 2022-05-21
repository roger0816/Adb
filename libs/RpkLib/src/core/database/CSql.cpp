#include "CSql.h"

CSql *CSql::m_pInstance = 0;

static QString KEY_PAIR_TABLE_NAME = "Settings";

CSql::CSql(QObject *parent):QThread(parent)
{

}

CSql::~CSql()
{
    closeDB();
}


bool CSql::openDb(QString sDbName,  QString sUser, QString sPassword,QString sIp, QString sPort,QString sSqldriver)
{

    m_dbType=sSqldriver;

    bool bRe=false;
    // QMYSQL  QSQLITE

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(sSqldriver,sDbName);

    db.setDatabaseName(sDbName);

    if(m_dbType == "QSQLITE")
    {

    }

    else
    {


        db.setPort(sPort.toInt());

        db.setHostName(sIp);

        db.setUserName(sUser);

        db.setPassword(sPassword);

    }
    emit signalLog("db name: "+sDbName);

    emit signalLog("db host name: "+sIp);

    emit signalLog("db port: "+sPort);

    emit signalLog("db User name: "+sUser);

    bRe=db.open();
    
    if(!bRe)
    {
        emit signalLog("ERROR: "+QSqlError(db.lastError()).text());
    }
    else
    {
        emit signalLog("sql open Ok");


    }

    if(bRe)
    {
        QSqlQuery sql(db);

        QString sCmd="CREATE TABLE `"+KEY_PAIR_TABLE_NAME+"` (`key`	TEXT NOT NULL,`value`	TEXT, PRIMARY KEY(`key`));";

        sql.exec(sCmd);

        m_listDb.append(db);
    }

    return bRe;
}

void CSql::closeDB(int iIdx)
{
    if(iIdx==-1)
    {
        foreach(QSqlDatabase db,m_listDb)
            db.close();
    }
    else
    {

        int i = qBound(0,iIdx, m_listDb.length()-1);

        m_listDb[i].close();

    }
}

bool CSql::dbCmd(QString st, int idx)
{
    if(m_listDb.length()<1 || idx>=m_listDb.length())
    {
        qDebug()<<"db no open";

        return false;
    }
    QSqlQuery sql(m_listDb[idx]);

    return sql.exec(st);
}

bool CSql::dbCmd(QString st, QList<QVariantList> &out, int idx)
{

    if(m_listDb.length()<1 || idx>=m_listDb.length())
    {
        qDebug()<<"db no open";

        return false;
    }
    QSqlQuery sql(m_listDb[idx]);

    bool b = sql.exec(st);

    if(b)
    {
        int iRow=0;
        while(sql.next())
        {
            QVariantList list;
            //  qDebug()<<" row : "<<iRow<<"  ,  column count: "<<query.record().count();
            for(int i=0;i<sql.record().count();i++)
            {
                list.append(sql.value(i));
            }
            out.append(list);
            iRow++;
        }

    }

    return b;
}

QList<QVariantList> CSql::getTable(QString sTableName, int idx)
{

    QList<QVariantList> dRe;

    dbCmd("SELECT  * FROM  "+sTableName,dRe,idx);

    return dRe;
 /*
    QString dbCmd="SELECT  * FROM  "+sTableName;

    if(m_listDb.length()<1 || idx>=m_listDb.length())
    {
        qDebug()<<"no open db";

        return dRe;
    }

    QSqlQuery query(m_listDb[idx]);

    QString dbCmd="SELECT  * FROM  "+sTableName;

    query.exec(dbCmd);
    int iRow=0;
    while(query.next())
    {
        QVariantList list;
        //  qDebug()<<" row : "<<iRow<<"  ,  column count: "<<query.record().count();
        for(int i=0;i<query.record().count();i++)
        {
            list.append(query.value(i));
        }
        dRe.append(list);
        iRow++;
    }

    return dRe;
    */
}

int CSql::insertDb(QString sTableName, QMap<QString, QString> list, int idx)
{
    int iRe=-1;

    if(m_listDb.length()<1 || idx>=m_listDb.length())
    {
        qDebug()<<"no open db";

        return iRe;
    }
    //  insert into 資料表名稱(欄位1,欄位2,欄位3,欄位4, ...... 欄位N)
    //  values('值1','值2','值3','值4', ...... '值N');
    // INSERT INTO table1 ( id , name , pwd ) VALUES ( '9', 'Jacky', '54545' );

    QSqlQuery query(m_listDb[idx]);

    QString sColName;

    QString sValues;


    for(int i=0;i<list.count();i++)
    {
        if(i!=0)
        {
            sColName+=",";
            sValues+=",";
        }

        sColName+=list.keys().at(i);
        sValues+="'";
        sValues+=list.values().at(i);
        sValues+="'";

    }

    QString sCmd="INSERT INTO "+sTableName+"(" +sColName+") VALUES ("+sValues +")";

    bool bExe=query.exec(sCmd);

    if(bExe)
        iRe=0;

    return iRe;
}

bool CSql::insertKeyPair(QString sKey, QString sValue, int idx, bool bIsHasKeyDoUpdate)
{

    QString sCmd;

    QString sTmp="";
    if(m_dbType == "QSQLITE")
    {
        if(bIsHasKeyDoUpdate)
            sTmp="OR REPLACE";

        sCmd = "INSERT "+ sTmp+" INTO "+KEY_PAIR_TABLE_NAME+" (key,value) VALUES ('"+sKey+"','"+sValue +"') ";
    }
    else
    {
        sCmd = "INSERT INTO "+KEY_PAIR_TABLE_NAME+" (key,value) VALUES ('"+sKey+"','"+sValue +"') ";

        if(bIsHasKeyDoUpdate)
            sTmp=" ON DUPLICATE KEY UPDATE key = '"+sKey+"', value = '"+sValue+"'";

        sCmd += sTmp;
    }

    return dbCmd(sCmd,idx);


}

bool CSql::updateKeyPair(QString sKey, QString sValue, int idx)
{

    QString sCmd;

    sCmd = "UPDATE "+KEY_PAIR_TABLE_NAME+" SET value = '"+sValue+"' WHERE key = '"+sKey+"'";

    return dbCmd(sCmd,idx);

}

QString CSql::getKeyPair(QString sKey, int idx)
{

    if(m_listDb.length()<1 || idx>=m_listDb.length())
    {
        qDebug()<<"no open db";

        return "";
    }

    QSqlQuery query(m_listDb[idx]);

    QString sCmd="SELECT value FROM "+KEY_PAIR_TABLE_NAME+" where key = '"+sKey+"';";

    query.exec(sCmd);

    QString sRe="";

    while (query.next())
    {
        sRe=query.value("value").toString();
    }

    return sRe;
}
