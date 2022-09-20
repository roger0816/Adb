#ifndef CACTION_H
#define CACTION_H

#include <QObject>


class CAction : public QObject
{
    Q_OBJECT
public:
    explicit CAction(QObject *parent = nullptr);
protected:


    bool m_bDataFromServer = true;
signals:

};

#endif // CACTION_H
