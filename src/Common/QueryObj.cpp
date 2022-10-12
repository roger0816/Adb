#include "QueryObj.h"

QueryObj::QueryObj(QObject *parent)
    : QObject{parent}
{

}

CData QueryObj::queryData(CData data)
{
    CData re;

    QString sError;

    QString sOkMsg;

    bool bOk =false;

    if(data.iAciton==ACT::LOGIN)
    {
        int iRe=-1;

        if(data.listData.length()>=2)
        {
            bOk = m_sql.checkLogin(data.listData.first().toString(),data.listData.last().toString(),re.dData,sError);

            re.listData.append(iRe);

        }

        sOkMsg ="登入成功";

    }
    else if(data.iAciton==ACT::ADD_USER)
    {
        while(data.listData.length()<6)
            data.listData.append("");

        bOk = m_sql.addUser(data.listData.at(0).toString(),data.listData.at(1).toString(),
                            data.listData.at(2).toString(),data.listData.at(3).toString(),
                            data.listData.at(4).toInt(),data.listData.at(5).toString(),sError);
    }
    else if(data.iAciton==ACT::DEL_USER)
    {
        bOk = m_sql.delUser(data.dData["Id"].toString(),sError);
    }
    else if(data.iAciton==ACT::QUERY_USER)
    {
        //        bOk = true;

        //        QString sQueryId ="";

        //        if(data.listData.length()>0)
        //            sQueryId =data.listData.first().toString();

        //        re.listData = m_sql.queryUser(sQueryId);



        bOk = m_sql.queryTb(SQL_TABLE::UserData(), data.dData,re.listData,sError);


    }

    else if(data.iAciton==ACT::EDIT_USER)
    {


        bOk = m_sql.editUser(data.listData.first().toMap(),sError);

        //re.listData = m_sql.queryUser(data.sMsg);


    }

    else if(data.iAciton==ACT::SET_VALUE)
    {

    }

    else if(data.iAciton==ACT::GET_VALUE)
    {

    }

    //    else if(data.iAciton==ACT::SAVE_EXCHANGE)
    //    {
    //        bOk = m_sql.saveExchange(data.listData,sError);
    //    }

    //    else if(data.iAciton==ACT::READ_EXCHANGE)
    //    {
    //        bOk = true;

    //        int iIdx = -1;

    //        if(data.listData.length()>0)
    //            iIdx = data.listData.first().toInt();

    //        re.listData = m_sql.readExchange(iIdx);
    //    }

    else if(data.iAciton==ACT::ADD_GAME_LIST)
    {
        bOk = m_sql.insertTb(SQL_TABLE::GameList(),data.dData,sError);
        sOkMsg = "遊戲新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME_LIST)
    {
        QVariantMap d;
        d["Sid"] =data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::GameList(),d ,data.dData,sError);
        sOkMsg = "遊戲修改完成";
    }

    else if(data.iAciton==ACT::DEL_GAME_LIST)
    {
        QVariantMap d;
        d["Sid"] =data.dData["Sid"];
        bOk = m_sql.delFromTb(SQL_TABLE::GameList(),d,sError);


        sOkMsg="遊戲刪除完成";
    }


    else if(data.iAciton==ACT::QUERY_GAME_LIST)
    {

        bOk = m_sql.queryTb(SQL_TABLE::GameList(),re.listData,sError);


    }


    else if(data.iAciton==ACT::ADD_GAME_ITEM)
    {
        bOk = m_sql.insertTb(SQL_TABLE::GameItem(),data.dData,sError);
        sOkMsg = "商品新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME_ITEM)
    {
        qDebug()<<"qeury game item : ";

        qDebug()<<"ll1 : "<<data.listData.length();

        QVariantMap d;

        d["Sid"] = data.dData["Sid"];


        bool bHasList = data.listData.length()>0;

        bOk =true;



        for(int i=0;i<data.listData.length();i++)
        {

            QVariantMap t = data.listData.at(i).toMap();

            QVariantMap tmp ;

            tmp["Sid"] = t["Sid"];

            bool b = m_sql.updateTb(SQL_TABLE::GameItem(),tmp,t,sError);

            if(!b)
                bOk = false;

        }



        if(!bHasList)
        {
            bOk = m_sql.updateTb(SQL_TABLE::GameItem(),d,data.dData,sError);
        }

        sOkMsg="修改完成";

    }

    else if(data.iAciton==ACT::DEL_GAME_ITEM)
    {
        qDebug()<<"qeury game item ";

        QVariantMap d;

        d["Sid"] = data.dData["Sid"];

        bOk = m_sql.delFromTb(SQL_TABLE::GameItem(),d,sError);

        sOkMsg="刪除完成";

    }

    else if(data.iAciton==ACT::QUERY_GAME_ITEM)
    {
        qDebug()<<"qeury game item ";


        bOk = m_sql.queryTb(SQL_TABLE::GameItem(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_BULLETIN)
    {

        bOk = m_sql.insertTb(SQL_TABLE::Bulletin(),data.dData,sError);
        sOkMsg = "公告新增完成";
    }

    else if(data.iAciton==ACT::EDIT_BULLETIN)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::Bulletin(),d,data.dData,sError);
        sOkMsg = "公告修改完成";
    }

    else if(data.iAciton==ACT::DEL_BULLETIN)
    {


        bOk = m_sql.delFromTb(SQL_TABLE::Bulletin(),data.dData,sError);

        sOkMsg ="公告刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_BULLETIN)
    {

        QVariantMap d;

        if(data.listData.length()>0)
            d = data.listData.first().toMap();

        bOk = m_sql.queryTb(SQL_TABLE::Bulletin(),d,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_CUSTOM_CLASS)
    {

        bOk = m_sql.insertTb(SQL_TABLE::CustomerClass(),data.dData,sError);
        sOkMsg = "客戶分類新增完成";
    }

    else if(data.iAciton==ACT::EDIT_CUSTOM_CLASS)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::CustomerClass(),d,data.dData,sError);
        sOkMsg = "客戶分類修改完成";
    }

    else if(data.iAciton==ACT::DEL_CUSTOM_CLASS)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::CustomerClass(),data.dData,sError);

        sOkMsg ="客戶分類刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_CUSTOM_CLASS)
    {

        QVariantMap d;

        if(data.listData.length()>0)
            d = data.listData.first().toMap();

        bOk = m_sql.queryTb(SQL_TABLE::CustomerClass(),d,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_FACTORY_CLASS)
    {

        bOk = m_sql.insertTb(SQL_TABLE::FactoryClass(),data.dData,sError);
        sOkMsg = "廠商新增完成";
    }

    else if(data.iAciton==ACT::EDIT_FACTORY_CLASS)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::FactoryClass(),d,data.dData,sError);
        sOkMsg = "廠商修改完成";
    }

    else if(data.iAciton==ACT::DEL_FACTORY_CLASS)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::FactoryClass(),data.dData,sError);

        sOkMsg ="廠商類型刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_FACTORY_CLASS)
    {

        QVariantMap d;

        if(data.listData.length()>0)
            d = data.listData.first().toMap();

        bOk = m_sql.queryTb(SQL_TABLE::FactoryClass(),d,re.listData,sError);

    }


    else if(data.iAciton==ACT::LAST_CUSTOMER_ID)
    {
        QString sReId="";

        QString sSid = data.dData["Class"].toString();

        QString sId =  data.dData["ClassId"].toString();

        bOk  =m_sql.lsatCustomerId(sSid,sId,sReId,sError);


        re.dData["Id"] = sReId;
    }

    else if(data.iAciton==ACT::ADD_CUSTOMER)
    {


        bOk = m_sql.insertTb(SQL_TABLE::CustomerData(),data.dData,sError);
        sOkMsg = "客戶資料新增完成";
    }

    else if(data.iAciton==ACT::QUERY_CUSTOMER)
    {
        bOk = m_sql.queryTb(SQL_TABLE::CustomerData(),data.dData,re.listData,sError);
    }

    else if(data.iAciton==ACT::EDIT_CUSTOMER)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::CustomerData(),d,data.dData,sError);
        sOkMsg = "客戶資料修改完成";
    }

    else if(data.iAciton==ACT::DEL_CUSTOMER)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.delFromTb(SQL_TABLE::CustomerData(),d,sError);
        qDebug()<<"del costmer data : "<<bOk;
        //

        QVariantMap d2;
        d2["CustomerId"] = data.dData["Id"];
        bool b = m_sql.delFromTb(SQL_TABLE::CustomerGameInfo(),d2,sError);
        if(!b)
            bOk = false;


        //
        QVariantMap d3;
        d3["CustomerSid"] = d["Sid"];
        b = m_sql.delFromTb(SQL_TABLE::CustomerCost(),d3,sError);
        if(!b)
            bOk = false;

        qDebug()<<"del costmer game info : "<<bOk;

        sOkMsg = "客戶資料刪除完成";
    }

    else if(data.iAciton==ACT::ADD_CUSTOMER_COST)
    {
        qDebug()<<"query Add customer cost : "<<data.dData;
        bOk = m_sql.insertTb(SQL_TABLE::CustomerCost(),data.dData,sError);
        sOkMsg = "加值完成";
    }

    else if(data.iAciton==ACT::QUERY_CUSTOMER_COST)
    {
        bOk = m_sql.queryTb(SQL_TABLE::CustomerCost(),data.dData,re.listData,sError);
    }

    else if(data.iAciton==ACT::REPLACE_GAME_INFO)
    {

        bOk = true;
        sOkMsg = "客戶遊戲資料修改完成";

        for(int i=0;i<data.listData.length();i++)
        {

            bool bTmp = m_sql.insertTb(SQL_TABLE::CustomerGameInfo(),data.listData.at(i).toMap(),sError,true);

            if(!bTmp)
            {
                bOk = false;

                sOkMsg = sError;
            }

        }


    }

    else if(data.iAciton==ACT::DEL_GAME_INFO)
    {
        bOk =true;
        for(int i=0;i<data.listData.length();i++)
        {
            QVariantMap d;
            d["Sid"] = data.listData.at(i).toMap()["Sid"];
            bool b = m_sql.delFromTb(SQL_TABLE::CustomerGameInfo(),d,sError);
            if(!b)
                bOk = false;
        }
        sOkMsg = "客戶遊戲資料修改完成";
    }

    else if(data.iAciton==ACT::QUERY_GAME_INFO)
    {
        bOk = m_sql.queryTb(SQL_TABLE::CustomerGameInfo(),data.dData,re.listData,sError);
    }


    else if(data.iAciton==ACT::REPLACE_ORDER)
    {

        bOk = m_sql.insertTb(SQL_TABLE::OrderData(),data.dData,sError,true);

        sOkMsg="訂單送出";

    }
    else if(data.iAciton==ACT::QUERY_ORDER)
    {
        bOk = m_sql.queryTb(SQL_TABLE::OrderData(),data.dData,re.listData,sError);
    }

    else if(data.iAciton==ACT::LAST_ORDER_ID)
    {
        QString sReId="";

        QString sDate = data.dData["OrderDate"].toString();

        bOk  =m_sql.lastOrderId(sDate,sReId,sError);

        re.dData["Id"] = sReId;
    }

    else if(data.iAciton==ACT::LAST_ORDER_NAME)
    {
        QString sReId="";

        QString sDate = data.dData["OrderDate"].toString();
        QString sOwner = data.dData["Owner"].toString();
        bOk  =m_sql.lastOrderName(sOwner,sDate,sReId,sError);

        re.dData["Name"] = sReId;
    }


    //
    else if(data.iAciton==ACT::ADD_PAY_TYPE)
    {


        bOk = m_sql.insertTb(SQL_TABLE::PayType(),data.dData,sError);
        sOkMsg = "新增完成";
    }

    else if(data.iAciton==ACT::QUERY_PAY_TYPE)
    {
        bOk = m_sql.queryTb(SQL_TABLE::PayType(),data.dData,re.listData,sError);
    }

    else if(data.iAciton==ACT::EDIT_PAY_TYPE)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::PayType(),d,data.dData,sError);
        sOkMsg = "修改完成";
    }


    else if(data.iAciton==ACT::ADD_GROUP)
    {


        bOk = m_sql.insertTb(SQL_TABLE::GroupData(),data.dData,sError);
        sOkMsg = "新增完成";
    }

    else if(data.iAciton==ACT::QUERY_GROUP)
    {
        bOk = m_sql.queryTb(SQL_TABLE::GroupData(),data.dData,re.listData,sError);
    }

    else if(data.iAciton==ACT::EDIT_GROUP)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::GroupData(),d,data.dData,sError);
        sOkMsg = "修改完成";
    }

    else if(data.iAciton==ACT::DEL_GROUP)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.delFromTb(SQL_TABLE::GroupData(),d,sError);
        sOkMsg = "刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_PRIMERATE)
    {

        bOk = m_sql.queryTb(SQL_TABLE::PrimeCostRate(),data.dData,re.listData,sError);


    }

    else if(data.iAciton==ACT::ADD_PRIMERATE)
    {
        bOk = m_sql.insertTb(SQL_TABLE::PrimeCostRate(),data.dData,sError);


        sOkMsg = "修改完成";
    }

    else if(data.iAciton==ACT::QUERY_EXCHANGE)
    {

        bOk = m_sql.queryTb(SQL_TABLE::ExchangeRate(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_EXCHANGE)
    {
        bOk = m_sql.insertTb(SQL_TABLE::ExchangeRate(),data.dData,sError);


        sOkMsg = "修改完成";
    }

    else if(data.iAciton==ACT::QUERY_BOUNS)
    {

        bOk = m_sql.queryTb(SQL_TABLE::UserBonus(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_BOUNS)
    {
        bOk = m_sql.insertTb(SQL_TABLE::UserBonus(),data.dData,sError);

        sOkMsg = "修改完成";
    }

    else if(data.iAciton==ACT::QUERY_SCHEDULE)
    {

        bOk = m_sql.queryTb(SQL_TABLE::Schedule(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_SCHEDULE)
    {


        bOk = m_sql.insertTb(SQL_TABLE::Schedule(),data.dData,sError,true);

        sOkMsg = "修改完成";
    }





    re.iAciton = data.iAciton;

    re.bOk = bOk;

    re.sMsg = sError;
    if(bOk)
        re.sMsg = sOkMsg;

    re.iState = ACT_RECALL;

    return re;
}


