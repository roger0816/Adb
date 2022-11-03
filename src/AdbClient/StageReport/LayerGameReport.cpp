#include "LayerGameReport.h"
#include "ui_LayerGameReport.h"

LayerGameReport::LayerGameReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerGameReport)
{
    ui->setupUi(this);
    m_btns.addButton(ui->btnMonth,0);
    m_btns.addButton(ui->btnDay,1);

    connect(&m_btns,SIGNAL(idClicked(int)),this,SLOT(slotBtnDate(int)));

    ui->dateEdit->setDateTime(GLOBAL.dateTimeUtc8());


    connect(ui->btnGameReport,&QPushButton::click,this,&LayerGameReport::slotGameReport);

    ui->tb->setModel(&m_model);

}

LayerGameReport::~LayerGameReport()
{
    delete ui;
}

void LayerGameReport::refresh()
{

}

void LayerGameReport::slotBtnDate(int iId)
{
    ui->stackDate->setCurrentIndex(0);

    if(iId==0)
    {
        ui->dateEdit->setDisplayFormat("yyyy/M");
        ui->dateEdit->setCurrentSection(QDateTimeEdit::MonthSection);
    }
    else
    {
        ui->dateEdit->setDisplayFormat("yyyy/M/d");
        ui->dateEdit->setCurrentSection(QDateTimeEdit::DaySection);
    }


}


void LayerGameReport::slotGameReport()
{
    refresh();
}
