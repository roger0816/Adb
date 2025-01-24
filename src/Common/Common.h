#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include "DEF.h"
#include "VojData.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>


#define COMMON Common::INS()


class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);

    static Common &INS();

    QString toBkString(QVariantMap d);


    QString toJsonString(QString sKey,QString sValue);


    QString toJsonString(QVariantMap d);




    QString listToJson(QVariantList list, QStringList listKey={});

    QVariantList jsonToList(const QString& jsonString);


    QString mapToJson(QVariantMap map, QStringList listKey={});



    QString addFlow(QString st, QString currency)
    {
        int iFlowCount =0;
        if(currency.toUpper().contains("USD"))
            iFlowCount =2;
        else if(currency.toUpper().contains("SGD"))
            iFlowCount =1;

        return addFlow(st,iFlowCount);
    }

    QString addFlow(QString sDouble, int flowCount)
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

    double addFlow(double value, int flowCount=0)
    {
        QString st = QString::number(value,'f',flowCount+1);

        return addFlow(st,flowCount).toDouble();
    }


private:
    static Common* m_pInstance;


signals:





};

#endif // COMMON_H
