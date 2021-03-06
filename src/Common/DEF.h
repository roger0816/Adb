#ifndef DEF_H
#define DEF_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>




struct SQL_TABLE
{
    static QString ExchangeRate(){return "ExchangeRate";}
    static QString PrimeCostRate(){return "PrimeCostRate";}
    static QString GameList(){return "GameList";}
    static QString GameItem(){return "GameItem";}
    static QString Bulletin(){return "Bulletin";}
    static QString CustomerClass(){return "CustomerClass";}
    static QString FactoryClass(){return "FactoryClass";}
    static QString UserData(){return "UserData";}
    static QString CustomerData(){return "CustomerData";}
    static QString CustomerCost(){return "CustomerCost";}
    static QString CustomerGameInfo(){return "CustomerGameInfo";}
    static QString OrderData(){return "OrderData";}
    static QString AddValueType(){return "AddValueType";}

};


namespace ACT
{
enum _KEY
{
    SET_VALUE=1001,
    GET_VALUE,

    LOGIN = 3000,
    ADD_USER =4001,
    DEL_USER,
    EDIT_USER,
    QUERY_USER,

    ADD_CUSTOMER =4011,
    DEL_CUSTOMER,
    EDIT_CUSTOMER,
    QUERY_CUSTOMER,
    LAST_CUSTOMER_ID,

    REPLACE_GAME_INFO =4021,
    DEL_GAME_INFO,
    QUERY_GAME_INFO,

    ADD_CUSTOMER_COST =4031,
    QUERY_CUSTOMER_COST,



    ADD_GAME_LIST = 5001,
    EDIT_GAME_LIST,
    DEL_GAME_LIST,
    QUERY_GAME_LIST,

    ADD_GAME_ITEM = 5011,
    EDIT_GAME_ITEM,
    DEL_GAME_ITEM,
    QUERY_GAME_ITEM,

    ADD_BULLETIN = 5101,
    EDIT_BULLETIN,
    DEL_BULLETIN,
    QUERY_BULLETIN,

    ADD_CUSTOM_CLASS = 5111,
    EDIT_CUSTOM_CLASS,
    DEL_CUSTOM_CLASS,
    QUERY_CUSTOM_CLASS,

    ADD_FACTORY_CLASS = 5121,
    EDIT_FACTORY_CLASS,
    DEL_FACTORY_CLASS,
    QUERY_FACTORY_CLASS,

    ADD_ADDVALUE_TYPE =5131,
    DEL_ADDVALUE_TYPE,
    EDIT_ADDVALUE_TYPE,
    QUERY_ADDVALUE_TYPE,


    REPLACE_ORDER =6001,
    QUERY_ORDER,
    LAST_ORDER_ID,
    LAST_ORDER_NAME,


    SAVE_EXCHANGE,
    READ_EXCHANGE,

    ADD_EXCHANGE,
    QUERY_EXCHANGE,


    ADD_PRIMERATE,
    QUERY_PRIMERATE



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









#endif // DEF_H
