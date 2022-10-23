#include "ItemPic.h"
#include "ui_ItemPic.h"



ItemPic::ItemPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPic)
{
    ui->setupUi(this);

    m_img = new QImage;

    m_dialogDetal->resize(1024,768);

    connect(ui->btnUpload,&QPushButton::clicked,this,&ItemPic::slotUpload);

    connect(ui->btnLbPicClear,&QPushButton::clicked,this,&ItemPic::slotClear);

    connect(ui->btnClip,&QPushButton::clicked,this,&ItemPic::slotClip);

    connect(ui->btnDownload,&QPushButton::clicked,this,&ItemPic::slotDownload);


    ui->stackedWidget->setCurrentIndex(0);
}

ItemPic::~ItemPic()
{
    qDebug()<<"~itemPic";
    //delete m_img;

    delete ui;

        qDebug()<<"~itemPic ok";

}
void ItemPic::setData(QByteArray data)
{
    if(data.length()<1)
        return;
    m_data=data;


    m_img->loadFromData(QByteArray::fromHex(m_data));

    ui->lbPic->setStyleSheet(" background-color: #f3f3f3;");

    ui->lbPic->setPixmap(QPixmap::fromImage(m_img->scaled(ui->lbPic->size(),Qt::KeepAspectRatio)));

}

void ItemPic::setDataFromFilePath(QString sFile)
{

    if(sFile=="")
    {
        sFile= QFileDialog::getOpenFileName(this,"選擇圖檔",".","*.png *.jpg");
    }

    if(sFile!="")
    {

        m_sFilePath = sFile;

        m_img->load(sFile);



        m_bHasPic= true;

        reSetPic();

        QFile file(m_sFilePath);
        if(file.open(QIODevice::ReadOnly))
        {

            m_data =file.readAll().toHex();
            file.close();
        }
    }
}

void ItemPic::setReadOnly(bool b)
{
    ui->stackedWidget->setCurrentIndex(b);
}

void ItemPic::showEvent(QShowEvent *)
{
    reSetPic();
}

void ItemPic::resizeEvent(QResizeEvent *)
{
    reSetPic();
}


QVariantMap ItemPic::data()
{
    QVariantMap re;

    QString sMd5;

    sMd5.append(QCryptographicHash::hash(m_data,QCryptographicHash::Md5).toHex());

    re["Md5"]=sMd5;

    re["Data"]=m_data;



    return re;
}




void ItemPic::showDetail()
{
    m_dialogDetal->m_img = m_img;

    m_dialogDetal->exec();

}




void ItemPic::mousePressEvent(QMouseEvent *e)
{

    if(e->y()<ui->lbPic->height() && m_bHasPic)
    {
        showDetail();
    }

}

void ItemPic::reSetPic()
{
    if(m_bHasPic)
    {
        ui->lbPic->setStyleSheet(" background-color: #f3f3f3;");

        ui->lbPic->setPixmap(QPixmap::fromImage(m_img->scaled(ui->lbPic->size(),Qt::KeepAspectRatio)));

    }
    else
    {
        ui->lbPic->clear();
        ui->lbPic->setStyleSheet("border-image: url(:/image0.png); \
                                 background-color: #f3f3f3;");
    }
}

void ItemPic::slotUpload()
{
    setDataFromFilePath();

}

void ItemPic::slotClear()
{
    m_sFilePath="";

    m_bHasPic = false;

    reSetPic();
}


void ItemPic::slotClip()
{

   //UI.m_mainWidget->hide();  //會觸發父層多個showEvent導致回來不在同畫面

    m_pos=UI.m_mainWidget->pos();

    UI.m_mainWidget->move(-10000,0);  //hide qApp

    QByteArray data = mutiScreen::Instance()->getCaptureData();

    UI.m_mainWidget->move(m_pos);  //Show qApp

    setData(data);


}

void ItemPic::slotDownload()
{

}


