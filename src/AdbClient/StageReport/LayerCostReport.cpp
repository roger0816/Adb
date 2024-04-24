#include "LayerCostReport.h"
#include "ui_LayerCostReport.h"

LayerCostReport::LayerCostReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCostReport)
{
    ui->setupUi(this);

    m_detialOrder = new LayerOrder;

    m_detialOrder->setReadOnly();
    m_detialOrder->hide();


    ui->dateEdit->setDateTime(GLOBAL.dateTimeUtc8());

    ui->tb->hideColumn(_Sid);

    ui->tb->hideColumn(_Note1);
}

LayerCostReport::~LayerCostReport()
{
    if(m_detialOrder!=nullptr)
    {
        m_detialOrder->hide();
        delete m_detialOrder;
    }

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
        in["ASC"]="Sid";

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

        CustomerData cus=DATA.getCustomer(costData.CustomerSid);

        if(!checkFilter(cus,costData))
            continue;

        m_listDisplay.append(m_listMix.at(i));
        ui->tb->setRowCount(iRow+1);



        ui->tb->setItem(iRow, _Sid,UI.tbItem(costData.Sid));

        ui->tb->setItem(iRow, _OrderId,UI.tbItem(costData.OrderId));

        if(!costData.IsAddCost &&
                (ui->dateEdit->date()==GLOBAL.dateTimeUtc8().date() || ui->dateEdit->date()==GLOBAL.dateTimeUtc8().addDays(-1).date()))
            ui->tb->setItem(iRow, _OrderId,UI.tbItem(costData.OrderId,UI._BUTTON));

        ui->tb->setItem(iRow, _CusId,UI.tbItem(cus.Id,UI._BUTTON));
        ui->tb->setItem(iRow, _CusName,UI.tbItem(cus.Name));
        ui->tb->setItem(iRow, _Currency,UI.tbItem(cus.Currency));
        ui->tb->setItem(iRow, _Cost,UI.tbItem(costData.Total,UI._BUTTON));
        ui->tb->setItem(iRow, _User,UI.tbItem(DATA.getUser(costData.UserSid).Name));
        //  ui->tb->setItem(iRow, _Note1,UI.tbItem(costData.Note1));

        QLabel *lbNote1 = new QLabel(ui->tb);
        lbNote1->setText(costData.Note1);
        ui->tb->setCellWidget(iRow,_Note1,lbNote1);



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

    if(cus.Id.contains(searchKey))
        return true;



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

    CustomerData cus=DATA.getCustomer(cos.CustomerSid);

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

    else if(column == _OrderId)
    {
        if(!cos.IsAddCost)
        {


            OrderData orderData=ACTION.getOrderByOrderId(cos.OrderId,true);

            if(orderData.Sid!="")
            {
                m_detialOrder->setData(orderData);

                //   m_detialOrder->refreshInfo();
                m_detialOrder->raise();

                m_detialOrder->show();
            }
        }
    }
    else if(column== _Note1)
    {
//        if(column==_Note1)
//        {
//            DialogInput dialog;

//            dialog.setTitle(cos.Id+"    "+cus.Name);

//            dialog.setText(cus.Note1);

//            dialog.hideDelete();

//            int ret =dialog.exec();

//            if(ret==1)
//            {
//                QString sError;
//                QVariantMap in;
//                in["Sid"]=cos.Sid;
//                in["Note1"]=dialog.text();

//                ACTION.action(ACT::REPLACE_ORDER,in,sError);
//                refresh();
//            }

//        }
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


void LayerCostReport::on_btnExcel_clicked()
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

    QString sFileName = sPath+"/"+ui->dateEdit->date().toString("MMdd")+"_消費明細表_"+GLOBAL.dateTimeUtc8().toString("MMddhhmmss");
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

            if(iCol==_Sid)
                continue;
            iXlsxCol++;

            if(iRow==0)
            {
                QString sHeader= ui->tb->horizontalHeaderItem(iCol)->text();
                xlsx.write(iRow+1,iXlsxCol,sHeader);
            }


            QString st ="";


            if(iCol==_Note1)
                st = dynamic_cast<QLabel*>(ui->tb->cellWidget(iRow,iCol))->text();
            else
            {
                if(ui->tb->item(iRow,iCol)!=nullptr)
                    st = ui->tb->item(iRow,iCol)->text();
            }

            // int iLineCount =1;

            if(st.trimmed()!="")
            {

                bool bOk = false;
                if(iCol==_Cost)
                {
                    bOk=xlsx.write(iRow+2,iXlsxCol,st.toDouble());

                }
                else
                {
                    if(iCol==_Note1)
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

    //        xlsx.write("A"+QString::number(ui->tb->rowCount()+3),ui->lbT->text());
    //        xlsx.write("G"+QString::number(ui->tb->rowCount()+3),ui->lbTotalBonus->text().toDouble());
    //        xlsx.write("K"+QString::number(ui->tb->rowCount()+3),ui->lbTotal0->text().toDouble());
    //        xlsx.write("L"+QString::number(ui->tb->rowCount()+3),ui->lbTotal1->text().toDouble());
    //        xlsx.write("M"+QString::number(ui->tb->rowCount()+3),ui->lbTotal2->text().toDouble());

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

