#ifndef DEF_H
#define DEF_H

#include <QString>
#include <QDebug>
#include <QPair>
#include <QVariantList>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

#define ADP_VER "v1.01.1105"

static QString SPLIT1 =";;" ;
static QString SPLIT2 =",," ;

struct SQL_TABLE
{
    static QString ExchangeRate(){return "ExchangeRate";}
    static QString PrimeCostRate(){return "PrimeCostRate";}
    static QString GameList(){return "GameList";}
    static QString GameItem(){return "GameItem";}
    static QString Bulletin(){return "Bulletin";}
    static QString CustomerClass(){return "CustomerClass";}
    static QString GroupData(){return "GroupData";}
    static QString FactoryClass(){return "FactoryClass";}
    static QString UserData(){return "UserData";}
    static QString CustomerData(){return "CustomerData";}
    static QString CustomerCost(){return "CustomerCost";}
    static QString CustomerGameInfo(){return "CustomerGameInfo";}
    static QString OrderData(){return "OrderData";}
    static QString PayType(){return "PayType";}
    static QString UserBonus(){return "UserBonus";}
    static QString Schedule(){return "Schedule";}
    static QString PicData(){return "PicData";}
    static QString GameItemCount(){return "GameItemCount";}
};

namespace ACT
{
enum _KEY
{

    SET_VALUE=1001,
    GET_VALUE,

    LOGIN = 1000,

    ADD_USER =1001,
    DEL_USER,
    EDIT_USER,
    QUERY_USER = 1031,


    ADD_CUSTOMER =1101,
    DEL_CUSTOMER,
    EDIT_CUSTOMER,
    QUERY_CUSTOMER=1131,
    LAST_CUSTOMER_ID,

    REPLACE_GAME_INFO =1201,
    DEL_GAME_INFO,
    QUERY_CUSTOMER_GAME_INFO=1231,

    ADD_CUSTOMER_COST =1301,
    QUERY_CUSTOMER_COST=1331,
    LAST_CUSTOMER_COST_ID,

    ADD_GAME_LIST = 1401,
    EDIT_GAME_LIST,
    DEL_GAME_LIST,
    QUERY_GAME_LIST=1431,

    ADD_GAME_ITEM = 1501,
    EDIT_GAME_ITEM,
    DEL_GAME_ITEM,
    QUERY_GAME_ITEM=1531,

    ADD_BULLETIN = 1601,
    EDIT_BULLETIN,
    DEL_BULLETIN,
    QUERY_BULLETIN=1631,

    ADD_CUSTOM_CLASS = 1701,
    EDIT_CUSTOM_CLASS,
    DEL_CUSTOM_CLASS,
    ADD_CUSTOM_DEBIT = 1711,
    EDIT_CUSTOM_DEBIT,
    DEL_CUSTOM_DEBIT,

    QUERY_CUSTOM_CLASS=1731,
    QUERY_CUSTOM_DEBIT,

    ADD_FACTORY_CLASS = 1801,
    EDIT_FACTORY_CLASS,
    DEL_FACTORY_CLASS,
    QUERY_FACTORY_CLASS=1831,

    ADD_PAY_TYPE =1901,
    DEL_PAY_TYPE,
    EDIT_PAY_TYPE,
    QUERY_PAY_TYPE=1931,

    ADD_GROUP=2001,
    DEL_GROUP,
    EDIT_GROUP,
    QUERY_GROUP=2031,

    REPLACE_ORDER =2101,
    QUERY_ORDER=2131,
    LAST_ORDER_ID,
    LAST_ORDER_NAME,

    ADD_BOUNS=2201,
    QUERY_BOUNS=2231,


    ADD_SCHEDULE=2301,
    QUERY_SCHEDULE=2331,


    ADD_EXCHANGE=2401,
    QUERY_EXCHANGE=2431,


    ADD_PRIMERATE=2501,
    QUERY_PRIMERATE=2531,

    UPLOAD_PIC=2601,
    QUERY_PIC=2631,

    ADD_ITEM_COUNT=2701,
    EDIT_ITEM_COUNT,
    DEL_ITEM_COUNT,
    QUERY_ITEM_COUNT=2731


};

}


namespace  GROUP_DATA{
enum
{
    PAY_PIPELINE=0


};
}






namespace USER_LV {
enum UserLv
{

    _LV1=1,
    _LV2=2,
    _LV3=3,
    _LV4=4,
    _ROOT =99
};
}




typedef QPair<QString,QString> CPair ;



struct CListPair : public QList< CPair >
{

    CListPair(QString st="")
    {
        if(st!="")
            fromString(st);
    }
    QStringList listFirst()
    {
        QStringList listRe;

        for(int i=0;i<this->length();i++)
        {
            listRe.append(this->at(i).first);
        }

        qDebug()<<"list first : "<<listRe;
        return listRe;
    }

    QStringList listSecond()
    {
        QStringList listRe;

        for(int i=0;i<this->length();i++)
        {
            listRe.append(this->at(i).second);
        }

        qDebug()<<"list sec : "<<listRe;
        return listRe;
    }

    QString toString()
    {
        QStringList list;
        for(int i=0;i<this->length();i++)
        {
            list.append(this->at(i).first+SPLIT2+this->at(i).second);
        }

        return list.join(SPLIT1);
    }

    void fromString(QString st)
    {
        clear();
        if(st.trimmed()=="")
            return;
        QStringList list = st.split(SPLIT1);

        foreach(QString v,list)
        {
            append(CPair(v.split(SPLIT2).first(),v.split(SPLIT2).last()));
        }

    }

    void getTheSameKey(CListPair data)
    {
        if(data.listFirst().length()<1)
            return;

        if(listFirst().length()<1)
            return this->fromString(data.toString());


        CListPair tmp;

        QSet<QString> t = listFirst().toSet().intersect(data.listFirst().toSet());

        QStringList list = t.toList();

        qDebug()<<"the same key : "<<list;

        for(int i=0;i<list.length();i++)
        {
            QString sKey = list.at(i);

            int idx = listFirst().indexOf(sKey);

            CPair v(listFirst().at(idx),listSecond().at(idx));

            tmp.append(v);
        }

        fromString(tmp.toString());

    }

    CPair findPairFromKey(QString sKey)
    {
        CPair re;

        int iIdx =-1;



//        if(sKey.length()>=3)
//        {
//            for(int i=0;i<listFirst().length();i++)
//            {
//                QString st = listFirst().at(i);

//                if(st.contains(sKey))
//                {
//                    iIdx=i;
//                    break;
//                }
//            }
//        }
//        else
        {
            iIdx= listFirst().indexOf(sKey);

        }


        if(iIdx>=0)
            re = at(iIdx);

        return re;
    }

    QString findValue(QString sKey)
    {
        return findPairFromKey(sKey).second;
    }


};

/*
struct CListMap : public QList<QVariant>
{
    QVariantList list(QString sKey)
    {
        QVariantList listRe;

        //        foreach(QVariant v,this)
        //        {
        //            QVariantMap data = v.toMap();

        //            if(data.keys().indexOf(sKey)>=0)
        //                listRe.append(data[sKey]);
        //        }

        return listRe;
    }

    QStringList stringList(QString sKey)
    {
        QStringList listRe;

        //        foreach(QVariant v,this)
        //        {
        //            QVariantMap data = v.toMap();

        //            if(data.keys().indexOf(sKey)>=0)
        //                listRe.append(data[sKey].toString());
        //        }

        return listRe;
    }
};

*/







#endif // DEF_H
