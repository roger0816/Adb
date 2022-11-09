#ifndef ITEMMINILOADBAR_H
#define ITEMMINILOADBAR_H

#include <QWidget>
#include <QLabel>
#include <QTimerEvent>
#include <QTimer>
#include <QDebug>

#include <QShowEvent>

namespace Ui {
class ItemMiniLoadbar;
}

class ItemMiniLoadbar : public QWidget
{
    Q_OBJECT

public:
    explicit ItemMiniLoadbar(QWidget *parent = 0);
    ~ItemMiniLoadbar();

    void setLoading(bool bIsLoading);

private:
    Ui::ItemMiniLoadbar *ui;

    int m_iIdx;

    QStringList m_listRes;

    bool m_bIsRun;

    void  timerEvent(QTimerEvent *);

    void showEvent(QShowEvent *);

    int m_iMsec;

    QList<bool> m_list;

    int m_iTimerMsec = 100;

private slots:

    void slotChangeEnaled();



};

#endif // ITEMMINILOADBAR_H
