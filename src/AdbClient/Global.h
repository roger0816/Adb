#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include "CSqlClass.h"

#define GLOBAL Global::Instance()


class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);

    static Global& Instance();

    CSqlClass& SQL(){return m_sql;}
private:
    static Global *m_pInstance;

    CSqlClass m_sql;


signals:

};

#endif // GLOBAL_H
