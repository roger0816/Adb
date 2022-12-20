#include "LayerDayReport.h"
#include "ui_LayerDayReport.h"

LayerDayReport::LayerDayReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayReport)
{
    ui->setupUi(this);

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

    m_dialogPic->setWindowFlags(m_dialogPic->windowFlags()  &  ~Qt::WindowContextHelpButtonHint);
    QGridLayout *lay = new QGridLayout(m_itemPic);
    lay->addWidget(m_itemPic);
    m_dialogPic->setLayout(lay);

    ui->tb->setMouseTracking(true);

    m_detialOrder = new LayerSayCost;
    m_detialOrder->m_bOrderMode = true;
    m_detialOrder->setReadOnly();
    m_detialOrder->hide();



    ui->tb->hideColumn(12);
    //    ui->tb->setColumnWidth(1,120);
    //    ui->tb->setColumnWidth(3,100);
    ui->tb->setColumnWidth(4,100);

    ui->tb->setColumnWidth(5,100);
    ui->tb->setColumnWidth(6,80);
    ui->tb->setColumnWidth(17,60);

    ui->tb->setColumnWidth(18,60);

    ui->tb->hideColumn(17);

    ui->btnExcel->hide();
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

    m_listOrder = ACTION.getOrderByDate(ui->dateEdit->date());

    ui->tb->setRowCount(0);
    QString sError;

    m_listInto.clear();

    int iTotal0=0;


    int iTotal1=0;


    int iTotal2=0;

    double iTotalBonus=0.0;

    for(int i=0;i<m_listOrder.length();i++)
    {
        OrderData data = m_listOrder.at(i);
        if(!checkFilter(data))
            continue;

        QVariantMap d;
        d["Sid"] = data.CustomerSid;
        QVariantList listCustomer;
        ACTION.action(ACT::QUERY_CUSTOMER,d,listCustomer,sError);
        if(listCustomer.length()<1)
            continue;

        int iRow = ui->tb->rowCount();
        ui->tb->setRowCount(iRow+1);

        ui->tb->setItem(iRow,0,UI.tbItem(data.Id,GlobalUi::_BUTTON));
        UserData owner =ACTION.getUser(data.Owner);



        CustomerData customer(listCustomer.first().toMap());
        QString sDate=data.OrderDate+data.OrderTime;
        ui->tb->setItem(iRow,1,UI.tbItem(data.Name,GlobalUi::_BUTTON));
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
        // ui->tb->setItem(iRow,5,UI.tbItem("詳細",GlobalUi::_BUTTON));


        QString sStatus = data.Step;

        if(sStatus=="-1")
        {
            sStatus+="取消訂單";
        }

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

        ui->tb->setItem(iRow,5,UI.tbItem(sStatus));
        ui->tb->setItem(iRow,6,UI.tbItem(data.Bouns));


        if(data.Step=="4")
        {
            ui->tb->setItem(iRow,7,UI.tbItem("點擊確認",GlobalUi::_BUTTON));
        }
        else if(data.Step=="5")
        {
            ui->tb->setItem(iRow,7,UI.tbItem("完成訂單"));
        }
        else
        {
            ui->tb->setItem(iRow,7,UI.tbItem("流程未到"));
        }

        ui->tb->setItem(iRow,8,UI.tbItem(customer.Currency));
        ui->tb->setItem(iRow,9,UI.tbItem(data.Cost));


        ui->tb->setItem(iRow,10,UI.tbItem(""));
        ui->tb->setItem(iRow,11,UI.tbItem(""));
        ui->tb->setItem(iRow,12,UI.tbItem(""));
        ui->tb->setItem(iRow,13,UI.tbItem(""));

        _LayerDayReport::OrderPayType orderPayType = getPayCount(data);


        DataRate rate=ACTION.primeRate(data.PrimeRateSid,true);
        double payRate = ACTION.payTypeToNTDRate(data.PayType,rate);


        int iNtdCost = data.Money.first().toInt();

        int iNtdPrime = data.Money[1].toInt();

        if(data.Step.toInt()>=0)
        {
            ui->tb->setItem(iRow,14,UI.tbItem(orderPayType.sPayName,true));


            ui->tb->setItem(iRow,15,UI.tbItem(orderPayType.iTotalCount));

            ui->tb->setItem(iRow,16,UI.tbItem(payRate));
        }

        if(data.Step.toInt()>=1)
        {
            if(iNtdCost==0 && data.Cost!="0")
            {
                ACTION.setSellMoney(data);

                iNtdCost=data.Money.first().toInt();
            }

            ui->tb->setItem(iRow,10,UI.tbItem(iNtdCost));

        }

        if(data.Step.toInt()>=3)
        {
            if(iNtdPrime<=0)
            {
                ACTION.setPrimeMoney(data);

                iNtdPrime=data.Money[1].toInt();
            }

            ui->tb->setItem(iRow,11,UI.tbItem(iNtdPrime));
            ui->tb->setItem(iRow,12,UI.tbItem(iNtdCost-iNtdPrime));
            double dTmp = 0.00;
            dTmp = (double)(iNtdCost-iNtdPrime) / data.Bouns.toDouble();
            ui->tb->setItem(iRow,13,UI.tbItem(dTmp));

            if(data.Pic0.length()>0)
                ui->tb->setItem(iRow,17,UI.tbItem("圖",1));
            if(data.Pic1.length()>0)
                ui->tb->setItem(iRow,18,UI.tbItem("圖",1));
        }

        m_listInto.append(data);

        if(data.Step.toInt()==5)
        {
            iTotal0 +=iNtdCost;
            iTotal1 +=iNtdPrime;

            int iTmp = iNtdCost-iNtdPrime;
            iTotal2 +=iTmp;

            iTotalBonus+=data.Bouns.toDouble();
        }




    }



    ui->lbTotal0->setText(QString::number(iTotal0));
    ui->lbTotal1->setText(QString::number(iTotal1));
    ui->lbTotal2->setText(QString::number(iTotal2));
    ui->lbTotalBonus->setText(QString::number(iTotalBonus));


}

bool LayerDayReport::checkFilter(OrderData order)
{
    QString step = order.Step;
    QString sDate = order.OrderDate;

    if(ui->dateEdit->date().toString("yyyyMMdd") != sDate)
        return false;

    if(step=="-1" && !ui->cbStep0_1->isChecked())
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


    if(column==0 || column==1)
    {

        QVariantMap d;

        d["Sid"] = data.CustomerSid;


        m_detialOrder->setCustomer(d,data.Sid);

        //   m_detialOrder->refreshInfo();
        m_detialOrder->raise();

        m_detialOrder->show();

    }

    if(column==7 && data.Step=="4" )
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

            listMoney.append(ui->tb->item(row,12)->text());

            listMoney.append(ui->tb->item(row,13)->text());

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

    if(column==14 && data.Step.toInt()>=4 )
    {
        DialogDayReportEdit dialog;

        dialog.setData(data);


        int iRet = dialog.exec();

        if(iRet==1)
        {
            //擔心order的狀態已被其它人改變，重取一次
            QVariantMap in,out;
            QString sError;
            in["Sid"]=data.Sid;
            ACTION.action(ACT::QUERY_ORDER,in,out,sError);

            OrderData order(out);
            order.PayType = dialog.data();

            ACTION.setPrimeMoney(order);

            ACTION.setSellMoney(order);

            bool bOk =ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);

            if(bOk)
                sError="修改儲值方式完成";

            DMSG.showMsg("",sError,"OK");
            refreshTb();

        }

    }

    if(column==17 || column==18 )
    {


        QString sText=data.Id;
        QString sKey="Md5";

        QVariant sValue = data.Pic0;

        if(column==18)
            sValue = data.Pic1;

        if(sValue.toString().length()<1)
            return;

        QVariantMap out;
        ACTION.action(ACT::QUERY_PIC,sKey,sValue,out);
        m_dialogPic->resize(480,360);

        m_itemPic->setFileName(
                    ui->tb->item(row,0)->text()+"_"+
                    ui->tb->item(row,1)->text()+"_"+
                    sText);

        m_itemPic->setData(out["Data"].toByteArray());

        m_dialogPic->setWindowTitle("編號 : "+
                                    ui->tb->item(row,0)->text());
        //+"          "+sText);

        QTimer::singleShot(50,this,[=](){ m_dialogPic->exec();});

    }
}

void LayerDayReport::on_cbStep0_1_clicked()
{
    refreshTb();
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




void LayerDayReport::delayRefresh()
{
    ui->tb->hideColumn(7);
    ui->tb->hideColumn(9);
    ui->tb->hideColumn(10);
    ui->tb->hideColumn(11);
    ui->tb->hideColumn(12);

    ui->tb->hideColumn(13);
    ui->tb->hideColumn(14);
    ui->tb->hideColumn(15);
    ui->tb->hideColumn(16);

    ui->wTotal->hide();

    ui->btnExcel->hide();

    qDebug()<<"lv : "<<ACTION.m_currentUser.Lv;

    if(ACTION.m_currentUser.Lv>=USER_LV::_LV3)
    {
        ui->tb->showColumn(7);
    }

    if(ACTION.m_currentUser.Lv>=USER_LV::_LV4)
    {
        ui->tb->showColumn(9);
        ui->tb->showColumn(10);
        ui->tb->showColumn(11);
        ui->tb->showColumn(12);
        ui->tb->showColumn(13);
        ui->tb->showColumn(14);
        ui->tb->showColumn(15);
        ui->tb->showColumn(16);
        ui->wTotal->show();

        ui->btnExcel->show();

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


_LayerDayReport::OrderPayType LayerDayReport::getPayCount(OrderData data)
{
    _LayerDayReport::OrderPayType re;


    QString sPaySid = data.PayType;

    re.sPayName = ACTION.getAddValueName(sPaySid);


    re.sPaySid = sPaySid;

    QStringList listItem = data.Item.split(";;");

    for(int i=0;i<listItem.length();i++)
    {
        QString itemSid = listItem.at(i).split(",,").first();

        int itemCount = listItem.at(i).split(",,").last().toInt();

        double iOnePayCount =ACTION.getGameItemPayCount(itemSid,sPaySid);


        double count = itemCount*iOnePayCount;

        re.m_iListCount.append(count);

        re.iTotalCount+=count;
    }


    return re;
}


void LayerDayReport::on_btnExcel_clicked()
{
    if(ui->tb->rowCount()<1)
    {
        DMSG.showMsg("","沒有資料","OK");

        return ;
    }
    QString sPath = QFileDialog::getExistingDirectory(this,"選擇存檔位置",".");

    if(sPath.trimmed()=="")
        return ;


    QString sFileName = sPath+"/"+"DayReport_"+ui->dateEdit->date().toString("yyyy_MMdd");
    qDebug()<<"sFileName : "<<sFileName;
    QTXLSX_USE_NAMESPACE

            Document xlsx;

    //  xlsx.addSheet();

    for(int iRow=0;iRow<ui->tb->rowCount();iRow++)
    {
        int iXlsxCol =0;
        for(int iCol=0;iCol<ui->tb->columnCount();iCol++)
        {
            if(iCol==17 || iCol==18)
                continue;
            iXlsxCol++;

            if(iRow==0)
            {
                QString sHeader= ui->tb->horizontalHeaderItem(iCol)->text();
                xlsx.write(iRow+1,iXlsxCol,sHeader);
            }


            QString st = ui->tb->item(iRow,iCol)->text();
            if(st.trimmed()!="")
            {
                if(iCol==6 || iCol==9 ||iCol==10 || iCol==11 || iCol==12 || iCol==13)
                    xlsx.write(iRow+2,iXlsxCol,st.toDouble());
                else
                    xlsx.write(iRow+2,iXlsxCol,st);
            }
            xlsx.setColumnWidth(iXlsxCol,iXlsxCol,16);
        }
    }

    xlsx.write("A"+QString::number(ui->tb->rowCount()+3),ui->lbT->text());
    xlsx.write("G"+QString::number(ui->tb->rowCount()+3),ui->lbTotalBonus->text().toDouble());
    xlsx.write("K"+QString::number(ui->tb->rowCount()+3),ui->lbTotal0->text().toDouble());
    xlsx.write("L"+QString::number(ui->tb->rowCount()+3),ui->lbTotal1->text().toDouble());
    xlsx.write("M"+QString::number(ui->tb->rowCount()+3),ui->lbTotal2->text().toDouble());

    xlsx.saveAs(sFileName+".xls");

    DMSG.showMsg("",sFileName.split("/").last()+"\n\n匯出完成","OK");
    /*
    CObjectExcel excel;

    excel.open(sFileName+"_2.xls");

    for(int iRow=0;iRow<ui->tb->rowCount();iRow++)
    {
        for(int iCol=0;iCol<ui->tb->columnCount();iCol++)
            excel.setCell(iRow,iCol,ui->tb->item(iRow,iCol)->text());
    }

    excel.save();

    excel.close();
    */



}

