#include "DialogInput.h"
#include "ui_DialogInput.h"

DialogInput::DialogInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInput)
{
    ui->setupUi(this);

    lay = new QVBoxLayout(ui->wBody);

    setWindowTitle("  ");

}

DialogInput::~DialogInput()
{
    delete ui;
}

void DialogInput::setTitle(QString sTitle)
{
    ui->lbTitle->setText(sTitle);
}

void DialogInput::addInput(QString sLb, QVariantMap input)
{
    DialogInputItem *item = new DialogInputItem(ui->wBody);

    item->setData(sLb,input);

    lay->addWidget(item);

    ui->wBody->setLayout(lay);

    m_listW.append(item);

}

void DialogInput::hideDelete()
{
    ui->btnDel->hide();
}

QVariantMap DialogInput::data()
{
    QVariantMap re;

    foreach(DialogInputItem *item ,m_listW)
    {
        if(!item->isHidden())
        {
            re[item->data().firstKey()]= item->data().first();
        }
    }

    return re;
}

DialogInputItem::DialogInputItem(QWidget *parent):QWidget(parent)
{
    this->setMinimumHeight(36);

    lb = new QLabel(this);

    lb->setMinimumWidth(100);

    lb->setMaximumWidth(100);

    txt = new QLineEdit(this);

    //  QSizePolicy policy()

    txt->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout *lay = new QHBoxLayout(this);

    lay->setMargin(6);

    lay->addWidget(lb);

    lay->addWidget(txt);
}

void DialogInputItem::setData(QString title, QVariantMap data)
{
    m_data = data;

    lb->setText(title);
    qDebug()<<"typetype :"<<m_data.first().type();
   if(m_data.first().type()==QVariant::UInt)
   {

       txt->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[1-9][0-9]*$")));
       //"^[0-9]*[1-9][0-9]*$"　　//正整数

   }
   else
   {

   }

    txt->setText(m_data.first().toString());
}

QVariantMap DialogInputItem::data()
{
    QString sKey=  m_data.firstKey();

    m_data[sKey] = txt->text().trimmed();

    return m_data;
}



void DialogInput::on_btnOk_clicked()
{
    done(1);
}


void DialogInput::on_btnCancel_clicked()
{
    reject();
}


void DialogInput::on_btnDel_clicked()
{
    if(1==DMSG.showMsg("","確定要刪除嗎？",QStringList()<<"否"<<"是"))
        done(3);
}

