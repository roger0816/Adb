#ifndef ITEMPICOBJ_H
#define ITEMPICOBJ_H



#include <QWidget>
#include <QBuffer>
#include <QLabel>
#include <QDateTime>
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QCryptographicHash>

#include <QResizeEvent>
#include <QGridLayout>

#include "screenapi.h"
#include "mutiscreen.h"
namespace Ui {
class ItemPicObj;
}

namespace _ItemPic {

class DialogPicDetail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPicDetail(QWidget *parent = nullptr):QDialog(parent)
    {
        setWindowFlags(windowFlags()  | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint );

        setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

        setWindowTitle(" ");
        m_img=new QImage;
        m_pic->setStyleSheet("background-color:black;");

    }

    ~DialogPicDetail(){delete m_img;}

    void reSetPic()
    {
        //  m_pic->setStyleSheet(" background-color: #f3f3f3;");

        m_pic->resize(size());

        m_pic->setPixmap(QPixmap::fromImage(m_img->scaled(m_pic->size(),Qt::KeepAspectRatio)));
    }


    void showEvent(QShowEvent *)override{reSetPic();}
    void resizeEvent(QResizeEvent *)override{reSetPic();}


    QLabel *m_pic = new QLabel(this);

    QImage *m_img = new QImage();
};

}

using namespace _ItemPic;

class ItemPicObj : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPicObj(QWidget *parent = nullptr);
    ~ItemPicObj();

    QVariantMap data();

    void setData(QByteArray data);

    void setMainWindow(QWidget *w);
    void setFileName(QString m_sName);


    void setDataFromFilePath(QString sFile="");

    void setReadOnly(bool b);

    void setEnableDetailMode(bool b=true);

    void setNoButton();

    bool m_bHasPic =false;

protected:
    virtual QString uploadPic()
    { return "";}



   // mutiScreen *captrue = new mutiScreen(this);

    bool m_bEnableDetail=true;

    QWidget *m_mainWindow = nullptr;

    QString m_sFileName=QDateTime::currentDateTimeUtc().addSecs(60*60*8).toString("yyyyMMddhhmmss");

    QPoint m_pos;

    QImage *m_img=nullptr;

    QString m_sFilePath="";

    QByteArray m_dataHex=QByteArray();

    DialogPicDetail *m_dialogDetal=new DialogPicDetail(this);


    void showEvent(QShowEvent *) override;

    void resizeEvent(QResizeEvent * )override;

    void mousePressEvent(QMouseEvent *e) override;

    void reSetPic();



   // QString m_sFileName = GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

private slots:


    void showDetail();


public slots:
    void slotClear();
    void slotClip();

    void slotDownload();

    void slotSetPic();



signals:

    void finishedSaveImage(QString ,bool);


private:
     Ui::ItemPicObj *ui;
};

#endif // ITEMPICOBJ_H
