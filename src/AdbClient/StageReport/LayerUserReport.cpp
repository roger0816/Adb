#include "LayerUserReport.h"
#include "ui_LayerUserReport.h"

LayerUserReport::LayerUserReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerUserReport)
{
    ui->setupUi(this);

    ui->stackDate->setCurrentIndex(1);

    ui->dateEdit->setDateTime(GLOBAL.dateTimeUtc8());

    m_btns.addButton(ui->btnMonth,0);
    m_btns.addButton(ui->btnDay,1);

    connect(&m_btns,SIGNAL(idClicked(int)),this,SLOT(slotBtnDate(int)));

    ui->tb->setModel(&m_model);



}

LayerUserReport::~LayerUserReport()
{
    delete ui;
}

void LayerUserReport::refresh()
{
    if(m_btns.checkedId()<0)
        return;

    bool bIsMonth = ui->btnMonth->isChecked();
    m_model.updateData(bIsMonth,ui->cbType->currentIndex(),ui->dateEdit->dateTime(),"");
}

void LayerUserReport::slotBtnDate(int iId)
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

    refresh();

}


void LayerUserReport::on_btnUserReport_clicked()
{
    refresh();
}


void LayerUserReport::on_dateEdit_dateChanged(const QDate &date)
{
     refresh();
}


void LayerUserReport::on_cbType_currentIndexChanged(int index)
{
     refresh();
}

