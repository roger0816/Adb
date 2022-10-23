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

    void setDataFromFilePath(QString sFile="");
private:

    mutiScreen *captrue = new mutiScreen();

    QPoint m_pos;

    QImage *m_img=nullptr;

    QString m_sFilePath="";

    QByteArray m_data=QByteArray();

    DialogPicDetail *m_dialogDetal=new DialogPicDetail(this);


    void showEvent(QShowEvent *) override;

    void resizeEvent(QResizeEvent * )override;

    void mousePressEvent(QMouseEvent *e) override;

    void reSetPic();

    bool m_bHasPic =false;

private slots:
    void slotUpload();

    void on_btnChip_clicked();

    void clear();

    void showDetail();

    void slotCaptrue();

private:
    Ui::ItemPic *ui;
};

#endif // ITEMPIC_H
