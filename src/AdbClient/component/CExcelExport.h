#ifndef CEXCELEXPORT_H
#define CEXCELEXPORT_H

#include <QObject>
#include <QAxObject>
#include <QDir>
#include <QFile>
#include <QColor>

class CExcelExport : public QObject
{
    Q_OBJECT
public:
    explicit CExcelExport(QObject *parent = nullptr);
    void newExcel(const QString &fileName);
    void appendSheet(const QString &sheetName);
    void setCellValue(int row, int column, const QString &value);
    void saveExcel(const QString &fileName);
    void freeExcel();
private:
    QAxObject *pApplication;
    QAxObject *pWorkBooks;
    QAxObject *pWorkBook;
    QAxObject *pSheets;
    QAxObject *pSheet;
signals:

};


#endif // CEXCELEXPORT_H
