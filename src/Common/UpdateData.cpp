#include "UpdateData.h"



UpdateData::UpdateData(QObject *parent)
{
    moveToThread(&m_thread);
    m_thread.start();

    // connect(&RPKCORE.network,&Network::singalLongConnect,this,&UpdateData::slotRead);
    m_timer.connect(&m_timer,&QTimer::timeout,this,&UpdateData::slotTimer);
    m_timer.start(1000);

    m_data["OrderData"]= new OrderDataProvider(ORDER_DATA,this);
    m_data["CustomerData"]= new CustomerDataProvider(CUSTOMER_DATA,this);
    m_data["UserData"]= new UserDataProvider(USER_DATA,this);
    m_data["GameList"]= new GameListProvider(GAME_LIST,this);
    m_data["GameItem"]= new GameItemProvider(GAME_ITEM,this);
    m_data["ExchangeRate"]= new ExchangeRateProvider(EXCHANGE_RATE,this);
    m_data["PrimeCostRate"]= new PrimeCostRateProvider(PRIMECOST_RATE,this);
    m_data["CustomerClass"]= new CustomerClassProvider(CUSTOMER_CLASS,this);
    m_data["FactoryClass"]= new FactoryClassProvider(FACTORY_CLASS,this);
    m_data["PayType"]= new PayTypeProvider(PAY_TYPE,this);
    m_data["UserBonus"]= new UserBonusProvider(USER_BONUS,this);
    m_data["BulletinData"]= new BulletinDataProvider(BULLETIN_DATA,this);


    m_listTarget<<"OrderData"<<"UserData"<<"CustomerData"
               <<"GameList"<<"GameItem"
              <<"ExchangeRate"<<"PrimeCostRate"
             <<"CustomerClass"<<"FactoryClass"
            <<"PayType"<<"UserBonus"<<"BulletinData";


    sHhmm=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("hhmm");
}

UpdateData &UpdateData::Instance()
{
    static UpdateData global;
    return global;
}

//int UpdateData::connectIp(QString sIp, QString sPort)
//{
//    int iRe = RPKCORE.network.openConnect(sIp,sPort);

//    return iRe;
//}

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
        //  qDebug()<<"run is : "<<m_bRun;
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

#if TEST_ACTION
        //if(sKey!="OrderData")
        //     in[sKey]="1";

        in[sKey]=QString::number(iForTestInt%10);

#endif
    }


    //in["OrderDate"]="19990101000000";
    //in["ASC"]="OrderTime";  //不能改顺序，依sid排，因为報價/下單要用
    QString sError;

    CData input;

    input.iAciton = ACT::UPDATE_DATA;

    input.dData = in;
    input.sUser = m_sUserSid;


    m_iWaitRecvSec=0;

    emit callUpdate(input.enCodeJson());

    //    bool bOk = RPKCORE.network.sendData("",input.enCodeJson());

    //    qDebug()<<"send data is :"<<bOk;
    //    if(!bOk)
    //    {
    //        QTimer::singleShot(500,this,[=]{
    //            runUpdate();
    //        });
    //    }



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
        {

            listRe.append(v);
        }


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

QList<OrderData> UpdateData::getOrderByDate(QDate date)
{
    QList<OrderData> list;

    //todo

    return list;
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

QList<DataGameItem> UpdateData::getGameItemList()
{
    return dynamic_cast<GameItemProvider*>(m_data["GameItem"])->m_listData;
}

DataGameItem UpdateData::getGameItem(QString sSid)
{
    QList<DataGameItem> list = getGameItemList();

    DataGameItem re;

    foreach (DataGameItem d, list) {
        if(d.Sid==sSid)
        {
            re = d;
        }
    }
    return re;
}

QList<DataGameItem> UpdateData::getGameItemFromGameSid(QString sGameSid)
{
    QList<DataGameItem> list = getGameItemList();

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

QString UpdateData::findGameSid(QString sGameItemSid)
{
    QList<DataGameItem> list = getGameItemList();

    for(int i=0;i<list.length();i++)
    {
        DataGameItem v =list.at(i);

        if(v.Sid==sGameItemSid)
            return v.GameSid;
    }
    return "";
}

double UpdateData::getGameItemPayCount(QString sGameItemSid, QString sPaySid)
{
    double iRe = 0;

    DataGameItem item = getGameItem(sGameItemSid);

    QStringList listTmp = item.AddValueTypeSid.split(";;");

    for(int i=0;i<listTmp.length();i++)
    {
        QString pay = listTmp.at(i).split(",,").first();

        double iCount = listTmp.at(i).split(",,").last().toDouble();

        if(pay==sPaySid)
        {
            iRe=iCount;
        }
    }


    return iRe;
}

QList<DataRate> UpdateData::costRateList()
{
    QList<DataRate> list = dynamic_cast<ExchangeRateProvider*>(m_data["ExchangeRate"])->m_listData;

    if(list.length()<1)
        list.append(DataRate());

    std::sort(list.begin(), list.end(), [](const DataRate &a, const DataRate &b) {
        return a.Sid.toInt() < b.Sid.toInt();
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

QList<DataRate> UpdateData::primeRateList()
{
    QList<DataRate> list = dynamic_cast<PrimeCostRateProvider*>(m_data["PrimeCostRate"])->m_listData;

    if(list.length()<1)
        list.append(DataRate());

    std::sort(list.begin(), list.end(), [](const DataRate &a, const DataRate &b) {
        return a.Sid.toInt() < b.Sid.toInt();
    });

    return list;
}

DataRate UpdateData::primeRate(QString sSid)
{
    QList<DataRate> list = primeRateList();

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

QList<DataCustomerClass> UpdateData::getCustomerClassList()
{
    return dynamic_cast<CustomerClassProvider*>(m_data["CustomerClass"])->m_listData;
}

DataCustomerClass UpdateData::getCustomerClass(QString sSid)
{
    QList<DataCustomerClass> list = getCustomerClassList();

    DataCustomerClass re;

    foreach(DataCustomerClass v, list)
    {
        if(v.Sid==sSid)
            re =v;
    }
    return re;
}

QList<DataFactory> UpdateData::getFactoryClassList()
{
    return dynamic_cast<FactoryClassProvider*>(m_data["FactoryClass"])->m_listData;
}

DataFactory UpdateData::getFactoryClass(QString sSid)
{
    QList<DataFactory> list = getFactoryClassList();

    DataFactory re;

    foreach(DataFactory v, list)
    {
        if(v.Sid==sSid)
            re =v;
    }
    return re;
}

QList<DataPayType> UpdateData::getPayTypeList()
{

    return dynamic_cast<PayTypeProvider*>(m_data["PayType"])->m_listData;
}

DataPayType UpdateData::getPayType(QString sSid)
{
    QList<DataPayType> list = getPayTypeList();
    DataPayType re;

    foreach(DataPayType v,list)
    {
        if(v.Sid==sSid)
            re = v;
    }

    return re;
}

CListPair UpdateData::getAddValueType()
{
    return dynamic_cast<PayTypeProvider*>(m_data["PayType"])->m_listAddValueType;
}

QString UpdateData::getAddValueName(QString sSid)
{
    QString sRe="";

    foreach(CPair v, getAddValueType())
    {
        if(v.first==sSid)
            sRe = v.second;
    }

    return sRe;
}

QString UpdateData::getPayRate(QString sPayTypeSid)
{
    DataPayType data=getPayType(sPayTypeSid);

    double re = data.Value[0].toDouble()*data.Value[1].toDouble()
            *data.Value[2].toDouble()*data.Value[3].toDouble()
            /data.SubValue.first().toDouble();


    return QString::number(re,'f',3);;
}

QVariantMap UpdateData::getUserBonus(QString sUserSid)
{
    QVariantList list =dynamic_cast<UserBonusProvider*>(m_data["UserBonus"])->m_listData;

    QVariantMap re;

    foreach(QVariant v,list)
    {
        if(v.toMap()["UserSid"]==sUserSid)
            re=v.toMap();
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
    //qDebug()<<"connect : "<<sConnect<<" , sId : "<<sId;

    m_iWaitRecvSec=0;
    CData tmp;
    tmp.deCodeJson(data);
    QVariantMap reData = tmp.dData;
    // qDebug()<< reData.keys();


    foreach(QString sTarget,m_listTarget)
    {

        if(reData.contains(sTarget) && m_data.contains(sTarget))
        {
            qDebug()<<"slot read : "<<sTarget;
            QVariantList list =reData[sTarget].toList();

            if(list.length()>0)
                qDebug()<<sTarget<<" data len : "<<list.length();

            QStringList listSid;

            for(int i=0;i<list.length();i++)
            {
                QVariantMap v = list.at(i).toMap();
                listSid.append(v["Sid"].toString());

#if TEST_ACTION

                if(sTarget=="OrderData")
                {

                    OrderData da(v);

                    //for test
                    int ii=QRandomGenerator::global()->bounded(2,4);
                    da.Step=QString::number(ii);
                    da.PaddingUser = m_sUserSid;
                    da.OrderDate=QDate::currentDate().addDays(-1).toString("yyyyMMdd");
                    list[i]=da.data();
                }

#endif

            }

            bool bIsUpdate = true;


            bIsUpdate= m_data[sTarget]->setData(list);

#if TEST_ACTION
            bIsUpdate = true;
#endif


            if(bIsUpdate)
            {
                if(m_data[sTarget]->m_bIsFirst)
                {
                    if(sTarget=="OrderData" || sTarget=="BulletinData")
                    {
                             qDebug()<<"update first : "<<sTarget;
                        emit updateNotify(m_data[sTarget]->m_iTag,listSid);
                    }
                }
                else
                {
                    qDebug()<<"update : "<<sTarget;
                    emit updateNotify(m_data[sTarget]->m_iTag,listSid);
                }
            }



        }
    }


    int iDelayTime=2000;

    if(m_runCount<3){
        iDelayTime=500;
        m_runCount++;
    }

    if(m_runCount==2)
        emit firstFinished();

    QTimer::singleShot(iDelayTime,this,[=]{
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
            //  qDebug()<<listKey.at(i)<<"  is on sync";
            return true;
        }
    }


    return false;
}

