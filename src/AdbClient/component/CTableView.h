#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QTableView>
#include <QDebug>
#include <QObject>
#include <QDateTime>


namespace  CTABLE {
static QString _HEADER_H_LIST="HEADER_H_LIST";
static QString _HEADER_V_LIST="HEADER_V_LIST";
static QString _DATA="DATA";
static QString _ROW_COUNT="ROW_COUNT";
static QString _COL_COUNT="COL_COUNT";

}


class CTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CTableModel(QObject *parent = nullptr):QAbstractTableModel(parent){}

    void updateData(QVariantMap data,QMap<QPair<int, int>, QColor> cellColors)
    {
        beginResetModel();
        m_cellColors=cellColors;
        m_data = data;
        endResetModel();
    }
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:


    QVariantMap m_data;
    QMap<QPair<int, int>, QColor> m_cellColors;
};


class CTableView : public QTableView
{
    Q_OBJECT
public:
    CTableView(QWidget *parent=nullptr);
     enum _tbItemType{_AUTO=0,_BUTTON,_TXT,_BOOL,_DOUBLE,_TOOLTIP,_DATE,_DATETIME,_HTML};
    void setHeaderVisiable(bool bVisiable, bool bIsV=true);
    void setRowCount(int i);
    void setColumnCount(int i);
    void setHorizontalHeaderLabels(QStringList list);
    void setItem(int iRow, int iCol, QVariant var, int type=0, int iPixSize=16);
    void setCellTextColor(int row, int column, const QColor &color);

    void doUpdate();

    int rowCount();
    int columnCount();

    int currentRow(){return currentIndex().row();}
    void setCurrentCell(int iRow, int iCol);

    void setHorizontalHeaderSize(int iSize);
    void setVerticalHeaderSize(int iSize);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex());
    QVariant item(int iRow, int iCol);
private:
    CTableModel m_model;

    QVariantMap m_data;

    QMap<QPair<int, int>, QColor> m_cellColors; // 跟蹤特定格子的顏色
};

#endif // CTABLEVIEW_H
