#ifndef VOJDATA_H
#define VOJDATA_H

#include <QString>
#include <QDateTime>
#include <QVariantMap>
#define VAR(x) #x

// name follow database fieldName





struct UserData
{
    QString Sid;
    QString Id;
    QString Password;
    QString Name;
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
    QString UpdateTime;

    UserData(){}

    UserData(QVariantMap dData):UserData(){setData(dData);}

    void setData(QVariantMap data)
    {
        Sid = data["Sid"].toString();
        Id = data["Id"].toString();
        Password = data["Password"].toString();
        Name = data["Name"].toString();
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
        UpdateTime = data["UpdateTime"].toString();
    }

    QVariantMap data()
    {
        QVariantMap re;
        re["Sid"] = Sid;
        re["Id"] = Id;
        re["Password"] = Password;
        re["Name"] = Name;
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
        re["UpdateTime"] = UpdateTime;
        return re;
    }
};


class DataExchange
{
public:

    enum{_NTD=0,_HKD,_RMB,_MYR,SGD};
    DataExchange()
    {
        listKey.clear();
        listKey<<"NTD"<<"HKD"<<"RMB"<<"MYR"<<"SGD";
    }

    DataExchange(QVariantList data):DataExchange()
    {
        setData(data);
    }

    QStringList listKey;

    struct Rate
    {

        QString Sid;
        QString UpdateTime;
        double NTD=0.00;
        double HKD=0.00;
        double RMB=0.00;
        //Malaysia
        double MYR=0.00;
        //Singapore
        double SGD=0.00;

        QStringList list()
        {
            QStringList re;

            re.append(QString::number(NTD));
            re.append(QString::number(HKD));
            re.append(QString::number(RMB));
            re.append(QString::number(MYR));
            re.append(QString::number(SGD));

            return re;
        }

    };

    Rate last(){return m_listData.last();}

    Rate rate(QString sId)
    {
        Rate re;

        for(int i=0;i<m_listData.length();i++)
        {
            if(m_listData.at(i).Sid.trimmed()==sId.trimmed())
                re = m_listData[i];

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
            rate.NTD =data["NTD"].toDouble();
            rate.HKD = data["HKD"].toDouble();
            rate.RMB = data["RMB"].toDouble();
            rate.MYR = data["MYR"].toDouble();
            rate.SGD = data["SGD"].toDouble();

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
            t["NTD"] = m_listData.at(i).NTD;
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


struct GameItem
{

    GameItem(){}

    GameItem(QVariantMap data){setData(data);}

    void setData(QVariantMap data)
    {
        Sid = data["Sid"].toInt();

        GameId = data["GameSid"].toInt();

        Enable = data["Enable"].toBool();

        Name = data["Name"].toString();

        OrderNTD = data["OrderNTD"].toDouble();

        OrderUSD = data["OrderUSD"].toDouble();

        NTD = data["NTD"].toDouble();

        EnableCost = data["EnableCost"].toBool();

        Cost = data["Cost"].toString();

        Note1 = data["Note1"].toString();

        Note2 = data["Note2"].toString();

        UpdateTime = data["UpdateTime"].toString();

    }

    int Sid;

    int GameId;

    bool Enable;

    QString  Name;

    double OrderNTD;

    double OrderUSD;

    double NTD;

    bool EnableCost;

    QString Cost;

    QString Note1;

    QString Note2;

    QString UpdateTime;
};







    class VojData
    {
    public:
        VojData(){}



    };







#endif // VOJDATA_H
