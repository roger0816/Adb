#include "ModelGameReport.h"

ModelGameReport::ModelGameReport(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_listHeader[_ModelGameReport::_NORMAL]<<"編號"<<"名稱"<<"商品數"<<"營業額"<<"淨利"<<"完成單數"<<"只報價單數"<<"進行中單數";

}

QVariant ModelGameReport::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();

    if(orientation==Qt::Vertical)
        return QVariant();

    int iIdx = qBound(0,section,m_listHeader[m_iType].length()-1);

    return m_listHeader[m_iType].at(iIdx);
}

int ModelGameReport::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_listData.length();
}

int ModelGameReport::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_listHeader[m_iType].length();
}

QVariant ModelGameReport::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.row()<0 || index.column()<0)
        return QVariant();

    using namespace _ModelGameReport;

    QVariant re;


    QFont font;
    QColor colorFront(QColor(44,44,44));

    if(index.column()>=3 && index.column()<9)
    {
        colorFront =QColor(85,170,255);

        //  font.setUnderline(true);
    }

    if(role==Qt::DisplayRole)
    {
        QString sText="";


        int iRow = qBound(0,index.row() ,m_listData.length()-1);

        switch (index.column())
        {
        case 0:
            sText = m_listData.at(iRow).Id;
            break;
        case 1:
            sText = m_listData.at(iRow).Name;
            break;
        case 2:
            sText = QString::number(m_listData.at(iRow).listGameItem.length());
            break;
        case 3:
             sText = QString::number(m_listData.at(iRow).iRevenue);
            break;
        case 4:
             sText = QString::number(m_listData.at(iRow).iRevenue-m_listData.at(iRow).iPrime);
            break;

        case 5:
        {
            DataGameReport data = m_listData.at(iRow);

            sText = QString::number(data.iFinishOrder);
            break;
        }

        case 6:
        {
            DataGameReport data = m_listData.at(iRow);

            sText = QString::number(data.iSayOrder);
            break;
        }
        case 7:
        {
            DataGameReport data = m_listData.at(iRow);

            sText = QString::number(data.iRuningOrder);
            break;
        }


        case 8:


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

void ModelGameReport::updateData(bool bIsMonth, int iType, QDateTime date, QString sFilterStr)
{
    beginResetModel();

    qDebug()<<"update Model GameReport";

    m_bIsMonth = bIsMonth;


    m_dateTime = date;


    m_strFilter = sFilterStr;

    // m_iType = iType;


    requestAction();

    endResetModel();
}

void ModelGameReport::requestAction()
{
    using namespace _ModelGameReport;


   // ACTION.getGameItem(true);  //update data

    m_listGame.clear();
    QList<DataGameList> listGame;
   // listGame=ACTION.getGameList(true);
    listGame = DATA.getGameList();

    foreach(DataGameList v,listGame)
    {
        DataGameReport data(v.data());

        m_listGame.append(data);

        m_dGame[data.Sid]=&m_listGame.last();
    }

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



    QString st = m_dateTime.toString("yyyyMM")+"01";

    QDate tmp=QDate::fromString(st,"yyyyMMdd");

    m_listOrder = ACTION.getOrderByDate(tmp);


    qDebug()<<" get order len : "<<m_listOrder.length();


    for(int i=0;i<m_listOrder.length();i++)
    {
        OrderData order = m_listOrder.at(i);


        bool bCheck = checkDate(order.OrderDate);

        if(!bCheck)
            continue;

        QStringList listOrderItem = order.Item.split(";;");

        if(listOrderItem.length()<1)
            continue;
        QString sItemSid = listOrderItem.first().split(",,").first();

        QString sGameSid = DATA.findGameSid(sItemSid);

        if(sGameSid=="")
            continue;

        qDebug()<<"Game Sid "<<sGameSid;
        // int iCount = listOrderItem.first().split(",,").last().toInt(); //算訂單，不計算game item數量
        int idx = findGameIndex(sGameSid);

        if(idx<0 || idx>= m_listGame.length())
            continue;

        int iStep = order.Step.toInt();

        if(iStep>0)
            continue;

        if(iStep==0)
        {
            m_listGame[idx].iSayOrder+=1;
        }
        else if(iStep==5)
        {
            m_listGame[idx].iFinishOrder+=1;

            m_listGame[idx].iRevenue += order.Money[0].toInt();

            m_listGame[idx].iPrime += order.Money[1].toInt();

        }
        else
        {
            m_listGame[idx].iRuningOrder+=1;
        }

        if(!m_listGame[idx].listOrderSid.contains(order.Sid))
            m_listGame[idx].listOrderSid.append(order.Sid);



        //            if(order.CustomerSid=="23")
        //            {
        //                 qDebug()<<"order sid : "<<order.Sid<<" , "<< listOrderItem;

        //            }



        //  }




    }






    m_listData.clear();

    foreach(DataGameReport v, m_listGame)
    {

        m_listData.append(v);
    }


}

int ModelGameReport::findGameIndex(QString sGameSid)
{
    int iRe = -1;

    for(int i=0;i<m_listGame.length();i++)
    {
        if(m_listGame.at(i).Sid==sGameSid)
            iRe = i;
    }

    return iRe;


}

_ModelGameReport::DataGameReport::DataGameReport(QVariantMap data)
{
    VGameList::setData(data);
    iTotalOrder=0;
    foreach(VGameItem v, listGameItem)
    {
        iTotalOrder+=v.totalSell;
    }
}

int _ModelGameReport::DataGameReport::totalOrderByDate(QDateTime date, bool bIsMonth)
{
    int iRe = 0;

    foreach(VGameItem v, listGameItem)
    {
        QDateTime vDate=QDateTime::fromString(v.UpdateTime,"yyyyMMddhhmmss");

        bool bIsMapping = false;


        if(bIsMonth)
        {
            if(date.toString("yyyyMM")==vDate.toString("yyyyMM"))
                bIsMapping = true;
        }
        else
        {
            if(date.toString("yyyyMMdd")==vDate.toString("yyyyMMdd"))
                bIsMapping = true;
        }


        if(bIsMapping)
            iRe+=v.totalSell;
    }


    return iRe;
}
