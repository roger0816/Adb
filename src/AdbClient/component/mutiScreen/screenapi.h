#ifndef SCREENAPI_H
#define SCREENAPI_H

#ifndef FRMSCREEN_H
#define FRMSCREEN_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QDialog>


class ScreenAPI
{
public:
    enum STATUS {SELECT, MOV, SET_W_H};
    ScreenAPI() {}
    ScreenAPI(QSize size);

    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();
    bool isInArea(QPoint pos);          // 檢測pos是否在截圖區域內
    void move(QPoint p);                // 按 p 移動截圖區域

private:
    QPoint leftUpPos, rightDownPos;     //記錄 截圖區域 左上角、右下角
    QPoint startPos, endPos;            //記錄 鼠標開始位置、結束位置
    int maxWidth, maxHeight;            //記錄屏幕大小
    STATUS status;                      //三個狀態 :  選擇區域、移動區域、設置width height

    void cmpPoint(QPoint &s, QPoint &e);//比較兩位置，判斷左上角、右下角
};

#endif // SCREENAPI_H

class frmScreen : public QDialog
{
    Q_OBJECT

public:
   explicit frmScreen(uint ID,QWidget *parent = 0);
   ~frmScreen();

   QPixmap *get_screen();

signals:
    void captureSignals();

public slots:
    void doCapture();

private:
    uint m_sid;
    QRect m_rect;
    static frmScreen *_instance;
    ScreenAPI *screen_api_p;      //截屏對象
    QPixmap *fullScreen;    //保存全屏圖像
    QPixmap *capScreen;    //保存全屏圖像
    QPixmap *bgScreen;      //模糊背景圖
    QPoint movPos;          //座標

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private slots:
    void InitForm();
    void SaveScreen();
    void SaveScreenOther();
    void SaveFullScreen();

};


#endif // FRMSCREEN_H
