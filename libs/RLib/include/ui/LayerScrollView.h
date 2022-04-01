#ifndef LAYERSCROLLVIEW_H
#define LAYERSCROLLVIEW_H

#include <QMouseEvent>
#include <QResizeEvent>
#include <QCoreApplication>
#include <QDebug>

#include <QPropertyAnimation>
#include "LayerWheel.h"

class TouchObj : public QWidget
{
    Q_OBJECT
public:
    explicit TouchObj(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint m_pOldpress;
signals:

    void signalPress(QMouseEvent *event);

    void signalMove(QMouseEvent *event);

    void signalRelease(QMouseEvent *event);

    void signalClick(QMouseEvent *event);
};



class LayerScrollView : public LayerWheel
{
    Q_OBJECT
public:
    explicit LayerScrollView(QWidget *parent = 0);


    /**
     * @brief setPage     properties inherited from LayerWheel
     * @param focus
     * @param bLayoutIsH  scroll的type, true 為水平 ，false 為垂直
     * @param iCol        單頁的column數 (table in scroll view)
     * @param iRow        單頁的放的row數
     * @param listItem    子容器指標
     * @param iMargin     單頁的邊框
     * @param iBorder     間距
     */
    void setPage(QRect focus, bool bLayoutIsH, int iCol, int iRow, QList<QWidget *> listItem, int iMargin=0, int iBorder=0);



    /**
     * @brief setContent
     * @param bHmove
     * @param bVmove
     * @param bAutePage
     * @param wContent
     */
    void setContent(bool bHmove, bool bVmove , bool bAutePage = false , QWidget *wContent = 0);


    void setTouchFlag(bool bIsUse);
private:
    QWidget *m_wBg;

    QWidget *m_wContent;

    //第幾個為索引值
    int m_iUseH;

    int m_iUseV;

    TouchObj *m_wTouch;

    int m_iMoveArrow;

    QPoint m_pOldPress;

    QPoint m_pOldContent;

    QPropertyAnimation m_ani;

//        void mousePressEvent(QMouseEvent *event);

//        void mouseMoveEvent(QMouseEvent *event);

//        void mouseReleaseEvent(QMouseEvent *);

    void resizeEvent(QResizeEvent *);

    void aniToIdx(QPoint sPre,QPoint sNext);

    bool m_bHmove;

    bool m_bVmove;

    bool m_bAutePage;

    QSize m_frameBorder;

    int m_iIdxY;

    int m_iIdxX;

    int m_iRowCount;

    int m_iColCount;

signals:

//    void signalChangeIdx(int iCol ,int iRow );

    void signalClick(int iCellIdx);

    void signalClick(int iPageIdx,int iColIdx,int iRowIdx);
public slots:

    void touchPressEvent(QMouseEvent *event);

    void touchMoveEvent(QMouseEvent *event);

    void touchReleaseEvent(QMouseEvent *event);

    void touchClick(QMouseEvent *event);
};

#endif // LAYERSCROLLVIEW_H
