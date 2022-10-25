#ifndef ITEMPIC_H
#define ITEMPIC_H

#include <QWidget>
#include <QBuffer>
#include <QLabel>
#include "Global.h"
#include "GlobalUi.h"
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QCryptographicHash>

#include <QResizeEvent>
#include <QGridLayout>

#include "screenapi.h"
#include "mutiscreen.h"
namespace Ui {
class ItemPic;
}


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



class ItemPic : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPic(QWidget *parent = nullptr);
    ~ItemPic();

    QVariantMap data();

    void setData(QByteArray data);

    void setFileName(QString m_sName);


    void setDataFromFilePath(QString sFile="");

    void setReadOnly(bool b);

    void setEnableDetailMode(bool b=true);
private:

   // mutiScreen *captrue = new mutiScreen(this);

    bool m_bEnableDetail=true;

    QPoint m_pos;

    QImage *m_img=nullptr;

    QString m_sFilePath="";

    QByteArray m_dataHex=QByteArray();

    DialogPicDetail *m_dialogDetal=new DialogPicDetail(this);


    void showEvent(QShowEvent *) override;

    void resizeEvent(QResizeEvent * )override;

    void mousePressEvent(QMouseEvent *e) override;

    void reSetPic();

    bool m_bHasPic =false;

    QString m_sFileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

private slots:
    void slotUpload();

    void slotClear();

    void slotClip();

    void slotDownload();

    void showDetail();

signals:

    void finishedSaveImage(QString ,bool);


private:
    Ui::ItemPic *ui;
};

#endif // ITEMPIC_H
