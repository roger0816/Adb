#include "ItemOrderSelector.h"
#include "ui_ItemOrderSelector.h"

ItemOrderSelector::ItemOrderSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemOrderSelector)
{
    ui->setupUi(this);

    m_lay = new QGridLayout(ui->btnArea);

    m_lay->setSpacing(5);

    m_lay->setMargin(0);
    int iColCount = 6;

    for(int i=0;i<12;i++)
    {
        QPushButton *btn=new QPushButton(ui->btnArea);

        btn->setMinimumSize(200,33);
        btn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


        btn->setCheckable(true);

        int iCol = i%iColCount;
        int iRow =i/iColCount;

        m_lay->addWidget(btn,iRow,iCol);


        btn->hide();


        m_btns.addButton(btn,m_btns.buttons().length());

    }

    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(slotClickedFactory(int)));

    QSpacerItem *spacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    m_lay->addItem(spacer,0,7);

}

ItemOrderSelector::~ItemOrderSelector()
{
    delete ui;
}

void ItemOrderSelector::setBtns(QStringList list)
{

    QList<QAbstractButton*> listBtn = m_btns.buttons();

    for(int i=0;i<listBtn.length();i++)
    {
        if(i<list.length())
            listBtn[i]->setText(list.at(i));
        listBtn[i]->setVisible(i<list.length());

        listBtn[i]->setMinimumWidth(ui->btnArea->width()/6-5);
    }


}

void ItemOrderSelector::showEvent(QShowEvent *)
{
     QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}



void ItemOrderSelector::on_pushButton_clicked()
{
    QStringList list;

    for(int i=0;i<ui->spinBox->value();i++)
    {
        list<<"AA";
    }

    setBtns(list);

}

void ItemOrderSelector::refresh()
{
    QVariantList listOut;

    ACTION.action(ACT::QUERY_FACTORY_CLASS,QVariantMap(),listOut);

    m_listFactoryClass= listOut;

    QStringList listBtnText;
    foreach(QVariant v,m_listFactoryClass)
    {
        DataFactory data(v.toMap());
        listBtnText.append(data.Name);
    }

    setBtns(listBtnText);

}

void ItemOrderSelector::slotClickedFactory(int id)
{
    QAbstractButton *btn = m_btns.checkedButton();

    qDebug()<<btn->text();
}

