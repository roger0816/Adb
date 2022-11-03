#include "ModelUserReport.h"

ModelUserReport::ModelUserReport(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_listHeader[_ORDER_TOTAL]<<"編號"<<"名稱"<<"職級"<<"報價數量"<<"下單數量"<<"接單儲值數量"<<"回報數量"<<"核簽數量";
    m_listHeader[_TIME_TOTAL]<<"編號"<<"名稱"<<"職級"<<"報價總時"<<"下單總時"<<"接單儲值總時"<<"回報總時"<<"核簽總時";
    m_listHeader[_TIME_AVE]<<"編號"<<"名稱"<<"職級"<<"報價均時"<<"下單均時"<<"接單儲值均時"<<"回報均時"<<"核簽均時";



    //SELECT * FROM 'OrderData' where OrderDate like "%202210%";
    //SELECT * FROM 'OrderData' where OrderDate >= '20221030' AND OrderDate < '20221031';
    //SELECT * FROM 'OrderData' where OrderDate = '20221030';
}

QVariant ModelUserReport::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if(role!=Qt::DisplayRole)
        return QVariant();

    if(orientation==Qt::Vertical)
        return QVariant();

    int iIdx = qBound(0,section,m_listHeader[m_iType].length()-1);

    return m_listHeader[m_iType].at(iIdx);

}

int ModelUserReport::rowCount(const QModelIndex &) const
{
    return m_listUser.length();

    //    if (parent.isValid())
    //        return 0;

    // FIXME: Implement me!
}

int ModelUserReport::columnCount(const QModelIndex &) const
{
    return m_listHeader[m_iType].length();

    //    if (parent.isValid())
    //        return 7;

    // FIXME: Implement me!
}

QVariant ModelUserReport::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row()<0 || index.column()<0)
        return QVariant();

    QVariant re;





    QFont font;
    QColor colorFront(Qt::darkGray);




    if(index.column()>=3 && index.column()<9)
    {
        colorFront =QColor(85,170,255);

        //  font.setUnderline(true);
    }


    if(role==Qt::DisplayRole)
    {
        QString sText="";


        int iRow = qBound(0,index.row() ,m_listUser.length()-1);

        switch (index.column())
        {
        case 0:
            sText = m_listUser.at(iRow).Cid;
            break;
        case 1:
            sText = m_listUser.at(iRow).Name;
            break;
        case 2:
            sText = GLOBAL.userLvToStr(m_listUser.at(iRow).Lv);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if(m_iType==_ORDER_TOTAL)
                sText = QString::number(m_listUser.at(iRow).iTotalStep[index.column()-3]);
            else if(m_iType==_TIME_TOTAL)
            {
                int iSec = m_listUser.at(iRow).iTotalStep[index.column()-3];

                QDateTime date;

                date.setSecsSinceEpoch(iSec);

                sText = date.toString("hh:mm:ss");
            }

            break;

        default:
            break;
        }

        re=sText;
    }


    if(role==Qt::TextAlignmentRole)
        re=Qt::AlignCenter;


    if(role==Qt::ForegroundRole)
    {
        re=colorFront;
    }

    if(role==Qt::FontRole)
    {
        re=font;

    }



    return re;
}

void ModelUserReport::updateData(bool bIsMonth,int iType ,QDateTime date, QString sFilterStr)
{
    beginResetModel();

    m_bIsMonth = bIsMonth;

    m_dateTime = date;

    m_strFilterStr = sFilterStr;

    m_iType = iType;





    requestAction();

    endResetModel();
}


void ModelUserReport::requestAction()
{
    m_listUser.clear();

    QList<UserData> list = ACTION.getUser(true);

    foreach(UserData v,list)
    {
        DataUserReport data(v.data());

        m_listUser.append(data);
        m_dUser[data.Sid]=&m_listUser.last();
    }


    m_listOrder = ACTION.getOrder(true);

    auto checkDate = [=](QString sDate)
    {
        if(sDate.length()<8)
            return false;


        if(m_bIsMonth)
        {
            return sDate.mid(0,6) == m_dateTime.toString("yyyyMM");
        }
        else
        {
            return sDate == m_dateTime.toString("yyyyMMdd");
        }

    };


    for(int i=0;i<m_listOrder.length();i++)
    {
        OrderData order = m_listOrder.at(i);

        if(!checkDate(order.OrderDate))
            continue;

        QStringList listStepUser=order.User;

        QStringList listTime=order.StepTime;

        for(int j=0;j<listStepUser.length()&&j<6;j++)
        {
            QString sUserSid = listStepUser.at(j);

            if(sUserSid.trimmed()=="")
                continue;
            int iStep =j;


            m_dUser[sUserSid]->iTotalStep[iStep]+=1;

            if(j==0)
            {
                m_dUser[sUserSid]->iTotalTimer[iStep]=0;
            }
            else
            {
                QString sTmp = listTime.at(j);
                QString sTmpPre = listTime.at(j-1);
                if(sTmp=="" || sTmpPre=="")
                    continue;
                QDateTime dateTime = QDateTime::fromString(sTmp,"yyyyMMddhhmmss");
                QDateTime dateTimePre = QDateTime::fromString(sTmpPre,"yyyyMMddhhmmss");

                double d = dateTime.toSecsSinceEpoch()-dateTimePre.toSecsSinceEpoch();

                m_dUser[sUserSid]->iTotalTimer[iStep]+=d;
            }

        }


    }


    foreach(DataUserReport v, m_listUser)
    {
        qDebug()<<"sid : "<<v.Sid<<" , "<<v.iTotalStep[0]<<","<<v.iTotalStep[1]
               <<","<<v.iTotalStep[2]<<","<<v.iTotalStep[3]<<","<<v.iTotalStep[4]
              <<","<<v.iTotalStep[5];
    }





}

QString ModelUserReport::countText(const int row,const int col)
{
    QString sText;

    int iRow = qBound(0,row ,m_listUser.length()-1);


    switch (col)
    {
    case 0:
        sText = m_listUser.at(iRow).Cid;
        break;
    case 1:

        sText = m_listUser.at(iRow).Name;
        break;
    case 2:
        sText = GLOBAL.userLvToStr(m_listUser.at(iRow).Lv);
        break;
    case 3:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[0]);
        break;
    case 4:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[1]);
        break;
    case 5:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[2]);
        break;
    case 6:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[3]);
        break;
    case 7:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[4]);
        break;
    case 8:
        sText = QString::number(m_listUser.at(iRow).iTotalStep[5]);
        break;
    default:
        break;
    }



    return sText;
}

QString ModelUserReport::timeText(int iRow, int iCol)
{
    QString sRe;



    return sRe;
}



/*
bool ModelUserReport::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool ModelUserReport::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void ModelUserReport::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}
*/
