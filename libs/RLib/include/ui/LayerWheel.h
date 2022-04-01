#ifndef LAYERWHEEL_H
#define LAYERWHEEL_H

#include <QWidget>
#include <QPushButton>
#include <QResizeEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include <QCoreApplication>
#include <QEventLoop>


class LayerWheel : public QWidget
{
    Q_OBJECT
public:
    explicit LayerWheel(QWidget *parent = 0);

    void setPage(QRect focus,bool bLayoutTypeH, int iCol, int iRow, QList<QWidget *> listItem, int iMargin, int iBorder);

    int m_iTotalPage;

    int m_iNowPage;

    QWidget *m_wheel;

protected:

    QWidget *m_wBg;

    QList<QWidget*> m_listItem;

    //單頁focus範圍
    QRect m_rect;

    int m_iMargin;

    QPropertyAnimation m_ani;

    void wheelMove(int iX, int iY,int iMsec);

    void resizeEvent(QResizeEvent *);

    bool m_bLayoutH;
signals:

    void signalChangePage(int iIdx);

public slots:
    /** 回傳值為移動後是否還能再移動一次
     * @brief nextPage
     * @param iMsec 動畫移動毫秒 <=0時，不使用動畫類別、直接move
     * @return
     */
    bool nextPage(int iMsec = 200);

    bool prePage(int iMsec = 200);

    void goPage(int iIdx,int iMsec = 200);


};

#endif // LAYERWHEEL_H
