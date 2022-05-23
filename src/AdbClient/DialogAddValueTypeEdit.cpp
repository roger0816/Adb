#include "DialogAddValueTypeEdit.h"
#include "ui_DialogAddValueTypeEdit.h"

DialogAddValueTypeEdit::DialogAddValueTypeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddValueTypeEdit)
{
    ui->setupUi(this);

    m_listItem<<ui->sb1<<ui->sb2<<ui->sbTotal<<ui->sb3<<ui->sb4
             <<ui->sb5<<ui->sb6<<ui->sb7<<ui->sb8<<ui->sb9<<ui->sb10<<ui->sb11
            <<ui->sb12<<ui->sb13<<ui->sb14<<ui->sb15;

    ui->btnDel->hide();

}

DialogAddValueTypeEdit::~DialogAddValueTypeEdit()
{
    delete ui;
}

void DialogAddValueTypeEdit::setName(QString sName)
{
    ui->txName->setText(sName);
}

QString DialogAddValueTypeEdit::Name()
{
    return ui->txName->text();
}

void DialogAddValueTypeEdit::setData(QStringList list)
{
    ui->btnDel->show();

    while(list.length()<m_listItem.length())
    {
        list.append("0");
    }

    for(int i=0;i<list.length();i++)
    {
        m_listItem[i]->setValue(list.at(i).toDouble());
    }
}

QStringList DialogAddValueTypeEdit::data()
{
    QStringList list;

    for(int i=0;i<m_listItem.length();i++)
    {
        list.append(QString::number(m_listItem.at(i)->value()));
    }

    return list;
}

void DialogAddValueTypeEdit::on_btnCancel_clicked()
{
    reject();
}


void DialogAddValueTypeEdit::on_btnOk_clicked()
{
    QString sMsg ="確認新增嗎？";

    if(!ui->btnDel->isHidden())
    {
        sMsg = "確定修改嗎？";
    }

    if(1==UI.showMsg("",sMsg,QStringList()<<"否"<<"是"))
        done(1);
}


void DialogAddValueTypeEdit::on_btnDel_clicked()
{
   if(1==UI.showMsg("","確認刪除嗎？",QStringList()<<"否"<<"是"))
    done(3);
}

