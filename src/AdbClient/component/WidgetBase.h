#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include <QWidget>

class WidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetBase(QWidget *parent = nullptr);

signals:

};

#endif // WIDGETBASE_H
