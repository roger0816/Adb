#include "Query.h"

Query::Query(QObject *parent)
    : QueryObj{parent}
{


}


CData Query::implementRecall(CData data)
{


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

                gameRate.Rate=game.GameRate;

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

    }


    else if(data.iAciton==ACT::LAST_CUSTOMER_ID)
    {
        QString sReId="";

        QString sSid = data.dData["Class"].toString();

        QString sId =  data.dData["ClassId"].toString();

        bOk  =m_sql.lsatCustomerId(sSid,sId,sReId,sError);

        QVariantMap tmp;
        tmp["Id"]=sReId;

        re.listData.append(tmp);
    }

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
        OrderData order(data.dData);

        bool bHasIt = false;

        if(order.Step=="0")
        {}
        else if(order.Step=="1")
        {
            order.Id=getNewOrderId();
            QVariantMap in;
            QVariantList tmpOut;
            in["Sid"]=order.GameSid;

            m_sql.queryTb(SQL_TABLE::GameList(),in,tmpOut,sError);

            if(tmpOut.length()>0)
            {

                DataGameList game(tmpOut.first().toMap());

                order.GameRate = game.GameRate;
            }


        }
        else
        {
            QVariantMap inTmp;
            QVariantList outTmp;
            inTmp["Sid"] = order.Sid;
            m_sql.queryTb(SQL_TABLE::OrderData(),inTmp,outTmp,sError);
            OrderData current;
            if(outTmp.length()>0)   //預防重複鎖定
            {
                current.setData(outTmp.first().toMap());

                if(order.Step=="2")    //接單鎖定的請求
                {
                    if(current.Step =="2")
                    {
                        bHasIt = true;

                        sError = getUser(current.User.at(2)).Name+" 已接單處理";
                    }

                    if(current.Step =="3")
                    {
                        bHasIt = true;

                        sError = getUser(current.User.at(3)).Name+" 已儲值完成";
                    }
                }
                else if(order.Step=="3" && order.PaddingUser.trimmed()!="") //回報鎖定的請求
                {
                    if(current.Step =="3" && current.PaddingUser.trimmed()!="")
                    {
                        bHasIt = true;

                        sError = getUser(current.PaddingUser).Name+" 正在回報中";
                    }

                    if(current.Step =="4") //
                    {
                        bHasIt = true;

                        sError = "此訂單 "+getUser(current.User.at(4)).Name+" 已回報";
                    }
                }

            }

        }




        if(!bHasIt)
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

        bOk = m_sql.insertTb(SQL_TABLE::GameItemCount(),data.dData,sError);
        sOkMsg = "新增完成";

    }

    else if(data.iAciton==ACT::EDIT_ITEM_COUNT)
    {

        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::GameItemCount(),d,data.dData,sError);
        sOkMsg = "修改完成";

    }

    else if(data.iAciton==ACT::DEL_ITEM_COUNT)
    {

        bOk = m_sql.delFromTb(SQL_TABLE::GameItemCount(),data.dData,sError);

        sOkMsg ="刪除完成";

    }


    else if(data.iAciton==ACT::QUERY_ITEM_COUNT)
    {

        bOk = m_sql.queryTb(SQL_TABLE::GameItemCount(),data.dData,re.listData,sError);

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

        costData.Total=QString::number(iNewTotal);


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

            if(tmpList.length()<1)
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

                cost.ChangeValue=QString::number(order.Cost.toDouble()*-1);

                double tTotal =preTotal+cost.ChangeValue.toDouble();

                cost.Total = QString::number(tTotal);

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
        data.setData(listOut.first().toMap());

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

QString Query::getNewOrderId()
{

    auto orderIdAdd=[=](QString last)
    {
        if(last=="")
        {
            return QDate::currentDate().toString("yyyyMMdd").remove(0,2)+"-"+"A001";
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

                sId = last.mid(0,last.length()-4)+sFirst+sNum;
            }
            else
            {


                sFirst=QChar::fromLatin1(sFirst.at(0).toLatin1()+1);

                sId = last.mid(0,last.length()-4)+sFirst+"001";
            }

        }

        return sId;
    };


    QString sTodayLast="";
    QString sError;
    QString sDate = QDate::currentDate().toString("yyyyMMdd");

    m_sql.lastOrderId(sDate,sTodayLast,sError);

    return orderIdAdd(sTodayLast);


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





