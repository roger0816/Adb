#ifndef ITEMLOADINGBARA_H
#define ITEMLOADINGBARA_H

#include <QWidget>
#include <QLabel>
#include <QDir>
#include <QTimer>
#include <QVector>
#include <QPixmap>
#include <QThread>
#define ANIMATION_SEC 200


namespace CWaitBarItem
{
class ItemThread : public QThread
{
    Q_OBJECT
public:
    explicit ItemThread(QObject *parent=0):QThread(parent)
    {

    }

    void run()
    {
        m_timer.start(ANIMATION_SEC);
    }

    QTimer m_timer;
};

}

using namespace CWaitBarItem;

class ItemLoadingBarA : public QWidget
{
    Q_OBJECT

public:
    explicit ItemLoadingBarA(QWidget *parent = 0);
    ~ItemLoadingBarA();

    void setPixmap(QList<QPixmap*> listPix);

    static void releasePixArray();

private:

    void showPic();
    void hidePic();
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void resizeEvent(QResizeEvent *);
    static QVector<QPixmap*> m_pixArray;
    ItemThread m_thread;
    QLabel *m_label;

    int k;

signals:
    void signalEventLock(bool bIsLock);
public slots:
    void animation();



};

#endif // ITEMLOADINGBARA_H
