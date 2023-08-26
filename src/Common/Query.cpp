#include "Query.h"

Query::Query(QObject *parent)
    : QueryObj{parent}
{

    m_api.m_sql=&m_sql;

    m_api.connect(&m_api,&QueryApi::signalDoOrder,this,&Query::slotApiDoOrder);
}


CData Query::implementRecall(CData data)
{




    if(data.iAciton>=ACT::API_REQUSET && data.iAciton<9900)
    {

        return m_api.api(data);

    }




    CData re;

    QString sError;

    QString sOkMsg;

    bool bOk =false;

    /*    if(data.iAciton==ACT::LOGIN)
    {
        int iRe=-1;


        if(!checkAppVersion(data.sMsg))
        {
            bOk=false;
            sError="版本無法使用，請更新版本";
        }

        else
        {
            QString sUserSid;
            if(data.listData.length()>=2)
            {
                bOk = m_sql.checkLogin(data.listData.first().toString(),data.listData.last().toString(),re.dData,sError);


                re.listData.append(iRe);

            }
            if(bOk)
            {
                sOkMsg ="登入成功";

                QString str=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmss");

                QByteArray s=QCryptographicHash::hash(str.toLatin1(),QCryptographicHash::Md5);

                QString sSession(s.toHex());

                re.dData["Session"]=sSession;
            }
            else
                sError="帳密錯誤";
        }

    }
    else*/ if(data.iAciton==ACT::ADD_USER)
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


        QVariantMap d;
        d["Sid"] =data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::UserData(),d ,data.dData,sError);


        //re.listData = m_sql.queryUser(data.sMsg);


    }

    else if(data.iAciton==ACT::SET_VALUE)
    {

        bOk = m_sql.insertTb(SQL_TABLE::Settings(),data.dData,sError,true);


    }

    else if(data.iAciton==ACT::GET_VALUE)
    {

        QVariantList listOut;

        bOk = m_sql.queryTb(SQL_TABLE::Settings(),listOut,sError);

        if(bOk&& listOut.length()>0)
            re.dData=listOut.first().toMap();


    }



    else if(data.iAciton==ACT::ADD_GAME_LIST)
    {

        DataGameList game(data.dData);

        DataGameRate gameRate;

        gameRate.Rate=QString::number(game.GameRate);

        gameRate.GameSid = game.Sid;

        gameRate.GameName = game.Name;

        gameRate.UserSid = game.UserSid;

        m_sql.insertTb(SQL_TABLE::GameRate(),gameRate.data(),sError);

        bOk = m_sql.insertTb(SQL_TABLE::GameList(),data.dData,sError);


        sOkMsg = "遊戲新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME_LIST)
    {
        QVariantMap d;
        d["Sid"] =data.dData["Sid"];


        DataGameList game(data.dData);

        DataGameRate gameRate;

        gameRate.Rate=QString::number(game.GameRate);

        gameRate.GameSid = game.Sid;

        gameRate.GameName = game.Name;

        gameRate.UserSid = game.UserSid;

        m_sql.insertTb(SQL_TABLE::GameRate(),gameRate.data(),sError);


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

    else if(data.iAciton==ACT::QUERY_GAME_RATE)
    {
        bOk = m_sql.queryTb(SQL_TABLE::GameRate(),data.dData,re.listData,sError);

        if(bOk && re.listData.length()<1)
        {
            QVariantMap d;
            QVariantList tmpOut;
            d["Sid"]=data.dData["GameSid"];
            m_sql.queryTb(SQL_TABLE::GameList(),d,tmpOut,sError);

            if(tmpOut.length()>0)
            {
                DataGameList game(tmpOut.first().toMap());


                DataGameRate gameRate;

                gameRate.Rate=QString::number(game.GameRate);


                gameRate.GameSid = game.Sid;

                gameRate.GameName = game.Name;

                gameRate.UserSid = game.UserSid;

                m_sql.insertTb(SQL_TABLE::GameRate(),gameRate.data(),sError);

                bOk = m_sql.queryTb(SQL_TABLE::GameRate(),data.dData,re.listData,sError);


            }
        }
    }


    else if(data.iAciton==ACT::ADD_GAME_ITEM)
    {
        bOk = m_sql.insertTb(SQL_TABLE::GameItem(),data.dData,sError);
        sOkMsg = "商品新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME_ITEM)
    {
        qDebug()<<"qeury game item : ";

        QVariantMap d;

        d["Sid"] = data.dData["Sid"];


        bool bHasList = data.listData.length()>0;

        bOk =true;
/*
        QEventLoop *loop=new QEventLoop(this);


                QTimer::singleShot(5000,this,[=](){loop->quit();});
                loop->exec();

                loop->deleteLater();
                */


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

        bOk = m_sql.insertTb(SQL_TABLE::Bulletin(),data.dData,sError,true);
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

        QVariantMap d = data.dData;

        //        if(data.listData.length()>0)
        //            d = data.listData.first().toMap();

        bOk = m_sql.queryTb(SQL_TABLE::Bulletin(),d,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_CUSTOM_CLASS)
    {
        data.dData["Type"] = "group";
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

        QVariantMap d=data.dData;
        d["Type"] = "group";
        bOk = m_sql.queryTb(SQL_TABLE::CustomerClass(),d,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_CUSTOM_DEBIT)
    {
        data.dData["Type"] = "debit";
        bOk = m_sql.insertTb(SQL_TABLE::CustomerClass(),data.dData,sError);
        sOkMsg = "入帳管道新增完成";
    }

    else if(data.iAciton==ACT::EDIT_CUSTOM_DEBIT)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::CustomerClass(),d,data.dData,sError);
        sOkMsg = "入帳管道修改完成";
    }

    else if(data.iAciton==ACT::DEL_CUSTOM_DEBIT)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::CustomerClass(),data.dData,sError);

        sOkMsg ="入帳管道刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_CUSTOM_DEBIT)
    {

        QVariantMap d = data.dData;

        d["Type"] = "debit";
        bOk = m_sql.queryTb(SQL_TABLE::CustomerClass(),d,re.listData,sError);

    }
    //
    else if(data.iAciton==ACT::ADD_DEBIT_CLASS)
    {
        bOk = m_sql.insertTb(SQL_TABLE::DebitClass(),data.dData,sError);
        sOkMsg = "入帳管道新增完成";
    }
    else if(data.iAciton==ACT::EDIT_DEBIT_CLASS)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::DebitClass(),d,data.dData,sError);
        sOkMsg = "入帳管道修改完成";
    }

    else if(data.iAciton==ACT::DEL_DEBIT_CLASS)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.delFromTb(SQL_TABLE::DebitClass(),d,sError);

        sOkMsg ="入帳管道刪除完成";
    }

    else if(data.iAciton==ACT::QUERY_DEBIT_CLASS)
    {

        QVariantMap d = data.dData;
        d["ASC"]="Sort";

        bOk = m_sql.queryTb(SQL_TABLE::DebitClass(),d,re.listData,sError);

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

        DataFactory fac;
        fac.Sid="999";
        fac.Id="未";
        fac.Name="未分配";
        re.listData.append(fac.data());


    }


//    else if(data.iAciton==ACT::LAST_CUSTOMER_ID)
//    {
//        QString sReId="";

//        QString sSid = data.dData["Class"].toString();

//        QString sId =  data.dData["ClassId"].toString();

//        bOk  =m_sql.lsatCustomerId(sSid,sId,sReId,sError);

//        QVariantMap tmp;
//        tmp["Id"]=sReId;

//        re.listData.append(tmp);
//    }

    else if(data.iAciton==ACT::ADD_CUSTOMER)
    {

        bOk = m_sql.insertTb(SQL_TABLE::CustomerData(),data.dData,sError);

        QString sCustomerSid;

        if(bOk)
        {
            QVariantMap tmpV;

            tmpV["Id"]=data.dData["Id"];

            QVariantList tmp;
            m_sql.queryTb(SQL_TABLE::CustomerData(),tmpV,tmp,sError);

            if(tmp.length()>0)
            {
                re.dData["Sid"]=tmp.first().toMap()["Sid"];
            }
            sOkMsg = "客戶資料新增完成";
        }


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
        bOk = m_sql.insertTb(SQL_TABLE::CustomerCost(),data.dData,sError,true);
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

    else if(data.iAciton==ACT::QUERY_CUSTOMER_GAME_INFO)
    {
        bOk = m_sql.queryTb(SQL_TABLE::CustomerGameInfo(),data.dData,re.listData,sError);
    }


    else if(data.iAciton==ACT::REPLACE_ORDER)
    {

        bOk =true;

        OrderData order(data.dData);

        OrderData current;

        if(order.Step=="0")
        {
            bOk = orderStep0(order,sError);
            current = order;

        }
        else
        {

            if(order.Owner=="未分配")
            {
                current = order;
            }

            else
            {
                QVariantMap inTmp;
                QVariantList outTmp;
                inTmp["Sid"] = order.Sid;
                m_sql.queryTb(SQL_TABLE::OrderData(),inTmp,outTmp,sError);

                if(outTmp.length()<1)
                {
                    sError="報價失敗，查詢不到該訂單";
                    bOk = false;
                }
                else
                {
                    current.setData(outTmp.first().toMap());
                }
            }
        }

        //


        if(bOk && order.Step!="0")  //能查詢到當前訂單狀態
        {
            if(order.Step=="-1")
            {
                QString sCountError;
                changeItemCount(order,true,sCountError);
                checkUpdate(ACT::ADD_ITEM_COUNT);
            }

            else if(order.Step=="1")
            {

                bOk = orderStep1(order,current,sError);

            }
            else if(order.Step=="2")
            {
                bOk = orderStep2(order,current,sError);
            }
            else if(order.Step=="3")
            {
                bOk = orderStep3(order,current,sError);
            }
            else if(order.Step=="4")
            {


                bOk =true;
                //0         報價 送出
                //1         下單 送出
                //2         接單儲值 鎖定
                //3         接單儲值 送出
                //3+padding 回報 鎖定
                //4         回報 送出
                //5         確認 送出
                //10        報價+下單
            }
            //只為了拆開fn， 羅輯比較好讀



        }





        if(bOk)
            bOk = m_sql.insertTb(SQL_TABLE::OrderData(),order.data(),sError,true);

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

        QVariantMap tmp;
        tmp["Id"]=sReId;

        re.listData.append(tmp);
    }

    else if(data.iAciton==ACT::LAST_CUSTOMER_COST_ID)
    {
        QString sReId="";

        //  QString sDate = data.dData["OrderTime"].toString();
        QString sDate =QDate::currentDate().toString("yyyyMMdd");
        bOk  =m_sql.lastCustomerAddCostId(sDate,sReId,sError);

        QVariantMap tmp;
        tmp["OrderId"]=sReId;

        re.listData.append(tmp);
    }


    else if(data.iAciton==ACT::LAST_ORDER_NAME)
    {
        QString sReId="";

        QString sDate = data.dData["OrderDate"].toString();
        QString sOwner = data.dData["Owner"].toString();
        bOk  =m_sql.lastOrderName(sOwner,sDate,sReId,sError);

        QVariantMap tmp;
        tmp["Name"] =sReId;

        re.listData.append(tmp);
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

    else if(data.iAciton==ACT::DEL_PAY_TYPE)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::PayType(),data.dData,sError);
        sOkMsg = "刪除完成";
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
    else if(data.iAciton==ACT::ADD_SCHEDULE)
    {


        bOk = m_sql.insertTb(SQL_TABLE::Schedule(),data.dData,sError,true);

        sOkMsg = "修改完成";
    }

    else if(data.iAciton==ACT::QUERY_SCHEDULE)
    {

        bOk = m_sql.queryTb(SQL_TABLE::Schedule(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::UPLOAD_PIC)
    {


        //bOk = m_sql.insertTb(SQL_TABLE::PicData(),data.dData,sError,true);
        setPic(data.dData);
        bOk = true;
        sOkMsg = "圖片上傳完成";
    }

    else if(data.iAciton==ACT::QUERY_PIC)
    {

        bOk = m_sql.queryTb(SQL_TABLE::PicData(),data.dData,re.listData,sError);

    }

    else if(data.iAciton==ACT::ADD_ITEM_COUNT)
    {

        QString sItemSid = data.dData["GameItemSid"].toString();
        DataGameItem item = getGameItem(sItemSid);

        data.dData["GameSid"]=item.GameSid;
        data.dData["Name"] = item.Name;
        bOk = m_sql.insertTb(SQL_TABLE::GameItemCount(),data.dData,sError);

        updateCount(item.GameSid,item.Sid,item.Name,data.dData["TotalSell"].toLongLong(),data.dData["TotalCount"].toLongLong());

        sOkMsg = "新增完成";

    }

    else if(data.iAciton==ACT::EDIT_ITEM_COUNT)
    {

        QString sItemSid = data.dData["GameItemSid"].toString();
        DataGameItem item = getGameItem(sItemSid);

        data.dData["GameSid"]=item.GameSid;
        data.dData["Name"] = item.Name;

        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::GameItemCount(),d,data.dData,sError);

        if(data.dData.keys().contains("TotalCount")
                && data.dData["TotalCount"].toInt()>0)
        {
            updateCount(item.GameSid,item.Sid,item.Name,data.dData["TotalSell"].toLongLong(),data.dData["TotalCount"].toLongLong());

        }


        sOkMsg = "修改完成";





    }

    else if(data.iAciton==ACT::DEL_ITEM_COUNT)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::GameItemCount(),data.dData,sError);

        sOkMsg ="刪除完成";

    }


    else if(data.iAciton==ACT::QUERY_ITEM_COUNT)
    {
        //  qDebug()<<"a1 : "<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        bOk = m_sql.queryTb(SQL_TABLE::GameItemCount(),data.dData,re.listData,sError);
        //  qDebug()<<"a2 : "<<QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    }


    else if(data.iAciton==ACT::PAY_ADD)
    {

        QVariantMap costData = data.dData["CostData"].toMap();

        QVariantMap customerData = data.dData["CustomerData"].toMap();


        QString oldTotal="0";
        QVariantList listOut;
        QVariantMap in;
        in["CustomerSid"]=customerData["Sid"];
        in["ASC"]="Sid";

        bool b = m_sql.queryTb(SQL_TABLE::CustomerCost(),in,listOut,sError);

        if(b && listOut.length()>0)
            oldTotal=listOut.last().toMap()["Total"].toString();

        double iNewTotal = oldTotal.toDouble()+costData["ChangeValue"].toDouble();

        costData["Total"]=iNewTotal;


        customerData["Money"] = costData["Total"];
        CData cost;

        cost.iAciton=ACT::ADD_CUSTOMER_COST;

        cost.dData=costData;

        CData costRe= queryData(cost);

        bOk = costRe.bOk;

        // bOk = m_sql.insertTb(SQL_TABLE::CustomerCost(),costData,sError,true);

        if(bOk)
        {
            qDebug()<<"pay add Ok";
            CData cus;

            cus.iAciton=ACT::EDIT_CUSTOMER;

            cus.dData=customerData;

            CData cusRe= queryData(cus);

            bOk = cusRe.bOk;

            qDebug()<<"edit customer "<<bOk;
            //            QVariantMap d;
            //            d["Sid"] = customerData["Sid"];
            //            bOk = m_sql.updateTb(SQL_TABLE::CustomerData(),d,customerData,sError);


            if(!bOk)
            {

                QVariantMap tmp;
                tmp["Sid"]=costData["Sid"];
                QString sTmp;
                m_sql.delFromTb(SQL_TABLE::CustomerCost(),tmp,sTmp);

            }

        }

        sOkMsg = "加值完成";

        sError="加值失敗 : "+sError;
    }


    else if(data.iAciton==ACT::PAY_ADD_COST)
    {


        CustomerCost costData(data.dData["CostData"].toMap());
        CustomerData cus(data.dData["CustomerData"].toMap());

        QString oldTotal="0";
        QVariantList listOut;
        QVariantMap in;
        in["CustomerSid"]=cus.Sid;
        in["ASC"]="Sid";

        bool b = m_sql.queryTb(SQL_TABLE::CustomerCost(),in,listOut,sError);

        if(b && listOut.length()>0)
            oldTotal=listOut.last().toMap()["Total"].toString();

        double iNewTotal = oldTotal.toDouble()+costData.ChangeValue.toDouble();

        costData.Total=QString::number(iNewTotal,'f',2);


        //    cus.Money = costData.Total;
        CData cost;

        cost.iAciton=ACT::ADD_CUSTOMER_COST;

        cost.dData=costData.data();

        CData costRe= queryData(cost);

        bOk = costRe.bOk;

        // bOk = m_sql.insertTb(SQL_TABLE::CustomerCost(),costData,sError,true);

        if(bOk)
        {
            qDebug()<<"pay add Ok";

            bOk = changeMoney(cus,costData.Total,sError);

        }


        sOkMsg = "加值完成";

        sError="加值失敗 : "+sError;



    }



    else if(data.iAciton==ACT::PAY_ORDER)
    {
        CData tmp=data;
        tmp.iAciton=ACT::REPLACE_ORDER;
        printTime("1");

        CData tmpRe=queryData(tmp);
        printTime("2");


        if(!tmpRe.bOk)
        {
            bOk=tmp.bOk;
            sError=tmp.sMsg;

        }
        else
        {


            /*
            "\nTime : 1 : " "23/01/14 07:47:15:188"
            cmd :  "REPLACE INTO OrderData (Bouns,CanSelectPayType,Cost,CustomerSid,ExRateSid,GameSid,Id,Item,Money,Name,Note0,Note1,Note2,Note3,Note4,Note5,OrderDate,OrderTime,Owner,PaddingUser,PayType,Pic0,Pic1,PrimeRateSid,Sid,Step,StepTime,UiRecord,UpdateTime,User)  VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"
            "\nTime : 2 : " "23/01/14 07:47:16:025"
            "query tb SELECT * FROM CustomerData  WHERE Sid =?  : " (QVariant(QString, "560"))  :  true
            "\nTime : 3 : " "23/01/14 07:47:16:621"
            "query tb SELECT * FROM CustomerCost  WHERE CustomerSid =?  Order By Sid DESC : " (QVariant(QString, "560"))  :  true
            "\nTime : 4 : " "23/01/14 07:47:17:219"
            cmd :  "INSERT INTO CustomerCost (AddRate,ChangeValue,Currency,CustomerSid,DebitNote,DebitSid,IsAddCost,Note0,Note1,OrderId,OrderTime,OriginCurrency,OriginValue,Pic0,Pic1,Rate,Total,UpdateTime,UserSid)  VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"
            "\nTime : 5 : " "23/01/14 07:47:17:837"
            "query tb SELECT * FROM CustomerMoney  WHERE Sid =?  : " (QVariant(QString, "560"))  :  true
            cmd :  "REPLACE INTO CustomerMoney (Currency,Id,Money,Name,Sid,UpdateTime)  VALUES(?,?,?,?,?,?);"
            "\nTime : 6 : " "23/01/14 07:47:19:029"
            sCmd :  "REPLACE INTO TriggerData (ApiGroup,UpdateTime) VALUES('13','20230114074719');"  ,  true
            "\nTime : 7 : " "23/01/14 07:47:19:231"
        */
            CustomerData cus;
            OrderData order;
            order.setData(data.dData);
            getCustomer(order.CustomerSid,cus);

            //check has
            QVariantMap tmpIn;
            QVariantList tmpList;
            tmpIn["OrderId"]=order.Id;
            m_sql.queryTb(SQL_TABLE::CustomerCost(),tmpIn,tmpList,sError);

            // if(tmpList.length()<1)
            {
                printTime("3");

                bool b;
                QVariantMap in;
                QVariantList listOut;
                in["CustomerSid"]=order.CustomerSid;
                in["DESC"]="Sid";

                double preTotal=0;

                listOut.clear();
                b =m_sql.queryTb(SQL_TABLE::CustomerCost(),in,listOut,sError);

                if(b && listOut.length()>0)
                    preTotal=listOut.first().toMap()["Total"].toDouble();

                printTime("4");

                //   QString Error;

                CustomerCost cost;

                int iTmp =qBound(0,3,order.User.length()-1);

                cost.UserSid = order.User.at(iTmp);

                cost.Rate = order.ExRateSid;

                cost.CustomerSid=order.CustomerSid;

                cost.IsAddCost=false;

                cost.Currency = cus.Currency;

                cost.ChangeValue=QString::number(order.Cost.toDouble()*-1,'f',2);

                double tTotal =preTotal+cost.ChangeValue.toDouble();

                cost.Total = QString::number(tTotal,'f',2);

                cost.OrderId = order.Id;

                cost.OrderTime=order.OrderDate+order.OrderTime;

                m_sql.insertTb(SQL_TABLE::CustomerCost(),cost.data(),sError);
                printTime("5");

                changeMoney(cus, cost.Total,sError);

                printTime("6");



                checkUpdate(ACT::ADD_CUSTOMER_COST);
                //   checkUpdate(ACT::REPLACE_ORDER);

                printTime("7");

                bOk=true;
                sOkMsg="回報完成";

            }





        }


    }



    qDebug()<<"Msg : "<<sOkMsg<<" : error : "<<sError;



    re.bOk = bOk;

    re.sMsg = sError;

    re.iAciton = data.iAciton;

    if(bOk)
    {
        re.sMsg = sOkMsg;

    }
    else
    {
        re.sTrigger="0";
    }
    re.iState = ACT_RECALL;

    re.dRecSync = checkSync(data.dSendSync);

    return re;
}

bool Query::changeMoney(QString sCustomerSid, QString sValue, QString &sError)
{

    QVariantMap in;
    QVariantList listOut;
    bool b;
    in["Sid"]=sCustomerSid;
    b = m_sql.queryTb(SQL_TABLE::CustomerData(),in,listOut,sError);

    if(!b || listOut.length()<1)
    {
        return false;
    }

    CustomerData cus(listOut.first().toMap());

    return changeMoney(cus,sValue,sError);
}

bool Query::changeMoney(CustomerData cus, QString sValue, QString &sError)
{




    QVariantMap in;
    in["Sid"]=cus.Sid;
    QVariantList listOut;
    bool b;
    listOut.clear();

    b = m_sql.queryTb(SQL_TABLE::CustomerMoney(),in,listOut,sError);

    if(!b)
    {
        return false;
    }

    CustomerMoney money;

    if(listOut.length()>0)
    {
        money.setData(listOut.first().toMap());
    }
    else
    {
        money.Sid=cus.Sid;
        money.Id=cus.Id;
        money.Name=cus.Name;
        money.Currency=cus.Currency;
    }


    money.Money=sValue;


    b = m_sql.insertTb(SQL_TABLE::CustomerMoney(),money.data(),sError,true);

    if(!b)
    {
        return false;
    }

    return true;
}

bool Query::getCustomer(QString sSid, CustomerData &data)
{
    bool bRe =false;

    QString sError;
    QVariantMap in;
    QVariantList listOut;
    in["Sid"]= sSid;

    m_sql.queryTb(SQL_TABLE::CustomerData(),in,listOut,sError);

    if(listOut.length()>0)
    {
        data.setData(listOut.first().toMap());
        bRe = true;
    }

    return bRe;
}

UserData Query::getUser(QString sSid)
{
    QString sError;
    QVariantMap in;
    QVariantList list;
    in["Sid"]=sSid;
    m_sql.queryTb(SQL_TABLE::UserData(),in,list,sError);

    UserData re;

    if(list.length()>0)
        re.setData(list.first().toMap());

    return re;
}

QString Query::getNewOrderId(QString sOrderDate)
{


    auto orderIdAdd=[=](QString sDate,QString last)
    {

        QString date = sDate;

        if(date.length()>6)
        {
            date = date.right(6);
        }

        if(last=="")
        {
            return date+"-"+"A001";
        }


        QString sId="";
        if(last.length()>=4)
        {
            QString sTmp = last.mid(last.length()-4,4);

            QString sSecond = sTmp.mid(1,3);

            QString sFirst = sTmp.mid(0,1);

            if(sSecond.toInt()<999)
            {
                QString sNum = QString("%1").arg(sSecond.toInt()+1,3,10,QLatin1Char('0'));

                sId = date+"-"+sFirst+sNum;
            }
            else
            {


                sFirst=QChar::fromLatin1(sFirst.at(0).toLatin1()+1);

                sId = date+"-"+sFirst+"001";
            }

        }

        return sId;
    };


    QString sTodayLast="";
    QString sError;

    m_sql.lastOrderId(sOrderDate,sTodayLast,sError);

    QString sRe = orderIdAdd(sOrderDate,sTodayLast);



    QVariantList listout;
    QVariantMap in;

    in["Id"]= sRe;

    bool b=m_sql.queryTb(SQL_TABLE::OrderData(),in,listout,sError);

    if(b && listout.length()>0)
    {
        sRe = orderIdAdd(sOrderDate,sRe);
    }


    return sRe;


}

void Query::printTime(QString st)
{
    qDebug()<<"\nTime : "+st+" : "<<QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yy/MM/dd hh:mm:ss:zzz");
}

void Query::setPic(QVariantMap data)
{
    QTimer::singleShot(100,[=]()
    {
        printTime("insert Pic: ");
        QString sError;
        m_sql.insertTb(SQL_TABLE::PicData(),data,sError,true);
        printTime("insert Pic OK: ");
    });

}

bool Query::checkItemCount(OrderData orderData, QList<DataItemCount> &listLast, QStringList &sErrorGameItemSid)
{
    bool bRe =true;

    sErrorGameItemSid.clear();

    listLast.clear();

    QStringList listItem = orderData.Item.split(";;");

    for(int i=0;i<listItem.length();i++)
    {
        QString item = listItem.at(i);
        QString gameItemSid = item.split(",,").first();
        double iCount =item.split(",,").last().toDouble();
        QVariantMap in;
        QVariantList out;
        QString sError;
        in["GameItemSid"]=gameItemSid;
        in["DESC"]="Sid";
        in["LIMIT"]="1";

        m_sql.queryTb(SQL_TABLE::GameItemCount(),in,out,sError);
        DataItemCount itemCount;
        itemCount.GameItemSid=gameItemSid;
        itemCount.ChangeValue=0;
        itemCount.TotalCount=0;
        itemCount.TotalSell=0;

        if(out.length()>0)
        {

            itemCount.setData(out.first().toMap());
        }

        listLast.append(itemCount);

        int iNowCount = itemCount.TotalCount-itemCount.TotalSell;

        if(iCount>iNowCount)
        {
            sErrorGameItemSid.append(gameItemSid);
            bRe = false;
        }

    }


    return bRe;
}

bool Query::isBackSayCost(OrderData orderData)
{
    //排除返回未處理
    QVariantMap tmp0;
    QVariantList listTmp;
    QString sError;
    tmp0["Sid"]=orderData.Sid;
    tmp0["Step"]="2";
    m_sql.queryTb(SQL_TABLE::OrderData(),tmp0,listTmp,sError);


    return listTmp.length()>0;
}

bool Query::changeItemCount(OrderData orderData, bool bIsAdd,QString &sErrorMsg)
{
    QList<DataItemCount> listLast;
    QStringList listErrorItemSid;

    bool bHasOne=checkItemCount(orderData,listLast,listErrorItemSid);


    if(!bIsAdd)
    {

        if(!bHasOne)
        {
            sErrorMsg = listErrorItemSid.join(",");
            return false;
        }
    }



    CListPair list(orderData.Item);

    for(int i=0;i<list.length();i++)
    {

        DataItemCount itemCount;

        itemCount.OrderSid=orderData.Sid;

        itemCount.GameItemSid = list.at(i).first;

        DataGameItem gameItem =getGameItem(itemCount.GameItemSid);

        itemCount.GameSid = gameItem.GameSid;

        itemCount.Name = gameItem.Name;

        itemCount.ChangeValue = list.at(i).second.toInt();

        if(!bIsAdd)
            itemCount.ChangeValue=itemCount.ChangeValue*-1;

        if(orderData.User.length()>1)
            itemCount.UserSid = orderData.User.at(1);

        int iTmpIdx = qBound(0,i,listLast.length()-1);


        itemCount.TotalSell= listLast.at(iTmpIdx).TotalSell+(itemCount.ChangeValue*-1);

        itemCount.TotalCount = listLast.at(iTmpIdx).TotalCount;
        QString sError;
        m_sql.insertTb(SQL_TABLE::GameItemCount(),itemCount.data(),sError,false);


        updateCount(itemCount.GameSid,itemCount.GameItemSid,itemCount.Name,itemCount.TotalSell,itemCount.TotalCount);

    }


    return true;
}

bool Query::orderStep0(OrderData &order, QString &sError)
{
    CustomerData cus;

    bool bOk = false;
    bOk = getCustomer(order.CustomerSid,cus);

    if(!bOk)
    {
        sError ="報價失敗，查詢客戶資料錯誤。";
        return false;
    }

    QList<DataItemCount> listLast;
    QStringList listSt;
    if(!checkItemCount(order,listLast,listSt))
    {

        sError = "報價失敗, 商品庫存數量不足。";

        return false;

    }

    order.Currency = cus.Currency;

    order.CustomerName = cus.Name;

    QVariantMap in;
    QVariantList tmpOut;
    in["Sid"]=order.GameSid;

    m_sql.queryTb(SQL_TABLE::GameList(),in,tmpOut,sError);

    if(tmpOut.length()>0)
    {

        DataGameList game(tmpOut.first().toMap());

        order.GameRate = QString::number(game.GameRate);
    }
    else
    {
        sError="報價失敗，查詢遊戲資料錯誤";
        return false;
    }


    if(order.Currency.toUpper().contains("NTD"))
    {
        order.Money[0] = order.Cost;
    }

    if(order.Cost.toDouble()==0)
    {
        order.Money[0]="0";
    }

    if(order.StepTime.length()>0)
        order.StepTime[0]=QDateTime::currentDateTimeUtc().addSecs(60*8).toString("yyyyMMddhhmmss");


    return true;
}

bool Query::orderStep1(OrderData &order, OrderData current, QString &sError)
{
    bool bOnlyChangeOwner = false;

    if(current.Owner=="未分配" || current.Owner.trimmed()=="")
        bOnlyChangeOwner = true;


    if(!isBackSayCost(order))
    {
        QString sCountError;
        if(!changeItemCount(order,false,sCountError))
        {

            sError = "下單失敗, 商品庫存數量不足。";

            return false;

        }

        else if(current.Note1==order.Note1 &&  current.Step!="0" && !bOnlyChangeOwner)
        {
            sError ="下單失敗，目標訂單不處於報價狀態。";

            return false;
        }
        else
        {


            checkUpdate(ACT::ADD_ITEM_COUNT);

            if(order.Id.trimmed()=="")
                order.Id=getNewOrderId(order.OrderDate);



            if(order.StepTime.length()>1)
            {
                order.StepTime[1]=QDateTime::currentDateTimeUtc().addSecs(60*8).toString("yyyyMMddhhmmss");
                if(order.StepTime.at(0).trimmed()=="")
                    order.StepTime[0]=QDateTime::currentDateTimeUtc().addSecs(60*8).toString("yyyyMMddhhmmss");
            }
            QVariantMap in;
            QVariantList tmpOut;
            in["Sid"]=order.GameSid;

            m_sql.queryTb(SQL_TABLE::GameList(),in,tmpOut,sError);

            if(tmpOut.length()>0)
            {

                DataGameList game(tmpOut.first().toMap());

                //order.GameRate = QString::number(game.GameRate);//by step 0 order
            }

            if(order.Owner.trimmed()=="")
                order.Owner="None";
            int iSeq=1;

            QVariantMap in3;
            in3["Owner"]=order.Owner;
            in3["OrderDate"]=order.OrderDate;
            iSeq =m_sql.queryCount(SQL_TABLE::OrderData(),in3);

            QString sDash="";

            if(order.Owner.right(1)!="-")
                sDash="-";

            // order.Name=order.Owner+sDash+QString("%1").arg(iSeq+1,2,10,QLatin1Char('0'));

            if(current.Sid==order.Sid && current.Step=="1" &&!bOnlyChangeOwner)
            {
                //改留言，不重新給與編號
            }
            else
            {
                if(order.Owner!="未分配")
                    order.Name=order.Owner+sDash+QString::number(iSeq+1);
            }


        }
    }

    return true;
}

bool Query::orderStep2(OrderData &order, OrderData current, QString &sError)
{



    if(current.Step =="2")
    {
        if(order.PaddingUser.trimmed()!="" && current.User.at(2)!=order.PaddingUser)
        {

            sError = getUser(current.User.at(2)).Name+" 已接單處理";

            return false;
        }
    }

    if(current.Step =="3")
    {

        sError = getUser(current.User.at(3)).Name+" 已儲值完成";

        return false;
    }


    return true;
}

bool Query::orderStep3(OrderData &order, OrderData current, QString &sError)
{


    if(order.Step=="3" && order.PaddingUser.trimmed()!="") //回報鎖定的請求
    {
        if(current.Step =="3" && current.PaddingUser.trimmed()!="")
        {


            sError = getUser(current.PaddingUser).Name+" 正在回報中";

            return false;
        }

        if(current.Step =="4") //
        {

            sError = "此訂單 "+getUser(current.User.at(4)).Name+" 已回報";

            return false;
        }
    }

    return true;
}

QVariantList Query::getOrderData(QString lastUpdateTime)
{
    return QVariantList();

}

DataGameItem Query::getGameItem(QString sSid)
{
    DataGameItem re;
    QString sError;
    QVariantMap in;
    QVariantList listOut;
    in["Sid"]= sSid;


    m_sql.queryTb(SQL_TABLE::GameItem(),in,listOut,sError);


    if(listOut.length()>0)
    {
        re.setData(listOut.first().toMap());
        //  sRe = listOut.first().toMap()["GameSid"].toString();
    }

    return re;
}

QVariantMap Query::checkSync(QVariantMap syncSend)
{
    QVariantMap re;

    QStringList listKey = syncSend.keys();

    for(int i=0;i<listKey.length();i++)
    {
        QString sTbName= listKey.at(i);
        QString orderUpdate=syncSend[sTbName].toString();
        QVariantList listOut;
        QString sNewUpdateTime = m_sql.queryLast(SQL_TABLE::OrderData(),orderUpdate,listOut);

        QVariantMap d;
        d["UpdateTime"] = sNewUpdateTime;
        d["data"]=listOut;

        re[sTbName]=d;

    }

    return re;
}

void Query::updateCount(QString sGameSid, QString sItemSid,QString sName, int TotalSell, int TotalCount)
{
    QString sSid="";

    QString sError;
    QVariantMap d;
    d["GameItemSid"]=sItemSid;
    QVariantList listOut;
    m_sql.queryTb(SQL_TABLE::QueryCount(),d,listOut,sError);

    if(listOut.length()>0)
    {
        sSid = listOut.last().toMap()["Sid"].toString();
    }


    QVariantMap data;

    data["GameSid"]=sGameSid;
    data["GameItemSid"]=sItemSid;
    data["Name"] = sName;
    data["TotalSell"]=TotalSell;
    data["TotalCount"]=TotalCount;


    if(sSid!="")
    {
        QVariantMap tmp;
        tmp["Sid"]=sSid;
        data["Sid"]=sSid;
        m_sql.updateTb(SQL_TABLE::QueryCount(),tmp,data,sError);

    }
    else
    {
        m_sql.insertTb(SQL_TABLE::QueryCount(),data,sError);
    }

}

QString Query::getNewCustomerId()
{
    QString sRe="";


    return sRe;
}

void Query::slotApiDoOrder(QVariantMap data)
{
    // OrderData d(data);

    qDebug()<<"get slot : "<<data;

    CData input;

    input.iAciton = ACT::REPLACE_ORDER;

    input.dData = data;

    CData re= implementRecall(input);

}





