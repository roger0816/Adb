#ifndef QUERY_H
#define QUERY_H

#include "QueryObj.h"
#include "DEF.h"







class Query : public QueryObj
{
    Q_OBJECT
public:
    explicit Query(QObject *parent = nullptr);

    CData implementRecall(CData data) override;


signals:

};

#endif // QUERY_H
