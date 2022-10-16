#ifndef ACTIONCACHE_H
#define ACTIONCACHE_H


#include <QObject>


class ActionCache : public QObject
{
    Q_OBJECT
public:
    explicit ActionCache(QObject *parent = nullptr);

signals:

};

#endif // ACTIONCACHE_H
