#include "DialogCustomerCostHistory.h"
#include "ui_DialogCustomerCostHistory.h"

DialogCustomerCostHistory::DialogCustomerCostHistory(QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::DialogCustomerCostHistory)
{
    ui->setupUi(this);

    setWindowTitle(" ");

    setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

    m_btns.addButton(ui->btn0,0);


    m_btns.addButton(ui->btn1,1);


    m_btns.addButton(ui->btn2,2);

    m_btns.connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(refresh(int)));

    m_itemPic->setReadOnly(true);

    m_itemPic->setEnableDetailMode(false);

    connect(m_itemPic,&ItemPic::finishedSaveImage,this,[=](QString sName,bool b)
    {
        if(b)
        {
            DMSG.showMsg("","圖片下載完成\n"+sName.split("/").last(),QStringList()<<"OK");
            m_dialogPic->done(1);
        }
        else
            DMSG.showMsg("","圖片下載失敗\n"+sName.split("/").last(),QStringList()<<"OK");
    });

    m_wMaskClick=new QWidget(ui->wBg);

    m_wMaskClick->resize(400,300);
    m_wMaskClick->setStyleSheet("background-color: rgba(81, 81, 81, 150);");
    m_wMaskClick->hide();
    //connect(m_itemPic,&ItemPic::sendLock,this,[=](bool b)
    //{
    //    m_wMaskClick->setVisible(b);
    //});

    m_dialogPic->setWindowFlags(m_dialogPic->windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

    QGridLayout *lay = new QGridLayout(m_itemPic);
    lay->addWidget(m_itemPic);
    m_dialogPic->setLayout(lay);

    ui->tableWidget->hideColumn(3);



}

DialogCustomerCostHistory::~DialogCustomerCostHistory()
{
    delete m_dialogPic;
    delete ui;
}

void DialogCustomerCostHistory::showEvent(QShowEvent *)
{
    // QTimer::singleShot(50,this,[=](){refresh();});
}

void DialogCustomerCostHistory::setCustomer(CustomerData data)
{
    m_cus = data;

    ui->lbId->setText(m_cus.Id);

    QString sTmp  = DATA.getCustomerClass(m_cus.Class).Name;

    ui->lbClass->setText(sTmp);
    ui->lbName->setText(m_cus.Name);
    ui->lbCurrency->setText(m_cus.Currency);
    ui->lbMoney->setText(ACTION.getCustomerNowMoney(m_cus.Sid));
    // ui->lbMoney->setText(m_cus.Money);

    refresh();

}

void DialogCustomerCostHistory::refresh(int)
{

    QVariantMap in;

    in["CustomerSid"]=m_cus.Sid;

    QVariantList out;

    QString sError;


    ACTION.action(ACT::QUERY_CUSTOMER_COST,in,out,sError,true);

    m_listAddCost = out;


    ACTION.action(ACT::QUERY_ORDER,in,out,sError,true);

    m_listOrder = out;

    mergeData();


    QVariantList list = filterData();

    ui->tableWidget->setRowCount(0);

    for(int i=0;i<list.length();i++)
    {

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QVariantMap v = list.at(i).toMap();


        if(v["IsAddCost"].toBool())
        {
            CustomerCost d(v);

            ui->tableWidget->setItem(i,0,UI.tbItem(d.OrderId));
            ui->tableWidget->setItem(i,1,UI.tbItem("加值"));
            ui->tableWidget->setItem(i,2,UI.tbItem(d.ChangeValue));

            QString sRate=QString::number(DATA.primeRate(d.Rate).findValue(m_cus.Currency));

            if(d.AddRate.toDouble()>0)
                sRate=sRate+"+"+d.AddRate;
            ui->tableWidget->setItem(i,3,UI.tbItem(sRate,GlobalUi::_TOOLTIP));

            ui->tableWidget->setItem(i,4,UI.tbItem("完成"));

            ui->tableWidget->setItem(i,5,UI.tbItem(QDateTime::fromString(d.OrderTime,"yyyyMMddhhmmss")));

            ui->tableWidget->setItem(i,6,UI.tbItem(DATA.getUser(d.UserSid).Name));

            QString sPic0="";
            if(d.Pic0.length()>0)
                sPic0="圖1";

            ui->tableWidget->setItem(i,7,UI.tbItem(sPic0,GlobalUi::_BUTTON));

            QString sPic1="";
            if(d.Pic1.length()>0)
                sPic1="圖2";

            ui->tableWidget->setItem(i,8,UI.tbItem(sPic1,GlobalUi::_BUTTON));

            ui->tableWidget->setItem(i,9,UI.tbItem(d.Note0));

        }
        else
        {
            OrderData d(v);

            ui->tableWidget->setItem(i,0,UI.tbItem(d.Id));
            ui->tableWidget->setItem(i,1,UI.tbItem("消費"));

            QString sCost=QString::number(d.Cost.toDouble()*-1);

            ui->tableWidget->setItem(i,2,UI.tbItem(sCost));

            QString sRate=QString::number(DATA.primeRate(d.PrimeRateSid).findValue(m_cus.Currency));

            ui->tableWidget->setItem(i,3,UI.tbItem(sRate));

            QStringList list;
            list<<"報價"<<"下單"<<"待處理"<<"待回報"<<"主管確認"<<"完成";

            QString sStep=list.at(qBound(0,d.Step.toInt(),list.length()-1));

            ui->tableWidget->setItem(i,4,UI.tbItem(sStep));
            ui->tableWidget->setItem(i,5,UI.tbItem(QDateTime::fromString(d.UpdateTime,"yyyyMMddhhmmss")));

            QString sUserSid = d.User.last();

            if(d.User.length()>=3)
                sUserSid = d.User.at(2);

            ui->tableWidget->setItem(i,6,UI.tbItem(DATA.getUser(sUserSid).Name));

            QString sPic0="";
            if(d.Pic0.length()>0)
                sPic0="圖1";

            ui->tableWidget->setItem(i,7,UI.tbItem(sPic0,GlobalUi::_BUTTON));

            QString sPic1="";
            if(d.Pic1.length()>0)
                sPic1="圖2";

            ui->tableWidget->setItem(i,8,UI.tbItem(sPic1,GlobalUi::_BUTTON));

            ui->tableWidget->setItem(i,9,UI.tbItem(d.Note0));

        }




    }



}

QVariantList DialogCustomerCostHistory::filterData()
{

    m_listDisplayData.clear();

    for(int i=0;i<m_listRowData.length();i++)
    {
        QVariantMap data = m_listRowData.at(i).toMap();

        if(m_btns.checkedId()==1)
        {
            if(!data["IsAddCost"].toBool())
                continue;
        }

        if(m_btns.checkedId()==2)
        {
            if(data["IsAddCost"].toBool())
                continue;
        }


        if(!data["IsAddCost"].toBool())
        {
            if(ui->cbShowNoPay->isChecked())
            {
                if(data["Step"].toInt()<4)
                    continue;
            }
        }

        m_listDisplayData.append(data);
    }


    return m_listDisplayData;
}

void DialogCustomerCostHistory::mergeData()
{
    //merge cost and order  for table data
    m_listRowData.clear();
    for(int i=0;i<m_listAddCost.length();i++)
    {


        CustomerCost d(m_listAddCost.at(i).toMap());

        if(!d.IsAddCost)
            continue;

        QVariantMap re;

        re=m_listAddCost.at(i).toMap();

        re["IsAddCost"] =true;

        m_listRowData.append(re);

    }


    foreach(QVariant v, m_listOrder)
    {

        OrderData d(v.toMap());

        QVariantMap re;

        re=v.toMap();

        re["IsAddCost"] =false;

        re["OrderTime"]=d.OrderDate+d.OrderTime;

        m_listRowData.append(re);


    }



    qSort(m_listRowData.begin(),m_listRowData.end(),[=](const QVariant &v1, const QVariant &v2)
    {
        return v1.toMap()["UpdateTime"].toString() > v2.toMap()["UpdateTime"].toString();
    }

    );






}

void DialogCustomerCostHistory::btnCustomerHistory()
{
    done(0);
}


void DialogCustomerCostHistory::on_tableWidget_cellClicked(int row, int column)
{
    if(row<0|| row>=m_listDisplayData.length())
        return;

    QString sText = ui->tableWidget->item(row,column)->text();

    if(sText.trimmed()=="")
        return;

    if(column==7 || column==8)
    {
        m_wMaskClick->move(0,0);
        m_wMaskClick->resize(size());
        m_wMaskClick->show();
        QVariantMap d= m_listDisplayData.at(row).toMap();

        QVariantMap out;

        QString sKey="Md5";

        QVariant sValue = d["Pic0"].toString();

        if(column==8)
            sValue = d["Pic1"].toString();


        ACTION.action(ACT::QUERY_PIC,sKey,sValue,out);
        m_dialogPic->resize(640,640);

        m_itemPic->setFileName(
                    ui->tableWidget->item(row,0)->text()+"_"+
                    ui->tableWidget->item(row,1)->text()+"_"+
                    sText);

        m_itemPic->setData(out["Data"].toByteArray());

        m_dialogPic->setWindowTitle("單號 : "+
                                    ui->tableWidget->item(row,0)->text()+"          "
                                    +sText);
        m_wMaskClick->hide();
        QTimer::singleShot(50,this,[=](){ m_dialogPic->exec(); });


    }
}




void DialogCustomerCostHistory::on_cbShowNoPay_clicked()
{
       refresh();
}

