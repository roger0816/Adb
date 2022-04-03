#include "CSideMenu.h"
#include "ui_CSideMenu.h"

CSideMenu::CSideMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSideMenu)
{
    // ui->setupUi(this);

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    m_wBg = new QWidget(this);
    m_wBg->setObjectName(QString::fromUtf8("wBg"));

    gridLayout->addWidget(m_wBg, 0, 0, 1, 1);





    this->setLayout(gridLayout);


    //  QPushButton {

    //      border:none;
    //      border-radius: 6px;
    //      border-color: beige;
    //      font:  20px;
    //      min-width: 8em;
    //      min-height:1.2em;
    //      padding: 6px;
    //color: rgb(255, 255, 255);
    //font: 700 20pt \"Microsoft JhengHei UI\";
    //  }

    //  QPushButton:hover
    //  {
    //      background-color: rgb(198, 200, 223);
    //      border-style: outset;
    //      border-width: 2px;

    //      font:  22px;
    //  }
    //  QPushButton:pressed {

    //      background-color: rgb(198, 200, 223);

    //      border-style: outset;
    //      border-width: 2px;
    //  }

    // background-color: rgb(0, 37, 88);


    //    QPushButton{
    //    color: rgb(255, 255, 255);
    //        font: 700 20pt "Microsoft JhengHei UI";
    //    }

}

CSideMenu::~CSideMenu()
{
    delete ui;
}



void CSideMenu::setBtns(QStringList listBtnName, bool bIsVBoxLayout, int baseSize)
{

    setButtonStyle(baseSize);

    foreach(QPushButton *btn ,m_listBtn)
    {
        btn->hide();
    }

    while(m_listBtn.length()<listBtnName.length())
    {
        QPushButton *btn = new QPushButton(m_wBg);

        btn->setCheckable(true);

        btn->setFlat(true);

        m_listBtn.append(btn);

    }

    m_wBg->setLayout(layoutBtns(listBtnName,m_listBtn,bIsVBoxLayout));

}

void CSideMenu::setSubBtns(int iIdx, QStringList listBtnName)
{

}

QGridLayout *CSideMenu::layoutBtns(QStringList listBtnName, QList<QPushButton *> &listBtn, bool bIsVBoxLayout)
{

    QGridLayout *lay = new QGridLayout();

    lay->setMargin(0);

    lay->setSpacing(0);

    for(int i=0;i<listBtn.length();i++)
    {
        listBtn[i]->setObjectName(QString::number(i)+"_0");

        listBtn[i]->show();

        listBtn[i]->setText(listBtnName.at(i));

        listBtn[i]->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        if(bIsVBoxLayout)
        {


            lay->addWidget(listBtn[i],i,0);
        }
        else
        {

            lay->addWidget(listBtn[i],0,i);
        }
    }


    QSpacerItem *space;

    if(bIsVBoxLayout)
    {
        space = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay->addItem(space,listBtn.length(),0);
    }
    else
    {
        space = new QSpacerItem(20, 40,  QSizePolicy::Expanding,QSizePolicy::Minimum);

        lay->addItem(space,0,listBtn.length());
    }

    return lay;
}

void CSideMenu::setButtonStyle(int iPoint)
{
    m_wBg->setStyleSheet("QWidget#wBg{"
                         "background-color: rgb(0, 37, 88);"
                         "}"

                         "QPushButton { \
                         border:none; \
            border-radius: 6px; \
    border-color: beige; \
font: 700 "+QString::number(iPoint)+"px \"Microsoft JhengHei UI\"; \
    min-width: 8em; \
    min-height:1.2em; \
padding: 6px; \
color: rgb(255, 255, 255); \
}"

" QPushButton:hover \
{ \
background-color: rgb(198, 200, 223); \
border-style: outset; \
border-width: 2px; \
font:  "+QString::number(iPoint*1.1)+"px; \
}"
" QPushButton:pressed { \
background-color: rgb(178, 180, 203); \
border-style: outset; \
border-width: 2px; \
}"
" QPushButton:checked { \
background-color: rgb(0, 0, 0); \
border-style: outset; \
border-width: 2px; \
}"

);


}
