#include "DialogNote.h"
#include "ui_DialogNote.h"

DialogNote::DialogNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNote)
{
    ui->setupUi(this);

    this->setWindowTitle("  ");

    connect(ui->btnOk,&QPushButton::clicked,this,&DialogNote::reject);

}

DialogNote::~DialogNote()
{
    delete ui;
}

void DialogNote::setData(QStringList list)
{
    QStringList listNote=list;

    while(listNote.length()<5)
        listNote.append("");

    ui->lb0->setText(listNote.at(0));

    ui->lb1->setText(listNote.at(1));

    ui->lb2->setText(listNote.at(2));

    ui->lb3->setText(listNote.at(3));

    ui->lb4->setText(listNote.at(4));



}

void DialogNote::hideReport()
{
    ui->groupBox4->hide();
}
