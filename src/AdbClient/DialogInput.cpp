#include "DialogInput.h"
#include "ui_DialogInput.h"

DialogInput::DialogInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInput)
{
    ui->setupUi(this);

    lay = new QVBoxLayout(ui->wBody);

    setWindowTitle("  ");

    ui->stackedWidget->setCurrentIndex(0);

}

DialogInput::~DialogInput()
{
    delete ui;

}

void DialogInput::setTitle(QString sTitle)
{
    ui->lbTitle->setText(sTitle);
}

void DialogInput::addComboBox(QString sLb, QVariantMap input)
{

    DialogInputItem *item = new DialogInputItem(ui->wBody);

    item->setComboData(sLb,input);

    lay->addWidget(item);

    ui->wBody->setLayout(lay);

    m_listW.append(item);
}

void DialogInput::addInput(QString sLb, QVariantMap input)
{
    DialogInputItem *item = new DialogInputItem(ui->wBody);

    item->setInputData(sLb,input);

    lay->addWidget(item);

    ui->wBody->setLayout(lay);

    m_listW.append(item);

}

void DialogInput::addSpinBox(QString sLb, double iMin, double iMax,double iValue)
{
    DialogInputItem *item = new DialogInputItem(ui->wBody);

    item->setSp(sLb,iMin,iMax,iValue);

    lay->addWidget(item);

    ui->wBody->setLayout(lay);

    m_listW.append(item);




}

void DialogInput::setText(QString sText)
{
    ui->stackedWidget->setCurrentWidget(ui->pageText);

    ui->text->setText(sText);
}

QString DialogInput::text()
{
    QString sRe="";

    if(ui->stackedWidget->currentWidget()==ui->pageText)
    {
        sRe = ui->text->toPlainText();
    }

    return sRe;
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

QVariantList DialogInput::datas()
{
    QVariantList listRe;
    foreach(DialogInputItem *item ,m_listW)
    {
        if(!item->isHidden())
        {
            listRe.append(item->data().first());
        }
    }

    return listRe;
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


//------------
DialogInputItem::DialogInputItem(QWidget *parent):QWidget(parent)
{
    this->setMinimumHeight(36);


}

void DialogInputItem::initInput()
{
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

void DialogInputItem::setInputData(QString title, QVariantMap data)
{

    initInput();

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

void DialogInputItem::initComboBox()
{
    lb = new QLabel(this);

    lb->setMinimumWidth(100);

    lb->setMaximumWidth(100);

    cb = new QComboBox(this);

    //  QSizePolicy policy()

    cb->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout *lay = new QHBoxLayout(this);

    lay->setMargin(6);

    lay->addWidget(lb);

    lay->addWidget(cb);
}

void DialogInputItem::setComboData(QString title,QVariantMap data)
{
    initComboBox();

    m_data = data;

    lb->setText(title);

    cb->addItems(m_data.first().toStringList());
}

void DialogInputItem::setSp(QString title, double iMin, double iMax, double iValue)
{
    lb = new QLabel(this);

    lb->setMinimumWidth(100);

    lb->setMaximumWidth(100);

    lb->setText(title);

    sp = new QSpinBox(this);

    //  QSizePolicy policy()

    sp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    sp->setRange(iMin,iMax);
    sp->setValue(iValue);
    m_data[title]=iValue;
    QHBoxLayout *lay = new QHBoxLayout(this);

    lay->setMargin(6);

    lay->addWidget(lb);

    lay->addWidget(sp);
}

QVariantMap DialogInputItem::data()
{
    QString sKey=  m_data.firstKey();

    if(cb!=nullptr)
    {
        m_data[sKey]=cb->currentText().trimmed();
    }
    if(txt!=nullptr)
    {
        m_data[sKey] = txt->text().trimmed();
    }
    if(sp!=nullptr)
    {
        m_data[sKey] = sp->value();
    }

    return m_data;
}


