#ifndef ITEMLINEEDIT_H
#define ITEMLINEEDIT_H

#include <QLineEdit>
#include "LayerKeyborad.h"

#include <QMouseEvent>


class ItemLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit ItemLineEdit(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);

signals:

public slots:

};

#endif // ITEMLINEEDIT_H
