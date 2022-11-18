#include "LayerDayDebit.h"
#include "ui_LayerDayDebit.h"

LayerDayDebit::LayerDayDebit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayDebit)
{
    ui->setupUi(this);
}

LayerDayDebit::~LayerDayDebit()
{
    delete ui;
}

void LayerDayDebit::showEvent(QShowEvent *)
{
    QTimer::singleShot(100,this,SLOT(refresh()));
}


void LayerDayDebit::refresh()
{


    ui->dateEdit->setDate(QDateTime::currentDateTime().date());


    ACTION.action(ACT::QUERY_DEBIT_CLASS,QVariantMap(),m_listDebit);

    QStringList list = GLOBAL.listMapToList(m_listDebit,"Name");

    //  ui->cbDebit->setProperty("lock",true);
    ui->cbDebit->clear();

    if(list.length()>0)
        ui->cbDebit->addItems(list);

    // ui->cbDebit->setProperty("lock",false);


    //  refreshTb();
}

void LayerDayDebit::refreshTb()
{

    QVariantMap in;
    in["UpdateTime like"]="%"+ui->dateEdit->date().toString("yyyyMMdd")+"%";
    in["IsAddCost"]="1";

    ACTION.action(ACT::QUERY_CUSTOMER_COST,in,m_listCustomerCost);

    double iTotal=0.00;

    ui->tb->setRowCount(0);


    for(int i=0;i<m_listCustomerCost.length();i++)
    {
        int iRow = ui->tb->rowCount();

        CustomerCost data(m_listCustomerCost.at(i).toMap());

        if(!checkData(data))
            continue;

        ui->tb->setRowCount(iRow+1);
        ui->tb->setItem(iRow,0,UI.tbItem(data.OrderId));

        CustomerData customer =ACTION.getCustomer(data.CustomerSid);

        ui->tb->setItem(iRow,1,UI.tbItem(customer.Id));

        ui->tb->setItem(iRow,2,UI.tbItem(customer.Name));
        ui->tb->setItem(iRow,3,UI.tbItem(customer.Currency));

        ui->tb->setItem(iRow,4,UI.tbItem(data.ChangeValue));
        ui->tb->setItem(iRow,5,UI.tbItem(data.DebitNote));
        ui->tb->setItem(iRow,6,UI.tbItem(data.OriginValue));
        ui->tb->setItem(iRow,7,UI.tbItem(QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss")));
        ui->tb->setItem(iRow,8,UI.tbItem(ACTION.getUser(data.UserSid).Name));
        ui->tb->setItem(iRow,9,UI.tbItem(data.Note0));
        iTotal+=data.OriginValue.toDouble();


    }

    ui->lbTotal->setText(QString::number(iTotal));

}

bool LayerDayDebit::checkData(CustomerCost data)
{

    if(data.Sid=="")
        return false;

    if(ui->cbDebit->count()<1 || ui->cbDebit->currentIndex()<0)
        return false;

    bool bRe = false;

    QDateTime date =QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss");

    if(date.time()<ui->timeStart->time() || date.time()>ui->timeEnd->time())
    {
        return false;
    }

    int iIdx = qBound(0,ui->cbDebit->currentIndex(),m_listDebit.length()-1);

    QString sCurrentDebitSid =  DebitClass(m_listDebit.at(iIdx).toMap()).Sid;

    bRe = data.DebitSid==sCurrentDebitSid;

    return bRe;
}


void LayerDayDebit::on_cbDebit_currentIndexChanged(int index)
{
    if(index<0 || ui->cbDebit->property("lock").toBool())
        return;

    int iIdx = qBound(0,ui->cbDebit->currentIndex(),m_listDebit.length()-1);

    QString sCurrency =  DebitClass(m_listDebit.at(iIdx).toMap()).Currency;

    ui->lbCurrency->setText(sCurrency);

    refreshTb();
}


void LayerDayDebit::on_dateEdit_userDateChanged(const QDate &date)
{
    refreshTb();
}


void LayerDayDebit::on_timeStart_userTimeChanged(const QTime &time)
{
    refreshTb();
}


void LayerDayDebit::on_timeEnd_userTimeChanged(const QTime &time)
{
    refreshTb();
}

