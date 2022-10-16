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

};

namespace  GROUP_DATA{
enum
{
    PAY_PIPELINE=0


};
}




namespace ACT
{
enum _KEY
{



    SET_VALUE=1001,
    GET_VALUE,

    LOGIN = 1000,
    ADD_USER =1011,
    DEL_USER,
    EDIT_USER,


    ADD_CUSTOMER =1021,
    DEL_CUSTOMER,
    EDIT_CUSTOMER,

    REPLACE_GAME_INFO =1031,
    DEL_GAME_INFO,

    ADD_CUSTOMER_COST =1041,




    ADD_GAME_LIST = 1051,
    EDIT_GAME_LIST,
    DEL_GAME_LIST,


    ADD_GAME_ITEM = 1061,
    EDIT_GAME_ITEM,
    DEL_GAME_ITEM,


    ADD_BULLETIN = 1071,
    EDIT_BULLETIN,
    DEL_BULLETIN,


    ADD_CUSTOM_CLASS = 1081,
    EDIT_CUSTOM_CLASS,
    DEL_CUSTOM_CLASS,


    ADD_FACTORY_CLASS = 1091,
    EDIT_FACTORY_CLASS,
    DEL_FACTORY_CLASS,


    ADD_PAY_TYPE =1101,
    DEL_PAY_TYPE,
    EDIT_PAY_TYPE,


    ADD_GROUP=1111,
    DEL_GROUP,
    EDIT_GROUP,


    REPLACE_ORDER =1121,



    ADD_BOUNS=1131,


    ADD_SCHEDULE=1141,



    SAVE_EXCHANGE=1151,


    ADD_EXCHANGE=1161,



    ADD_PRIMERATE=1171,


    //  query key

    QUERY_USER = 3011,
    QUERY_CUSTOMER=3021,
    LAST_CUSTOMER_ID,
    QUERY_GAME_INFO=3031,
    QUERY_CUSTOMER_COST=3041,
    QUERY_GAME_LIST=3051,
    QUERY_GAME_ITEM=3061,
    QUERY_BULLETIN=3071,
    QUERY_CUSTOM_CLASS=3081,
    QUERY_FACTORY_CLASS=3091,
    QUERY_PAY_TYPE=3101,
    QUERY_GROUP=3111,

    QUERY_ORDER=3121,
    LAST_ORDER_ID,
    LAST_ORDER_NAME,

    QUERY_BOUNS=3131,

    QUERY_SCHEDULE=3141,
    READ_EXCHANGE=3151,
    QUERY_EXCHANGE=3161,
    QUERY_PRIMERATE=3171,
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

        int iIdx = listFirst().indexOf(sKey);

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
