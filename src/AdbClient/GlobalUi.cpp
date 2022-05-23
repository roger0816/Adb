#include "GlobalUi.h"

GlobalUi *GlobalUi::m_pInstance = nullptr;

GlobalUi::GlobalUi(QObject *parent)
    : QObject{parent}
{

}

GlobalUi &GlobalUi::Instance()
{
    if(m_pInstance==0)
        m_pInstance=new GlobalUi();
    return *m_pInstance;
}

int GlobalUi::showMsg(QString sTitle, QString sMsg, QStringList listBtn)
{
    return DMSG.showMsg(sTitle,sMsg,listBtn);
}

int GlobalUi::showMsg(QString sTitle, QString sMsg, QString btn)
{
    QStringList list;

    list.append(btn);

    return showMsg(sTitle,sMsg,list);
}


QTableWidgetItem *GlobalUi::tbItem(QVariant var, bool bBtn, int iPixSize)
{


    QString st = var.toString();

    if(var.type() == QVariant::Bool)
    {
        st ="是";

        if(!var.toBool())
            st="否";
    }
    else if(var.type() == QVariant::Date)
    {
        st = var.toDateTime().toString("yyyy/MM/dd");

    }
    else if(var.type() == QVariant::DateTime)
    {
        st = var.toDateTime().toString("yyyy/MM/dd hh:mm");
    }
    else if(var.type()==QVariant::Double)
    {
        st = QString::number(var.toDouble(),'f', 2);
    }


    QTableWidgetItem *item = new QTableWidgetItem(st);

    QFont f;

    f.setPixelSize(iPixSize);


    if(bBtn)
    {

     f.setUnderline(true);

     item->setTextColor(QColor(85,170,255));

    }

    item->setFont(f);


    item->setTextAlignment(Qt::AlignCenter);

    return item;

}

QFont GlobalUi::font(int iPixSize)
{
    QFont f;

    f.setPixelSize(iPixSize);

    return f;
}
