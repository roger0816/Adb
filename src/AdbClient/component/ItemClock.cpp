#include "ItemClock.h"

ItemClock::ItemClock(QWidget *parent)
    : QDateTimeEdit{parent}
{
    setReadOnly(true);

    startTimer(1000);
}

void ItemClock::timerEvent(QTimerEvent *)
{
    QDateTime date = GLOBAL.dateTimeUtc8();

    setDateTime(date);

}
