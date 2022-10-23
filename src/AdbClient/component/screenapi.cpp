#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "screenapi.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QFont>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>
#include <QMouseEvent>
#include <QScreen>
#include <QDebug>

#define STRDATETIME QDateTime::currentDateTime().toString("yyyyMMddhhmmss")

ScreenAPI::ScreenAPI(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    startPos = QPoint(-1, -1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;

}

int ScreenAPI::width()
{
    return maxWidth;
}

int ScreenAPI::height()
{
    return maxHeight;
}

ScreenAPI::STATUS ScreenAPI::getStatus()
{
    return status;
}

void ScreenAPI::setStatus(STATUS status)
{
    this->status = status;
}

void ScreenAPI::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos, rightDownPos);
}

void ScreenAPI::setStart(QPoint pos)
{
    startPos = pos;
}

QPoint ScreenAPI::getEnd()
{
    return endPos;
}

QPoint ScreenAPI::getStart()
{
    return startPos;
}

QPoint ScreenAPI::getLeftUp()
{
    return leftUpPos;
}

QPoint ScreenAPI::getRightDown()
{
    return rightDownPos;
}

bool ScreenAPI::isInArea(QPoint pos)
{
    if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() && pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
        return true;
    }

    return false;
}

void ScreenAPI::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > maxWidth)  {
        rx = maxWidth;
        lx -= p.x();
    }

    if (ry > maxHeight) {
        ry = maxHeight;
        ly -= p.y();
    }

    leftUpPos = QPoint(lx, ly);
    rightDownPos = QPoint(rx, ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}

void ScreenAPI::cmpPoint(QPoint &leftTop, QPoint &rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {
            ;
        } else {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    } else {
        if (l.y() < r.y()) {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        } else {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}



frmScreen::frmScreen(uint ID, QWidget *parent) : QDialog(parent)
{
    m_sid = ID;
    this->InitForm();
}

frmScreen::~frmScreen()
{
    if(screen_api_p)
        delete screen_api_p;
    if(fullScreen)
        delete fullScreen;
    if(capScreen)
        delete capScreen;
    if(bgScreen)
        delete bgScreen;
}

QPixmap *frmScreen::get_screen()
{
    return this->capScreen;
}

void frmScreen::doCapture()
{
    SaveScreen();
}

void frmScreen::InitForm()
{
//    Qt::WindowStaysOnTopHint 總是顯示在最前面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

     m_rect = QApplication::desktop()->screenGeometry(m_sid);

    screen_api_p = new ScreenAPI(QSize(m_rect.width(),m_rect.height()));

    //保存全屏
    fullScreen = new QPixmap();
}

void frmScreen::paintEvent(QPaintEvent *)
{
    int x = screen_api_p->getLeftUp().x();
    int y = screen_api_p->getLeftUp().y();
    int w = screen_api_p->getRightDown().x() - x;
    int h = screen_api_p->getRightDown().y() - y;

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    QFont font;
    font.setFamily(QString("Microsoft YaHei"));
    font.setPixelSize(14);
    painter.setFont(font);

    painter.drawPixmap(0, 0, *bgScreen);

    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);

    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawText(x + 2, y - 8, tr("截圖範圍：( %1 x %2 ) - ( %3 x %4 )  圖片大小：( %5 x %6 )")
                     .arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));
}

void frmScreen::showEvent(QShowEvent *)
{
    QPoint point(-1, -1);
    screen_api_p->setStart(point);
    screen_api_p->setEnd(point);

    QScreen *toolscreen = QGuiApplication::primaryScreen();

    *fullScreen=toolscreen->grabWindow(0,m_rect.x(),m_rect.y(),m_rect.width(),m_rect.height());

    bgScreen = new QPixmap(*fullScreen);
    QPainter p(bgScreen);

    //設置透明度實現模糊背景
    QPixmap pix(screen_api_p->width(), screen_api_p->height());

    pix.fill((QColor(32, 34, 32, 150)));

    p.drawPixmap(0, 0, pix);
}

void frmScreen::SaveScreenOther()
{
    int x = screen_api_p->getLeftUp().x();
    int y = screen_api_p->getLeftUp().y();
    int w = screen_api_p->getRightDown().x() - x;
    int h = screen_api_p->getRightDown().y() - y;
    capScreen= new QPixmap(fullScreen->copy(x, y, w, h));
    emit captureSignals();
    close();
}

void frmScreen::SaveScreen()
{
    int x = screen_api_p->getLeftUp().x();
    int y = screen_api_p->getLeftUp().y();
    int w = screen_api_p->getRightDown().x() - x;
    int h = screen_api_p->getRightDown().y() - y;

    capScreen= new QPixmap(fullScreen->copy(x, y, w, h));
    emit captureSignals();

    close();
}

void frmScreen::SaveFullScreen()
{
    capScreen= new QPixmap(fullScreen->copy());
    emit captureSignals();
    close();
}

void frmScreen::mouseMoveEvent(QMouseEvent *e)
{
    if (screen_api_p->getStatus() == ScreenAPI::SELECT) {
        screen_api_p->setEnd(e->pos());
    } else if (screen_api_p->getStatus() == ScreenAPI::MOV) {
        QPoint p(e->x() - movPos.x(), e->y() - movPos.y());
        screen_api_p->move(p);
        movPos = e->pos();
    }

    update();
}

void frmScreen::mousePressEvent(QMouseEvent *e)
{
    int status = screen_api_p->getStatus();

    if (status == ScreenAPI::SELECT) {
        screen_api_p->setStart(e->pos());
    } else if (status == ScreenAPI::MOV) {
        if (screen_api_p->isInArea(e->pos()) == false) {
            screen_api_p->setStart(e->pos());
            screen_api_p->setStatus(ScreenAPI::SELECT);
        } else {
            movPos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }

    update();
}

void frmScreen::mouseReleaseEvent(QMouseEvent *)
{
    if (screen_api_p->getStatus() == ScreenAPI::SELECT) {
        screen_api_p->setStatus(ScreenAPI::MOV);
        this->doCapture();

    } else if (screen_api_p->getStatus() == ScreenAPI::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}

