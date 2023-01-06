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

    ui->tb->setColumnWidth(10,40);

    ui->tb->setColumnWidth(11,40);

    connect(ui->btnDebitExport,&QPushButton::clicked,this,&LayerDayDebit::slotBtnDebitExport);

    connect(ui->cbCurrency,&QComboBox::currentTextChanged,[=](){
        refresh();
    });


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


void LayerDayDebit::refresh(bool bRe)
{



    setCb();



    refreshTb();


}

void LayerDayDebit::refreshTb()
{

    if(m_bLockRe)
        return;

    m_bLockRe = true;

    QVariantMap in;
    in["OrderTime like"]="%"+ui->dateEdit->date().toString("yyyyMMdd")+"%";
    in["IsAddCost"]="1";

    qDebug()<<"BBBBB";
    ACTION.action(ACT::QUERY_CUSTOMER_COST,in,m_listCustomerCost);

    long int iTotal=0;

    ui->tb->setRowCount(0);

    m_listDisplayCustomerCost.clear();

    ui->tb->hideColumn(0);

    if(ui->cbDebit->currentIndex()==0)
        ui->tb->showColumn(0);

    for(int i=0;i<m_listCustomerCost.length();i++)
    {
        int iRow = ui->tb->rowCount();

        CustomerCost data(m_listCustomerCost.at(i).toMap());

        if(!checkData(data))
            continue;

        ui->tb->setRowCount(iRow+1);

        ui->tb->setItem(iRow,0,UI.tbItem(getDebitName(data.DebitSid)));

        ui->tb->setItem(iRow,1,UI.tbItem(data.OrderId));

        CustomerData customer =ACTION.getCustomer(data.CustomerSid);

        ui->tb->setItem(iRow,2,UI.tbItem(customer.Id));

        ui->tb->setItem(iRow,3,UI.tbItem(customer.Name));
        ui->tb->setItem(iRow,4,UI.tbItem(customer.Currency));

        ui->tb->setItem(iRow,5,UI.tbItem(data.Total));
        ui->tb->setItem(iRow,6,UI.tbItem(data.DebitNote));
        int iValue = data.OriginValue.toDouble();
        ui->tb->setItem(iRow,7,UI.tbItem(iValue));
        ui->tb->setItem(iRow,8,UI.tbItem(QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss")));
        ui->tb->setItem(iRow,9,UI.tbItem(ACTION.getUser(data.UserSid).Name));
        if(data.Pic0.trimmed()!="")
        {
            ui->tb->setItem(iRow,10,UI.tbItem("圖1",1));
        }

        if(data.Pic1.trimmed()!="")
        {
            ui->tb->setItem(iRow,11,UI.tbItem("圖2",1));
        }



        ui->tb->setItem(iRow,12,UI.tbItem(data.Note0));
        iTotal+=data.OriginValue.toDouble();

        m_listDisplayCustomerCost.append(data.data());
    }

    ui->lbTotal->setText(QString::number(iTotal));

    m_bLockRe = false;

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


    m_listDebit.clear();

    ACTION.action(ACT::QUERY_DEBIT_CLASS,QVariantMap(),m_allDebit);

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

    if(column!=10 && column!=11)
        return;


    CustomerCost data(m_listDisplayCustomerCost.at(row).toMap());

    QString sText=data.OrderId;
    QString sKey="Md5";

    QVariant sValue = data.Pic0;

    if(column==11)
        sValue = data.Pic1;


    QVariantMap out;
    ACTION.action(ACT::QUERY_PIC,sKey,sValue,out);
    m_dialogPic->resize(480,360);

    m_itemPic->setFileName(
                ui->tb->item(row,0)->text()+"_"+
                ui->tb->item(row,1)->text()+"_"+
                sText);

    m_itemPic->setData(out["Data"].toByteArray());

    m_dialogPic->setWindowTitle("編號 : "+
                                ui->tb->item(row,0)->text()+"          "
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

            if(iCol==10 || iCol==11)
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
                if(iCol!=5 && iCol!=7)
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

