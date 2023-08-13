#include "CListenApi.h"

CListenApi::CListenApi(QObject *parent)
    : CHttpServerObj{parent}
{



}

void CListenApi::startRESTfulApi(QString sPort)
{
    listen(sPort);

}

QString CListenApi::funcGet(bool bIsBrowser, QString path, QVariantMap args)
{
    return func(bIsBrowser,path,args);
}

QString CListenApi::funcPost(bool bIsBrowser, QString path, QVariantMap args)
{
    return func(bIsBrowser,path,args);
}



//===============================================



QString CListenApi::func(bool bIsBrowser,QString path, QVariantMap args)
{
    qDebug()<<" ori path : "<<path<<" , args : "<<args;

    QString sSendData ="";

    QString sSubPath;

    if(dPath(path,"Test",sSubPath))
    {

        qDebug()<<"cmd : test , subPath : "<<sSubPath<<" , args: "<<args;


        QVariantMap d = args;

        d["Test"]="ok";


            sSendData = toJsonString(d);


        qDebug()<<"reply : "<<sSendData;


    }

    else if(dPath(path,"Rate",sSubPath))
    {

        sSendData=m_request.getRate();
    }

    else if(dPath(path,"GameList",sSubPath))
    {

        sSendData=m_request.getAllGames();
        qDebug()<<"AAA : "<<sSendData;
    }

    else if(dPath(path,"GameItem",sSubPath))
    {
        if(args.keys().contains("Sid"))
        {
            QString sSid = args["Sid"].toString();
            sSendData=m_request.getGameItem(sSid);
            qDebug()<<"send : "<<sSendData;
        }
        else
        {
            QVariantMap d;
            d["error"]="error:400 Bad Reqeust: please input 'Sid' ";

           sSendData =toJsonString("Error","400 Bad Reqeust: please input 'Sid' \n");


        }

    }

    else if(dPath(path,"Customer",sSubPath))
    {
        if(args.keys().contains("Line"))
        {
            QString sSid = args["Line"].toString();
            sSendData=m_request.getCustomer(sSid);
            qDebug()<<"send : "<<sSendData;
        }
        else
        {
            QVariantMap d;
            d["error"]="error:400 Bad Reqeust: please input 'Line' ";

           sSendData =toJsonString("Error","400 Bad Reqeust: please input 'Sid' \n");


        }

    }

    else if(dPath(path,"History",sSubPath))
    {
        if(args.keys().contains("Sid"))
        {
            QString sSid = args["Sid"].toString();
            sSendData=m_request.getHistory(sSid);
            qDebug()<<"send : "<<sSendData;
        }
        else
        {
            QVariantMap d;
            d["error"]="error:400 Bad Reqeust: please input 'Sid' ";

           sSendData =toJsonString("Error","400 Bad Reqeust: please input 'Sid' \n");


        }

    }

    else if(dPath(path,"GameAccount",sSubPath))
    {
        if(args.keys().contains("Sid"))
        {
            QString sSid = args["Sid"].toString();
            sSendData=m_request.getCusGame(sSid);
            qDebug()<<"send : "<<sSendData;
        }
        else
        {
            QVariantMap d;
            d["error"]="error:400 Bad Reqeust: please input 'Sid' ";

           sSendData =toJsonString("Error","400 Bad Reqeust: please input 'Sid' \n");


        }

    }

    else if(dPath(path,"Order",sSubPath))
    {
            QStringList listKey;
            listKey<<"UserId"<<"Password"<<"Item"<<"Count"<<"Customer"<<"GameAccount";

            bool bOk=true;

            foreach(QString v,listKey)
            {
                if(!args.keys().contains(v))
                    bOk = false;
            }

            if(!bOk)
            {
                sSendData=toJsonString("Error","400 Bad Request : input Error ");

            }
            else
            {
                sSendData=m_request.doOrder(args);
                qDebug()<<"send : "<<sSendData;
            }



    }

    else if(dPath(path,"AddValueType",sSubPath))
    {

            sSendData=m_request.getPayType();
            qDebug()<<"send : "<<sSendData;

    }



    else
    {



        sSendData=toJsonString("Error","400 Bad Request : not found api ");

        // 不知哪來的/favicon.ico  不處理


    }



    return sSendData;
}
