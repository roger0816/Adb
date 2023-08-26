#ifndef CSQLITE_H
#define CSQLITE_H

#include <QObject>

class CSqlite : public QObject
{
    Q_OBJECT
public:
    explicit CSqlite(QObject *parent = nullptr);

signals:

};

#endif // CSQLITE_H
