#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QDialog>

class DialogBase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogBase(QWidget *parent = nullptr);
    QWidget *m_wMask;
public slots:
    void slotMask(bool b);
signals:

};

#endif // DIALOGBASE_H
