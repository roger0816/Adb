#include "Global.h"

Global *Global::m_pInstance = nullptr;

Global::Global(QObject *parent)
    : QObject{parent}
{
    loadConfig();

  //  m_ping.start();
}

Global::~Global()
{
    qDebug()<<"~Global";

    m_ping.m_bIsStop = true;

    m_ping.wait(1000);

    m_ping.quit();
}

void Global::setServer(bool b, QString sIp, QString sPort)
{
    m_action.setServer(b,sIp,sPort);

    //   m_dataSync.setServer(b,sIp,sPort);
}

QStringList Global::listMapToList(const QVariantList list, QString sKey)
{
    QStringList listRe;

    foreach(QVariant v,list)
    {
        if(v.toMap().keys().contains(sKey))
        {
            listRe.append(v.toMap()[sKey].toString());
        }
    }

    return listRe;
}





bool Global::isDiff(QStringList listKey, QVariantMap pre, QVariantMap current)
{


    for(int i=0;i<listKey.length();i++)
    {
        QString sKey = listKey.at(i);

        if(pre.keys().indexOf(sKey)<0 && current.keys().indexOf(sKey)<0)
            continue;

        if(pre.keys().indexOf(sKey)<0 && current.keys().indexOf(sKey)>=0)
            return true;

        if(pre.keys().indexOf(sKey)>=0 && current.keys().indexOf(sKey)<0)
            return true;


        if(pre[sKey]!= current[sKey])
            return true;

    }


    return false;

}

QString Global::displayCurrency(QString st)
{
    return st;
    QString sRe="新台幣";

    if(st.trimmed()=="HKD")
        sRe="港幣";
    if(st.trimmed()=="USD")
        sRe="美金";
    else if(st.trimmed()=="RMB")
        sRe="人民幣";
    else if(st.trimmed()=="MYR")
        sRe="林吉特";
    else if(st.trimmed()=="SGD")
        sRe="新加坡元";
    return sRe;

}

QString Global::originCurrency(QString st)
{
    return st;
    QString sRe="NTD";

    if(st.trimmed()=="港幣")
        sRe="HKD";
    else if(st.trimmed()=="人民幣")
        sRe="RMB";
    else if(st.trimmed()=="美金")
        sRe="USD";
    else if(st.trimmed()=="林吉特")
        sRe="MYR";
    else if(st.trimmed()=="新加坡元")
        sRe="SGD";
    return sRe;
}

QString Global::displayCustomerLv(QString iLv)
{

    QString sRe="一般";
    if(iLv=="1")
        sRe = "VIP";

    return sRe;
}

QString Global::sidAdd(QString last)
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
}

QString Global::addFlow(QString st, QString currency)
{
    int iFlowCount =0;
    if(currency.toUpper().contains("USD"))
        iFlowCount =2;
    else if(currency.toUpper().contains("SGD"))
        iFlowCount =1;

    return addFlow(st,iFlowCount);
}

QString Global::addFlow(QString sDouble, int flowCount)
{
    QString st =sDouble;

    if(st.length()<=0)
        return "";

    bool bArrow0 = true;

    if(st.toDouble()<0)
    {
        bArrow0 = false;

        st.replace("-","");
    }





    auto nSt=[=](QString st,int iN)
    {
        QString sRe="";

        while(sRe.length()<iN)
        {
            sRe+=st;
        }

        return sRe;
    };




    int iInt = st.split(".").first().toInt();

    QString sFlow="";
    //切整數與浮店數
    if(st.split(".").length()>=2)
    {
        sFlow = st.split(".").at(1);
    }

    //浮點數補0
    while(sFlow.length()<flowCount+1)
        sFlow+="0";


    //    if(!bArrow0)  //負數
    //    {
    //        if(flowCount==0)
    //            return "-"+QString::number(iInt);
    //        else
    //        {
    //             return "-"+QString::number(iInt)+sFlow.mid(0,flowCount);
    //        }

    //    }


    bool bAddInt = false; //是否進位到整數

    if(flowCount==0)    //取整數情況
    {

        if(sFlow.mid(0,1)!="0")
            bAddInt= true;
        sFlow="";
    }
    else                //取指定浮點數位
    {
        QString sFlowL = sFlow.mid(0,flowCount); //固定數
        QString sFlowR = sFlow.mid(flowCount,1); //辨視數

        bool bIsMax =false;   //分辨是否為 99...

        if(sFlowL==nSt("9",flowCount))
            bIsMax = true;

        if(sFlowR=="0")     //不需進位
        {
            sFlow = sFlowL;

        }
        else                //無條件進位
        {
            if(bIsMax)          //進位到整數
            {
                bAddInt = true;

                sFlow=nSt("0",flowCount);
            }
            else
                sFlow=QString::number(sFlowL.toInt()+1);
        }



    }


    if(bAddInt)
        iInt++;

    QString sRe= QString::number(iInt);

    if(sFlow!="")
        sRe=sRe+"."+sFlow;

    if(!bArrow0)
        sRe="-"+sRe;
    return sRe;
}

double Global::addFlow(double value, int flowCount)
{
    QString st = QString::number(value,'f',flowCount+1);

    return addFlow(st,flowCount).toDouble();
}

QVariantList Global::reData(QVariantList data, QStringList listKey)
{
    QVariantList listRe;

    for(int i=0;i<data.length();i++)
    {
        QVariantMap v;
        QVariantMap t =data.at(i).toMap();

        for(int j=0;j<listKey.length();j++)
        {
            QString sKey = listKey.at(j);
            v[sKey] = t[sKey];
        }

        listRe.append(v);
    }

    return listRe;
}

QStringList Global::toList(QString sData)
{
    return sData.split(SPLIT1);
}

QString Global::toString(QStringList list)
{
    return list.join(SPLIT1);
}

QString Global::toString(CListPair listPair)
{
    return listPair.toString();
}

CListPair Global::toListPair(QString st)
{
    return CListPair(st);
}

QStringList Global::mapping(CListPair listData, QStringList listKey, bool bMappingFirst)
{
    QStringList listRe;

    QStringList keys = listData.listFirst();

    QStringList values = listData.listSecond();

    if(!bMappingFirst)
    {
        keys = listData.listSecond();

        values = listData.listFirst();
    }

    qDebug()<<"list key : "<<listKey<<" ,keys:  "<<keys<<",value "<<values;


    for(int i=0;i<listKey.length();i++)
    {
        int iIdx = keys.indexOf(listKey.at(i));

        if(iIdx<0)
            continue;

        listRe.append(values.at(iIdx));

    }


    return listRe;
}

void Global::loadConfig()
{
    qDebug()<<"loading config";

    QString file=QCoreApplication::applicationDirPath()+"/conf.ini";

    QSettings conf(file, QSettings::IniFormat);

    QStringList list = conf.allKeys();

    if(list.indexOf("ServerIp")<0)
        list.append("ServerIp");


    if(list.indexOf("ServerPort")<0)
        list.append("ServerPort");

    for(int i=0;i<list.length();i++)
    {
        QString sKey = list.at(i);

        if(sKey=="ServerIp")
        {
            m_config[list.at(i)]= conf.value(list.at(i),"127.0.0.1");
        }
        else if(sKey=="ServerPort")
        {
            m_config[list.at(i)]= conf.value(list.at(i),"6000");
        }
        else
        {
            m_config[list.at(i)]= conf.value(list.at(i));
        }
    }


}







Global &Global::Instance()
{
    //    if(m_pInstance==0)
    //        m_pInstance=new Global();
    //    return *m_pInstance;
    static Global global;
    return global;
}

QVariant Global::config(QString st)
{

    return m_config.value(st);
}

QDateTime Global::dateTimeUtc8()
{
    return QDateTime::currentDateTimeUtc().addSecs(60*60*8+m_virtualSec);
}

QString Global::userLvToStr(int iLv)
{

    QString sLv = "客服專員";
    if(iLv==99)
        sLv = "系統管理員";
    else if(iLv==USER_LV::_LV2)
        sLv = "儲值專員";
    else if(iLv==USER_LV::_LV3)
        sLv = "主管";
    else if(iLv==USER_LV::_LV4)
        sLv = "會計";

    return sLv;
}

//double Global::subFloat(double v, int f)
//{
//    double re;

//    re = QString::number(v,'f',f).toDouble();

//    return re;


//    QStringList list = QString::number(v).split(".");

//    if(list.length()<2)
//    {
//        return list.first().toInt();
//    }

//    QString s0=list.first();
//    QString s1 = list.last();

//    if(s1.toInt()==0 || s1.length()<=f)
//    {
//        return v;
//    }


//    if(f==0)
//    {
//        int iTmp=s0.toInt()+1;
//        return iTmp;
//    }
//    else
//    {
//            //to do
//    }



//    return re;
//}

bool Global::checkSearch(QString sFilterStr, QVariantMap dTarget, bool caseNeedDiff)
{
    if(sFilterStr.trimmed()=="")
        return true;

    QStringList listKey = sFilterStr.split("&");

    if(listKey.length()>0 && listKey.last().trimmed()=="")
        listKey.pop_back();

    qDebug()<<"list key : "<<listKey;

    bool bRe = false;

    QList<int> listOk;

    foreach(QString v, listKey)
    {
        int iOk = 0;
        QString dateTime=QDateTime::fromString("yyyyMMddhhmmss").toString("yyyy/MM/dd hh:mm:ss");

        QString sKey = v.trimmed();

        if(!caseNeedDiff)
            sKey = sKey.toUpper();



        //  if(data["Name"].toString().indexOf(m_sSearchKey,Qt::CaseInsensitive)>=0)
        //奇怪，Qt::CaseInsensitive 不起作用

        QStringList listTargetKey = dTarget.keys();

        for(int i=0;i<listTargetKey.length();i++)
        {
            QString sTargetKey = listTargetKey.at(i);
            QVariant v = dTarget[sTargetKey];

            QString sTarget="";

            if(v.type()==QVariant::Bool)
            {
                if(sKey=="是" ||sKey=="對" || sKey=="有" || sKey=="1" || sKey=="TRUE")
                {
                    if(v==true)
                        iOk=1;
                }
                else if(sKey=="不是" || sKey=="否" ||  sKey=="無"|| sKey=="沒有" || sKey=="0" || sKey=="FALSE")
                {
                    if(v==false)
                        iOk=1;
                }
            }

            else if(v.type()==QVariant::StringList)
            {
                foreach(QString st,v.toStringList())
                {
                    QString sTmp=st.trimmed();
                    if(!caseNeedDiff)
                        sTmp=sTmp.toUpper();

                    if(sTmp.contains(sKey))
                        iOk=1;
                }

            }
            else
            {

                QString sTmp=v.toString().trimmed();
                if(!caseNeedDiff)
                    sTmp=sTmp.toUpper();

                if(sTmp.contains(sKey))
                    iOk=1;
            }

        }



        listOk.append(iOk);
    }

    bRe = !listOk.contains(0);

    return bRe;
}

QString Global::currencyStr(QString st)
{

    return st;  //to do 未完成
    QString sInt=st.split(".").first();
    QString sFlot="";

    if(st.split(".").length()>1)
        sFlot = st.split(".").at(1);

    QString sReInt="";

    int len=st.length();

    if(len>3)
    {
        int iTmp = st.length()%3;
        if(iTmp!=0)
        {
            sReInt=st.insert(iTmp,',');
            iTmp+=1;
        }
        if(len>=6)
        {
            sReInt=st.insert(iTmp+3,',');
            iTmp+=1;
        }
        if(len>=9)
        {
            sReInt=st.insert(iTmp+6,',');
        }
    }
    else
    {
        return st;
    }

    if(sFlot!="")
    {
        return sReInt+"."+sFlot;
    }

    return sReInt;
}

void Global::ping(QString sIp)
{
    m_ping.setIp(sIp);
}

QString Global::printTime(QString st)
{
    QString sRe = st+" "+dateTimeUtc8().toString("mm:ss.zzz");
    qDebug()<<sRe;
    return sRe;
}


QString Global::strNumber(double number)
{
    QString sRe = QString::number(number, 'f', 2);

    for(int point = 0, i = (sRe.lastIndexOf('.') == -1 ? sRe.length() : sRe.lastIndexOf('.')); i > 0; --i, ++point)
    {
        if(point != 0 && point % 3 == 0)
        {
            sRe.insert(i, ',');
        }
    }

    return sRe;
}
