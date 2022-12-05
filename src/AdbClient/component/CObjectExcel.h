#ifndef COBJECTEXCEL_H
#define COBJECTEXCEL_H

#include <QAxObject>

#include "cobjectspreadsheet.h"

class CObjectExcel : public CObjectSpreadsheet
{
public:
    explicit CObjectExcel();

    ~CObjectExcel();

    // Attempt to open a file from sFilePath.
    // Return true if success, false if any error occured.
    bool open(QString sFilePath="") override;

    bool save() override;

    bool close() override;

    void setColumn(int iCol, QStringList list) override;

    void setRow(int iRow, QStringList list) override;

    void setCell(int iRow, int iCol, QVariant v) override;

    void setBulkCell(int iRow, int rowCount, int startColumn, int endColumn, QVariant v) override;

    void setColumnWidth(int iColumn, int iWidth) override;

    void setRowHeight(int iRow, int iHeight) override;

    QAxObject * getWorkSheets();

    QAxObject * getWorkSheet();

private:
    QAxObject *m_excel;

    QString m_sFilePath;

    QAxObject * m_workBook;

    QAxObject * m_sheets;

    QAxObject * m_sheet;

    QStringList m_listColKey;
};

#endif // COBJECTEXCEL_H
