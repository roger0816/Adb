#include "EditScheduleHeader.h"
#include "ui_EditScheduleHeader.h"

EditScheduleHeader::EditScheduleHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditScheduleHeader)
{
    ui->setupUi(this);

    m_listTx0<<ui->tx0<<ui->tx1<<ui->tx2<<ui->tx3
              <<ui->tx4<<ui->tx5<<ui->tx6<<ui->tx7;

    m_listTx1<<ui->tx0_2<<ui->tx1_2<<ui->tx2_2<<ui->tx3_2
              <<ui->tx4_2<<ui->tx5_2<<ui->tx6_2<<ui->tx7_2;

    setTabOrder(ui->tx0,ui->tx1);
    setTabOrder(ui->tx1,ui->tx2);
    setTabOrder(ui->tx2,ui->tx3);
    setTabOrder(ui->tx3,ui->tx4);
    setTabOrder(ui->tx4,ui->tx5);
    setTabOrder(ui->tx5,ui->tx6);
    setTabOrder(ui->tx6,ui->tx7);
    setTabOrder(ui->tx7,ui->btnOk);

    setTabOrder(ui->btnOk,ui->tx0);

}

EditScheduleHeader::~EditScheduleHeader()
{
    delete ui;
}

void EditScheduleHeader::setData(QStringList list0,QStringList list1)
{

    reCount(list0.length(),list1.length());


    for(int i=0;i<m_iCount0;i++)
    {
       m_listTx0[i]->setText(list0.at(i));

    }

    for(int i=0;i<m_iCount1;i++)
    {
       m_listTx1[i]->setText(list1.at(i));

    }

}

void EditScheduleHeader::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event); // 調用基類的事件處理

    // 當子窗口獲得焦點時，設置初始焦點到 tx0 控件（第一次獲得焦點時）
    if (!event->gotFocus())
        ui->tx0->setFocus();
}

void EditScheduleHeader::focusOutEvent(QFocusEvent *event)
{
    // 當焦點因 Tab 或 Shift+Tab 離開時，重新設置焦點到 tx0
    if (event->reason() == Qt::TabFocusReason || event->reason() == Qt::BacktabFocusReason)
    {
        ui->tx0->setFocus();
        event->accept(); // 阻止事件向上傳遞，防止焦點轉移到父窗口
    }
    else
    {
        QWidget::focusOutEvent(event); // 調用基類的事件處理
    }
}

void EditScheduleHeader::on_btnCancel_clicked()
{
    hide();
}

void EditScheduleHeader::showEvent(QShowEvent *)
{
    ui->tx0->setFocus();
}

void EditScheduleHeader::reCount(int iCount0,int iCount1)
{
    m_iCount0 = qBound(0,iCount0,m_listTx0.length());

    for(int i=0;i<m_listTx0.length();i++)
    {
        m_listTx0[i]->setVisible(i<iCount0);
    }

    m_iCount1 = qBound(0,iCount1,m_listTx1.length());

    for(int i=0;i<m_listTx1.length();i++)
    {
        m_listTx1[i]->setVisible(i<iCount1);
    }

}


void EditScheduleHeader::on_btnSub_clicked()
{
    if(m_iCount0<=1)
        return;

    reCount(m_iCount0-1,m_iCount1);
}

void EditScheduleHeader::on_btnAdd_clicked()
{
    if(m_iCount0>=m_listTx0.length())
        return;

    reCount(m_iCount0+1,m_iCount1);
}

void EditScheduleHeader::on_btnSub_2_clicked()
{

    if(m_iCount1<=1)
        return;

    reCount(m_iCount0,m_iCount1-1);


}


void EditScheduleHeader::on_btnAdd_2_clicked()
{
    if(m_iCount1>=m_listTx1.length())
        return;

    reCount(m_iCount0,m_iCount1+1);
}





void EditScheduleHeader::on_btnOk_clicked()
{
    QStringList list0,list1;

    for(int i=0;i<m_listTx0.length();i++)
    {
        if(m_listTx0.at(i)->isVisible() &&m_listTx0.at(i)->text().trimmed()!="" &&m_listTx0.at(i)->text()!="備註")
        {
            list0.append(m_listTx0.at(i)->text());
        }

    }

    for(int i=0;i<m_listTx1.length();i++)
    {
        if(m_listTx1.at(i)->isVisible() &&m_listTx1.at(i)->text().trimmed()!=""  &&m_listTx1.at(i)->text()!="備註")
        {
            list1.append(m_listTx1.at(i)->text());
        }

    }


    emit done(list0,list1);
    hide();

}





