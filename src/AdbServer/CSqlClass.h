#ifndef CSQLCLASS_H
#define CSQLCLASS_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
class CSqlClass : public QObject
{
    Q_OBJECT
public:
    explicit CSqlClass(QObject *parent = nullptr);

    QSqlDatabase m_db;

signals:

};

#endif // CSQLCLASS_H
