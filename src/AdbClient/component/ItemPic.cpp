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

    setMainWindow(UI.m_mainWidget);

    ItemPicObj::showEvent(e);
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





