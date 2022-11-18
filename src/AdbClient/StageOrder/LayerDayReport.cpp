#include "LayerDayReport.h"
#include "ui_LayerDayReport.h"

LayerDayReport::LayerDayReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayReport)
{
    ui->setupUi(this);

    ui->tb->setMouseTracking(true);

    m_detialOrder = new LayerSayCost;
    m_detialOrder->m_bOrderMode = true;
    m_detialOrder->setReadOnly();
    m_detialOrder->hide();



    ui->tb->hideColumn(12);
    //    ui->tb->setColumnWidth(1,120);
    //    ui->tb->setColumnWidth(3,100);
    ui->tb->setColumnWidth(4,100);
    ui->tb->setColumnWidth(5,80);
    ui->tb->setColumnWidth(6,100);
    ui->tb->setColumnWidth(7,80);
    //     ui->tb->setColumnWidth(8,60);
    //    ui->tb->setColumnWidth(9,80);
    //    ui->tb->setColumnWidth(11,100);
    //   ui->tb->setColumnWidth(7,80);
}

LayerDayReport::~LayerDayReport()
{
    if(m_detialOrder!=nullptr)
    {
        m_detialOrder->hide();
        delete m_detialOrder;
    }

    delete ui;
}

void LayerDayReport::showEvent(QShowEvent *)
{
    m_bLockDate = true;
    ui->dateEdit->setDate(GLOBAL.dateTimeUtc8().date());
    m_bLockDate = false;


    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(delayRefresh()));
}

void LayerDayReport::refreshTb()
{

    m_listOrder = ACTION.getOrder(true);

    ui->tb->setRowCount(0);
    QString sError;

    m_listInto.clear();

    for(int i=0;i<m_listOrder.length();i++)
    {
        OrderData data = m_listOrder.at(i);
        if(checkFilter(data))
        {
            QVariantMap d;
            d["Sid"] = data.CustomerSid;
            QVariantList listCustomer;
            ACTION.action(ACT::QUERY_CUSTOMER,d,listCustomer,sError);
            if(listCustomer.length()<1)
                continue;

            int iRow = ui->tb->rowCount();
            ui->tb->setRowCount(iRow+1);

            ui->tb->setItem(iRow,0,UI.tbItem(data.Id));
            UserData owner =ACTION.getUser(data.Owner);



            CustomerData customer(listCustomer.first().toMap());
            QString sDate=data.OrderDate+data.OrderTime;
            ui->tb->setItem(iRow,1,UI.tbItem(data.Name));
            QDateTime date=QDateTime::fromString(sDate,"yyyyMMddhhmmss");
            ui->tb->setItem(iRow,2,UI.tbItem(date));


            QString sUser="";

            if(data.User.length()>2)
            {
                UserData user = ACTION.getUser(data.User.at(2));

                sUser = user.Name;
            }


            ui->tb->setItem(iRow,3,UI.tbItem(sUser,GlobalUi::_TOOLTIP));
            ui->tb->setItem(iRow,4,UI.tbItem(customer.Id));
            ui->tb->setItem(iRow,5,UI.tbItem("詳細",GlobalUi::_BUTTON));


            QString sStatus = data.Step;

            if(sStatus=="0")
            {
                sStatus+="報價";
            }
            if(sStatus=="1")
            {
                sStatus+="下單";
            }
            if(sStatus=="2")
            {
                sStatus+="待處理";
            }
            if(sStatus=="3")
            {
                sStatus+="待回報";
            }
            if(sStatus=="4")
            {
                sStatus+="主管確認";
            }
            if(sStatus=="5")
            {
                sStatus="訂單結束";
            }

            qDebug()<<"check status";

            ui->tb->setItem(iRow,6,UI.tbItem(sStatus));
            ui->tb->setItem(iRow,7,UI.tbItem(data.Bouns));


            if(data.Step=="4")
            {
                ui->tb->setItem(iRow,8,UI.tbItem("點擊確認",GlobalUi::_BUTTON));
            }
            else if(data.Step=="5")
            {
                ui->tb->setItem(iRow,8,UI.tbItem("完成訂單"));
            }
            else
            {
                ui->tb->setItem(iRow,8,UI.tbItem("流程未到"));
            }

            ui->tb->setItem(iRow,9,UI.tbItem(customer.Currency));
            ui->tb->setItem(iRow,10,UI.tbItem(data.Cost));

            int iNtdCost = data.Money.first().toInt();

            int iNtdPrime = data.Money[1].toInt();

            ui->tb->setItem(iRow,11,UI.tbItem(""));
            ui->tb->setItem(iRow,13,UI.tbItem(""));
            ui->tb->setItem(iRow,14,UI.tbItem(""));

            if(data.Step.toInt()>=1)
            {

                ui->tb->setItem(iRow,11,UI.tbItem(iNtdCost));

            }

            if(data.Step.toInt()>=3)
            {
                ui->tb->setItem(iRow,13,UI.tbItem(iNtdPrime));
                ui->tb->setItem(iRow,14,UI.tbItem(iNtdCost-iNtdPrime));
            }

              m_listInto.append(data);

            /*
                QList<DataFactory> fac=ACTION.getFactoryClass("",true);
                DataFactory target;
                for(int i=0;i<fac.length();i++)
                {
                    if(fac.at(i).Name==data.Owner)
                    {
                        qDebug()<<data.Owner;
                        target = fac.at(i);
                    }
                }

                //target.Cost


                DataRate rate=ACTION.primeRate("",true);

                qDebug()<<" rate listKey "<<rate.listKey()<<" ,target currentcy : "<<target.Currency;
                double r = 1;

                int iIdx =qBound(0,rate.listKey().indexOf(target.Currency),rate.listKey().length()-1);
                qDebug()<<"tar currency : "<<target.Currency<<" idx "<<iIdx;
                r = rate.listData.at(iIdx).second.toDouble();

                double primeCost = data.Bouns.toDouble()*target.Cost.toDouble()*r;

                ui->tb->setItem(iRow,12,UI.tbItem(primeCost));

                ui->tb->setItem(iRow,13,UI.tbItem(data.Cost.toDouble()-primeCost));

            */


        }

    }



}

bool LayerDayReport::checkFilter(OrderData order)
{
    QString step = order.Step;
    QString sDate = order.OrderDate;

    if(ui->dateEdit->date().toString("yyyyMMdd") != sDate)
        return false;

    if(step=="0" && !ui->cbStep0->isChecked())
        return false;
    if(step=="1" && !ui->cbStep1->isChecked())
        return false;
    if(step=="2" && !ui->cbStep2->isChecked())
        return false;
    if(step=="3" && !ui->cbStep3->isChecked())
        return false;
    if(step=="4" && !ui->cbStep4->isChecked())
        return false;
    if(step=="5" && !ui->cbStep5->isChecked())
        return false;


    return true;
}

void LayerDayReport::on_tb_cellPressed(int row, int column)
{
    if(row<0 || row>=m_listInto.length())
        return;
    OrderData data = m_listInto.at(row);

    if(column==5)
    {

        QVariantMap d;

        d["Sid"] = data.CustomerSid;


        m_detialOrder->setCustomer(d,data.Sid);

        //  m_detialOrder->refreshInfo();
        m_detialOrder->raise();

        m_detialOrder->show();

    }

    if(column==8 && data.Step=="4" )
    {

        int iRet= UI.showMsg("",QString("請再確認 ( %1 ) \n完成訂單嗎？").arg(data.Id),QStringList()<<"否"<<"是");

        if(iRet==1)
        {

            QString sError;

            data.PaddingUser="";

            data.User[5] = ACTION.m_currentUser.Sid;

            data.Step="5";

            data.StepTime[5]=GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

            QStringList listMoney;

            listMoney.append(ui->tb->item(row,11)->text());

            listMoney.append(ui->tb->item(row,13)->text());

            listMoney.append(ui->tb->item(row,14)->text());

            data.Money = listMoney;


            bool bOk =ACTION.replaceOrder(data,sError);

            if(bOk && data.User.length()>2)
            {
                UserData user = ACTION.getUser(data.User.at(2));

                QVariantMap in;
                QVariantList out;

                double dTotalBonus=0.0;

                in["UserSid"] = user.Sid;

                ACTION.action(ACT::QUERY_BOUNS,in,out,sError);

                if(out.length()>0)
                {
                    dTotalBonus = out.first().toMap()["Bonus"].toDouble();
                    in["Pay"] = out.first().toMap()["Pay"];
                }


                in["Bonus"] = dTotalBonus+data.Bouns;

                in["AddBonus"] = data.Bouns;

                in["OrderSid"] = data.Sid;

                ACTION.action(ACT::ADD_BOUNS,in,sError);

                ACTION.orderUpdateCount(data.Sid,user.Sid,data.Item);

            }


            UI.showMsg("",sError,"OK");

            refreshTb();


        }
    }
}


void LayerDayReport::on_cbStep0_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep1_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep2_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep3_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep4_clicked()
{
    refreshTb();
}


void LayerDayReport::on_cbStep5_clicked()
{
    refreshTb();
}


void LayerDayReport::on_tb_cellClicked(int , int )
{

}

void LayerDayReport::delayRefresh()
{
    ui->tb->hideColumn(8);
    ui->tb->hideColumn(10);
    ui->tb->hideColumn(11);
    ui->tb->hideColumn(12);
    ui->tb->hideColumn(13);
    ui->tb->hideColumn(14);

    qDebug()<<"lv : "<<ACTION.m_currentUser.Lv;

    if(ACTION.m_currentUser.Lv>=USER_LV::_LV3)
    {
        ui->tb->showColumn(8);
    }

    if(ACTION.m_currentUser.Lv>=USER_LV::_LV4)
    {
        ui->tb->showColumn(10);
        ui->tb->showColumn(11);
        //   ui->tb->showColumn(12);
        ui->tb->showColumn(13);
        ui->tb->showColumn(14);
    }

    ACTION.primeRate("",true);
    refreshTb();
}





void LayerDayReport::on_dateEdit_userDateChanged(const QDate &date)
{
    if(m_bLockDate)
        return ;

    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(delayRefresh()));
}


void LayerDayReport::on_tb_cellEntered(int row, int column)
{

    qDebug()<<"AAAAAAAAAAA";

    if(row<0 || row>=m_listInto.length())
        return;
    OrderData data = m_listInto.at(row);
    if(column==3)
    {
        QString st="訂單編號:"+data.Id+"\n"
                   "報價: %1\n"
                   "下單: %2\n"
                   "處理: %3\n"
                   "回報: %4\n"
                   "簽核: %5\n";


        QStringList listName;

        foreach(QString sUserSid,data.User)
        {
            listName.append(ACTION.getUser(sUserSid).Name);
        }

        while(listName.length()<6)
        {
            listName.append(" ");
        }



        UI.toolTip(st.arg(listName.at(0),listName.at(1),listName.at(2),listName.at(4),listName.at(5)));


    }
    else
    {
         // QToolTip::hideText();
    }
}

