#include "LayerDayDebit.h"
#include "ui_LayerDayDebit.h"

LayerDayDebit::LayerDayDebit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerDayDebit)
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

    ui->tb->setColumnWidth(_Pic0,40);

    ui->tb->setColumnWidth(_Pic1,40);

    ui->tb->setColumnWidth(_OrderTime,90);

    connect(ui->btnDebitExport,&QPushButton::clicked,this,&LayerDayDebit::slotBtnDebitExport);

    connect(ui->cbCurrency,&QComboBox::currentTextChanged,[=](){
        refresh();
    });


    //    ui->tb->hideColumn(_OriValue);
    //       ui->tb->hideColumn(_OriCurrency);
}

LayerDayDebit::~LayerDayDebit()
{
    delete ui;
}

void LayerDayDebit::init()
{

    ui->dateEdit->setProperty("lock",true);
    ui->dateEdit->setDate(QDateTime::currentDateTime().date());
    ui->dateEdit->setProperty("lock",false);
    refresh();
}


void LayerDayDebit::updateTbData(bool bRequery)
{
    if(m_bLockRe)
        return;

    m_bLockRe = true;


    m_listDebit.clear();

    ACTION.action(ACT::QUERY_DEBIT_CLASS,QVariantMap(),m_allDebit);


    bool bStrong = false;

    if(ui->dateEdit->date()==GLOBAL.dateTimeUtc8().date())
        bStrong = true;

    if(bRequery)
    {
        QString sError;
        QVariantMap in;
        in["OrderTime like"]="%"+ui->dateEdit->date().toString("yyyyMMdd")+"%";
        in["IsAddCost"]="1";

        ACTION.action(ACT::QUERY_CUSTOMER_COST,in,m_listCustomerCost,sError,bStrong);
    }


    m_bLockRe = false;

}


void LayerDayDebit::refresh(bool bRequery)
{

    updateTbData(bRequery);


    setCb();



    refreshTb();


}

void LayerDayDebit::refreshTb()
{



    long int iTotal=0;

    ui->tb->setRowCount(0);

    m_listDisplayCustomerCost.clear();

    ui->tb->hideColumn(_DebitSid);

    if(ui->cbDebit->currentIndex()==0)
        ui->tb->showColumn(_DebitSid);

    for(int i=0;i<m_listCustomerCost.length();i++)
    {
        int iRow = ui->tb->rowCount();

        CustomerCost data(m_listCustomerCost.at(i).toMap());

        if(!checkData(data))
            continue;

        ui->tb->setRowCount(iRow+1);

        ui->tb->setItem(iRow,_DebitSid,UI.tbItem(getDebitName(data.DebitSid)));

        ui->tb->setItem(iRow,_OrderId,UI.tbItem(data.OrderId));

        CustomerData customer =ACTION.getCustomer(data.CustomerSid);

        ui->tb->setItem(iRow,_CusSid,UI.tbItem(customer.Id));

        ui->tb->setItem(iRow,_CusName,UI.tbItem(customer.Name));
        ui->tb->setItem(iRow,_CusCurrency,UI.tbItem(customer.Currency));

        ui->tb->setItem(iRow,_CusTotal,UI.tbItem(data.Total));
        ui->tb->setItem(iRow,_DebitNote,UI.tbItem(data.DebitNote));

        ui->tb->setItem(iRow,_ChangeValue,UI.tbItem(data.ChangeValue));

        if(data.OriginCurrency!=data.Currency)
        {
            ui->tb->setItem(iRow,_OriValue,UI.tbItem(data.OriginValue));
            ui->tb->setItem(iRow,_OriCurrency,UI.tbItem(data.OriginCurrency));
        }


        QString sData = QDateTime::fromString(data.OrderTime,"yyyyMMddhhmmss").toString("hh:mm:ss");
        ui->tb->setItem(iRow,_OrderTime,UI.tbItem(sData));
        ui->tb->setItem(iRow,_UserName,UI.tbItem(ACTION.getUser(data.UserSid).Name));
        if(data.Pic0.trimmed()!="")
        {
            ui->tb->setItem(iRow,_Pic0,UI.tbItem("圖1",1));
        }

        if(data.Pic1.trimmed()!="")
        {
            ui->tb->setItem(iRow,_Pic1,UI.tbItem("圖2",1));
        }



        ui->tb->setItem(iRow,_Note0,UI.tbItem(data.Note0));
        iTotal+=data.OriginValue.toDouble();

        m_listDisplayCustomerCost.append(data.data());
    }


    ui->lbTotal->setText(QString::number(iTotal));

    ui->lbT->setVisible(ui->cbCurrency->currentIndex()!=0);


    ui->lbTotal->setVisible(ui->cbCurrency->currentIndex()!=0);



}

bool LayerDayDebit::checkData(CustomerCost data)
{

    if(data.Sid=="")
        return false;



    QDateTime date =QDateTime::fromString(data.OrderTime,"yyyyMMddhhmmss");

    if(date.time()<ui->timeStart->time() || date.time()>ui->timeEnd->time())
    {

        return false;
    }





    /*

    if(ui->cbCurrency->currentIndex()==0 && ui->cbDebit->currentIndex()==0)
        return true;

    if(ui->cbCurrency->currentIndex()!=0 && data.Currency!=ui->cbCurrency->currentText())
    {
        qDebug()<<data.Sid<<" : "<<data.Currency<<" : "<<ui->cbCurrency->currentIndex();
        return false;
    }
    if(ui->cbDebit->currentIndex()==0)
        return true;
*/


    QStringList listDebitSid;
    if(ui->cbDebit->currentIndex()==0)
    {


        for(int i=0;i<m_listDebit.length();i++)
        {
            listDebitSid.append(DebitClass(m_listDebit.at(i).toMap()).Sid);

        }


    }
    else
    {



        int iIdx = qBound(0,ui->cbDebit->currentIndex()-1,m_listDebit.length()-1);


        QString sCurrentDebitSid =  DebitClass(m_listDebit.at(iIdx).toMap()).Sid;

        listDebitSid.append(sCurrentDebitSid);

    }

    return listDebitSid.contains(data.DebitSid);


}

void LayerDayDebit::setCb(bool bRe)
{

    if(m_bLockRe)
        return;
    m_bLockRe = true;


    QStringList listCbName;

    listCbName.append("全部");

    for(int i=0;i<m_allDebit.length();i++)
    {
        QString sFilterCurrency="";

        if(ui->cbCurrency->currentIndex()!=0)
        {
            sFilterCurrency = ui->cbCurrency->currentText();
        }


        DebitClass d(m_allDebit.at(i).toMap());

        if(d.Currency.indexOf(sFilterCurrency)>=0 || sFilterCurrency=="")
        {
            listCbName.append(d.Name);

            m_listDebit.append(d.data());
        }

    }

    int iOldIdx = ui->cbDebit->currentIndex();

    ui->cbDebit->setProperty("lock",true);
    ui->cbDebit->clear();

    ui->cbDebit->addItems(listCbName);

    ui->cbDebit->setProperty("lock",false);

    iOldIdx=qBound(0,iOldIdx,ui->cbDebit->count()-1);

    if(bRe)
        ui->cbDebit->setCurrentIndex(iOldIdx);

    m_bLockRe = false;
}

QString LayerDayDebit::getDebitName(QString debitSid)
{
    QString sRe="";
    for(int i=0;i<m_allDebit.length();i++)
    {
        DebitClass d(m_allDebit.at(i).toMap());

        if(debitSid==d.Sid)
            sRe=d.Name;

    }

    return sRe;
}


void LayerDayDebit::on_cbDebit_currentIndexChanged(int index)
{
    if(index<0 || ui->cbDebit->property("lock").toBool())
        return;

    //    int iIdx = qBound(0,ui->cbDebit2->currentIndex(),m_listDebit.length()-1);

    //    QString sCurrency =  DebitClass(m_listDebit.at(iIdx).toMap()).Currency;

    //    ui->lbCurrency->setText(sCurrency);

    refreshTb();
}


void LayerDayDebit::on_dateEdit_userDateChanged(const QDate &date)
{
    //    if(ui->dateEdit->property("lock").toBool())
    //        return;
    //    refreshTb();
}


void LayerDayDebit::on_timeStart_userTimeChanged(const QTime &time)
{
    // refreshTb();
}


void LayerDayDebit::on_timeEnd_userTimeChanged(const QTime &time)
{
    //refreshTb();
}


void LayerDayDebit::on_tb_cellPressed(int row, int column)
{
    if(row<0 || row>=m_listDisplayCustomerCost.length())
        return ;

    if(column!=_Pic0 && column!=_Pic1)
        return;


    CustomerCost data(m_listDisplayCustomerCost.at(row).toMap());

    QString sText=data.OrderId;
    QString sKey="Md5";

    QVariant sValue = data.Pic0;

    if(column==_Pic1)
        sValue = data.Pic1;

    if(sValue.toString().trimmed()=="")
        return;



    QVariantMap out;
    ACTION.action(ACT::QUERY_PIC,sKey,sValue,out);
    m_dialogPic->resize(480,360);

    m_itemPic->setFileName(
                ui->tb->item(row,_DebitSid)->text()+"_"+
                ui->tb->item(row,_OrderId)->text()+"_"+
                sText);

    m_itemPic->setData(out["Data"].toByteArray());

    m_dialogPic->setWindowTitle("編號 : "+
                                ui->tb->item(row,_DebitSid)->text()+"          "
                                +sText);

    QTimer::singleShot(50,this,[=](){ m_dialogPic->exec();});
}


void LayerDayDebit::slotBtnDebitExport()
{
    if(ui->tb->rowCount()<1)
    {
        DMSG.showMsg("","沒有資料","OK");

        return ;
    }
    QString sPath = QFileDialog::getExistingDirectory(this,"選擇存檔位置",".");

    if(sPath.trimmed()=="")
        return ;

    QString sDebitText="all";

    if(ui->cbDebit->currentIndex()!=0)
        sDebitText = ui->cbDebit->currentText();


    QString sFileName = sPath+"/"+"DayDebit_"+sDebitText+"_"+ui->dateEdit->date().toString("yyyy_MMdd");
    qDebug()<<"sFileName : "<<sFileName;

    QTXLSX_USE_NAMESPACE

            Document xlsx;

    // xlsx.renameSheet(xlsx.currentSheet()->sheetName(),ui->cbDebit->currentText());
    //  xlsx.addSheet();

    for(int iRow=0;iRow<ui->tb->rowCount();iRow++)
    {
        int iXlsxCol =0;
        for(int iCol=0;iCol<ui->tb->columnCount();iCol++)
        {

            if(iCol==_Pic0 || iCol==_Pic1)
                continue;

            iXlsxCol++;

            if(iRow==0)
            {
                QString sHeader= ui->tb->horizontalHeaderItem(iCol)->text();
                xlsx.write(iRow+1,iXlsxCol,sHeader);
            }

            QString st="";
            if(ui->tb->item(iRow,iCol)!=nullptr)
                st= ui->tb->item(iRow,iCol)->text();

            if(st.trimmed()!="")
            {
                if(iCol!=_CusTotal && iCol!=_ChangeValue)
                    xlsx.write(iRow+2,iXlsxCol,st);
                else
                    xlsx.write(iRow+2,iXlsxCol,st.toDouble());
            }
            xlsx.setColumnWidth(iXlsxCol,iXlsxCol,16);
        }
    }

    xlsx.write("F"+QString::number(ui->tb->rowCount()+3),ui->lbT->text().toDouble());
    xlsx.write("G"+QString::number(ui->tb->rowCount()+3),ui->lbTotal->text().toLongLong());


    xlsx.saveAs(sFileName+".xls");

    DMSG.showMsg("",sFileName.split("/").last()+"\n\n匯出完成","OK");
}


void LayerDayDebit::on_btnChangeDate_clicked()
{
    refresh();
}

