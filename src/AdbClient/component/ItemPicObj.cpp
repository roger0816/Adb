#include "ItemPicObj.h"
#include "ui_ItemPicObj.h"



ItemPicObj::ItemPicObj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPicObj)
{
    ui->setupUi(this);

    m_img = new QImage;

    m_dialogDetal->resize(1024,768);

    connect(ui->btnSelectPic,&QPushButton::clicked,this,&ItemPicObj::slotSetPic);

    connect(ui->btnLbPicClear,&QPushButton::clicked,this,&ItemPicObj::slotClear);

    connect(ui->btnClip,&QPushButton::clicked,this,&ItemPicObj::slotClip);

    connect(ui->btnDownload,&QPushButton::clicked,this,&ItemPicObj::slotDownload);


    ui->stackedWidget->setCurrentIndex(0);
}

ItemPicObj::~ItemPicObj()
{

    delete m_img;

    delete ui;



}
void ItemPicObj::setData(QByteArray data)
{
    if(data.length()<1)
        return;

    m_bHasPic=true;

    m_dataHex=data;


    m_img->loadFromData(QByteArray::fromHex(m_dataHex));

    reSetPic();

}

void ItemPicObj::setMainWindow(QWidget *w)
{
    m_mainWindow = w;
}

void ItemPicObj::setFileName(QString m_sName)
{
    m_sFileName=m_sName;
}

void ItemPicObj::setDataFromFilePath(QString sFile)
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

            m_dataHex =file.readAll().toHex();
            file.close();
        }
    }
}

void ItemPicObj::setReadOnly(bool b)
{
    ui->stackedWidget->setCurrentIndex(b);
}

void ItemPicObj::setEnableDetailMode(bool b)
{
    m_bEnableDetail =b;
}

void ItemPicObj::setNoButton()
{
    ui->stackedWidget->hide();
}


void ItemPicObj::showEvent(QShowEvent *)
{
    QTimer::singleShot(100,this,SLOT(reSetPic()));

}

void ItemPicObj::resizeEvent(QResizeEvent *)
{
    reSetPic();
}


QVariantMap ItemPicObj::data()
{
    QVariantMap re;

    QString sMd5;

    sMd5.append(QCryptographicHash::hash(m_dataHex,QCryptographicHash::Md5).toHex());

    re["Md5"]=sMd5;

    re["Data"]=m_dataHex;



    return re;
}




void ItemPicObj::showDetail()
{
    if(!m_bEnableDetail)
        return;
    m_dialogDetal->m_img = m_img;

    m_dialogDetal->exec();

}




void ItemPicObj::mousePressEvent(QMouseEvent *e)
{

    if(e->y()<ui->lbPic->height() && m_bHasPic)
    {
        showDetail();
    }

}

void ItemPicObj::reSetPic()
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

void ItemPicObj::slotSetPic()
{
    setDataFromFilePath();

}

void ItemPicObj::slotClear()
{
    m_sFilePath="";

    m_bHasPic = false;

    reSetPic();
}


void ItemPicObj::slotClip()
{

    //UI.m_mainWidget->hide();  //會觸發父層多個showEvent導致回來不在同畫面


    if(m_mainWindow!=nullptr)
    {
        m_pos=m_mainWindow->pos();

        m_mainWindow->move(-10000,0);  //hide qApp
    }

    QByteArray data = mutiScreen::Instance()->getCaptureData();

    if(m_mainWindow!=nullptr)
    {
        m_mainWindow->move(m_pos);  //Show qApp
    }
    setData(data);

}

void ItemPicObj::slotDownload()
{
    QString sDir =QFileDialog::getExistingDirectory(this,"選擇存檔位置",".");

    QString sFileName = sDir+"/"+m_sFileName+".png";

    bool bOk = m_img->save(sFileName,"PNG");

    emit finishedSaveImage(sFileName,bOk);
}






