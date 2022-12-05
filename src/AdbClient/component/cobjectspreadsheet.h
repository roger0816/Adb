#ifndef COBJECTSPREADSHEET_H
#define COBJECTSPREADSHEET_H

#include <QStringList>
#include <QVariant>

class CObjectSpreadsheet
{
public:
    explicit CObjectSpreadsheet();

    virtual ~CObjectSpreadsheet();

    virtual bool open(QString sFilePath="");

    virtual bool save();

    virtual bool close();

    virtual void setColumn(int iCol, QStringList list);

    virtual void setRow(int iRow, QStringList list);

    virtual void setCell(int iRow, int iCol, QVariant v);

    virtual void setBulkCell(int iRow, int rowCount, int startColumn, int endColumn, QVariant v);

    virtual void setColumnWidth(int iColumn, int iWidth);

    virtual void setRowHeight(int iRow, int iHeight);
};

#endif // COBJECTSPREADSHEET_H
