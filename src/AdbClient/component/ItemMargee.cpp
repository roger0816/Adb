#include "ItemMargee.h"
#include "ui_ItemMargee.h"

ItemMargee::ItemMargee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemMargee)
{
    ui->setupUi(this);
setAttribute(Qt::WA_TransparentForMouseEvents);
    label = new QLabel(ui->wContent);
    // label->hide();
    label->setText("abcdefghijklmnopqrstuvwxyz");

    label->resize(400, 50);
    label->setAlignment(Qt::AlignCenter);

    connect(&m_timer,&QTimer::timeout,this,&ItemMargee::slotMove);

    label->setStyleSheet("background-color:white");
    label->raise();


    m_timer.start(50);



}

ItemMargee::~ItemMargee()
{
    delete ui;
}



void ItemMargee::appendText(QString sTitle,QString sName,QString st)
{

    DataMargee d;
    d.sName=sName;
    d.sTitle=sTitle;
    d.sText =st;

    m_list.append(d);
    if(m_list.length()==1)
        reStart();
}

void ItemMargee::reStart()
{
    if(m_list.length()<=0)
        return;

    DataMargee data = m_list.first();

    ui->lbTitle->setText(data.sTitle);
    ui->lbName->setText(data.sName);
    QString st =m_list.first().sText;
    label->setText(st);
    QFontMetrics metrics(label->font());
    label->resize(metrics.horizontalAdvance(st) + 10, ui->wContent->height()); // 添加一些额外空间
    iX= width();

}

void ItemMargee::resizeEvent(QResizeEvent *)
{

}

void ItemMargee::slotMove()
{
    if(m_list.length()<1)
    {
        ui->wBg->hide();
        return ;

    }
    else
    {
         ui->wBg->show();
    }

  //  label->setText(m_list.first());

    label->move(iX-=3,(ui->wContent->height()-label->height())/2);
    if (iX + label->width() <= 0) {
        // 跑马灯运行完毕
        emit marqueeFinished();
        iX= width();
        if(m_list.length()>0)
            m_list.pop_front();

        reStart();
    }

}
