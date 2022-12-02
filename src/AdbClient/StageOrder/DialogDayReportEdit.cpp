#include "DialogDayReportEdit.h"
#include "ui_DialogDayReportEdit.h"

DialogDayReportEdit::DialogDayReportEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDayReportEdit)
{
    ui->setupUi(this);

    connect(ui->btnCancel,&QPushButton::clicked,[=](){ reject(); });


    connect(ui->btnOk,&QPushButton::clicked,[=](){ done(1);});

    ui->tb->setColumnWidth(0,240);

    ui->tb->setColumnWidth(1,90);

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(refresh()));
}

DialogDayReportEdit::~DialogDayReportEdit()
{
    delete ui;
}

void DialogDayReportEdit::setData(OrderData data)
{
    m_data =data;

    m_listPayTypeSid=m_data.CanSelectPayType.split(";;");

    QStringList listCb;
    foreach(QString st ,m_listPayTypeSid)
        listCb.append(ACTION.getAddValueName(st));

    ui->comboBox->clear();

    ui->comboBox->addItems(listCb);

    int iIdx=qBound(0, m_listPayTypeSid.indexOf(m_data.PayType),m_listPayTypeSid.length()-1);

    ui->comboBox->setCurrentIndex(iIdx);

    refresh();
}

QString DialogDayReportEdit::data()
{
    return m_listPayTypeSid.at(ui->comboBox->currentIndex());
}

void DialogDayReportEdit::refresh()
{
    ui->lbOrder->setText(m_data.Id);

    ui->lbGame->setText(ACTION.getGameName(m_data.GameSid));



    ui->lbPayType->setText(ui->comboBox->currentText());
    //


    int cbIdx=qBound(0, ui->comboBox->currentIndex(),m_listPayTypeSid.length()-1);

    QString sPaySid = m_listPayTypeSid.at(cbIdx);

    auto getPayCount =[=](DataGameItem item,QString paySid)
    {
        QString re="0";

        QStringList list =item.AddValueTypeSid.split(";;");

        foreach(QString st, list)
        {
            QStringList tmp = st.split(",,");
            if(paySid==tmp.first())
            {
                re = tmp.last();
            }

        }

        return re;
    };


    QStringList listGameItem=m_data.Item.split(";;");

    ui->tb->setRowCount(0);

    for(int i=0;i<listGameItem.length();i++)
    {
        int iRow = ui->tb->rowCount();

        ui->tb->setRowCount(iRow+1);


        QString sGameItemSid = listGameItem.at(i).split(",,").first();

        QString sGameItemCount = listGameItem.at(i).split(",,").last();

        DataGameItem gameItem=ACTION.getGameItemFromSid(sGameItemSid,true);

        ui->tb->setItem(iRow,0, UI.tbItem(gameItem.Name));

        ui->tb->setItem(iRow,1, UI.tbItem(sGameItemCount));

        QString sPayCount=getPayCount(gameItem,sPaySid);

        ui->tb->setItem(iRow,2, UI.tbItem(sPayCount));


    }

}
