#ifndef LAYERBLOCK_H
#define LAYERBLOCK_H

#include <QWidget>

#include <QMovie>
#include <QShowEvent>


namespace Ui {
class LayerBlock;
}

class LayerBlock : public QWidget
{
    Q_OBJECT

public:
    explicit LayerBlock(QWidget *parent = 0);
    ~LayerBlock();

    void setListPixmap(QList<QPixmap*> listPix);

private:
    Ui::LayerBlock *ui;

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void timerEvent(QTimerEvent *);
    int m_iSec;

    int m_iTimeout;

    bool m_bBlock;

    void setCanView(bool bIsCan);
public slots:
    void slotBlockFlag(bool bIsBlock,bool bIsCanView=true,int iMsecTimeout=5000);
};

#endif // LAYERBLOCK_H
