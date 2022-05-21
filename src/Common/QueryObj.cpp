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
        bOk = m_sql.delUser(data.sMsg,sError);
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

    else if(data.iAciton==ACT::SAVE_EXCHANGE)
    {
        bOk = m_sql.saveExchange(data.listData,sError);
    }

    else if(data.iAciton==ACT::READ_EXCHANGE)
    {
        bOk = true;

        int iIdx = -1;

        if(data.listData.length()>0)
            iIdx = data.listData.first().toInt();

        re.listData = m_sql.readExchange(iIdx);
    }

    else if(data.iAciton==ACT::ADD_GAME)
    {
        bOk = m_sql.insertTb(SQL_TABLE::GameList(),data.dData,sError);
        sOkMsg = "遊戲新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME)
    {
        QVariantMap d;
        d["Sid"] =data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::GameList(),d ,data.dData,sError);
        sOkMsg = "遊戲修改完成";
    }

    else if(data.iAciton==ACT::DEL_GAME)
    {
        QVariantMap d;
        d["Sid"] =data.dData["Sid"];
        bOk = m_sql.delFromTb(SQL_TABLE::GameList(),d,sError);


        sOkMsg="遊戲刪除完成";
    }


    else if(data.iAciton==ACT::QUERY_GAME)
    {
        qDebug()<<"qeury game list ";
        bOk = m_sql.queryTb(SQL_TABLE::GameList(),re.listData,sError);


    }


    else if(data.iAciton==ACT::ADD_GAME_ITEM)
    {
        bOk = m_sql.insertTb(SQL_TABLE::GameItem(),data.dData,sError);
        sOkMsg = "商品新增完成";
    }

    else if(data.iAciton==ACT::EDIT_GAME_ITEM)
    {
        qDebug()<<"qeury game item ";

        QVariantMap d;

        d["GameSid"] = data.dData["GameSid"];

        bOk = m_sql.updateTb(SQL_TABLE::GameItem(),d,data.dData,sError);

        sOkMsg="修改完成";



    }

    else if(data.iAciton==ACT::QUERY_GAME_ITEM)
    {
        qDebug()<<"qeury game item ";

        QVariantMap d;

        if(data.listData.length()>0)
            d = data.listData.first().toMap();

        bOk = m_sql.queryTb(SQL_TABLE::GameItem(),d,re.listData,sError);

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
        sOkMsg = "廠商類型新增完成";
    }

    else if(data.iAciton==ACT::EDIT_FACTORY_CLASS)
    {
        QVariantMap d;
        d["Sid"] = data.dData["Sid"];
        bOk = m_sql.updateTb(SQL_TABLE::FactoryClass(),d,data.dData,sError);
        sOkMsg = "廠商類型修改完成";
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




    re.iAciton = data.iAciton;

    re.bOk = bOk;

    re.sMsg = sError;
    if(bOk)
        re.sMsg = sOkMsg;

    re.iState = ACT_RECALL;

    return re;
}
