#include "Label3.h"

Label3::Label3(QWidget *parent)
    : QWidget{parent}
{

}

void Label3::paintEvent(QPaintEvent *)
{






    QRect r = rect();

    r.setWidth(r.width()-4);

    r.setHeight(r.height()-2);

    QPainter p(this);

    auto drawString =[=](int i,QPainter &p)
    {


        if(i!=m_iIdx)
        {

            QColor color(Qt::gray);

            if(m_sColor[i]!="")
                color.setNamedColor(m_sColor[i]);

            p.setPen(color);

            QFont f("Arial");
            f.setPixelSize(12);

            p.setFont(f);

            if(i==0)
            {
                p.drawText(r,Qt::AlignLeft | Qt::AlignTop,m_sText[i]);
            }
            else if(i==2)
            {
                p.drawText(r,Qt::AlignRight | Qt::AlignBottom,m_sText[i]);
            }
            else
            {

                f.setPixelSize(14);

                p.setFont(f);

                if(m_iIdx==0)
                    p.drawText(r,Qt::AlignHCenter | Qt::AlignTop,m_sText[i]);
                else
                    p.drawText(r,Qt::AlignHCenter | Qt::AlignBottom,m_sText[i]);
            }

        }
        else
        {

            QColor color(Qt::black);

            if(m_sColor[i]!="")
                color.setNamedColor(m_sColor[i]);


            p.setPen(color);

            QFont f("Arial");

            f.setPixelSize(16);

            if(!m_bFlag)
            {
//                f.setBold(true);

//                f.setPointSize(16);
            }


            p.setFont(f);

            if(i==0)
                p.drawText(r,Qt::AlignLeft | Qt::AlignVCenter,m_sText[i]);
            else if(i==2)
                p.drawText(r,Qt::AlignRight | Qt::AlignVCenter,m_sText[i]);
            else
                p.drawText(r,Qt::AlignCenter,m_sText[i]);
        }


    };




    if(m_bBorder)
    {
        p.setPen(Qt::blue);

        p.drawRect(rect());
    }

    if(m_bVisable[LABEL_3::_Left])
        drawString(LABEL_3::_Left,p);

    if(m_bVisable[LABEL_3::_Right])
        drawString(LABEL_3::_Right,p);

    if(m_bVisable[LABEL_3::_Cent])
        drawString(LABEL_3::_Cent,p);





}

void Label3::setCurrentIdx(int idx)
{
    int i = qBound(0,idx,2);

    m_iIdx = i;
}

void Label3::setText(QString sCurrentText)
{
    m_sText[m_iIdx]=sCurrentText;
}

void Label3::setText(int idx, QString sText, QString sColorName)
{
    int i = qBound(0,idx,2);

    m_sText[i] = sText;
    m_sColor[i] = sColorName;
}

void Label3::setText(QString sTextL, QString sTextC, QString sTextR)
{
    m_sText[LABEL_3::_Left] = sTextL;

    m_sText[LABEL_3::_Cent] = sTextC;

    m_sText[LABEL_3::_Right] = sTextR;

}

QString Label3::text()
{
    return m_sText[m_iIdx];
}

QString Label3::text(int iIdx)
{
    int i = qBound(0,iIdx,2);

    return m_sText[i];
}

void Label3::setData(QVariantList data)
{

    if(data.length()<4)
        return;


    m_sText[LABEL_3::_Left] = data.first().toString();
    m_sText[LABEL_3::_Cent] = data.at(1).toString();
    m_sText[LABEL_3::_Right]=data.at(2).toString();
    m_iIdx = qBound(0,data.at(3).toInt(),2);

    if(data.length()<8)
        return;

    m_bVisable[LABEL_3::_Left] = data.at(4).toBool();
    m_bVisable[LABEL_3::_Cent] = data.at(5).toBool();
    m_bVisable[LABEL_3::_Right]= data.at(6).toBool();
    m_bBorder= data.at(7).toBool();


}

QVariantList Label3::data()
{
    QVariantList list;

    list<<m_sText[LABEL_3::_Left];
    list<<m_sText[LABEL_3::_Cent];
    list<<m_sText[LABEL_3::_Right];
    list<<m_iIdx;
    list<<m_bVisable[LABEL_3::_Left];
    list<<m_bVisable[LABEL_3::_Cent];
    list<<m_bVisable[LABEL_3::_Right];
    list<<m_bBorder;

    return list;
}

void Label3::setVisable(bool bL, bool bC, bool bR)
{
    m_bVisable[LABEL_3::_Left] = bL;

    m_bVisable[LABEL_3::_Cent] = bC;

    m_bVisable[LABEL_3::_Right] = bR;
}

void Label3::setFlag(bool b)
{
    m_bFlag = b;
}

void Label3::setBorder(bool b)
{
    m_bBorder = b;
}
