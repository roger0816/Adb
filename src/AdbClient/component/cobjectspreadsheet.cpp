#include "cobjectspreadsheet.h"

#include <QVariant>

CObjectSpreadsheet::CObjectSpreadsheet()
{

}

CObjectSpreadsheet::~CObjectSpreadsheet()
{

}

bool CObjectSpreadsheet::open(QString sFilePath)
{
    return false;
}

bool CObjectSpreadsheet::save()
{
    return false;
}

bool CObjectSpreadsheet::close()
{
    return false;
}

void CObjectSpreadsheet::setColumn(int iCol, QStringList list)
{

}

void CObjectSpreadsheet::setRow(int iRow, QStringList list)
{

}

void CObjectSpreadsheet::setCell(int iRow, int iCol, QVariant v)
{

}


void CObjectSpreadsheet::setBulkCell(int iRow, int rowCount, int startColumn, int endColumn, QVariant v)
{

}

void CObjectSpreadsheet::setColumnWidth(int iColumn, int iWidth)
{

}

void CObjectSpreadsheet::setRowHeight(int iRow, int iHeight)
{

}
