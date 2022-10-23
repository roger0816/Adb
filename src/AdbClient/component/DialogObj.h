#ifndef DIALOGOBJ_H
#define DIALOGOBJ_H

#include <QDialog>
#include "Global.h"
#include "GlobalUi.h"



class DialogObj : public QDialog
{
    Q_OBJECT
public:
    explicit DialogObj(QWidget *parent = nullptr);

signals:

};

#endif // DIALOGOBJ_H
