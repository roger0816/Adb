#ifndef QUERY_H
#define QUERY_H

#include "QueryObj.h"
#include "DEF.h"
#include <QCryptographicHash>






class Query : public QueryObj
{
    Q_OBJECT
public:
    explicit Query(QObject *parent = nullptr);

    CData implementRecall(CData data) override;

    bool checkAppVersion(QString sVersion);

signals:

};

#endif // QUERY_H
