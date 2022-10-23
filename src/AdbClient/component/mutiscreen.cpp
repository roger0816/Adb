#include "mutiscreen.h"
#include <QDesktopWidget>
#include <QApplication>

mutiScreen::mutiScreen(QObject *parent) : QObject(parent)
{
    QDesktopWidget *desktop = QApplication::desktop();
    int screenNum = desktop->numScreens();

    mScreenlist.clear();

    for(int i = 0 ; i < screenNum ; i++)
    {
        QWidget *parent  = desktop->screen(i);
        frmScreen * s = new frmScreen(i,parent);
        QObject::connect(s,SIGNAL(captureSignals()),this,SLOT(screenImageReady()));
        mScreenlist << s;
    }

}
mutiScreen *mutiScreen::_instance = 0;

mutiScreen::~mutiScreen()
{
    while(mScreenlist.count())
    {
        frmScreen * s = mScreenlist.takeFirst();
        delete s;
    }
}

QPixmap *mutiScreen::get_screen()
{
    return &capicture_pix;
}

void mutiScreen::showCaptureScreen()
{
    foreach(frmScreen * s ,mScreenlist )
    {
        s->showMaximized();
    }
}

void mutiScreen::screenImageReady()
{
    frmScreen * s = qobject_cast<frmScreen *>(sender());

    this->capicture_pix = s->get_screen()->copy();

    foreach(frmScreen * s ,mScreenlist )
    {
        s->close();
    }
    emit capture_done();
}
