#include "LayerCostReport.h"
#include "ui_LayerCostReport.h"

LayerCostReport::LayerCostReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostReport)
{
    ui->setupUi(this);

    ui->dateEdit->setDateTime(GLOBAL.dateTimeUtc8());
}

LayerCostReport::~LayerCostReport()
{
    delete ui;
}

void LayerCostReport::init()
{

}

void LayerCostReport::refresh(bool bRequest)
{
    if(bRequest)
    {
        QVariantMap in;

        m_listOrigin.clear();

        QString sError;

        in["OrderTime >="]=ui->dateEdit->dateTime().toString("yyyyMMdd")+"000000";
        in["OrderTime <"]=ui->dateEdit->dateTime().addDays(1).toString("yyyyMMdd")+"000000";
        in["ASC"]="OrderTime";

        bool bStrong = ui->dateEdit->date()==QDateTime::currentDateTime().date()
                || ui->dateEdit->date()==QDateTime::currentDateTime().date().addDays(-1) ;

        ACTION.action(ACT::QUERY_CUSTOMER_COST,in,m_listOrigin,sError,bStrong);

    }





    ui->tb->setRowCount(0);
    m_listDisplay.clear();
    reMix();

    for(int i=0;i<m_listMix.length();i++)
    {
        int iRow = ui->tb->rowCount();

        CustomerCost costData(m_listMix.at(i).toMap());

        CustomerData cus=ACTION.getCustomer(costData.CustomerSid,false);

        if(!checkFilter(cus,costData))
            continue;

        m_listDisplay.append(m_listMix.at(i));
        ui->tb->setRowCount(iRow+1);



        ui->tb->setItem(iRow, _Sid,UI.tbItem(costData.Sid));
        ui->tb->setItem(iRow, _OrderId,UI.tbItem(costData.OrderId));
        ui->tb->setItem(iRow, _CusId,UI.tbItem(cus.Id));
        ui->tb->setItem(iRow, _CusName,UI.tbItem(cus.Name));
        ui->tb->setItem(iRow, _Currency,UI.tbItem(cus.Currency));
        ui->tb->setItem(iRow, _Cost,UI.tbItem(costData.Total,UI._BUTTON));
        ui->tb->setItem(iRow, _User,UI.tbItem(costData.UserSid));
        ui->tb->setItem(iRow, _Note1,UI.tbItem(costData.Note1));

    }
}

void LayerCostReport::on_btnChangeDate_clicked()
{

    refresh(true);
}

bool LayerCostReport::checkFilter(CustomerData cus, CustomerCost cos)
{

    if(!ui->chAddCost->isChecked())
    {
        if(cos.IsAddCost)
            return false;

    }

    if(!ui->chOrder->isChecked())
    {
        if(!cos.IsAddCost)
            return false;

    }



    QString searchKey = ui->txSearch->text();

    //if(cus.Id)



    if(searchKey.trimmed()=="")
        return true;

    QStringList listKey = searchKey.split("&");


    bool bRe = false;

    QList<int> listOk;

    foreach(QString v, listKey)
    {
        int iOk = 0;
        QString dateTime=QDateTime::fromString(cus.UpdateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd hh:mm:ss");

        QString Vip="一般";
        if(cus.Vip=="1")
            Vip="VIP";

        QString sGroup=ACTION.getCustomerClass(cus.Class).Name;

        QString sKey = v.toUpper().trimmed();
        //  if(data["Name"].toString().indexOf(m_sSearchKey,Qt::CaseInsensitive)>=0)
        //奇怪，Qt::CaseInsensitive 不起作用
        if(cus.Name.toUpper().contains(sKey))
            iOk = 1;
        else if(cus.Id.toUpper().contains(sKey))
            iOk =1;
        else if(cus.Currency.toUpper().contains(sKey))
            iOk =1;
        else if(cus.PayInfo.toUpper().contains(sKey))
            iOk =1;
        else if(dateTime.toUpper().contains(sKey))
            iOk =1;
        else if(Vip.toUpper().contains(sKey))
            iOk =1;
        else if(sGroup.toUpper().contains(sKey))
            iOk = 1;

        listOk.append(iOk);
    }

    bRe = !listOk.contains(0);

    return bRe;



}

void LayerCostReport::reMix()
{
    if(ui->chMix->isChecked())
    {
        m_listMix = m_listOrigin;

        return ;

    }



    QStringList listSortUser;  //需要順序

    QVariantMap dUser;

    for(int i=0;i<m_listOrigin.length();i++)
    {
        CustomerCost costData(m_listOrigin.at(i).toMap());


        if(dUser.keys().contains(costData.CustomerSid))
        {
            listSortUser.removeOne(costData.CustomerSid);
        }

        dUser[costData.CustomerSid] = costData.data();
        listSortUser.append(costData.CustomerSid);



    }

    m_listMix.clear();

    for(int i=0;i<listSortUser.length();i++)
    {

        m_listMix.append(dUser[listSortUser.at(i)].toMap());


    }



}


void LayerCostReport::on_chOrder_clicked()
{
    refresh();
}


void LayerCostReport::on_chAddCost_clicked()
{
    refresh();
}


void LayerCostReport::on_chMix_clicked()
{
    refresh();
}


void LayerCostReport::on_tb_cellClicked(int row, int column)
{
    if(row<0 || row>=m_listDisplay.length())
        return;

    CustomerCost cos (m_listDisplay.at(row).toMap());

    CustomerData cus=ACTION.getCustomer(cos.CustomerSid,false);

    if(column==_CusId)
    {
        DialogCustomerEdit dialog;


        dialog.setData(cus.Sid);

        dialog.setReadOnly(true);

        dialog.exec();
    }
    else if(column==_Cost)
    {
        DialogCustomerCostHistory dialog;

        dialog.setCustomer(cus);

        dialog.exec();

    }
}


void LayerCostReport::on_btnFilter_clicked()
{
    refresh();
}


void LayerCostReport::on_btnFilterClear_clicked()
{
    ui->txSearch->clear();

    refresh();
}

