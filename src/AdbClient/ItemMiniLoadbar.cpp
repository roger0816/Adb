#include "ItemMiniLoadbar.h"
#include "ui_ItemMiniLoadbar.h"

ItemMiniLoadbar::ItemMiniLoadbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemMiniLoadbar)
{
    ui->setupUi(this);

    m_bIsRun = false;

    m_iIdx = 0;

    m_iMsec = 0;

    for(int i=1;i<=8;i++)
    {
        m_listRes<<":/loading/loading1-"+QString::number(i)<<".png";
    }

    startTimer(100);

    //    QPixmap pixmap(":/icon/icon/iconImage.png");

    //    ui->lbText->setPixmap(pixmap.scaled(QSize(20,20),Qt::KeepAspectRatio));

    //  ui->lbText->hide();

    hide();

}

ItemMiniLoadbar::~ItemMiniLoadbar()
{

    delete ui;
}

void ItemMiniLoadbar::setLoading(bool bIsLoading)
{

    qDebug()<<"loading : "<<bIsLoading;

    m_bIsRun = bIsLoading;

    if(!m_bIsRun)
        QTimer::singleShot(3000,this,SLOT(slotChangeEnaled()));
    else
        slotChangeEnaled();

}

void ItemMiniLoadbar::timerEvent(QTimerEvent *)
{

    m_list.append(m_bIsRun);
    while(m_list.length()>3)
        m_list.pop_front();

    bool bRun = false;

    for(int i=0;i<m_list.length();i++)
    {
        if(m_list.at(i))
            bRun = true;
    }


    if(!bRun)
    {
        ui->lbPic->setVisible(false);

        this->hide();

        return;
    }
    else
    {
        this->show();

        ui->lbPic->setVisible(true);

    }



    m_iMsec +=200;

    if(m_iMsec >= 20000)
        m_iMsec = 0;

    if(ui->lbPic->isVisible())
    {
        m_iIdx++;

        if(m_iIdx>=m_listRes.length())
            m_iIdx = 0;

        QPixmap pixmap(m_listRes[qBound(0,m_iIdx++,m_listRes.length()-1)]);

        if(!pixmap.isNull())
        {

            ui->lbPic->setPixmap(pixmap.scaled(ui->lbPic->size(),Qt::KeepAspectRatio));
        }

    }


}

void ItemMiniLoadbar::showEvent(QShowEvent *)
{
    ui->lbPic->setMinimumWidth(ui->lbPic->height());

    ui->lbPic->setMaximumWidth(ui->lbPic->height());
}


void ItemMiniLoadbar::slotChangeEnaled()
{



    ui->lbPic->setVisible(m_bIsRun);


}


