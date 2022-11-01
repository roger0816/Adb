#include "ModelUserReport.h"

ModelUserReport::ModelUserReport(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_listHeader<<"編號"<<"名稱"<<"職級"<<"報價數量"<<"下單數量"<<"接單儲值數量"<<"回報數量"<<"核簽數量";


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

    int iIdx = qBound(0,section,m_listHeader.length()-1);

    return m_listHeader.at(iIdx);

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
    return m_listHeader.length();

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

  if(role==Qt::TextAlignmentRole)
      re=Qt::AlignCenter;


    if(role==Qt::DisplayRole)
    {
        QString sSt="";


        int iRow = qBound(0,index.row() ,m_listUser.length()-1);

        if(index.column()==0)
            sSt = m_listUser.at(iRow).Cid;
        else if(index.column()==1)
            sSt = m_listUser.at(iRow).Name;
        else if(index.column()==2)
            sSt = GLOBAL.userLvToStr(m_listUser.at(iRow).Lv);
        else if(index.column()==3)
            sSt = m_listUser.at(iRow).iTotalStep[0];
        if(index.column()==4)
            sSt = m_listUser.at(iRow).iTotalStep[1];
        if(index.column()==5)
            sSt = m_listUser.at(iRow).iTotalStep[2];
        if(index.column()==6)
            sSt = m_listUser.at(iRow).iTotalStep[3];

        if(index.column()==7)
            sSt = m_listUser.at(iRow).iTotalStep[4];

        if(index.column()==8)
            sSt = m_listUser.at(iRow).iTotalStep[5];

        re=sSt;
    }

    return re;
}

void ModelUserReport::updateData(bool bIsMonth, QDateTime date, QString sFilterStr)
{
    beginResetModel();

    m_bIsMonth = bIsMonth;

    m_dateTime = date;

    m_strFilterStr = sFilterStr;

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
     //   m_dUser[data.Sid]=&m_listUser.last();
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

        for(int j=0;j<listStepUser.length()&&j<6;j++)
        {
            QString sUserSid = listStepUser.at(j);

            int iStep =j;

            //m_dUser[sUserSid]->iTotalStep[iStep]+=1;
        }


    }





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
