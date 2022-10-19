#include "QueryObj.h"




QueryObj::QueryObj(QObject *parent)
    : QObject{parent}
{
  //  connect(&m_sql,&CSqlClass::tbUpdate,this,&QueryObj::updateTrigger);




}

void QueryObj::linkage(int iApi, QList<int> listApi)
{

    QString sApi =QString::number(iApi);

    QStringList list;

    foreach(int i,listApi)
    {
        list.append(QString::number(i));
    }

    m_dLinkage[sApi]=list;

}

void QueryObj::linkage(int iApi, int iBindApi)
{
    QList<int> list;

    list.append(iBindApi);

    return linkage(iApi,list);
}



void QueryObj::setDataBase(bool bMysql, QString sIp, QString sPort)
{
    if(m_sql.openDb(bMysql,sIp,sPort,"adp"))
        m_dTrigger = m_sql.readTrigger();
}

CData QueryObj::queryData(CData data)
{
    CData re;
    re = implementRecall(data);

    if(re.bOk)
    {
        re.sTrigger = checkUpdate(data.iAciton);
    }
    else
    {
        re.sTrigger="0";
    }

    qDebug()<<"recall api "<<data.iAciton<<", trigger : "<<re.sTrigger;

    return re;
}


QByteArray QueryObj::heartBeat()
{
    QStringList list;

    foreach(QString sKey,m_dTrigger.keys())
    {
        list.append(sKey+"="+m_dTrigger.value(sKey));
    }

    QByteArray bRe;

    bRe.append(list.join(",").toUtf8());

    return bRe;
}

bool QueryObj::isQueryApi(int iApi)
{
    QString sApi =QString::number(iApi);

    return sApi.length()>=4 && sApi.mid(2,1)=="3";

}



QString QueryObj::checkUpdate(int iApi)
{
    QString sTrigger="0";

    QString sTmp = QString::number(iApi);

    while(sTmp.length()<4)
        sTmp="0"+sTmp;

    QString sGroup = sTmp.left(2);


    if(isQueryApi(iApi))
    {
        if(!m_dTrigger.keys().contains(sGroup))
        {
             m_dTrigger[sGroup] ="1";
        }
        else{}

    }
    else
    {
        QString sUpdateTime = QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmss");

        m_dTrigger[sGroup] = sUpdateTime;

        m_sql.saveTrigger(sGroup,sUpdateTime);
    }

      sTrigger = m_dTrigger[sGroup];


    return sTrigger;
}


//void QueryObj::updateTrigger(QString sTableName, QString sDateTime)
//{
//    /*將 sql tableName : dateTime
//      轉換與client 比對的 api : dateTime
//      有可能更動一個table 影響多隻api
//      */
//    using namespace ACT;



//    QVariantMap list;


//    list[SQL_TABLE::ExchangeRate()] =
//            QVariantList()<<QUERY_EXCHANGE;

//    list[SQL_TABLE::PrimeCostRate()] =
//            QVariantList()<<QUERY_PRIMERATE;

//    list[SQL_TABLE::GameList()] =
//            QVariantList()<<QUERY_GAME_LIST;

//    list[SQL_TABLE::GameItem()] =
//            QVariantList()<<QUERY_GAME_ITEM;

//    list[SQL_TABLE::Bulletin()] =
//            QVariantList()<<QUERY_BULLETIN;

//    list[SQL_TABLE::CustomerClass()] =
//            QVariantList()<<QUERY_CUSTOM_CLASS;

//    list[SQL_TABLE::GroupData()] =
//            QVariantList()<<QUERY_GROUP;

//    list[SQL_TABLE::FactoryClass()] =
//            QVariantList()<<QUERY_FACTORY_CLASS;

//    list[SQL_TABLE::UserData()] =
//            QVariantList()<<QUERY_USER;

//    list[SQL_TABLE::CustomerData()] =
//            QVariantList()<<QUERY_CUSTOMER<< LAST_CUSTOMER_ID;

//    list[SQL_TABLE::CustomerGameInfo()] =
//            QVariantList()<<QUERY_CUSTOMER_GAME_INFO;

//    list[SQL_TABLE::CustomerCost()] =
//            QVariantList()<<QUERY_CUSTOMER_COST;

//    list[SQL_TABLE::OrderData()] =
//            QVariantList()<<QUERY_ORDER<<LAST_ORDER_ID<<LAST_ORDER_NAME;

//    list[SQL_TABLE::PayType()] =
//            QVariantList()<<QUERY_PAY_TYPE;

//    list[SQL_TABLE::UserBonus()] =
//            QVariantList()<<QUERY_BOUNS;

//    list[SQL_TABLE::Schedule()] =
//            QVariantList()<<QUERY_SCHEDULE;




//    QVariantList tmp = list[sTableName].toList();

//    for(int i=0;i<tmp.length();i++)
//    {
//        QString sApi = tmp.at(i).toString();

//        m_dTrigger[sApi] = sDateTime;
//    }



//}




