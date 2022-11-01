#include "CSqlClass.h"

CSqlClass::CSqlClass(QObject *parent)
    : QObject{parent}
{
    bool bOk = RPKCORE.database.openDb("local.db");

    m_local = RPKCORE.database.getDb(0);



    qDebug()<<"open local sql save"<<bOk;



}


bool CSqlClass::insertTb(QString sTableName, QVariantMap input, QString &sError,bool bOrRplace)
{


    QVariantMap data = input;

    QString sDateTime =currentDateTime().toString("yyyyMMddhhmmss");

    if(data.keys().indexOf("UpdateTime")<0 || data["UpdateTime"].toString().trimmed()=="")
        data["UpdateTime"] =sDateTime;

    QStringList listKey = data.keys();

    if(listKey.indexOf("Sid")>=0)
    {
        if(data["Sid"].toString()=="")
        {
            listKey.removeOne("Sid");
        }

    }


    QSqlQuery query(m_db);

    QString sTmp="INSERT";
    if(bOrRplace)
        sTmp="REPLACE";

    QString sCmd = sTmp+" INTO "+sTableName+" (%1) "
                                            " VALUES(%2);";

    QString tmpKey,tmpValue;

    for(int i=0;i<listKey.length();i++)
    {
        QString sKey = listKey.at(i);
        if(i!=0)
        {
            tmpKey+=",";
            tmpValue+=",";
        }


        tmpKey+=sKey;
        tmpValue+="?";

    }

    sCmd = sCmd.arg(tmpKey,tmpValue);



    query.prepare(sCmd);

    qDebug()<<"cmd : "<<sCmd;
    for(int j=0;j<listKey.length();j++)
    {
        QString sKey = listKey.at(j);

        query.bindValue(j,data[sKey]);

        qDebug()<<sKey<< ": "<<data[sKey];

    }

    bool bOk = query.exec();

    sError =  query.lastError().text();
    qDebug()<<"sql : "<<bOk;
    if(bOk)
    {
        // setTrigger(sTableName,sDateTime);
        //db寫入修改記錄、並存在server 的map
    }
    else
        qDebug()<<sError;
    return bOk;

    //ex :
    //  query.prepare("INSERT INTO  UserData (Id,Password,Cid,Name,Lv,StartDay,CreateTime,UpdateTime) "
    //                " VALUES(?,?,?,?,?,?,?,?);");
    //  query.bindValue(0,sId);
    //  query.bindValue(1,sPass);


}

bool CSqlClass::delFromTb(QString sTableName, QVariantMap conditions, QString &sError)
{
    QString sDateTime =currentDateTime().toString("yyyyMMddhhmmss");

    bool bRe =false;
    QSqlQuery query(m_db);
    QString sCmd ="DELETE FROM "+sTableName;


    QString sSub = "";

    QStringList listKey = conditions.keys();

    for(int i=0;i<listKey.length();i++)
    {
        if(i==0)
            sSub+="  WHERE ";
        else
            sSub+=" AND ";

        sSub+= listKey.at(i)+" =? ";

    }

    query.prepare(sCmd+sSub);
    qDebug()<<"del from tb cmd : "<<sCmd+sSub;
    for(int j=0;j<listKey.length();j++)
    {
        query.bindValue(j,conditions[listKey.at(j)]);
        qDebug()<<"bind : "<<conditions[listKey.at(j)];
    }

    bRe = query.exec();

    if(bRe)
    {
        //  setTrigger(sTableName,sDateTime);
    }
    else
        sError = query.lastError().text();

    return bRe;
}

bool CSqlClass::queryTb(QString sTableName, QVariantList &listOut, QString &sError)
{
    QVariantMap v;

    return queryTb(sTableName,v,listOut,sError);

}

bool CSqlClass::queryTb(QString sTableName, QVariantMap conditions, QVariantList &listOut, QString &sError)
{


    listOut.clear();

    QSqlQuery query(m_db);

    QString sCmd = "SELECT * FROM " +sTableName;

    QString sSub = "";

    QStringList listKey = conditions.keys();


    QString sOrderBy="";

    int iCount = 0;

    for(int i=0;i<listKey.length();i++)
    {
        QString sKey = listKey.at(i);
        if(sKey.toUpper()=="ASC")
        {
            sOrderBy =" Order By "+conditions[sKey].toString();
            continue;
        }
        if(sKey.toUpper()=="DESC")
        {
            sOrderBy =" Order By "+conditions[sKey].toString()+" DESC";
            continue;
        }


        if(iCount==0)
            sSub+="  WHERE ";
        else
            sSub+=" AND ";

        sSub+= sKey+" =? ";
        iCount++;
    }

    if(sOrderBy!="")
        sSub=sSub+sOrderBy;

    query.prepare(sCmd+sSub);


    QString sLog="query tb "+sCmd+sSub+" : ";

    QVariantList listTmp;

    iCount =0;
    for(int j=0;j<listKey.length();j++)
    {
        QString sKey =listKey.at(j);
        if(sKey.toUpper()=="ASC" || sKey.toUpper()=="DESC")
            continue;

        query.bindValue(iCount,conditions[sKey]);
        listTmp.append(conditions[sKey]);

        iCount++;
    }

    /*  ex
            query.prepare("SELECT * FROM UserData WHERE Id=:id AND Password =:pass;");
            query.bindValue(":id", sUser.trimmed());
            query.bindValue(":pass",sPass.trimmed());
            query.exec();
            */


    bool bOk = query.exec();

    QStringList listHeader = fieldNames(query.record());

    while(query.next())
    {

        QVariantMap data;

        for(int k=0;k<listHeader.length();k++)
        {
            QString sKey = listHeader.at(k);

            data[sKey] = query.value(sKey);



        }

        listOut.append(data);
    }

    sError =  query.lastError().text();

    qDebug()<<sLog<<listTmp<<" : "<<bOk;

    if(!bOk)
    {
        qDebug()<< sError;

    }


    return bOk;
}

bool CSqlClass::updateTb(QString sTableName, QVariantMap conditions, QVariantMap data, QString &sError)
{
    QString sCmd="UPDATE "+sTableName+" SET ";

    data["UpdateTime"] =currentDateTime().toString("yyyyMMddhhmmss");


    QStringList listKey = data.keys();

    bool bFirst = true;

    for(int i=0;i<listKey.length();i++)
    {
        QVariant v = data[listKey.at(i)];

        if( listKey.at(i) == "Sid" || v.toString().trimmed()=="" || v.isNull())
            continue;

        if(!bFirst)
            sCmd+=" , ";
        sCmd+=listKey.at(i)+" =? ";


        bFirst = false;
    }

    QString sSub="";

    QStringList tmp = conditions.keys();
    for(int i=0;i<tmp.length();i++)
    {
        if(i==0)
        {
            sSub+=" WHERE ";
        }
        else
        {
            sSub+=" AND ";
        }

        QVariant v = conditions[tmp.at(i)];

        if(v.type()==QVariant::Bool)
        {
            v = conditions[tmp.at(i)].toInt();
        }

        if(conditions[tmp.at(i)].type()==QVariant::Char || conditions[tmp.at(i)].type()==QVariant::String)
        {
            sSub+=tmp.at(i)+"='"+conditions[tmp.at(i)].toString()+"' ";
        }
        else
        {
            sSub+=tmp.at(i)+"="+conditions[tmp.at(i)].toString()+" ";
        }
        //sSub+=tmp.at(i)=;
    }

    QSqlQuery sql(m_db);

    sql.prepare(sCmd+sSub);


    qDebug()<<"update tb : "<<sCmd+sSub;
    for(int i=0;i<listKey.length();i++)
    {
        QVariant v=data[listKey.at(i)];

        if( listKey.at(i) == "Sid" || v.toString().trimmed()=="" || v.isNull())
            continue;
        sql.addBindValue(data[listKey.at(i)]);

        qDebug()<<data[listKey.at(i)];
    }


    bool bOk = sql.exec() ;
    qDebug()<<"sql update cmd : "<<sql.lastQuery();
    sError = sql.lastError().text();

    return bOk;
    /*
    QString sCmd="UPDATE UserData SET Password=?,Name=?,Cid=?,Lv=?,ParentId=?,StartDay=? "
                 " ,BirthDay=?,Tel=? ,Email=?,Note1=? ,Note2=?,Note3=? ,CreateTime=? ,UpdateTime=? "
                 " WHERE Id =? ;";
                 */

}



void CSqlClass::createTable()
{

    if(!bRunMysql)
        createTableSqlite();
    else
        createTableMysql();

}

void CSqlClass::createTableSqlite()
{
    QSqlQuery sql(m_db);



    sql.exec("CREATE TABLE 'UserData' ( \
             'Sid'	INTEGER, \
             'Id'	TEXT NOT NULL, \
             'Password'	TEXT NOT NULL, \
             'Name'	TEXT, \
             'Cid'	TEXT, \
             'Lv'	INTEGER DEFAULT 0, \
             'ParentId'	TEXT, \
             'StartDay'	TEXT, \
             'BirthDay'	TEXT, \
             'Tel'	TEXT, \
             'Email'	TEXT, \
             'Note1'	TEXT, \
             'Note2'	TEXT, \
             'Note3'	TEXT, \
             'CreateTime'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'TriggerData' ( \
             'ApiGroup'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('TableName') \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'ExchangeRate' ( \
             'Sid'	INTEGER, \
             'Id'	TEXT, \
             'Name'	TEXT, \
             'UserSid'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'PrimeCostRate' ( \
             'Sid'	INTEGER, \
             'Id'	TEXT, \
             'Name'	TEXT, \
             'UserSid'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'GameList' ( \
             'Sid'	INTEGER, \
             'Id'	TEXT NOT NULL, \
             'Name'	TEXT NOT NULL, \
             'Enable'	INTEGER NOT NULL, \
             'GameRate' TEXT,\
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'GameItem' (  \
             'Sid'	INTEGER,           \
             'GameSid'	INTEGER,        \
             'Enable'	INTEGER DEFAULT 1, \
             'Name'	TEXT,               \
             'OrderNTD'	TEXT,           \
             'Bonus'	TEXT,           \
             'NTD'	TEXT,               \
             'EnableCost'	INTEGER DEFAULT 0, \
             'Cost'	TEXT,                       \
             'AddValueTypeSid' TEXT,       \
             'Note1'	TEXT,           \
             'Note2'	TEXT,           \
             'UpdateTime'	TEXT,       \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();


    sql.exec("CREATE TABLE 'Bulletin' ( \
             'Sid'	INTEGER,            \
             'UserSid'	INTEGER,        \
             'Top'	INTEGER,        \
             'UpdateTime'	TEXT,       \
             'EndTime'	TEXT,       \
             'Title'	TEXT,           \
             'Content'	TEXT,           \
             'Note'	TEXT,               \
             PRIMARY KEY('Sid' AUTOINCREMENT)   \
             );");


    sql.clear();


    sql.exec("CREATE TABLE 'CustomerClass' (      \
             'Sid'	INTEGER,                    \
             'Id'	TEXT NOT NULL,              \
             'Name'	TEXT NOT NULL,              \
             'UpdateTime'	TEXT,               \
             PRIMARY KEY('Sid' AUTOINCREMENT)   \
             );");

    sql.clear();


    sql.exec("CREATE TABLE 'GroupData' (  \
             'Sid'	INTEGER,    \
             'Id'	TEXT,   \
             'Type'	TEXT,   \
             'Name'	TEXT,   \
             'Value'	TEXT,   \
             'Blob'	BLOB,   \
             'UpdateTime'	TEXT,   \
             'Note1'	TEXT,   \
             'Note2'	TEXT,   \
             'NoteBlob'	BLOB,   \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");


    sql.clear();

    sql.exec("CREATE TABLE 'FactoryClass' (      \
             'Sid'	INTEGER,                    \
             'Id'	TEXT NOT NULL,              \
             'Name'	TEXT NOT NULL,              \
             'Currency'	TEXT ,           \
             'PayTypeSid'	TEXT NOT NULL,       \
             'CostRate'	TEXT NOT NULL,              \
             'UpdateTime'	TEXT,               \
             PRIMARY KEY('Sid' AUTOINCREMENT)   \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'CustomerData' (     \
             'Sid'	INTEGER,                    \
             'Id'	TEXT NOT NULL,              \
             'Vip'	TEXT,                       \
             'Class'	TEXT NOT NULL,             \
             'Name'	TEXT,                       \
             'Money'	INTEGER DEFAULT 0,          \
             'Currency'	TEXT,                   \
             'PayType'	TEXT,                   \
             'PayInfo'	TEXT,                   \
             'UpdateTime'	TEXT,               \
             'UserSid'	TEXT,                   \
             'Note1'	TEXT,                       \
             'Note2'	TEXT,                       \
             PRIMARY KEY('Sid' AUTOINCREMENT)    \
             );");

    sql.clear();
    sql.exec("CREATE TABLE 'CustomerGameInfo' (     \
             'Sid'	INTEGER,                            \
             'CustomerId'	TEXT,                           \
             'GameSid'	TEXT,                           \
             'LoginType'	TEXT,                           \
             'LoginAccount'	TEXT,                       \
             'LoginPassword'	TEXT,                       \
             'ServerName'	TEXT,                       \
             'Characters'	TEXT,                           \
             'LastTime'	TEXT,                           \
             'UpdateTime'	TEXT,                       \
             'Note1'	TEXT,                               \
             PRIMARY KEY('Sid' AUTOINCREMENT)            \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'CustomerCost' (        \
             'Sid'	INTEGER,                            \
             'CustomerSid'	TEXT,                       \
             'OrderId'	TEXT,                        \
             'Currency'	TEXT,                               \
             'Rate'	TEXT,                   \
             'AddRate'	TEXT,                   \
             'DebitSid'	TEXT,                               \
             'DebitNote'	TEXT,                               \
             'ChangeValue'	TEXT,                        \
             'TotalCount'	TEXT,                            \
             'TotalSell'	TEXT,                            \
             'UserSid'	TEXT,                           \
             'OrderSid'	TEXT,                            \
             'UpdateTime'	TEXT,                       \
             'OrderTime'	TEXT,                       \
             'Pic0'	TEXT,                               \
             'Pic1'	TEXT,                               \
             'Note0'	TEXT,                               \
             'Note1'	TEXT,                               \
             PRIMARY KEY('Sid' AUTOINCREMENT)            \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'OrderData' (    \
             'Sid'	INTEGER,                \
             'Id'	TEXT,                       \
             'Name'	TEXT,                       \
             'UiRecord'	TEXT,                       \
             'CustomerSid'	TEXT,           \
             'Step'	TEXT,                   \
             'StepTime'	INTEGER,            \
             'User'	TEXT,                   \
             'Owner'	TEXT,                   \
             'PaddingUser'	TEXT,                   \
             'GameSid'	TEXT,                   \
             'Item'	TEXT,                   \
             'Cost'	TEXT,                   \
             'Bouns'	TEXT,                   \
             'ExRateSid'	TEXT,                   \
             'PrimeRateSid'	TEXT,                   \
             'PayType'	TEXT,                   \
             'CanSelectPayType'	TEXT,                   \
             'Money'  TEXT, \
             'Note0'	TEXT,                   \
             'Note1'	TEXT,                   \
             'Note2'	TEXT,                   \
             'Note3'	TEXT,                   \
             'Note4'	TEXT,                   \
             'Note5'	TEXT,                   \
             'Pic0'	TEXT,                               \
             'Pic1'	TEXT,                               \
             'UpdateTime'	TEXT,           \
             'OrderDate'	TEXT,                 \
             'OrderTime'	TEXT,                 \
             PRIMARY KEY('Sid' AUTOINCREMENT)    \
             );");

    sql.clear();

    sql.exec("CREATE TABLE 'PayType' (    \
             'Sid'	INTEGER,                    \
             'Name'	TEXT,                       \
             'Id'	TEXT,                       \
             'UpdateTime'	TEXT,               \
             'Value'	TEXT,                   \
             PRIMARY KEY('Sid' AUTOINCREMENT)   \
             );");

    sql.clear();
    sql.exec("CREATE TABLE 'UserBonus' (   \
             'Sid'	INTEGER,  \
             'UserSid'	TEXT, \
             'OrderSid'	TEXT, \
             'Bonus'	TEXT,     \
             'Pay'	TEXT,    \
             'AddBonus'	TEXT,    \
             'AddPay'	TEXT,    \
             'UpdateTime'	TEXT,    \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();


    sql.exec("CREATE TABLE 'Schedule' ( \
             'Sid'	INTEGER, \
             'Id'	TEXT, \
             'Header'	TEXT, \
             'Data'	TEXT, \
             'UserCheck'	TEXT, \
             'Note'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();
    sql.exec("CREATE TABLE 'PicData' ( \
             'Sid'	INTEGER, \
             'Md5'	BLOB, \
             'Type'	TEXT, \
             'Data'	TEXT, \
             'UpdateTime'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");

    sql.clear();
    sql.exec("CREATE TABLE 'GameItemCount' ( \
             'Sid'	INTEGER, \
              'Id'	TEXT, \
             'GameItemSid'	TEXT, \
             'GameRate'	TEXT, \
             'Name'	TEXT, \
             'UserSid'	TEXT, \
             'ChangeValue'	INTEGER, \
             'Total'	INTEGER, \
             'UpdateTime'	TEXT, \
             'Note'	TEXT, \
            'Pic0'	TEXT, \
            'Pic1'	TEXT, \
             PRIMARY KEY('Sid' AUTOINCREMENT) \
             );");


}

void CSqlClass::createTableMysql()
{

}

QStringList CSqlClass::fieldNames(QSqlRecord record)
{
    QStringList list;

    int iCount = record.count();

    for(int i=0;i<iCount;i++)
    {
        list.append(record.fieldName(i));
    }

    return list;
}

//void CSqlClass::setTrigger(QString sTableName, QString sDateTime)
//{
//    // REPLACE INTO Trigger (TableName,UpdateTime) VALUES(sTableNam,sDateTime);
//    QString sCmd ="REPLACE INTO TriggerData (TableName,UpdateTime) VALUES('%1','%2');";
//    sCmd=sCmd.arg(sTableName,sDateTime);
//    QSqlQuery query(m_db);


//    bool bRe=query.exec(sCmd);

//        qDebug()<<"sCmd : "<<sCmd<<" , "<<bRe;
//    if(bRe)
//        emit tbUpdate(sTableName,sDateTime);
//}

void CSqlClass::saveTrigger(QString sApi, QString sDateTime)
{
    QString sCmd ="REPLACE INTO TriggerData (ApiGroup,UpdateTime) VALUES('%1','%2');";
    sCmd=sCmd.arg(sApi,sDateTime);
    QSqlQuery query(m_db);


    bool bRe=query.exec(sCmd);

    qDebug()<<"sCmd : "<<sCmd<<" , "<<bRe;
    if(bRe)
        emit tbUpdate(sApi,sDateTime);
}

QMap<QString, QString> CSqlClass::readTrigger()
{
    QMap<QString,QString> re;
    QSqlQuery query(m_db);
    query.exec("select * from TriggerData");
    while(query.next())
    {
        QString sApi = query.value(0).toString();

        QString sUpdateTime = query.value(1).toString();

        re[sApi] = sUpdateTime;
    }

    return re;
}

QDateTime CSqlClass::currentDateTime()
{
    return QDateTime::currentDateTimeUtc().addSecs(60*60*8);
}

//void CSqlClass::loadTrigger()
//{

//    QSqlQuery query(m_db);
//    query.exec("select * from TriggerData");
//    while(query.next())
//    {
//        QString sTableName = query.value(0).toString();

//        QString sUpdateTime = query.value(1).toString();

//        emit tbUpdate(sTableName,sUpdateTime);

//    }

//}

bool CSqlClass::checkLogin(QString sUser, QString sPass, QVariantMap &out, QString &sError)
{
    qDebug()<<"user :"<<sUser<<" ,pass:"<<sPass;
    QSqlQuery query(m_db);

    query.prepare("SELECT * FROM UserData WHERE Id=:id AND Password =:pass;");

    query.bindValue(":id", sUser.trimmed());
    query.bindValue(":pass",sPass.trimmed());

    query.exec();

    bool bRe = false;

    QStringList list = fieldNames(query.record());

    if(query.next())
    {
        bRe = true;
        //   iRe=query.value("Lv").toInt();

        for(int i=0;i<list.length();i++)
        {
            QString sKey =  list.at(i);

            out[sKey] = query.value(sKey);
        }


    }

    return bRe;
}

bool CSqlClass::addUser(QString sId, QString sPass, QString sCid, QString sName, int iLv,QString startDate, QString &sError)
{
    bool bRe =false;

    QVariantMap dUser;

    if(queryUser(sId,dUser))
    {
        sError="使用者: "+sId+" 已經存在!";
    }
    else
    {
        bRe = true;

        QSqlQuery query(m_db);

        query.prepare("INSERT INTO  UserData (Id,Password,Cid,Name,Lv,StartDay,CreateTime,UpdateTime) "
                      " VALUES(?,?,?,?,?,?,?,?);");

        query.bindValue(0,sId);
        query.bindValue(1,sPass);
        query.bindValue(2,sCid);
        query.bindValue(3,sName);
        query.bindValue(4,iLv);
        query.bindValue(5,startDate);

        query.bindValue(6,currentDateTime().toString("yyyyMMddhhmmss"));
        query.bindValue(7,currentDateTime().toString("yyyyMMddhhmmss"));

        query.exec();
    }

    return bRe;
}

bool CSqlClass::delUser(QString sId, QString &sError)
{
    bool bRe =false;
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM UserData WHERE Id=? ");
    query.bindValue(0,sId);
    bRe = query.exec();
    if(!bRe)
        sError = "ERROR:4002";
    return bRe;
}

bool CSqlClass::editUser(QVariantMap data, QString &sError)
{
    bool bRe = false;

    QString sCmd="UPDATE UserData SET Password=?,Name=?,Cid=?,Lv=?,ParentId=?,StartDay=? "
                 " ,BirthDay=?,Tel=? ,Email=?,Note1=? ,Note2=?,Note3=? ,CreateTime=? ,UpdateTime=? "
                 " WHERE Id =? ;";

    QSqlQuery query(m_db);

    query.prepare(sCmd);

    query.bindValue(0,data["Password"]);
    query.bindValue(1,data["Name"]);
    query.bindValue(2,data["Cid"]);
    query.bindValue(3,data["Lv"].toInt());
    query.bindValue(4,data["ParentId"]);
    query.bindValue(5,data["StartDay"]);
    query.bindValue(6,data["BirthDay"]);
    query.bindValue(7,data["Tel"]);
    query.bindValue(8,data["Email"]);
    query.bindValue(9,data["Note1"]);
    query.bindValue(10,data["Note2"]);
    query.bindValue(11,data["Note3"]);
    query.bindValue(12,data["CreateTime"]);
    query.bindValue(13,currentDateTime().toString("yyyyMMddhhmmss"));
    query.bindValue(14,data["Id"]);

    bRe = query.exec();



    if(!bRe)
        sError = "ERROR:4003";

    return bRe;
}

bool CSqlClass::queryUser(QString sId, QVariantMap &sData)
{

    bool bRe =false;

    QSqlQuery query(m_db);

    query.prepare("SELECT * FROM UserData WHERE Id= ? ;");
    query.bindValue(0,sId);
    query.exec();
    if(query.next())
    {
        bRe = true;

    }

    return bRe;
}

QVariantList CSqlClass::queryUser(QString sId)
{
    QVariantList listRe;

    QSqlQuery query(m_db);

    QString sCmd = "SELECT * FROM UserData ";

    if(sId!="")
        sCmd +="WHERE Id= '"+sId+"'";

    query.exec(sCmd);

    QStringList listKey = fieldNames(query.record());

    while(query.next())
    {
        QVariantMap t;

        for(int i=0;i<listKey.length();i++)
        {
            t[listKey.at(i)] = query.value(i).toString();
        }

        listRe.append(t);
    }

    return listRe;
}

bool CSqlClass::saveExchange(QVariantList list, QString &sError)
{
    bool bRe =false;

    if(list.length()<1)
    {
        sError = "exchange data error";
        return bRe;
    }



    QVariantMap data = list.first().toMap();



    QStringList listKey,listValue;

    for(int i=0;i<list.length();i++)
    {
        QVariantMap tmp = list.at(i).toMap();

        if(tmp.keys().length()>0)
        {
            QString sKey = tmp.keys().first();

            listKey.append(sKey);

            listValue.append(tmp[sKey].toString());

        }

    }


    QSqlQuery query(m_db);

    query.prepare("INSERT INTO  ExchangeRate (Class,Rate,UpdateTime) "
                  " VALUES(?,?,?);");

    query.bindValue(0,listKey.join(";"));

    query.bindValue(1,listValue.join(";"));

    query.bindValue(2,currentDateTime().toString("yyyyMMddhhmmss"));

    bRe = query.exec();

    return bRe;
}

QVariantList CSqlClass::readExchange(int iSid)
{
    QString sCmd = "SELECT * FROM ExchangeRate ";

    if(iSid!=-1)
        sCmd +=" WHERE Sid= "+QString::number(iSid)+" ;";
    else
        sCmd +=" ORDER BY  Sid ASC ;";

    QSqlQuery query(m_db);

    query.exec(sCmd);

    QVariantList listRe;

    while(query.next())
    {
        QStringList listKey,listValue;

        QVariantMap data;

        data["Sid"] = query.value("Sid").toString();

        data["UpdateTime"] = query.value("UpdateTime").toString();

        listKey.append(query.value("Class").toString().split(";"));

        listValue.append(query.value("Rate").toString().split(";"));

        while(listValue.length()<listKey.length())
        {
            listKey.append("0");
        }


        for(int i=0;i<listKey.length();i++)
        {
            data[listKey[i]] = listValue[i].toDouble();
        }

        listRe.append(data);
    }
    qDebug()<<"rate : "<<listRe;
    return listRe;
}


bool CSqlClass::lsatCustomerId(QString sClassSid, QString sClassId, QString &out, QString &sError)
{
    out = sClassId+"-A000";

    QSqlQuery query(m_db);



    QString sCmd = "SELECT Id FROM CustomerData WHERE Class='%1' ORDER BY Id DESC; ";

    bool bRe = query.exec(sCmd.arg(sClassSid));

    if(query.next())
    {
        out = query.value(0).toString();
    }

    sError = query.lastError().text();

    return bRe;
}

bool CSqlClass::lastCustomerAddCostId(QString sDate, QString &sId, QString &sError)
{
    QString tmpDate = sDate;
    sId=tmpDate.remove(0,2)+"-0000";
    QSqlQuery query(m_db);
   // SELECT * FROM CustomerCost where OrderTime like "%202210%" ORDER BY OrderId DESC;
    QString sCmd = "SELECT * FROM CustomerCost where OrderTime like '%%1%' ORDER BY OrderId DESC;";

    sCmd = sCmd.arg(sDate);

    qDebug()<<"cmd : "<<sCmd;

    bool bRe = query.exec(sCmd);

    if(query.next())
    {
        sId = query.value("OrderId").toString();
    }

    sError = query.lastError().text();


    return bRe;
}

bool CSqlClass::lastOrderId(QString sDate,QString &sId,QString &sError)
{
    QString tmpDate = sDate;
    sId=tmpDate.remove(0,2)+"-A000";
    QSqlQuery query(m_db);

    QString sCmd = "SELECT Id FROM OrderData WHERE OrderDate='%1' ORDER BY Id DESC; ";

    sCmd = sCmd.arg(sDate);

    qDebug()<<"cmd : "<<sCmd;

    bool bRe = query.exec(sCmd);

    if(query.next())
    {
        sId = query.value("Id").toString();
    }

    sError = query.lastError().text();

    return bRe;
}

bool CSqlClass::lastOrderName(QString sOwnerSid, QString sDate, QString &sRe, QString &sError)
{
    QString tmpDate = sDate;
    //sId=tmpDate.remove(0,2)+"-A000";
    QSqlQuery query(m_db);

    QString sCmd = "SELECT Name FROM OrderData WHERE OrderDate='%1' AND Owner='%2' ORDER BY Id DESC; ";

    sCmd = sCmd.arg(sDate).arg(sOwnerSid);

    qDebug()<<"cmd : "<<sCmd;

    bool bRe = query.exec(sCmd);

    sRe="";
    if(query.next())
    {
        sRe = query.value("Name").toString();
    }

    sError = query.lastError().text();

    return bRe;
}

bool CSqlClass::openDb(bool bMysql, QString sIp, QString sPort, QString sDbName)
{
    bool bOk = false;
    if(bMysql)
    {

        qDebug()<< QSqlDatabase::drivers();

        m_db =QSqlDatabase::addDatabase("QMYSQL");
        //m_db =QSqlDatabase::addDatabase("QMYSQL","adp");


        //  m_db.setHostName("206.189.185.20");

        m_db.setHostName(sIp);


        m_db.setPort(sPort.toInt());

        m_db.setUserName("roger");

        m_db.setPassword("Aa111111");

        m_db.setDatabaseName(sDbName);

        bOk = m_db.open();
        qDebug()<<"open mysql : "<<sIp<<" : "<<bOk;

    }

    else
    {

        qDebug()<<"open sqlite";

        bOk = RPKCORE.database.openDb("ADB.db");

        m_db = RPKCORE.database.getDb(1);

        bOk = m_db.isOpen();

    }




    qDebug()<<"db open : "<<bOk;

    if(bOk)
    {
        createTable();

    }

    return bOk;
}




