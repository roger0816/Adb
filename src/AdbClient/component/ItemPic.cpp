#include "ItemPic.h"


ItemPic::ItemPic(QWidget *parent) :
    ItemPicObj(parent)
{


}

ItemPic::~ItemPic()
{


}

void ItemPic::showEvent(QShowEvent *e)
{

    setMainWindow(UI.mainWidget());

    ItemPicObj::showEvent(e);
}

void ItemPic::setMd5(QString sMd5)
{
    emit sendLock(true);
    QVariantMap out;

    QString sKey="Md5";

    QVariant sValue = sMd5;

    ACTION.action(ACT::QUERY_PIC,sKey,sValue,out);

    if(out.contains("Data"))
    {
        setData(out["Data"].toByteArray());

        emit sendLock(false);
    }
}

QString ItemPic::md5()
{
    return this->data()["Md5"].toString();
}

QString ItemPic::uploadPic()
{
    QString sRe="";
    QString sError;
    QVariantMap d =data();

    if(!m_bHasPic)
        return sRe;

    bool bOk= ACTION.action(ACT::UPLOAD_PIC,d,sError);

    if(bOk)
        sRe = d["Md5"].toString();

    return sRe;
}





