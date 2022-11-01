#ifndef ITEMCLOCK_H
#define ITEMCLOCK_H

#include <QWidget>
#include "Global.h"
#include <QTimerEvent>
#include "GlobalUi.h"
#include <QDateTimeEdit>
class ItemClock : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit ItemClock(QWidget *parent = nullptr);

    void timerEvent(QTimerEvent *) override;
signals:

};

#endif // ITEMCLOCK_H
