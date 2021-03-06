#ifndef VOJDATA_H
#define VOJDATA_H

#include <QString>
#include <QDateTime>
#include <QVariantMap>
#define VAR(x) #x

// name follow database fieldName


struct DataObj
{
    DataObj(){}
    DataObj(QVariantMap data):DataObj(){setData(data);}
    QString Sid="";

    QString Id;

    QString Name;

    QString UpdateTime;

    void setData(QVariantMap data)
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

struct CustomerData :public DataObj
{
    CustomerData(){}
    CustomerData(QVariantMap data):DataObj(){setData(data);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Class = data["Class"].toString();
        Money = data["Money"].toString();
        if(Money=="")
            Money="0";

        Currency = data["Currency"].toString();
        PayType =data["PayType"].toString();
        PayInfo =data["PayInfo"].toString();
        UserSid = data["UserSid"].toString();
        Note1   =data["Note1"].toString();
        Note2   =data["Note2"].toString();


    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["Class"] = Class;
        d["Money"] = Money;
        d["Currency"] = Currency;
        d["PayType"] = PayType;
        d["PayInfo"] =PayInfo;
        d["UserSid"] =UserSid;
        d["Note1"] = Note1;
        d["Note2"]= Note2;

        return d;
    }

    QString Class;
    QString Money="0";
    QString Currency;
    QString PayType;
    QString PayInfo;
    QString UserSid;
    QString Note1;
    QString Note2;
};

struct CustomerCost
{
    CustomerCost(){}
    CustomerCost(QVariantMap data)
    {
        Sid = data["Sid"].toString();
        CustomerSid = data["CustomerSid"].toString();
        Currency = data["Currency"].toString();
        OrderId = data["OrderId"].toString();
        Change = data["Change"].toString();
        Type = data["Type"].toString();
        Rate = data["Rate"].toString();
        AddRate = data["AddRate"].toString();

        Value = data["Value"].toString();

        if(Value=="")
            Value="0";

        UserSid = data["UserSid"].toString();
        OrderTime = data["OrderTime"].toString();
        UpdateTime = data["UpdateTime"].toString();
        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
    }

    QVariantMap data()
    {
        QVariantMap re;

        re["Sid"]=Sid;
        re["CustomerSid"]=CustomerSid;
        re["OrderId"]=OrderId;
        re["Currency"]=Currency;
        re["Type"]=Type;
        re["Rate"]=Rate;
        re["AddRate"]=AddRate;
        re["Change"]=Change;
        re["Value"]=Value;
        re["UserSid"]=UserSid;
        re["OrderTime"]=OrderTime;
        re["UpdateTime"]=UpdateTime;
        re["Note1"]=Note1;
        re["Note2"]=Note2;

        return re;
    }



    QString Sid;
    QString CustomerSid;
    QString OrderId;
    QString Rate;
    QString AddRate="0";
    QString Type;
    QString Currency;
    QString Change ="0";
    QString Value ="0";
    QString UserSid;
    QString OrderTime;
    QString UpdateTime;
    QString Note1;
    QString Note2;

};


struct DataCustomerClass :public DataObj
{

};




struct CustomerGameInfo :public DataObj
{
    CustomerGameInfo(){}
    CustomerGameInfo(QVariantMap data):DataObj(){setData(data);}

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        CustomerId = data["CustomerId"].toString();
        GameSid = data["GameSid"].toString();
        LoginType = data["LoginType"].toString();
        LoginAccount = data["LoginAccount"].toString();
        ServerName = data["ServerName"].toString();
        Character = data["Character"].toString();
        LastTime = data["LastTime"].toString();
        Note1 = data["Note1"].toString();

    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["CustomerId"] = CustomerId;
        d["GameSid"] = GameSid;
        d["LoginType"] = LoginType;
        d["LoginAccount"] = LoginAccount;
        d["ServerName"] = ServerName;
        d["Character"] = Character;
        d["LastTime"] = LastTime;
        d["Note1"] = Note1;


        return d;
    }

    QString CustomerId;
    QString GameSid;
    QString LoginType;
    QString LoginAccount;
    QString ServerName;
    QString Character;
    QString LastTime;
    QString Note1;
};


struct OrderData :public DataObj
{
    OrderData()
    {
        while(User.length()<5)
            User.append("");
        while(StepTime.length()<5)
            StepTime.append("");
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
        Item = data["Item"].toString();
        Cost = data["Cost"].toString();
         Bouns = data["Bouns"].toString();
        AddValueType = data["AddValueType"].toString();
        Rate = data["Rate"].toString();
        Note0 = data["Note0"].toString();
        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
        Note3 = data["Note3"].toString();
        Note4 = data["Note4"].toString();
        Note5 = data["Note5"].toString();
        UpdateTime = data["UpdateTime"].toString();
        OrderDate = data["OrderDate"].toString();
        OrderTime = data["OrderTime"].toString();

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
        re["Item"] = Item;
        re["Cost"] = Cost;
                re["Bouns"] = Bouns;
        re["AddValueType"] = AddValueType;
        re["Rate"] = Rate;
        re["Note0"] = Note0;
        re["Note1"] = Note1;
        re["Note2"] = Note2;
        re["Note3"] = Note3;
        re["Note4"] = Note4;
        re["Note5"] = Note5;
        re["OrderDate"] = OrderDate;
        re["OrderTime"] = OrderTime;


        return re;

    }

    QString CustomerSid;
    QString Step;
    QString UiRecord;
    QStringList StepTime;
    QStringList User;
    QString Owner;
    QString PaddingUser;
    QString AddValueType;
    QString Item;
    QString Cost="0";
        QString Bouns="0";
    QString Rate="";
    QString Note0;
    QString Note1;
    QString Note2;
    QString Note3;
    QString Note4;
    QString Note5;
    QString UpdateTime;
    QString OrderDate;
    QString OrderTime;




};


struct DataFactory :public DataObj
{
    bool Enable;

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Currency = data["Currency"].toString();
        SellCurrency = data["SellCurrency"].toString();
        Cost = data["Cost"].toString();
    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["Currency"] = Currency;
        re["SellCurrency"] = SellCurrency;
        re["Cost"] = Cost;

        return re;
    }

    QString Currency;
    QString SellCurrency;
    QString Cost;
};

struct DataGameList :public DataObj
{
    bool Enable;

    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        Enable = data["Enable"].toBool();
    }

    QVariantMap data()
    {
        QVariantMap re =DataObj::data();

        re["Enable"] = Enable;

        return re;
    }
};


//struct DataGameList
//{

//    void setGameList(QVariantList list)
//    {
//        listData.clear();

//        for(int i=0;i<list.length();i++)
//        {
//            QVariantMap data = list.at(i).toMap();

//            GameData game;

//            game.Sid = data["Sid"].toString();

//            game.Id = data["Id"].toString();

//            game.Name = data["Name"].toString();

//            game.Enable = data["Enable"].toInt();

//            game.UpdateTime = data["UpdateTime"].toString();

//            listData.append(game);
//        }

//    }

//    QVariantList data()
//    {
//        QVariantList listRe;

//        for(int i=0;i<listData.length();i++)
//        {
//            GameData game = listData.at(i);
//            QVariantMap v;

//            v["Sid"] = game.Sid;
//            v["Id"] = game.Id;
//            v["Name"] = game.Name;
//            v["UpdateTime"] = game.UpdateTime;
//            v["Enable"] = game.Enable;

//            listRe.append(v);
//        }

//        return listRe;
//    }

//    struct GameData
//    {
//        QString Sid;

//        QString Id;

//        QString Name;

//        bool Enable;

//        QString UpdateTime;

//    };


//    QList<GameData> listData;

//};


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
        Enable = data["Enable"].toBool();
        OrderNTD = data["OrderNTD"].toString();
        Bouns = data["Bouns"].toString();
        NTD = data["NTD"].toString();
        EnableCost = data["EnableCost"].toBool();
        Cost = data["Cost"].toString();
        Note1 = data["Note1"].toString();
        Note2 = data["Note2"].toString();
    }

    QVariantMap data()
    {
        QVariantMap d = DataObj::data();

        d["GameSid"]=GameSid;
        d["Enable"]=Enable;
        d["OrderNTD"]=OrderNTD;
        d["Bouns"]=Bouns;
        d["NTD"]=NTD;
        d["EnableCost"]=EnableCost;
        d["Cost"]=Cost;
        d["Note1"]=Note1;
        d["Note2"]=Note2;


        return d;
    }


    QString GameSid;
    bool Enable;
    QString OrderNTD;
    QString Bouns;
    QString NTD;
    bool EnableCost;
    QString Cost;
    QString Note1;
    QString Note2;

    int Count=0;
};


class DataExchange
{
public:

    enum{_NTD=0,_HKD,_RMB,_MYR,SGD};
    DataExchange()
    {
        listKey.clear();
        listKey<<"?????????(NTD)"<<"??????(USD)"<<"??????(HKD)"<<"?????????(RMB)"<<"?????????(MYR)"<<"????????????(SGD)";
    }

    DataExchange(QVariantList data):DataExchange()
    {
        setData(data);
    }

    QStringList listKey;

    struct Rate
    {

        void fromPrime(QVariantMap data)
        {
            Sid = data["Sid"].toString();
            UpdateTime = data["UpdateTime"].toString();

            listKey.clear();

            listKey.append("?????????(NTD)");
            QStringList list = data["Name"].toString().split(";");

            if(list.length()>1)
            {
                QStringList tmp = list.at(1).split("=");
                if(tmp.length()>1)
                {
                    listKey.append(tmp.first());

                    USD = tmp.last().toDouble();
                }
            }

            if(list.length()>2)
            {
                QStringList tmp = list.at(2).split("=");
                if(tmp.length()>1)
                {
                    listKey.append(tmp.first());

                    HKD = tmp.last().toDouble();
                }
            }

            if(list.length()>3)
            {
                QStringList tmp = list.at(3).split("=");
                if(tmp.length()>1)
                {
                    listKey.append(tmp.first());

                    RMB = tmp.last().toDouble();
                }
            }

            if(list.length()>4)
            {
                QStringList tmp = list.at(4).split("=");
                if(tmp.length()>1)
                {
                    listKey.append(tmp.first());

                    MYR = tmp.last().toDouble();
                }
            }

            if(list.length()>5)
            {
                QStringList tmp = list.at(5).split("=");
                if(tmp.length()>1)
                {
                    listKey.append(tmp.first());

                    SGD = tmp.last().toDouble();
                }
            }

        }


        QString Sid;
        QString UpdateTime;

        double USD=0.00;
        double HKD=0.00;
        double RMB=0.00;
        //Malaysia
        double MYR=0.00;
        //Singapore
        double SGD=0.00;
        QStringList listKey;

        QStringList list()
        {
            QStringList re;

            re.append(QString::number(USD));
            re.append(QString::number(HKD));
            re.append(QString::number(RMB));
            re.append(QString::number(MYR));
            re.append(QString::number(SGD));

            while(re.length()<listKey.length())
            {
                re.append("0");
            }

            return re;
        }

        double value(QString sKey)
        {
            int iIdx = qBound(0,listKey.indexOf(sKey),listKey.length());

            return list().at(iIdx).toDouble();
        }

    };

    Rate last(){return m_listData.last();}

    Rate rate(QString sId)
    {
        Rate re;

        if(m_listData.length()<1)
            return re;

        if(sId=="")
            return last();


        for(int i=0;i<m_listData.length();i++)
        {
            if(m_listData.at(i).Sid.trimmed()==sId.trimmed())
            {
                re = m_listData[i];
            }
        }

        return re;
    }

    void setData(QVariantList list)
    {
        m_listData.clear();

        for(int i=0;i<list.length();i++)
        {
            QVariantMap data = list.at(i).toMap();
            Rate rate;
            rate.Sid = data["Sid"].toString();
            rate.UpdateTime = data["UpdateTime"].toString();
            rate.USD =data["USD"].toDouble();
            rate.HKD = data["HKD"].toDouble();
            rate.RMB = data["RMB"].toDouble();
            rate.MYR = data["MYR"].toDouble();
            rate.SGD = data["SGD"].toDouble();
            rate.listKey = listKey;

            m_listData.append(rate);
        }

    }

    QVariantList data()
    {
        QVariantList re;

        for(int i=0;i<m_listData.length();i++)
        {
            QVariantMap t ;
            t["Sid"] = m_listData.at(i).Sid;
            t["UpdateTime"] = m_listData.at(i).UpdateTime;
            t["USD"] = m_listData.at(i).USD;
            t["HKD"] = m_listData.at(i).HKD;
            t["RMB"] = m_listData.at(i).RMB;
            t["MYR"] = m_listData.at(i).MYR;
            t["SGD"] = m_listData.at(i).SGD;

            re.append(t);
        }

        return re;
    }


    QList<Rate> m_listData;


};


struct PrimeRate :public DataObj
{
    void setData(QVariantMap data)
    {
        DataObj::setData(data);

        QStringList tmp = data["Name"].toString().split(";");

        listData.clear();


        for(int i=0;i<tmp.length();i++)
        {
            QPair<QString,QString> data;
            data.first = tmp.at(i).split("=").first();
            data.second = tmp.at(i).split("=").last();

            listData.append(data);
        }

    }


    QVariantMap data()
    {
        QVariantMap re = DataObj::data();

        QStringList list;

        for(int i=0;i<listData.length();i++)
        {
            QString sTmp = listData.at(i).first+"="+listData.at(i).second;

            list.append(sTmp);
        }

        re["Name"] = list.join(";");

        return re;
    }

    QStringList listKey()
    {
        QStringList listRe;

        for(int i=0;i<listData.length();i++)
        {
            listRe.append(listData.at(i).first);
        }

        return listRe;

    }

    QList<QPair<QString,QString> > listData;

    double USD()
    {
        int iRe=0.00;

        if(listData.length()>=2)
            iRe = listData.at(1).second.toDouble();

        return iRe;
    }

    double HKD()
    {
        int iRe=0.00;

        if(listData.length()>=3)
            iRe = listData.at(2).second.toDouble();

        return iRe;
    }

    double RMB()
    {
        int iRe=0.00;

        if(listData.length()>=4)
            iRe = listData.at(3).second.toDouble();

        return iRe;
    }

    double MYR()
    {
        int iRe=0.00;

        if(listData.length()>=5)
            iRe = listData.at(4).second.toDouble();

        return iRe;
    }

    double SGD()
    {
        int iRe=0.00;

        if(listData.length()>=6)
            iRe = listData.at(5).second.toDouble();

        return iRe;
    }

};


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

            listRe.append(v);
        }

        return listRe;
    }

    struct GameData
    {
        QString Sid;

        QString Id;

        QString Name;

        bool Enable;

        QString UpdateTime;

    };


    QList<GameData> listData;

};


//struct GameItem
//{

//    GameItem(){}

//    GameItem(QVariantMap data){setData(data);}

//    void setData(QVariantMap data)
//    {
//        Sid = data["Sid"].toInt();

//        GameId = data["GameSid"].toInt();

//        Enable = data["Enable"].toBool();

//        Name = data["Name"].toString();

//        OrderNTD = data["OrderNTD"].toDouble();

//        Bouns = data["Bouns"].toDouble();

//        NTD = data["NTD"].toDouble();

//        EnableCost = data["EnableCost"].toBool();

//        Cost = data["Cost"].toString();

//        Note1 = data["Note1"].toString();

//        Note2 = data["Note2"].toString();

//        UpdateTime = data["UpdateTime"].toString();

//    }

//    int Sid;

//    int GameId;

//    bool Enable;

//    QString  Name;

//    double OrderNTD;

//    double Bouns;

//    double NTD;

//    bool EnableCost;

//    QString Cost;

//    QString Note1;

//    QString Note2;

//    QString UpdateTime;
//};







class VojData
{
public:
    VojData(){}



};







#endif // VOJDATA_H
