#include "DialogAddValueTypeEdit.h"
#include "ui_DialogAddValueTypeEdit.h"

DialogAddValueTypeEdit::DialogAddValueTypeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddValueTypeEdit)
{
    ui->setupUi(this);

    m_listItem<<ui->sb0<<ui->sb1<<ui->sb3<<ui->sbSub;

    ui->btnDel->hide();

  //  ui->comboBox->addItem("未設定");

    for(int i=0;i<m_listItem.length();i++)
    {

        connect(m_listItem[i],SIGNAL(valueChanged(double)),this,SLOT(updateTotal(double)));
    }

    ui->lbRate->hide();

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

void DialogAddValueTypeEdit::setRate(QStringList sName, QStringList sRate)
{
    m_listRateName = sName;

    m_listRate = sRate;

    while(sRate.length()<sName.length())
    {
        sRate.append("1");
    }

    ui->comboBox->clear();

    ui->comboBox->addItem("未設定");

    ui->comboBox->addItems(sName);


}

//void DialogAddValueTypeEdit::setData(QStringList list)
//{
//    ui->btnDel->show();

//    while(list.length()<m_listItem.length())
//    {
//        list.append("0");
//    }

//    if(list.length()==m_listItem.length())
//    {
//        list.append("1");
//    }

//    if(list.length()==m_listItem.length()+1)
//    {
//        list.append("unkonw");
//    }

//    m_listData = list;

//    for(int i=0;i<m_listData.length() && i<m_listItem.length();i++)
//    {
//        m_listItem[i]->setValue(list.at(i).toDouble());
//    }

//    int iIdx = m_listRateName.indexOf(m_listData.last())+1;

//    ui->comboBox->setCurrentIndex(qBound(0,iIdx,ui->comboBox->count()-1));

//}

void DialogAddValueTypeEdit::setData(QVariantMap data)
{
    ui->btnDel->show();

    DataPayType d(data);

    ui->txName->setText(d.Name);

    ui->sbSub->setValue(d.SubValue.first().toDouble());

    ui->sb0->setValue(d.Value[0].toDouble());
    ui->sb1->setValue(d.Value[1].toDouble());
    ui->sb2->setValue(d.Value[2].toDouble());
    ui->sb3->setValue(d.Value[3].toDouble());

    ui->txName->setText(d.Name);

    int iIdx = m_listRateName.indexOf(d.Currency);

    ui->comboBox->setCurrentIndex(qBound(0,iIdx,ui->comboBox->count()-1)+1);

}




QVariantMap DialogAddValueTypeEdit::data()
{
   DataPayType data;

   data.Name=ui->txName->text().trimmed();

   data.Value.clear();

   data.Value<<ui->sb0->text()<<ui->sb1->text()<<ui->sb2->text()<<ui->sb3->text();

   data.SubValue.clear();

   data.SubValue<<ui->sbSub->text();

   data.Currency = ui->comboBox->currentText();

   return data.data();

}

void DialogAddValueTypeEdit::on_btnCancel_clicked()
{
    reject();
}


void DialogAddValueTypeEdit::on_btnOk_clicked()
{
    if(ui->comboBox->currentText()=="未設定")
    {
        UI.showMsg("","請選擇幣別",QStringList()<<"OK");
        return;
    }

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


void DialogAddValueTypeEdit::on_comboBox_currentIndexChanged(int index)
{
    updateTotal();

    if(index<1 || index>m_listRate.length())
    {
        ui->lbRate->hide();
        ui->lbTotal->hide();
        return;
    }

    ui->lbRate->show();

    ui->lbTotal->show();

    ui->lbRate->setText(m_listRate.at(index-1));
}

void DialogAddValueTypeEdit::updateTotal(double)
{
    if(ui->comboBox->currentIndex()<=0)
        return;


    double d= 1.000*ui->sb0->value()*ui->sb1->value()*ui->sb2->value()*ui->sb3->value()/ui->sbSub->value();


    double total= d*m_listRate.at(ui->comboBox->currentIndex()-1).toDouble();

    ui->lbTotal->setText(QString::number(total, 'f', 3));

    ui->spPrime->setValue(ui->spOrigin->value()* ui->lbTotal->text().toDouble());

}



void DialogAddValueTypeEdit::on_spOrigin_valueChanged(double )
{
     ui->spPrime->setValue(ui->spOrigin->value()*ui->lbTotal->text().toDouble());
}


void DialogAddValueTypeEdit::on_spPrime_valueChanged(double )
{
    ui->spOrigin->setValue(ui->spPrime->value()/ui->lbTotal->text().toDouble());
}

