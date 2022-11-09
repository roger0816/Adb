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

    ui->tb->setModel(&m_model);

    ui->tb->hideColumn(6);

    connect(&m_btns,SIGNAL(idClicked(int)),this,SLOT(slotBtnDate(int)));

    connect(ui->btnClear,&QPushButton::clicked,this,[=](){
        ui->lineEdit->clear();
    });


    connect(ui->cbType,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](){refresh();});

    connect(ui->dateEdit,QOverload<const QDate&>::of(&QDateTimeEdit::dateChanged),[=](){refresh();});

    connect(ui->lineEdit,&QLineEdit::textChanged,[=](){refresh();});



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
    m_model.updateData(bIsMonth,ui->cbType->currentIndex(),ui->dateEdit->dateTime(),ui->lineEdit->text().trimmed());
}

void LayerUserReport::showEvent(QShowEvent *)
{
    QTimer::singleShot(100,this,SLOT(refresh()));
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








