#include "ItemPic.h"
#include "ui_ItemPic.h"

ItemPic::ItemPic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPic)
{
    ui->setupUi(this);

    m_img = new QImage;


    m_dialogDetal = new QDialog(this);

    QGridLayout *lay=new QGridLayout;

    m_lbDetailPic = new QLabel(m_dialogDetal);

    m_lbDetailPic->setStyleSheet("background-color:black;");

    lay->addWidget(m_lbDetailPic);

    m_dialogDetal->setLayout(lay);

    m_dialogDetal->resize(1024,768);
    connect(ui->btnLbPicClear,&QPushButton::clicked,this,&ItemPic::clear);


}

ItemPic::~ItemPic()
{
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
    ui->lbPic->clear();
    ui->lbPic->setStyleSheet("border-image: url(:/image0.png); \
                             background-color: #f3f3f3;");
}

void ItemPic::showDetail()
{

    m_lbDetailPic->setPixmap(QPixmap::fromImage(m_img->scaled(m_lbDetailPic->size(),Qt::KeepAspectRatio)));



    m_dialogDetal->exec();
}

void ItemPic::mousePressEvent(QMouseEvent *e)
{

    if(e->y()<ui->lbPic->height())
    {
        showDetail();
    }

}

void ItemPic::on_btnUpload_clicked(QString sFilePath)
{
    QString sFile =sFilePath;

    if(sFilePath=="")
    {
        sFile= QFileDialog::getOpenFileName(this,"選擇圖檔",".","*.png *.jpg");
    }

    if(sFile!="")
    {

        m_sFilePath = sFile;

        m_img->load(sFile);

        ui->lbPic->setStyleSheet(" background-color: #f3f3f3;");

        ui->lbPic->setPixmap(QPixmap::fromImage(m_img->scaled(ui->lbPic->size(),Qt::KeepAspectRatio)));


        QFile file(m_sFilePath);
        if(file.open(QIODevice::ReadOnly))
        {

            m_data =file.readAll().toHex();
            file.close();
        }
    }

}


void ItemPic::on_btnChip_clicked()
{

        QVariantMap in;

        QVariantList listOut;

        QString sError;
        ACTION.action(ACT::QUERY_PIC,in,listOut,sError);
        qDebug()<<"dl length : "<<listOut.length();
        if(listOut.length()>0)
        {
            QByteArray data;

            data.append(listOut.first().toMap()["Data"].toByteArray());
            qDebug()<<"data size "<<data.size();
           setData(data);
        }
}



