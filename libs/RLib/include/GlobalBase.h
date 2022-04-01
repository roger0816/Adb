#ifndef GLOBALBASE_H
#define GLOBALBASE_H

#include <QObject>


//外部要呼叫統一使用define的，design patten : singleton
//#define GLOBAL Global::Instance()


class GlobalBase : public QObject
{
    Q_OBJECT
public:

    static GlobalBase& Instance();


protected:
    GlobalBase(QObject *parent = 0);

    static GlobalBase* m_pInstance;

signals:

public slots:
};

#endif // GLOBALBASE_H
