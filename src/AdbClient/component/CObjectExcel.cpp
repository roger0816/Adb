#include "CObjectExcel.h"

#include <QDir>

CObjectExcel::CObjectExcel() :
    m_excel(nullptr)
{
    m_listColKey <<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J" \
                 <<"K"<<"L"<<"M"<<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T" \
                 <<"U"<<"V"<<"W"<<"X"<<"Y"<<"Z";
}

CObjectExcel::~CObjectExcel()
{
    if(m_excel!=nullptr)
    {
        delete m_excel;
    }
}

bool CObjectExcel::open(QString sFilePath)
{
    m_excel = new QAxObject();

    m_excel->setControl("Excel.Application");//連接excel

    m_excel->dynamicCall("SetVisible (bool Visible)","false");//不顯示 視窗

    m_excel->setProperty("DisplayAlerts", false);// 不顯示任何警告訊息

    if(sFilePath!="")
        m_sFilePath = sFilePath;

    QAxObject *workbooks = m_excel->querySubObject("WorkBooks");//工作簿列表
    if(workbooks==nullptr)
        return false;

    workbooks->dynamicCall("Add");//新建一个工作簿

    m_workBook = m_excel->querySubObject("ActiveWorkBook");//當前工作簿

    m_sheets = m_workBook->querySubObject("Sheets");//工作表列表

    m_sheet = m_sheets->querySubObject("Item(int)",1);//獲取 工作表，即sheet1

    return true;
}

bool CObjectExcel::save()
{
    if(m_excel==nullptr)
        open("");

    m_workBook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(m_sFilePath));

    return true;
}

bool CObjectExcel::close()
{
    if(m_excel==nullptr)
        open();
    m_workBook->dynamicCall("Close()");//关闭工作簿

    m_excel->dynamicCall("Quit()");//关闭excel
    delete m_excel;
    m_excel=nullptr;

    return  true;
}

void CObjectExcel::setColumn(int iCol, QStringList list)
{
    for(int i=0;i<list.length();i++)
    {
        setCell(i,iCol,list[i]);
    }
}

void CObjectExcel::setRow(int iRow, QStringList list)
{
    for(int i=0;i<list.length();i++)
    {
        setCell(iRow,i,list[i]);
    }
}

void CObjectExcel::setCell(int iRow,int iCol, QVariant v)
{
    QAxObject *cellX ;

    cellX = m_sheet->querySubObject("Range(QVariant, QVariant)",m_listColKey[iCol]+QString::number(iRow+1));

    cellX->dynamicCall("SetValue(const QVariant&)",v);
}

void CObjectExcel::setBulkCell(int iRow, int rowCount, int startColumn, int endColumn, QVariant v)
{
    QAxObject *cellX;

    QString startCell = QString("%1%2").arg(m_listColKey[startColumn]).arg(iRow);
    QString endCell   = QString("%1%2").arg(m_listColKey[endColumn]).arg((iRow-1)+rowCount);

    cellX = m_sheet->querySubObject("Range(QVariant, QVariant)",startCell,endCell);

    cellX->dynamicCall("SetValue(const QVariant&)",v);
}

void CObjectExcel::setColumnWidth(int iColumn, int iWidth)
{
    QAxObject * col = m_sheet->querySubObject("Columns(const QString&)",  m_listColKey[iColumn]);
    col->setProperty("ColumnWidth", iWidth);
}

void CObjectExcel::setRowHeight(int iRow, int iHeight)
{
    QAxObject * r = m_sheet->querySubObject("Rows(const QString &)", QString::number(iRow));
    r->setProperty("RowHeight", iHeight);
}
