#include "CLinkTable.h"

CLinkTable::CLinkTable(QWidget *parent)
    : QWidget{parent}
{
    m_tb =new QTableWidget(this);
    m_tb->move(0,0);

    m_tb->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tb->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tb->horizontalHeader()->setDefaultSectionSize(60);
    m_tb->verticalHeader()->setVisible(false);

}

void CLinkTable::setData(QVariantList data)
{
    m_listData = data;

    refresh();
}

void CLinkTable::setEnableColKey(QStringList list)
{
    m_listColKey = list;

    refresh();
}

void CLinkTable::setHeaderNameH(QStringList list)
{
    m_tb->setHorizontalHeaderLabels(list);
}

QTableWidgetItem *CLinkTable::tbItem(QVariant dData,int iType)
{
    Q_UNUSED(iType)

    QTableWidgetItem * item =new QTableWidgetItem();

   return item;
}



void CLinkTable::showEvent(QShowEvent *)
{
    reSetSize();
}

void CLinkTable::resizeEvent(QResizeEvent *)
{
    reSetSize();
}

void CLinkTable::reSetSize()
{
    m_tb->resize(size());
}

void CLinkTable::refresh()
{
    m_tb->setRowCount(0);

    if(m_listData.length()<1)
        return;

    QStringList listKey = m_listColKey;

    if(listKey.length()<1)
        listKey = m_listData.first().toMap().keys();

    int iColCount = listKey.length();

    m_tb->setColumnCount(iColCount);

    for(int i=0;i<m_listData.length();i++)
    {
        m_tb->setRowCount(i+1);

        QVariantMap data = m_listData.at(i).toMap();

        for(int j=0;j<listKey.length();j++)
        {

            m_tb->setItem(i,j,tbItem(data[listKey.at(j)]));


        }

    }



}
