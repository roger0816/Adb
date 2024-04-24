#include "UpdateData.h"

DataProvider::DataProvider(int iTag, QObject *parent)
    : QObject{parent}
{
    m_iTag = iTag;
}

bool DataProvider::setData(QVariantList data)
{
    if(data.length()<1)
    {
        return false;
    }

    m_bOnSync = true;
    QVariantMap d;
    QVariant v =d["data"];

    foreach(QVariant v ,data)
    {
        m_oriData[v.toMap()["Sid"].toInt()]=v;
    }


    QString sOldDate =m_lastUpdate;

    QList<int> keys=m_oriData.keys();
    // 使用 Qt 的 qSort 函數進行排序
    qSort(keys.begin(), keys.end());

    m_list.clear();

    for(int i=0;i<keys.length();i++)
    {
        QVariant d =m_oriData[keys[i]];
        QString sUpdateTime = d.toMap()["UpdateTime"].toString();
        m_list.append(d);
        if(sUpdateTime>m_lastUpdate)
            m_lastUpdate=sUpdateTime;
    }


    changeData();

    m_bOnSync = false;



    return sOldDate!="0" && m_lastUpdate != sOldDate;
}


//--------------------------------------------------

UpdateData::UpdateData(QObject *parent)
{
    connect(&RPKCORE.network,&Network::singalLongConnect,this,&UpdateData::slotRead);
    m_timer.connect(&m_timer,&QTimer::timeout,this,&UpdateData::slotTimer);
    m_timer.start(1000);

    m_data["OrderData"]= new OrderDataProvider(ORDER_DATA,this);
    m_data["CustomerData"]= new CustomerDataProvider(CUSTOMER_DATA,this);
    m_data["UserData"]= new UserDataProvider(USER_DATA,this);
    m_data["GameList"]= new GameListProvider(GAME_LIST,this);
    m_data["GameItem"]= new GameItemProvider(GAME_ITEM,this);
    m_data["ExchangeRate"]= new ExchangeRateProvider(EXCHANGE_RATE,this);
    m_data["PrimeCostRate"]= new PrimeCostRateProvider(PRIMECOST_RATE,this);
    m_data["BulletinData"]= new BulletinDataProvider(BULLETIN_DATA,this);


    m_listTarget<<"OrderData"<<"CustomerData"<<"UserData"<<"GameList"<<"GameItem"
               <<"ExchangeRate"<<"PrimeCostRate"<<"BulletinData";


    sHhmm=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("hhmm");
}

UpdateData &UpdateData::Instance()
{
    static UpdateData global;
    return global;
}

int UpdateData::connectIp(QString sIp, QString sPort)
{
    int iRe = RPKCORE.network.openConnect(sIp,sPort);
    qDebug()<<"connect update port "<<iRe;
    return iRe;
}

void UpdateData::setRun(bool b)
{
    m_bRun=b;
    if(b){
        QTimer::singleShot(1000,this,[=]{
            runUpdate();
        });

    }
}



void UpdateData::runUpdate()
{
    if(!m_bRun || isOnSync())
    {
        qDebug()<<"run is : "<<m_bRun;
        return;
    }


    QString sTmp=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("hhmm");

    if(sHhmm=="2359" && sTmp=="0000")
        emit updateNotify(ORDER_DATA,QStringList());

    sHhmm = sTmp;


    QVariantMap in;
    QVariantList out;



    for(int i=0;i<m_listTarget.length();i++)
    {
        QString sKey = m_listTarget.at(i);
        in[sKey] = m_data[sKey]->m_lastUpdate;
    }

    qDebug()<<"AAAAAA : send : "<<in;
    //in["OrderDate"]="19990101000000";
    //in["ASC"]="OrderTime";  //不能改顺序，依sid排，因为報價/下單要用
    QString sError;

    CData input;

    input.iAciton = ACT::UPDATE_DATA;

    input.dData = in;

    m_iWaitRecvSec=0;
    qDebug()<<"update port send data : "<<in;
    bool bOk = RPKCORE.network.sendData("",input.enCodeJson());

    qDebug()<<"send data is :"<<bOk;
    if(!bOk)
    {
        QTimer::singleShot(1000,this,[=]{
            runUpdate();
        });
    }



}

QList<OrderData> UpdateData::getOrder()
{

    QList<OrderData> list= dynamic_cast<OrderDataProvider*>(m_data["OrderData"])->m_listData;


    QDateTime currentDateTimeUtc8 = QDateTime::currentDateTimeUtc().addSecs(60*60*8);

    QString sToday=currentDateTimeUtc8.toString("yyyyMMdd");
    QString sYestoday = currentDateTimeUtc8.addDays(-1).toString("yyyyMMdd");

    QList<OrderData> listRe;
    foreach(OrderData v ,list)
    {
        if(v.OrderDate==sToday || v.OrderDate == sYestoday)
            listRe.append(v);

    }

    return listRe;
}

OrderData UpdateData::getOrder(QString sSid)
{
    QList<OrderData> list = getOrder();
    OrderData re;

    for(int i=0;i<list.length();i++)
    {
        if(list.at(i).Sid==sSid)
            re = list.at(i);
    }

    return re;
}

QList<CustomerData> UpdateData::getCustomerList()
{
    return dynamic_cast<CustomerDataProvider*>(m_data["CustomerData"])->m_listData;
}

CustomerData UpdateData::getCustomer(QString sCusId)
{
    QList<CustomerData> list = getCustomerList();

    CustomerData re;

    foreach(CustomerData vData,list)
    {
        if(vData.Sid == sCusId)
        {
            re = vData;

        }
    }

    return re;
}

QList<UserData> UpdateData::getUserList()
{
    return dynamic_cast<UserDataProvider*>(m_data["UserData"])->m_listData;
}

UserData UpdateData::getUser(QString sSid)
{
    QList<UserData> list = getUserList();
    UserData re;

    for(int i=0;i<list.length();i++)
    {
        if(sSid==list.at(i).Sid)
            re =list.at(i);
    }

    return re;
}

QList<DataGameList> UpdateData::getGameList()
{
    return dynamic_cast<GameListProvider*>(m_data["GameList"])->m_listData;
}

DataGameList UpdateData::getGameList(QString sSid)
{
    QList<DataGameList> list = getGameList();

    DataGameList re;

    foreach(DataGameList vData,list)
    {
        if(vData.Sid == sSid)
        {
            re = vData;

        }
    }

    return re;

}

QString UpdateData::getGameName(QString sId)
{
    QString sRe="";

    QList<DataGameList> list = getGameList();

    for(int i=0;i<list.length();i++)
    {
        if(sId==list.at(i).Sid)
        {
            sRe =list.at(i).Name;
            break;
        }
    }
    return sRe;

}

QString UpdateData::getGameId(QString sName)
{
    QList<DataGameList> list = getGameList();
    QString sRe="";

    for(int i=0;i<list.length();i++)
    {
        if(sName==list.at(i).Name)
        {
            sRe =list.at(i).Sid;

            break;
        }
    }

    return sRe;
}

QList<DataGameItem> UpdateData::getGameItem()
{
    return dynamic_cast<GameItemProvider*>(m_data["GameItem"])->m_listData;
}

QList<DataGameItem> UpdateData::getGameItemFromGameSid(QString sGameSid)
{
    QList<DataGameItem> list = getGameItem();

    QList<DataGameItem> re;

    foreach (DataGameItem d, list) {
        if(d.GameSid==sGameSid)
        {
            re.append(d);
        }
    }

    std::sort(re.begin(), re.end(), [](const DataGameItem &a, const DataGameItem &b) {
        return a.Sort < b.Sort;
    });
    return re;
}

 QList<DataRate> UpdateData::costRateList()
{
     QList<DataRate> list = dynamic_cast<ExchangeRateProvider*>(m_data["ExchangeRate"])->m_listData;

     if(list.length()<1)
         list.append(DataRate());

     std::sort(list.begin(), list.end(), [](const DataRate &a, const DataRate &b) {
         return a.Sid < b.Sid;
     });

     return list;
 }

 DataRate UpdateData::costRate(QString sSid)
 {


     QList<DataRate> list = costRateList();

     if(sSid=="")
         return list.last();

     DataRate re;

     foreach(DataRate v,list)
     {
         if(v.Sid==sSid)
             re = v;
     }

     return re;
 }

 QVariantList UpdateData::getBulletin()
 {
     return dynamic_cast<BulletinDataProvider*>(m_data["BulletinData"])->m_listData;
 }






//-------------------------------------------------


void UpdateData::slotRead(QString sConnect, QString sId, QByteArray data, int Error)
{
    qDebug()<<"connect : "<<sConnect<<" , sId : "<<sId;
    m_iWaitRecvSec=0;
    CData tmp;
    tmp.deCodeJson(data);
    QVariantMap reData = tmp.dData;
    qDebug()<< reData.keys();


    foreach(QString sTarget,m_listTarget)
    {
        if(reData.contains(sTarget) && m_data.contains(sTarget))
        {
            QVariantList list =reData[sTarget].toList();

            QStringList listSid;

            foreach(QVariant v,list)
            {
                listSid.append(v.toMap()["Sid"].toString());
            }

            bool bIsUpdate = m_data[sTarget]->setData(list);
            if(bIsUpdate)
                emit updateNotify(m_data[sTarget]->m_iTag,listSid);

        }
    }



    QTimer::singleShot(2000,this,[=]{
        runUpdate();
    });

}


void UpdateData::slotTimer()
{
    m_iWaitRecvSec++;

    if(m_iWaitRecvSec>=10)
        runUpdate();
}

bool UpdateData::isOnSync()
{

    QStringList listKey =m_data.keys();
    for(int i=0;i<listKey.length();i++)
    {
        if(m_data[listKey.at(i)]->m_bOnSync)
        {
            qDebug()<<listKey.at(i)<<"  is on sync";
            return true;
        }
    }


    return false;
}

