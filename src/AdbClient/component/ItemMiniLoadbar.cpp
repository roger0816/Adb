#include "ItemMiniLoadbar.h"
#include "ui_ItemMiniLoadbar.h"

ItemMiniLoadbar::ItemMiniLoadbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemMiniLoadbar)
{
    ui->setupUi(this);

    m_bIsRun = false;

    m_list.append(false);

    m_iIdx = 0;

    m_iMsec = 0;

    for(int i=1;i<=8;i++)
    {
        m_listRes<<":/loading/loading1-"+QString::number(i)<<".png";
    }

    startTimer(m_iTimerMsec);

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

    //連續二次沒run 才中止，防止loading 不連續感
    bool bRun = m_bIsRun;

    if(m_list.last())
        bRun= true;

    m_list.append(m_bIsRun);
    while(m_list.length()>3)
        m_list.pop_front();


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



    m_iMsec +=m_iTimerMsec;

    if(m_iMsec >= 99999)
        m_iMsec = 0;

    if(ui->lbPic->isVisible())
    {
        if(m_iMsec%(m_iTimerMsec*10)==0)
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


