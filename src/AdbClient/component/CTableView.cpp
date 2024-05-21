#include "CTableView.h"
#include "qheaderview.h"


QVariant CTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!

    if(orientation == Qt::Horizontal)
    {
        if(role==Qt::DisplayRole)
        {
            if(m_data.contains(CTABLE::_HEADER_H_LIST) &&
                    m_data[CTABLE::_HEADER_H_LIST].toStringList().length()>section)
            {
                QVariant v(m_data[CTABLE::_HEADER_H_LIST].toStringList().at(section));
                return v;
            }
            else
                return QVariant();
        }
        else
        {
            return QVariant();
        }
    }

    return QAbstractTableModel::headerData(section,orientation,role);
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(m_data.contains(CTABLE::_ROW_COUNT))
        return m_data[CTABLE::_ROW_COUNT].toInt();
    else
        return 0;
    // FIXME: Implement me!
}

int CTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(m_data.contains(CTABLE::_COL_COUNT))
        return m_data[CTABLE::_COL_COUNT].toInt();
    else
        return 0;
    // FIXME: Implement me!
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if(role ==Qt::DisplayRole || role== Qt::EditRole)
    {
        if(m_data.contains(CTABLE::_DATA))
        {
            QVariantList d = m_data[CTABLE::_DATA].toList();
            if(d.length()>index.row())
            {
                QVariantList rowData = d[index.row()].toList();
                if(rowData.length()>index.column())
                    return rowData[index.column()];
            }

        }

    }
    else if(role==Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    else if (role == Qt::TextColorRole)
    {
        // 檢查是否有設置特定格子的顏色
        if (m_cellColors.contains(QPair<int, int>(index.row(), index.column())))
        {
            return m_cellColors[QPair<int, int>(index.row(), index.column())];
        }
    }

    return QVariant();
}


//==================

CTableView::CTableView(QWidget *parent):QTableView(parent)
{
    setModel(&m_model);

    // 將文字置中
    horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    horizontalHeader()->setVisible(true);

    verticalHeader()->setVisible(false);
}

void CTableView::setHeaderVisiable(bool bVisiable, bool bIsV)
{
    if(!bIsV)
    {
        horizontalHeader()->setVisible(bVisiable);
    }
    else
        verticalHeader()->setVisible(bVisiable);
}

void CTableView::setRowCount(int i)
{
    m_data[CTABLE::_ROW_COUNT]=i;
    if(i==0)
     doUpdate();
}

void CTableView::setColumnCount(int i)
{
    m_data[CTABLE::_COL_COUNT]=i;
   // doUpdate();
}

void CTableView::setHorizontalHeaderLabels(QStringList list)
{
    if(columnCount()<list.length())
        setColumnCount(list.length());

    m_data[CTABLE::_HEADER_H_LIST]=list;
    doUpdate();
}

void CTableView::setItem(int iRow, int iCol, QVariant var, int type, int iPixSize)
{

    QString st = var.toString();


    if(type==_AUTO)
    {
        if(var.type()==QVariant::Bool)
            type = _BOOL;
        else if(var.type()==QVariant::Double)
            type = _DOUBLE;
        else if(var.type()==QVariant::Date)
            type = _DATE;
        else if(var.type()==QVariant::DateTime)
            type = _DATETIME;
        else
            type = _TXT;

    }

  //  QFont f =item->font();

    if(type == _BOOL)
    {
        st ="是";

        if(!var.toBool())
            st="否";
    }
    else if(type == _DOUBLE)
    {
        st = QString::number(var.toDouble(),'f', 2);
    }
    else if(type == _DATE)
    {
        st = var.toDateTime().toString("yyyy/MM/dd");

    }
    else if(type == _DATETIME)
    {
        st = var.toDateTime().toString("yyyy/MM/dd hh:mm");
     //   f.setPixelSize(12);
    }
    else if(type == _BUTTON)
    {
     //   f.setUnderline(true);

   //     item->setForeground(QColor(85,170,255));
    }
    else if(type == _TOOLTIP)
    {
     //   item->setForeground(QColor(77,77,77));
    }
    else if(type==_HTML)
    {
        //to do
    }
    else{}




    if(!m_data.contains(CTABLE::_DATA))
    {
        m_data[CTABLE::_DATA]= QVariantList();

    }


    QVariantList list=m_data[CTABLE::_DATA].toList();


    while(list.length()<=iRow)
    {
        list.append(QVariantList()<<"");
    }


    QVariantList rowData = list.at(iRow).toList();


    while(rowData.length()<=iCol)
    {
        rowData.append(QVariant());
    }

    rowData[iCol]=QVariant(st);


    list[iRow] =rowData;
    m_data[CTABLE::_DATA] = list;

}

void CTableView::setCellTextColor(int row, int column, const QColor &color)
{
    m_cellColors[QPair<int, int>(row, column)] = color;

    // 更新特定格子的顏色，以觸發單元格重新繪製
    //QModelIndex index = m_model.index(row, column);
    // m_model.dataChanged(index, index);
}

void CTableView::doUpdate()
{

    m_model.updateData(m_data,m_cellColors);

}

int CTableView::rowCount()
{
    return m_model.rowCount();
}

int CTableView::columnCount()
{
    return m_model.columnCount();
}

void CTableView::setCurrentCell(int iRow, int iCol)
{
    QModelIndex idx = index(iRow, iCol);

    setCurrentIndex(idx);
}

void CTableView::setHorizontalHeaderSize(int iSize)
{
    horizontalHeader()->setDefaultSectionSize(iSize);
}

void CTableView::setVerticalHeaderSize(int iSize)
{
    verticalHeader()->setDefaultSectionSize(iSize);
}



QModelIndex CTableView::index(int row, int column, const QModelIndex &parent)
{
    return m_model.index(row,column,parent);
}

QVariant CTableView::item(int iRow,int iCol)
{
    QModelIndex index = m_model.index(iRow, iCol); // row 和 c

    QVariant re;

    if (index.isValid()) {
        re= m_model.data(index);
    }

    return re;
}

