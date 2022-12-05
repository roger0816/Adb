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

    ui->tb->setColumnWidth(9,40);

    ui->tb->setColumnWidth(10,40);

    connect(ui->btnDebitExport,&QPushButton::clicked,this,&LayerDayDebit::slotBtnDebitExport);

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

    m_listDisplayCustomerCost.clear();

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

        ui->tb->setItem(iRow,4,UI.tbItem(data.Total));
        ui->tb->setItem(iRow,5,UI.tbItem(data.DebitNote));
        ui->tb->setItem(iRow,6,UI.tbItem(data.OriginValue));
        ui->tb->setItem(iRow,7,UI.tbItem(QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss")));
           ui->tb->setItem(iRow,8,UI.tbItem(ACTION.getUser(data.UserSid).Name));
        if(data.Pic0.trimmed()!="")
        {
            ui->tb->setItem(iRow,9,UI.tbItem("圖1",1));
        }

        if(data.Pic1.trimmed()!="")
        {
            ui->tb->setItem(iRow,10,UI.tbItem("圖2",1));
        }



        ui->tb->setItem(iRow,11,UI.tbItem(data.Note0));
        iTotal+=data.OriginValue.toDouble();

        m_listDisplayCustomerCost.append(data.data());
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


void LayerDayDebit::on_tb_cellPressed(int row, int column)
{
    if(row<0 || row>=m_listDisplayCustomerCost.length())
        return ;

    if(column!=9 && column!=10)
        return;


    CustomerCost data(m_listDisplayCustomerCost.at(row).toMap());

    QString sText=data.OrderId;
    QString sKey="Md5";

    QVariant sValue = data.Pic0;

    if(column==10)
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


    QString sFileName = sPath+"/"+"DayDebit_"+ui->cbDebit->currentText()+"_"+ui->dateEdit->date().toString("yyyy_MMdd");
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

            if(iCol==9 || iCol==10)
                continue;

            iXlsxCol++;

            if(iRow==0)
            {
                QString sHeader= ui->tb->horizontalHeaderItem(iCol)->text();
                xlsx.write(iRow+1,iXlsxCol,sHeader);
            }

            QString st = ui->tb->item(iRow,iCol)->text();
            qDebug()<<"row : "<<iRow<<" col: "<<iCol<<" data: "<<st;
            xlsx.write(iRow+2,iXlsxCol,st);
            xlsx.setColumnWidth(iXlsxCol,iXlsxCol,16);
        }
    }

    xlsx.write("F"+QString::number(ui->tb->rowCount()+3),ui->lbT->text());
    xlsx.write("G"+QString::number(ui->tb->rowCount()+3),ui->lbTotal->text());


    xlsx.saveAs(sFileName+".xls");

    DMSG.showMsg("",sFileName.split("/").last()+"\n\n匯出完成","OK");
}

