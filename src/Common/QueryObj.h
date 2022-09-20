#ifndef QUERYOBJ_H
#define QUERYOBJ_H

#include <QObject>
#include <QVariantMap>
#include "CSqlClass.h"
#include "DEF.h"
#include "RpkCore.h"

//server query
class QueryObj : public QObject
{
    Q_OBJECT
public:
    explicit QueryObj(QObject *parent = nullptr);

    CData queryData(CData data);

  //  QVariantMap queryLogin(QString sUser,QString sPasseor)

    void openDb(bool bMysql=false);


    CSqlClass m_sql;
signals:

};

#endif // QUERYOBJ_H
