#include "ItemPic.h"
#include "ui_ItemPic.h"



ItemPic::ItemPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPic)
{
    ui->setupUi(this);

    m_img = new QImage;

    m_dialogDetal->resize(1024,768);
    connect(ui->btnLbPicClear,&QPushButton::clicked,this,&ItemPic::clear);

    connect(ui->btnUpload,&QPushButton::clicked,this,&ItemPic::slotUpload);

    connect(captrue,&mutiScreen::capture_done,this,&ItemPic::slotCaptrue);

}

ItemPic::~ItemPic()
{
    delete captrue;

    delete m_img;

    delete ui;

}
void ItemPic::setData(QByteArray data)
{
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


void ItemPic::clear()
{
    m_sFilePath="";

    m_bHasPic = false;

    reSetPic();
}

void ItemPic::showDetail()
{
    m_dialogDetal->m_img = m_img;

    m_dialogDetal->exec();

}

void ItemPic::slotCaptrue()
{
    //UI.m_mainWidget->show();

    UI.m_mainWidget->move(m_pos);

    QPixmap p =captrue->get_screen()->copy();

    QByteArray data;

    QImage image = p.toImage();

    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG"); // writes image into ba in PNG format

    setData(data.toHex());

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


void ItemPic::on_btnChip_clicked()
{

   //UI.m_mainWidget->hide();  //會觸發父層多個showEvent導致回來不在同畫面

    m_pos=UI.m_mainWidget->pos();

    UI.m_mainWidget->move(-10000,0);

   QTimer::singleShot(500,this,[=](){ captrue->showCaptureScreen();});


    //  mutiScreen::Instance()->showCaptureScreen();

}



