#ifndef CSQLCLASS_H
#define CSQLCLASS_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
class CSqlClass : public QObject
{
    Q_OBJECT
public:
    explicit CSqlClass(QObject *parent = nullptr);

    bool checkLogin(QString sUser,QString sPass,QString &sError);

private:
    void createTable();

    QSqlDatabase m_db;

signals:

};

#endif // CSQLCLASS_H
