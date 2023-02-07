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

void DialogNote::setUser(QStringList list)
{
    QStringList userList=list;

    while(userList.length()<6)
    {
        userList.append(" ");
    }

//    QObject::tr("<font color = red>%1</font>").arg("abc")+
//                                  QObject::tr("<font color = blue>%1</font>").arg("efg");


    ui->groupBox0->setTitle("報價                "+userList.at(0));
    ui->groupBox1->setTitle("下單                "+userList.at(1));
    ui->groupBox2->setTitle("接單                "+userList.at(2));
    ui->groupBox3->setTitle("儲值                "+userList.at(3));
    ui->groupBox4->setTitle("回報                "+userList.at(4));
    if(userList.at(5).trimmed()!="")
        ui->lbCheckUser->setText("  確認                "
                                 +userList.at(5));
}

void DialogNote::setData( QStringList list)
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
