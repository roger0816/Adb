#ifndef ITEMSELECTNUMBER_H
#define ITEMSELECTNUMBER_H

#include <QWidget>
#include <QResizeEvent>
#include <QLabel>
#include <QShowEvent>

#include "LayerScrollView.h"

class ItemSelectNumber : public QWidget
{
    Q_OBJECT
public:
    explicit ItemSelectNumber(QWidget *parent = 0);

    void setNumber(int iMin,int iMax,int iStep=1);

private:

    int m_iIdx;

    LayerScrollView *m_wScrollView;

    QList<QWidget*> m_listItem;

    void resizeEvent(QResizeEvent *);

    void showEvent(QShowEvent *);

signals:

public slots:
};

#endif // ITEMSELECTNUMBER_H
