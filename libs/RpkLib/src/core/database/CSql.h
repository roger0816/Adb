#ifndef CSQL_H
#define CSQL_H

#include <QThread>
#include <QtSql/QtSql>



class CSql : public QThread
{

    Q_OBJECT

public:

    CSql(QObject *parent = 0);

    ~CSql();

    QList<QSqlDatabase> m_listDb;


    static CSql& Instance()
    {
        if(m_pInstance==0)
            m_pInstance=new CSql();
        return *m_pInstance;
    }

    void run(){}

    bool openDb(QString sDbName,  QString sUser, QString sPassword,QString sIp, QString sPort="3306",QString sSqldriver="QSQLITE");

    void closeDB(int iIdx=-1);

    bool dbCmd(QString st,int idx=0);

    bool dbCmd(QString st, QList<QVariantList> &out, int idx=0);

    QList<QVariantList> getTable(QString sTableName,int idx=0);

    int insertDb(QString sTableName,QMap<QString,QString> list,int idx=0);

    bool insertKeyPair(QString sKey ,QString sValue,int idx=0,bool bIsHasKeyDoUpdate = true );

    bool updateKeyPair(QString sKey, QString sValue,int idx=0);

    QString getKeyPair(QString sKey,int idx=0);

signals:
    void signalLog(QString sLog);

private:

    QString m_dbType;
    static CSql* m_pInstance;
};

#endif // CSQL_H
