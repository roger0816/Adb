#include "LayerDayReport.h"
#include "ui_LayerDayReport.h"

using namespace _LayerDayReport;

LayerDayReport::LayerDayReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayReport)
{
    ui->setupUi(this);

    // ui->tb->setSortingEnabled(true);

    ui->wShowArea->hide();

    ui->tb->hideColumn(_Bonus);

    ui->tb->hideColumn(_GameItem);

    ui->tb->hideColumn(_Cost);

    ui->tb->hideColumn(_Pic1);

    ui->tb->hideColumn(_Pic0);

    ui->tb->setColumnCount(_TB_COL_COUNT);

    ui->tb->hideColumn(_Sid);

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




    //    ui->tb->setColumnWidth(1,120);
    //    ui->tb->setColumnWidth(3,100);
    ui->tb->setColumnWidth(_Customer,100);

    ui->tb->setColumnWidth(_Status,100);
    ui->tb->setColumnWidth(_Bonus,80);
    ui->tb->setColumnWidth(_Pic0,60);

    ui->tb->setColumnWidth(_Pic1,60);

    ui->btnExcel->hide();

    //    ui->btnFilter->hide();

    //    ui->btnFilterClear->hide();
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

void LayerDayReport::init()
{
    m_bLockDate = true;
    ui->dateEdit->setDate(GLOBAL.dateTimeUtc8().date());
    m_bLockDate = false;


    delayRefresh();
}

void LayerDayReport::refreshTb(bool bRequery, bool bResetCb)
{


    updateOrderData(bRequery,true);

  //  ACTION.getGameItemFromGameSid()

    ui->tb->setRowCount(0);

    m_mappingData.clear();
    double iTotal0=0;


    double iTotal1=0;


    double iTotal2=0;

    double iTotalBonus=0.0;

    QStringList listCbFilter;
    listCbFilter.append(m_sFilterKey);

    for(int i=0;i<m_listOrder.length();i++)
    {

        OrderData data = m_listOrder.at(i);



        if(!listCbFilter.contains(data.Owner))
            listCbFilter.append(data.Owner);


        if(!checkFilter(data))
            continue;


        CustomerData customer;
#if 0
        QString sError;

        QVariantMap d;
        d["Sid"] = data.CustomerSid;
        QVariantList listCustomer;
        ACTION.action(ACT::QUERY_CUSTOMER,d,listCustomer,sError);
        if(listCustomer.length()<1)
            continue;

        customer.setData(listCustomer.first().toMap());
#else
        customer =ACTION.getCustomer(data.CustomerSid);
#endif


        int iRow = ui->tb->rowCount();
        ui->tb->setRowCount(iRow+1);
        int rowHeight = ui->tb->rowHeight(iRow);

        ui->tb->setItem(iRow,_Sid,UI.tbItem(data.Sid));

        ui->tb->setItem(iRow,_OderId,UI.tbItem(data.Id,GlobalUi::_BUTTON));

        //        UserData owner =ACTION.getUser(data.Owner);


        QString sDate=data.OrderDate+data.OrderTime;
        ui->tb->setItem(iRow,_Name,UI.tbItem(data.Name,GlobalUi::_BUTTON));
        QDateTime date=QDateTime::fromString(sDate,"yyyyMMddhhmmss");
        ui->tb->setItem(iRow,_DateTime,UI.tbItem(date.toString("hh:mm:ss")));
        ui->tb->setItem(iRow,_Note1,UI.tbItem(data.Note1));


        QString sUser="";

        if(data.User.length()>3)
        {
            UserData user = ACTION.getUser(data.User.at(3));


            sUser = user.Name;
        }



        ui->tb->setItem(iRow,_User,UI.tbItem(sUser,GlobalUi::_BUTTON));
        ui->tb->setItem(iRow,_Customer,UI.tbItem(customer.Id));


        QString sStatus =statusString(data.Step);

        QTableWidgetItem *tmpItem;

        if(data.Step=="4")
            tmpItem= UI.tbItem(sStatus,GlobalUi::_BUTTON);
        else
            tmpItem= UI.tbItem(sStatus);


        if(data.Note2.trimmed()!="")
        {
            double note2 = data.Note2.toDouble();

            if(data.Cost.toDouble()!=note2)
            {
                tmpItem->setForeground(QColor(255,0,0));

            }
        }


        ui->tb->setItem(iRow,_Status,tmpItem);

        ui->tb->setItem(iRow,_Bonus,UI.tbItem(data.Bouns));

        QString sGameName = ACTION.getGameName( data.GameSid);

        ui->tb->setItem(iRow,_GameName,UI.tbItem(sGameName));

        QTableWidgetItem *gameItem = UI.tbItem(getGameItemStr(data.Item));
        ui->tb->setItem(iRow,_GameItem,gameItem);

//        QFontMetrics fm(gameItem->font());
//        QSize size(fm.width(gameItem->text()), fm.height());
//        size = QSize(size.width() + 10, size.height() + 5);
//        if (size.height() > rowHeight)
//        {
//            ui->tb->setRowHeight(iRow, size.height());
//        }


        ui->tb->setItem(iRow,_Currency,UI.tbItem(customer.Currency));
        ui->tb->setItem(iRow,_TodayCost,UI.tbItem(data.Cost));


        _LayerDayReport::OrderPayType orderPayType = getPayCount(data);

        DataRate primeRate=ACTION.primeRate(data.PrimeRateSid,iRow==0);

        DataRate exRate=ACTION.costRate(data.ExRateSid,iRow==0);

        QString sPrimeRate="";

        //double payRate = ACTION.payTypeToNTDRate(data.PayType,primeRate,sPrimeRate);

        double iNtdCost = data.Money.first().toDouble();

        QStringList listNote = data.Note0;

        if(listNote.length()>4)
        {
            ui->tb->setItem(iRow,_Note,UI.tbItem(listNote.at(4),1));
        }


        if(data.Step.toInt()>=0)
        {
            ui->tb->setItem(iRow,_PayType,UI.tbItem(orderPayType.sPayName,true));


            ui->tb->setItem(iRow,_PayCount,UI.tbItem(""));

            // ui->tb->setItem(iRow,_PayRate,UI.tbItem(payRate));
        }

        if(data.Step.toInt()>=1)
        {
            //            if(iNtdCost==0 && data.Cost!="0")
            //            {
            //                QString sExRate =ACTION.setSellMoney(data);

            //                iNtdCost=data.Money.first().toInt();
            //            }


            QString sExRate="1";

            int idx =exRate.listKey().indexOf(ACTION.getCustomer(data.CustomerSid).Currency);

            if(idx>=0)
                sExRate = exRate.listValue().at(idx);

            ui->tb->setItem(iRow,_ExRate,UI.tbItem(sExRate));

            ui->tb->setItem(iRow,_Cost,UI.tbItem(iNtdCost));

        }

        QString sNtdPrime;// = data.Money[1];
        if(data.Step.toInt()>=3)
        {





            //成本匯率是要看儲值方式的幣別
            QString sPayTypeCurrency= ACTION.getAddValueCurrency(data.PayType);
            sPrimeRate = primeRate.listData.findValue(sPayTypeCurrency);
            ui->tb->setItem(iRow,_PayCount,UI.tbItem(orderPayType.iTotalCount));

            ui->tb->setItem(iRow,_PayRate,UI.tbItem(ACTION.getPayRate(data.PayType)));
            ui->tb->setItem(iRow,_PrimeRate,UI.tbItem(sPrimeRate));


            //成本
            // ACTION.setPrimeMoney(data);
            // sNtdPrime=data.Money[1];
            double iNtdPrime=sPrimeRate.toDouble()*orderPayType.iTotalCount*ACTION.getPayRate(data.PayType).toDouble();
            sNtdPrime=QString::number(iNtdPrime,'f',2);


            ui->tb->setItem(iRow,_Prime,UI.tbItem(sNtdPrime));
            ui->tb->setItem(iRow,_Profit,UI.tbItem(iNtdCost-sNtdPrime.toDouble()));
            double dTmp = 0.00;
            dTmp = (double)(iNtdCost-sNtdPrime.toDouble()) / data.Bouns.toDouble();
            ui->tb->setItem(iRow,_ProfitForOne,UI.tbItem(dTmp));

            if(data.Pic0.length()>0)
                ui->tb->setItem(iRow,_Pic0,UI.tbItem("儲值",1));
            if(data.Pic1.length()>0)
                ui->tb->setItem(iRow,_Pic1,UI.tbItem("回報",1));






        }



        qDebug()<<"ntdcost : "<<iNtdCost<<" , "<<data.Step.toInt();

        if(data.Step.toInt()==5)
        {

            iTotal0 +=iNtdCost;

            iTotal1 =iTotal1+sNtdPrime.toDouble();

            int iTmp = iNtdCost-sNtdPrime.toDouble();
            iTotal2 +=iTmp;

            iTotalBonus+=data.Bouns.toDouble();
        }


        m_mappingData[data.Sid]=data.data();

    }


    ui->lbTotal0->setText(QString::number(iTotal0));
    ui->lbTotal1->setText(QString::number(iTotal1));
    ui->lbTotal2->setText(QString::number(iTotal2));
    ui->lbTotalBonus->setText(QString::number(iTotalBonus));

    if(bResetCb)
    {
        ui->cbFilter->setProperty("lock",true);
        ui->cbFilter->clear();

        ui->cbFilter->addItems(listCbFilter);

        ui->cbFilter->setEditable(true);

        QCompleter *completer=new QCompleter(ui->cbFilter->model(),this);
        //    //        completer->setCompletionMode(QCompleter::PopupCompletion);
        ui->cbFilter->setCompleter(completer);

        ui->cbFilter->setProperty("lock",false);
    }


}

bool LayerDayReport::checkFilter(OrderData order)
{
    QString step = order.Step;
    QString sDate = order.OrderDate;


    if(ui->dateEdit->date().toString("yyyyMMdd") != sDate)
    {

        return false;
    }


    if(step=="-1" && !ui->cbStep0_1->isChecked())
    {

        return false;
    }


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



    QString st = ui->cbFilter->currentText().toUpper();

    if(st.trimmed()!="")
    {

        bool b = false;
        QString sDate=order.OrderDate+order.OrderTime;
        QDateTime date=QDateTime::fromString(sDate,"yyyyMMddhhmmss");

        CustomerData cus=ACTION.getCustomer(order.CustomerSid);


        QStringList target;
        target<<order.Owner
             <<order.Id<<order.Name
            <<cus.Id<<cus.Currency
           <<ACTION.getGameName(order.GameSid);
        //        <<date.toString("hh:mm:ss");



        foreach(QString tmp,target)
        {

            if(tmp.toUpper().contains(st.toUpper()))
            {

                b = true;
                break;
            }
        }


        return b;

    }

    return true;
}

void LayerDayReport::on_tb_cellPressed(int row, int column)
{
    if(row<0 || row>=m_mappingData.keys().length())
        return;


    QString orderSid= ui->tb->item(row,0)->text();

    OrderData data(m_mappingData[orderSid].toMap());

    if(column==_OderId || column==_Name)
    {

        QVariantMap d;

        d["Sid"] = data.CustomerSid;


        m_detialOrder->setCustomer(d,data.Sid);

        //   m_detialOrder->refreshInfo();
        m_detialOrder->raise();

        m_detialOrder->show();

    }

    if(column==_Status && data.Step=="4" && ACTION.m_currentUser.Lv>=USER_LV::_LV3)
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

            //  data.Money = listMoney;


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

                //   ACTION.orderUpdateCount(data.Sid,user.Sid,data.Item);

            }


            UI.showMsg("",sError,"OK");

            refreshTb();


        }
    }

    if(column==_PayType && data.Step.toInt()>=4 )
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

            //ACTION.setSellMoney(order);

            bool bOk =ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);

            if(bOk)
                sError="修改儲值方式完成";

            DMSG.showMsg("",sError,"OK");
            refreshTb();

        }

    }

    if(column==_Pic0 || column==_Pic1 )
    {


        QString sText=data.Id;
        QString sKey="Md5";

        QVariant sValue = data.Pic0;

        if(column==_Pic1)
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



    if(column==_Note ||column==_User)
    {

        QString st="訂單編號:"+data.Id+"\n"
                                   "報價:     %1\n"
                                   "下單:     %2\n"
                                   "接單/儲值: %3\n"
                                   "回報:     %4\n"
                                   "確認:     %5\n";


        QStringList listName;

        foreach(QString sUserSid,data.User)
        {
            listName.append(ACTION.getUser(sUserSid).Name);
        }


        DialogNote dialog;
        dialog.setUser(listName);
        dialog.setData(data.Note0);

        dialog.exec();

    }

    if(column==_Note1)
    {
        DialogInput dialog;

        dialog.setTitle(data.Id+"    "+data.Name);

        dialog.setText(data.Note1);

        dialog.hideDelete();

        int ret =dialog.exec();

        if(ret==1)
        {
            QString sError;
            data.Note1=dialog.text();
            ACTION.action(ACT::REPLACE_ORDER,data.data(),sError);
            refreshTb();
        }

    }
}

void LayerDayReport::on_cbStep0_1_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep0_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep1_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep2_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep3_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep4_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_cbStep5_clicked()
{
    refreshTb(false);
}


void LayerDayReport::on_btnFilter_clicked()
{
    m_sFilterKey=ui->cbFilter->currentText();
    refreshTb(false);
}

void LayerDayReport::on_btnFilterClear_clicked()
{
    m_sFilterKey="";
    ui->cbFilter->clear();
    refreshTb(false);
}



void LayerDayReport::delayRefresh()
{

    if(m_bLockLoading)
        return;

    m_bLockLoading=true;

    ui->tb->hideColumn(_CheckNum);
    //
    ui->tb->hideColumn(_Cost);
    ui->tb->hideColumn(_PrimeRate);
    ui->tb->hideColumn(_Prime);
    ui->tb->hideColumn(_Profit);

    ui->tb->hideColumn(_ProfitForOne);
    ui->tb->hideColumn(_PayRate);



    ui->wTotal->hide();

    ui->btnExcel->hide();


    if(ACTION.m_currentUser.Lv>=USER_LV::_LV4)
    {

        ui->wShowArea->show();

        ui->tb->showColumn(_PrimeRate);
        ui->tb->showColumn(_Prime);
        ui->tb->showColumn(_Profit);

        if(ui->cbShowCost->isChecked())
            ui->tb->showColumn(_Cost);

        ui->tb->showColumn(_ProfitForOne);
        ui->tb->showColumn(_PayRate);
        ui->wTotal->show();

        ui->btnExcel->show();

    }

    ACTION.primeRate("",true);
    refreshTb();

    m_bLockLoading = false;
}





void LayerDayReport::on_dateEdit_userDateChanged(const QDate &date)
{

    /*
    if(m_bLockDate)
    {

        return ;
    }

    QTimer::singleShot(500,[=]()
    {
        ui->dateEdit->setEnabled(false);
        delayRefresh();


        ui->dateEdit->setEnabled(true);
    });
    */
}


void LayerDayReport::on_tb_cellEntered(int row, int column)
{


    if(row<0 || row>=m_mappingData.keys().length())
        return;

    QString orderSid= ui->tb->item(row,0)->text();

    OrderData data(m_mappingData[orderSid].toMap());

    if(column==_User)
    {
        QString st="訂單編號:"+data.Id+"\n"
                                   "報價:     %1\n"
                                   "下單:     %2\n"
                                   "接單:     %3\n"
                                   "儲值:     %4\n"
                                   "回報:     %5\n"
                                   "確認:     %6\n";


        QStringList listName;

        foreach(QString sUserSid,data.User)
        {
            listName.append(ACTION.getUser(sUserSid).Name);
        }

        while(listName.length()<6)
        {
            listName.append(" ");
        }



        UI.toolTip(st.arg(listName.at(0),listName.at(1),listName.at(2),listName.at(3),listName.at(4),listName.at(5)));


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

void LayerDayReport::changeVisable()
{
    ui->tb->setColumnHidden(_Bonus,!ui->cbShowBonus->isChecked());

    ui->tb->setColumnHidden(_GameItem,!ui->cbShowGameItem->isChecked());

    ui->tb->setColumnHidden(_Cost,!ui->cbShowCost->isChecked());

    bool bHidePic = !ui->cbShowPic->isChecked();

    ui->tb->setColumnHidden(_Pic0,bHidePic);
    ui->tb->setColumnHidden(_Pic1,bHidePic);
}

void LayerDayReport::updateOrderData(bool bUpdate, bool bStrong)
{

    if(bUpdate)
    {

        if(bStrong)
        {
            if(ui->dateEdit->date()!=GLOBAL.dateTimeUtc8().date() && ui->dateEdit->date()!=GLOBAL.dateTimeUtc8().date().addDays(-1))
                bStrong=false;
        }


        m_listOrder = ACTION.getOrderByDate(ui->dateEdit->date(),bStrong);
    }
}

QString LayerDayReport::statusString(QString sStep)
{
    QString sStatus = sStep;

    if(sStatus=="-1")
    {
        sStatus+="取消";
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
        sStatus+="接單";
    }
    if(sStatus=="3")
    {
        sStatus+="儲值";
    }
    if(sStatus=="4")
    {
        sStatus+="回報";
    }
    if(sStatus=="5")
    {
        sStatus="完成";
    }

    return sStatus;
}

QString LayerDayReport::getGameItemStr(QString items)
{
    QString sRe="";
    QStringList listItem=items.split(";;");

    foreach(QString v,listItem)
    {
        QString sSid =v.split(",,").first();
        QString sCount = v.split(",,").last();

           sRe+= ACTION.getGameItemFromSid(sSid).Name+"*"+sCount+" ";

    }



    return sRe;
}


void LayerDayReport::on_btnExcel_clicked()
{
    if(ui->tb->rowCount()<1)
    {
        DMSG.showMsg("","沒有資料","OK");

        return ;
    }

    QString sPath;

#if 0
    sPath = QFileDialog::getExistingDirectory(this,"選擇存檔位置",".");
    if(sPath.trimmed()=="")
        return ;
#else

    sPath = QApplication::applicationDirPath()+"/out";
    QDir dir(sPath);
    if (!dir.exists())
    {
        dir.mkdir(".");
    }

    sPath = QApplication::applicationDirPath()+"/out/report";
    QDir dir2(sPath);
    if (!dir2.exists())
    {
        dir2.mkdir(".");
    }






#endif

    //

    QString sFileName = sPath+"/"+ui->dateEdit->date().toString("MMdd")+"_每日報表_"+GLOBAL.dateTimeUtc8().toString("MMddhhmmss");
    qDebug()<<"sFileName : "<<sFileName;
    QTXLSX_USE_NAMESPACE

            Document xlsx;

    //  xlsx.addSheet();

    for(int iRow=0;iRow<ui->tb->rowCount();iRow++)
    {
        int iXlsxCol =0;
//        int iH = xlsx.rowHeight(iRow);

        for(int iCol=0;iCol<ui->tb->columnCount();iCol++)
        {
            qDebug()<<"col : "<<iCol<<" row: "<<iRow;

            if(iCol==_Sid || iCol==_Pic0 || iCol==_Pic1 || iCol==_CheckNum)
                continue;
            iXlsxCol++;

            if(iRow==0)
            {
                QString sHeader= ui->tb->horizontalHeaderItem(iCol)->text();
                xlsx.write(iRow+1,iXlsxCol,sHeader);
            }


            QString st ="";

            if(ui->tb->item(iRow,iCol)!=nullptr)
                st = ui->tb->item(iRow,iCol)->text();

           // int iLineCount =1;

            if(st.trimmed()!="")
            {

                bool bOk = false;
                if(iCol==_Bonus || iCol==_PayCount ||iCol==_TodayCost || iCol==_Cost
                        || iCol==_Prime || iCol==_Profit || iCol==_ProfitForOne || iCol==_PayRate)
                {
                    bOk=xlsx.write(iRow+2,iXlsxCol,st.toDouble());

                }
                else
                {
                    if(iCol==_Note)
                    {
                           st=st.replace("\n","");

                    }
                    bOk = xlsx.write(iRow+2,iXlsxCol,st);

                }

                if(!bOk)
                {
                    qDebug()<<"st : "<<st;
                }

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


    QString sMsg="存檔位置 : "+sPath+
            "\n檔名 : "+sFileName.split("/").last()+"\n"
            "\n匯出完成";


    int iRet= DMSG.showMsg("",sMsg,QStringList()<<"打開資料夾"<<"OK");

    if(iRet==0)
    {
        QString folderPath = sPath;
        QUrl folderUrl = QUrl::fromLocalFile(folderPath);
        QString sCmd="start explorer " +sPath.replace("/","\\");
        //system(sCmd.toStdString().c_str());
        QDesktopServices::openUrl(folderUrl);
    }

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


void LayerDayReport::on_cbShowBonus_clicked()
{
    changeVisable();
}


void LayerDayReport::on_cbShowPic_clicked()
{
    changeVisable();
}


void LayerDayReport::on_cbShowCost_clicked()
{
    changeVisable();
}


void LayerDayReport::on_btnChangeDate_clicked()
{
    delayRefresh();

}






void LayerDayReport::on_cbFilter_currentIndexChanged(int index)
{
    //    if(ui->cbFilter->property("lock").toBool())
    //        return ;

    //    ui->cbFilter->setProperty("lock",true);
    //    refreshTb(false,false);
    //    ui->cbFilter->setProperty("lock",false);
}


void LayerDayReport::on_cbShowGameItem_clicked()
{
     changeVisable();
}

