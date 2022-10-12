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

void GlobalUi::setTbData(QTableWidget *tb, QVariantList data, QStringList listHeader, bool reTb, QList<int> listType)
{
    if(tb==nullptr || data.length()<1)
        return;
    if(reTb)
        tb->setRowCount(0);

    for(int i=0;i<data.length();i++)
    {
        if(tb->rowCount()<=i)
            tb->setRowCount(tb->rowCount()+1);

        for(int j=0;j<listHeader.length();j++)
        {
            int iType=0;

            if(listType.length()>=j)
                iType = listType.at(j);

            tb->setItem(i,j,tbItem(data.at(i),iType));
        }
    }


}


QTableWidgetItem *GlobalUi::tbItem(QVariant var, int iType, int iPixSize)
{

    QString st = var.toString();

    int type =iType;

    if(type==_AUTO)
    {
        if(var.type()==QVariant::Bool)
            type = _BOOL;
        else if(var.type()==QVariant::Double)
            type = _DOUBLE;
        else if(var.type()==QVariant::Date)
            type = _DATE;
        else if(var.type()==QVariant::DateTime)
            type = _DATETIME;
        else
            type = _TXT;

    }




    QTableWidgetItem *item = new QTableWidgetItem();

    QFont f =item->font();


    if(type == _BOOL)
    {
        st ="是";

        if(!var.toBool())
            st="否";
    }
    else if(type == _DOUBLE)
    {
        st = QString::number(var.toDouble(),'f', 2);
    }
    else if(type == _DATE)
    {
        st = var.toDateTime().toString("yyyy/MM/dd");

    }
    else if(type == _DATETIME)
    {
        st = var.toDateTime().toString("yyyy/MM/dd hh:mm");
        f.setPixelSize(12);
    }
    else if(type == _BUTTON)
    {
        f.setUnderline(true);

        item->setTextColor(QColor(85,170,255));
    }
    else if(type == _TOOLTIP)
    {
        item->setTextColor(QColor(77,77,77));
    }
    else //_TXT
    {

    }

    item->setText(st);


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

void GlobalUi::copyMsg(QString sMsg)
{
    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(sMsg, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(sMsg, QClipboard::Selection);
    }

}

void GlobalUi::toolTip(QString st)
{
  QToolTip::showText(QCursor::pos(),st);
}

void GlobalUi::slotLockLoading(bool b)
{
    m_loading->setLoading(b);
}
