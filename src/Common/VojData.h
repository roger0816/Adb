#ifndef VOJ_H
#define VOJ_H

#include <QString>
#include "DEF.h"
#include <QDateTime>
#include <QVariantMap>
#include <QThread>
// name follow database fieldName


struct DataObj
{
public:
    DataObj(){}

    DataObj(const QVariantMap &data){setData(data);}
    QString Sid="";

    QString Id="";

    QString Name="";

    bool bRead=false;

    QString UpdateTime;

    void setData(const QVariantMap &data)
    {
        Sid = data["Sid"].toString();

        Id = data["Id"].toString();

        Name = data["Name"].toString();

        UpdateTime = data["UpdateTime"].toString();
    }

    QVariantMap data()
    {
        QVariantMap re;

        re["Sid"] = Sid;

        re["Id"] = Id;

        re["Name"] =Name;

        re["UpdateTime"] = UpdateTime;

        return re;
    }



};



struct UserData :public DataObj
{


    QString Password;

    QString Cid;
    int Lv ;
    QString ParentId;
    QString StartDay;
    QString BirthDay;
    QString Tel;
    QString Email;
    QString Note1;
    QString Note2;
    QString Note3;
    QString CreateTime;


    UserData():DataObj(){}

    UserData(QVariantMap dData):UserData(){setData(dData);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Password = data["Password"].toString();
        Sid=data["Sid"].toString();
        Cid = data["Cid"].toString();
        Lv = data["Lv"].toInt();
        ParentId = data["ParentId"].toString();
        StartDay = data["StartDay"].toString();
        BirthDay = data["BirthDay"].toString();
        Tel = data["Tel"].toString();
        Email = data["Email"].toString();
        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
        Note3 = data["Note3"].toString();
        CreateTime = data["CreateTime"].toString();

    }

    QVariantMap data()
    {
        QVariantMap re = DataObj::data();

        re["Password"] = Password;

        re["Cid"] = Cid;
        re["Lv"] = Lv;
        re["ParentId"] = ParentId;
        re["StartDay"] = StartDay;
        re["BirthDay"] = BirthDay;
        re["Tel"] = Tel;
        re["Email"] = Email;
        re["Note1"] = Note1;
        re["Note2"] = Note2;
        re["Note3"] = Note3;
        re["CreateTime"] = CreateTime;

        return re;
    }
};


struct DataUserBonus
{

    void setData(QVariantMap data)
    {
        Sid = data["Sid"].toString();
        UserSid = data["UserSid"].toString();
        OrderSid = data["OrderSid"].toString();
        Bonus = data["Bonus"].toString();
        Pay = data["Pay"].toString();
        AddBonus = data["AddBonus"].toString();
        AddPay = data["AddPay"].toString();
        UpdateTime = data["UpdateTime"].toString();

    }
    QVariantMap data()
    {
        QVariantMap re;

        re["Sid"] = Sid;
        re["UserSid"] = UserSid;
        re["OrderSid"] = OrderSid;
        re["Bonus"] = Bonus;
        re["Pay"] = Pay;
        re["AddBonus"] = AddBonus;
        re["AddPay"] = AddPay;
        re["UpdateTime"] = UpdateTime;

        return re;
    }

    QString Sid;
    QString UserSid;
    QString OrderSid;
    QString Bonus="0";
    QString Pay="0";
    QString AddBonus;
    QString AddPay;
    QString UpdateTime;

};


struct CustomerData :public DataObj
{
    CustomerData(){}
    CustomerData(const QVariantMap &data):DataObj(){setData(data);}

    void setData(const QVariantMap &data)
    {

        DataObj::setData(data);

        Class = data["Class"].toString();
        Line = data["Line"].toString();
        Money = data["Money"].toString();
        if(Money=="")
            Money="0";

        Vip = data["Vip"].toString();
        Currency = data["Currency"].toString();
        PayType =data["PayType"].toString();
        PayInfo =data["PayInfo"].toString();
        UserSid = data["UserSid"].toString();
        Num5 = data["Num5"].toString();
        Note1   =data["Note1"].toString();
        Note2   =data["Note2"].toString();


    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["Class"] = Class;
        d["Vip"] = Vip;
              d["Line"] = Line;
        d["Money"] = Money;
        d["Currency"] = Currency;
        d["PayType"] = PayType;
        d["PayInfo"] =PayInfo;
        d["UserSid"] =UserSid;
        d["Num5"] = Num5;
        d["Note1"] = Note1;
        d["Note2"]= Note2;

        return d;
    }

    QString Vip;
    QString Class;
    QString Money="0";
    QString Line="";
    QString Currency;
    QString PayType;
    QString PayInfo;
    QString UserSid;
    QString Num5;
    QString Note1;
    QString Note2;
};



struct CustomerMoney :public DataObj
{
    QString Money;
    QString Currency;

    CustomerMoney():DataObj(){};
    CustomerMoney(QVariantMap data){setData(data);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Money = data["Money"].toString();

        Currency=data["Currency"].toString();

    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();
        re["Money"] = Money;
        re["Currency"] =Currency;
        return re;
    }
};






struct CustomerCost
{
    CustomerCost(){}
    CustomerCost(QVariantMap data){setData(data);}
    void setData(QVariantMap data)
    {
        Sid = data["Sid"].toString();
        CustomerSid = data["CustomerSid"].toString();
        OrderId = data["OrderId"].toString();
        Currency = data["Currency"].toString();
        ChangeValue = data["ChangeValue"].toString();
        OriginCurrency = data["OriginCurrency"].toString();
        OriginValue = data["OriginValue"].toString();
        DebitSid = data["DebitSid"].toString();
        DebitNote = data["DebitNote"].toString();
        Rate = data["Rate"].toString();
        AddRate = data["AddRate"].toString();
        IsAddCost = data["IsAddCost"].toBool();
        Total = data["Total"].toString();

        if(Total=="")
            Total="0";

        UserSid = data["UserSid"].toString();
        OrderTime = data["OrderTime"].toString();
        UpdateTime = data["UpdateTime"].toString();
        Pic0 = data["Pic0"].toString();
        Pic1 = data["Pic1"].toString();
        Note1 = data["Note1"].toString();
        Note0 = data["Note0"].toString();
    }

    QVariantMap data()
    {
        QVariantMap re;

        re["Sid"]=Sid;
        re["CustomerSid"]=CustomerSid;
        re["OrderId"]=OrderId;
        re["Currency"]=Currency;
        re["ChangeValue"]=ChangeValue;
        re["OriginCurrency"]=OriginCurrency;
        re["OriginValue"]=OriginValue;
        re["DebitSid"]=DebitSid;
        re["DebitNote"]=DebitNote;
        re["Rate"]=Rate;
        re["AddRate"]=AddRate;
        re["IsAddCost"] = IsAddCost;

        re["Total"]=Total;
        re["UserSid"]=UserSid;
        re["OrderTime"]=OrderTime;
        re["UpdateTime"]=UpdateTime;
        re["Pic0"]=Pic0;
        re["Pic1"]=Pic1;
        re["Note0"]=Note0;
        re["Note1"]=Note1;

        return re;
    }



    QString Sid="";
    QString CustomerSid;
    QString OrderId;
    QString Rate;
    QString AddRate="0";
    bool IsAddCost=true;
    QString DebitSid;
    QString DebitNote;
    QString OriginCurrency;       //加值幣別
    QString OriginValue ="0";     //原始數字
    QString Currency;             //轉換客戶幣別
    QString ChangeValue ="0";     //換匯後金額
    QString Total ="0";
    QString UserSid;
    QString OrderTime;
    QString UpdateTime;
    QString Pic0;
    QString Pic1;
    QString Note0;
    QString Note1;

};


struct DataCustomerClass :public DataObj
{
    DataCustomerClass(){}
    DataCustomerClass(QVariantMap v){setData(v);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);
        Sort=data["Sort"].toInt();
        Type=data["Type"].toString();
        Note1=data["Note1"].toString();
        Note2=data["Note2"].toString();
    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["Sort"]=Sort;
        d["Type"]=Type;
        d["Note1"]=Note1;
        d["Note2"]=Note2;

        return d;
    }
    int Sort=0;
    QString Type;
    QString Note1;
    QString Note2;
};

struct DebitClass :public DataObj
{
    DebitClass(QVariantMap v){setData(v);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);
        Sort=data["Sort"].toInt();

        Currency=data["Currency"].toString();
        Note1=data["Note1"].toString();
        Note2=data["Note2"].toString();
    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();
        d["Sort"]=Sort;
        d["Currency"]=Currency;
        d["Note1"]=Note1;
        d["Note2"]=Note2;

        return d;
    }
    int Sort=0;
    QString Currency;
    QString Note1;
    QString Note2;

};




struct GroupData :public DataObj
{
    GroupData(QVariantMap v):DataObj(v){}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Type=data["Type"].toString();
        Value=data["Value"].toString();
        Blob=data["Blob"].toByteArray();
        Note1=data["Note1"].toString();
        Note2=data["Note2"].toString();
        NoteBlob=data["NoteBlob"].toByteArray();

    }
    QVariantMap data()
    {
        QVariantMap d = DataObj::data();
        d["Type"]=Type;
        d["Value"]=Value;
        d["Blob"]=Blob;
        d["Note1"]=Note1;
        d["Note2"]=Note2;
        d["NoteBlob"]=NoteBlob;

        return d;
    }
    QString Type;
    QString Value;
    QByteArray Blob;
    QString Note1;
    QString Note2;
    QByteArray NoteBlob;

};




struct CustomerGameInfo :public DataObj
{
    CustomerGameInfo(){}
    CustomerGameInfo(QVariantMap data):DataObj(){setData(data);}

    void setData(QVariantMap data)
    {


        DataObj::setData(data);
        CustomerSid = data["CustomerSid"].toString();
        CustomerId = data["CustomerId"].toString();
        GameSid = data["GameSid"].toString();
        LoginType = data["LoginType"].toString();
        LoginAccount = data["LoginAccount"].toString();
        LoginPassword = data["LoginPassword"].toString();
        ServerName = data["ServerName"].toString();
        Characters = data["Characters"].toString();
        LastTime = data["LastTime"].toString();
        Note1 = data["Note1"].toString();

    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();
        d["CustomerSid"] = CustomerSid;
        d["CustomerId"] = CustomerId;
        d["GameSid"] = GameSid;
        d["LoginType"] = LoginType;
        d["LoginAccount"] = LoginAccount;
        d["LoginPassword"] = LoginPassword;
        d["ServerName"] = ServerName;
        d["Characters"] = Characters;
        d["LastTime"] = LastTime;
        d["Note1"] = Note1;


        return d;
    }
    QString CustomerSid;
    QString CustomerId;
    QString GameSid;
    QString LoginType;
    QString LoginAccount;
    QString LoginPassword;
    QString ServerName;
    QString Characters;
    QString LastTime;
    QString Note1;
};


struct OrderData :public DataObj
{
    OrderData()
    {
        while(User.length()<6)
            User.append("");
        while(StepTime.length()<6)
            StepTime.append("");

        while(Note0.length()<6)
            Note0.append("");

        while(Money.length()<3)
            Money.append("");




    }
    OrderData(QVariantMap data):DataObj(){OrderData();setData(data);}

    void setData(QVariantMap data)
    {


        DataObj::setData(data);

        CustomerSid = data["CustomerSid"].toString();
        UiRecord = data["UiRecord"].toString();
        Step = data["Step"].toString();
        StepTime = data["StepTime"].toString().split(",");
        User = data["User"].toString().split(",");
        Owner = data["Owner"].toString();
        PaddingUser = data["PaddingUser"].toString();
        GameSid = data["GameSid"].toString();
        Item = data["Item"].toString();
        Cost = data["Cost"].toString();
        Bouns = data["Bouns"].toString();
        PayType = data["PayType"].toString();
        CanSelectPayType = data["CanSelectPayType"].toString();
        GameRate=data["GameRate"].toString();
        ExRateSid = data["ExRateSid"].toString();
        PrimeRateSid = data["PrimeRateSid"].toString();
        Money = data["Money"].toString().split(";");
        Note0 = data["Note0"].toString().split(";;");
        if(data["Note0"].toString().split(";;").length()<6)
            Note0 = data["Note0"].toString().split(","); //for before v1.09.0212

        ListCost = data["ListCost"].toString().split(";;");

        ListBouns=data["ListBouns"].toString().split(";;");

        while(ListCost.length()<Item.split(";;").length())
        {
            ListCost.append("");
        }

        ItemInfo = data["ItemInfo"].toString().split(";;");

        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
        Note3 = data["Note3"].toString();
        Note4 = data["Note4"].toString();
        Note5 = data["Note5"].toString();
        Pic0 = data["Pic0"].toString();
        Pic1 = data["Pic1"].toString();
        UpdateTime = data["UpdateTime"].toString();
        OrderDate = data["OrderDate"].toString();
        OrderTime = data["OrderTime"].toString();
        CustomerName = data["CustomerName"].toString();
        Currency = data["Currency"].toString();

        while(Note0.length()<6)
            Note0.append("");
        while(User.length()<6)
            User.append("");
        while(StepTime.length()<6)
            StepTime.append("");

        while(Money.length()<3)
            Money.append("");

    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["CustomerSid"] = CustomerSid;
        re["Step"] = Step;
        re["UiRecord"] = UiRecord;
        re["StepTime"] = StepTime.join(",");
        re["User"] = User.join(",");
        re["Owner"] = Owner;
        re["PaddingUser"] = PaddingUser;
        re["GameSid"] = GameSid;
        re["Item"] = Item;
        re["Cost"] = Cost;
        re["Bouns"] = Bouns;
        re["PayType"] = PayType;
        re["CanSelectPayType"] = CanSelectPayType;
        re["GameRate"] = GameRate;
        re["ExRateSid"] = ExRateSid;
        re["PrimeRateSid"] = PrimeRateSid;
        re["Money"] = Money.join(";");

        for(int i=0;i<Note0.length();i++)
        {
            QString sNote = Note0.at(i);
            Note0[i] = sNote.replace(";;","");
        }

        re["Note0"] = Note0.join(";;");
        re["Note1"] = Note1;
        re["Note2"] = Note2;
        re["Note3"] = Note3;
        re["Note4"] = Note4;
        re["Note5"] = Note5;
        re["Pic0"] = Pic0;
        re["Pic1"] = Pic1;
        re["OrderDate"] = OrderDate;
        re["OrderTime"] = OrderTime;
        re["CustomerName"] = CustomerName;
        re["Currency"] = Currency;


        while(ListCost.length()<Item.split(";;").length())
        {
            ListCost.append("");
        }

        re["ListCost"] =ListCost.join(";;");

        while(ListBouns.length()<Item.split(";;").length())
        {
            ListBouns.append("");
        }

        re["ListBouns"] =ListBouns.join(";;");

        while(ItemInfo.length()<6)
        {
            ItemInfo.append("");
        }

        re["ItemInfo"] =ItemInfo.join(";;");

        return re;

    }

    QString CustomerSid;
    QString CustomerName;
    QString Step;
    QString UiRecord;
    QStringList ItemInfo;
    QStringList StepTime;
    QStringList User;
    QString Owner;
    QString PaddingUser;
    QString PayType;
    QString CanSelectPayType;
    QString GameSid;
    QString Item;
    QStringList ListCost;
    QString Cost="0";
    QString Currency;
    QString Bouns="0";
    QStringList ListBouns;
    QString GameRate="";
    QString ExRateSid="";
    QString PrimeRateSid="";
    QStringList Money;
    QStringList Note0;          //訂單流程備註
    QString Note1;              //訂單留言
    QString Note2;              //備註總金額
    QString Note3;              //下單回報文字
    QString Note4;
    QString Note5;
    QString Pic0;
    QString Pic1;
    QString OrderDate;
    QString OrderTime;




};


struct DataFactory :public DataObj
{
    DataFactory(){}
    bool Enable;

    DataFactory(QVariantMap data){setData(data);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Currency = data["Currency"].toString();

        PayTypeSid = data["PayTypeSid"].toString().split(SPLIT1);

        Sort = data["Sort"].toInt();
    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["Currency"] = Currency;

        re["PayTypeSid"] = PayTypeSid.join(SPLIT1);

        re["Sort"] = Sort;
        return re;
    }
    int Sort=9999;
    QString Gounp="";
    QStringList PayTypeSid;
    QString Currency;

};

struct DataGameList :public DataObj
{
    bool Enable;

    int IsDelete =0;

    double GameRate;  //這個只存最新的， 獨立開一個table GameRate, 存歷史記錄
    QString UserSid="";
    QString SellNote; //價目表
    QString BK;
    DataGameList():DataObj(){};
    DataGameList(const QVariantMap &data){setData(data);}

    void setData(const QVariantMap &data)
    {
        DataObj::setData(data);

        IsDelete =data["IsDelete"].toInt();

        Enable = data["Enable"].toBool();

        GameRate=data["GameRate"].toDouble();

        UserSid=data["UserSid"].toString();

        SellNote = data["SellNote"].toString();
        BK = data["BK"].toString();

    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["Enable"] = Enable;

        re["GameRate"] = QString::number(GameRate);

        re["UserSid"] = UserSid;

        re["SellNote"] = SellNote;

        re["IsDelete"] = IsDelete;
        re["BK"] = BK;

        return re;
    }
};

struct DataGameRate
{
    DataGameRate(){}
    DataGameRate(QVariantMap data){setData(data);}

    QString BK;
    void setData(QVariantMap data)
    {
        Sid =data["Sid"].toString();
        GameSid =data["GameSid"].toString();
        GameName =data["GameName"].toString();
        Rate =data["Rate"].toString();
        UserSid =data["UserSid"].toString();
        UpdateTime =data["UpdateTime"].toString();
        BK = data["BK"].toString();

    }

    QVariantMap data()
    {
        QVariantMap re;

        re["Sid"]=Sid;
        re["GameSid"]=GameSid;
        re["GameName"]=GameName;
        re["Rate"]=Rate;
        re["UserSid"]=UserSid;
        re["UpdateTime"]=UpdateTime;
        re["BK"] = BK;

        return re;
    }

    QString Sid="";

    QString GameSid="";

    QString GameName="";

    QString Rate="";

    QString UserSid="";

    QString UpdateTime;
};

struct DataGameItem :public DataObj
{
    DataGameItem(){}
    DataGameItem(QVariantMap data):DataObj()
    {

        setData(data);
    }

    void setData(QVariantMap data)
    {
        DataObj::setData(data);
        GameSid = data["GameSid"].toString();
        Sort=data["Sort"].toInt();
        Enable = data["Enable"].toBool();
        IsDelete = data["IsDelete"].toInt();
        OrderNTD = data["OrderNTD"].toString();
        Bonus = data["Bonus"].toString();
        NTD = data["NTD"].toString();
        EnableCost = data["EnableCost"].toBool();
        Cost = data["Cost"].toString();
        AddValueTypeSid= data["AddValueTypeSid"].toString();
        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
        ForApi = data["ForApi"].toInt();
    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["GameSid"]=GameSid;
        d["Sort"]=Sort;
        d["Enable"]=Enable;
        d["IsDelete"] = IsDelete;
        d["OrderNTD"]=OrderNTD;
        d["Bonus"]=Bonus;
        d["NTD"]=NTD;
        d["EnableCost"]=EnableCost;
        d["Cost"]=Cost;
        d["AddValueTypeSid"]=AddValueTypeSid;
        d["Note1"]=Note1;
        d["Note2"]=Note2;
        d["ForApi"]= ForApi;

        return d;
    }


    QString GameSid;
    bool Enable;
    int IsDelete =0;
    int ForApi=1;
    int Sort;
    QString OrderNTD;
    QString Bonus;
    QString NTD;
    bool EnableCost;
    QString Cost;
    QString AddValueTypeSid;
    QString Note1;
    QString Note2;

    int Count=0;
};




struct DataRate :public DataObj
{

    DataRate(){}
    DataRate(QVariantMap data):DataObj()
    {
        setData(data);
    }

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        listData = CListPair(data["Name"].toString());
        UserSid = data["UserSid"].toString();
    }

    QString UserSid;

    QVariantMap data()
    {
        QVariantMap re = DataObj::data();

        re["Name"] = listData.toString();
        re["UserSid"] =UserSid;
        return re;
    }

    QStringList listKey()
    {
        return listData.listFirst();
    }

    QStringList listValue()
    {
        return listData.listSecond();

    }

    //QList<QPair<QString,QString> > listData;

    CListPair listData;

    double findValue(QString currency)
    {
        return listData.findValue(currency).toDouble();
    }

    double NTD()
    {
        double iRe=0.00;

        if(listData.length()>0)
            iRe = listData.at(0).second.toDouble();

        return iRe;
    }

    double USD()
    {
        double iRe=0.00;

        if(listData.length()>1)
            iRe = listData.at(1).second.toDouble();

        return iRe;
    }

    double HKD()
    {
        double iRe=0.00;

        if(listData.length()>2)
            iRe = listData.at(2).second.toDouble();

        return iRe;
    }

    double RMB()
    {
        double iRe=0.00;

        if(listData.length()>3)
            iRe = listData.at(3).second.toDouble();

        return iRe;
    }

    double MYR()
    {
        double iRe=0.00;

        if(listData.length()>4)
            iRe = listData.at(4).second.toDouble();

        return iRe;
    }

    double SGD()
    {
        double iRe=0.00;

        if(listData.length()>5)
            iRe = listData.at(5).second.toDouble();

        return iRe;
    }

};

/*
// old ,waitting delete it
struct GameList
{

    void setGameList(QVariantList list)
    {
        listData.clear();

        for(int i=0;i<list.length();i++)
        {
            QVariantMap data = list.at(i).toMap();

            GameData game;

            game.Sid = data["Sid"].toString();

            game.Id = data["Id"].toString();

            game.Name = data["Name"].toString();

            game.Enable = data["Enable"].toInt();

            game.UpdateTime = data["UpdateTime"].toString();

            game.GameRate = data["GameRate"].toDouble();

            listData.append(game);
        }

    }

    QVariantList data()
    {
        QVariantList listRe;

        for(int i=0;i<listData.length();i++)
        {
            GameData game = listData.at(i);
            QVariantMap v;

            v["Sid"] = game.Sid;
            v["Id"] = game.Id;
            v["Name"] = game.Name;
            v["UpdateTime"] = game.UpdateTime;
            v["Enable"] = game.Enable;

            v["GameRate"] = game.GameRate;


            listRe.append(v);
        }

        return listRe;
    }

    struct GameData
    {
        QString Sid;

        QString Id;

        QString Name;

        double GameRate;

        bool Enable;

        QString UpdateTime;

    };


    QList<GameData> listData;

};
*/


struct DataItemCount :public DataObj
{
    DataItemCount(){}

    DataItemCount(QVariantMap data){setData(data);}



    QString  UserSid;

    QString GameSid;

    QString  GameItemSid;

    qlonglong ChangeValue=0;

    qlonglong TotalCount=0;

    qlonglong TotalSell=0;
    QString OrderSid;

    QString Note;

    QString GameRate;

    QString Pic0;
    QString Pic1;

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        UserSid = data["UserSid"].toString();

        GameSid=data["GameSid"].toString();

        GameItemSid=data["GameItemSid"].toString();

        ChangeValue = data["ChangeValue"].toLongLong();

        TotalCount = data["TotalCount"].toLongLong();
        TotalSell = data["TotalSell"].toLongLong();
        OrderSid = data["OrderSid"].toString();
        GameRate = data["GameRate"].toString();
        Pic0 = data["Pic0"].toString();

        Pic1 = data["Pic1"].toString();
        Note = data["Note"].toString();

    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["UserSid"] = UserSid;
        re["GameSid"] = GameSid;
        re["GameItemSid"] = GameItemSid;
        re["GameRate"] = GameRate;

        re["ChangeValue"] = ChangeValue;

        re["TotalCount"] = TotalCount;
        re["TotalSell"] = TotalSell;
        re["OrderSid"] = OrderSid;
        re["Pic0"] = Pic0;
        re["Pic1"] = Pic1;


        re["Note"] = Note;

        return re;
    }
};



struct DataPayType :public DataObj
{
    DataPayType(){}

    DataPayType(QVariantMap data)
    {
        setData(data);

    }

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Value.clear();

        Value = data["Value"].toString().split(",");

        while(Value.length()<4)
            Value.append("");

        SubValue =data["SubValue"].toString().split(",");

        Currency =data["Currency"].toString();
        Sort = data["Sort"].toInt();
    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        while(Value.length()<4)
            Value.append("");

        re["Value"] =Value.join(",");

        re["SubValue"] =SubValue.join(",");

        re["Currency"] =Currency;
        re["Sort"] =Sort;

        return re;
    }

    QStringList Value={"1","1","1","1"};
    int Sort=0;
    QString Currency;

    QStringList SubValue={"1"};
};



class TimerThread : public QThread {
    Q_OBJECT

public:
    TimerThread(QObject *parent = nullptr) : QThread(parent), m_stop(false)
    {
        start();
    }

    void stop() {
        m_stop = true;
    }

    qint64 elapsedTime() const {
        return m_timer.elapsed();
    }

    QString convertMilliseconds() {

        long long milliseconds = elapsedTime();
        // 计算小时、分钟、秒和毫秒
        long long totalSeconds = milliseconds / 1000;
        long long hours = totalSeconds / 3600;
        long long minutes = (totalSeconds % 3600) / 60;
        long long seconds = totalSeconds % 60;
        long long milliseconds_remainder = milliseconds % 1000;

        QString sRe=QString::number(minutes)+":"+QString::number(seconds)+"."+QString::number(milliseconds_remainder);

        return "["+sRe+"] ";
    };


protected:
    void run() override {
        m_timer.start();
        while (!m_stop) {
            // 每隔一段时间打印一次
            QThread::msleep(1000); // 1秒
        }
    }

private:
    QElapsedTimer m_timer;
    bool m_stop;
};









#endif // VOJ_H
