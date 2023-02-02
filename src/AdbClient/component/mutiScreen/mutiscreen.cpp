#include "mutiscreen.h"
#include <QDesktopWidget>
#include <QApplication>
#include "screenapi.h"
#include <QList>
#include <QPixmap>
#include <QClipboard>
#include <QMimeData>
#include <QVariant>



QList  <frmScreen*> mScreenlist;


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
    QDesktopWidget *desktop = QApplication::desktop();
    int i = 0;
    foreach(frmScreen * s ,mScreenlist )
    {
        s->showMaximized();
        s->move(desktop->screen(i)->pos());
        s->setGeometry(desktop->screen(i)->geometry());
        i++;
    }
}

QPixmap *mutiScreen::getCaptureScreen()
{


    showCaptureScreen();
    QEventLoop loop;

    loop.connect(this,&mutiScreen::capture_done,&loop,&QEventLoop::quit);

    loop.exec();

    return get_screen();

}

QPixmap *mutiScreen::getWindowXImage()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if(mimeData->hasImage())
    {
        capicture_pix = qvariant_cast<QPixmap>(mimeData->imageData());
        return &capicture_pix;
    }
    return nullptr;
}

QByteArray mutiScreen::getCaptureData()
{
    QPixmap *p = getCaptureScreen();

    QByteArray data;
    QImage image = p->toImage();
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // writes image into ba in PNG format

    return data.toHex();
}

QByteArray mutiScreen::getWindowsCaptureData()
{
    QPixmap *p = getWindowXImage();
    QByteArray data;

    if(p)
    {
        QImage image = p->toImage();
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // writes image into ba in PNG format
    }

    return data.toHex();
}



void mutiScreen::screenImageReady()
{
    frmScreen * s = qobject_cast<frmScreen *>(sender());

    capicture_pix = s->get_screen()->copy();

    foreach(frmScreen * s ,mScreenlist )
    {
        s->close();
    }
    emit capture_done();
}
