#include "LayerExchangeRate.h"
#include "ui_LayerExchangeRate.h"

LayerExchangeRate::LayerExchangeRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerExchangeRate)
{
    ui->setupUi(this);


   // ui->tbHistory->setColumnWidth(6,200);

    DataExchange tempClass;

    m_listKey = tempClass.listKey;

    m_listHeaderName<<"新台幣(NTD)"<<"港幣(HKD)"<<"人民幣(RMB)"<<"林吉特(MYR)"<<"新加坡元(SGD)";

    ui->tableWidget->setRowCount(m_listHeaderName.length());


    QHeaderView *header =ui->tableWidget->verticalHeader();

    header->setMinimumWidth(80);

    // QTableWidget QHeaderView::section { background-color:#2e323d };

    ui->tableWidget->setVerticalHeader(header);

    ui->tableWidget->setVerticalHeaderLabels(m_listHeaderName);

    QLineEdit *t = ui->lineEdit;

    QDoubleValidator d(0,100,2,this);

    //  t->setValidator(new QDoubleValidator(0,100,2,ui->lineEdit));

    // QRegExp v("[1-9]\\d{0,7}");
    QRegExp v("^\d+(\.\d+)?$");

    // QRegExp v("[1-9][1-9 | .]{0,7}");

    QRegExp r("-?\\d{0,3}");

    QRegExpValidator v2(v,0);

    // t->setValidator(new QRegExpValidator(v,0));

    ui->lineEdit->hide();
}

LayerExchangeRate::~LayerExchangeRate()
{
    delete ui;
}

void LayerExchangeRate::refresh()
{
    m_listRate.clear();

    QVariantList listData;

    QString sError;

    bool bOk = ACTION.action(ACT::READ_EXCHANGE,listData,m_listRate,sError);

    if(!bOk || m_listRate.length()<1)
    {
        DMSG.showMsg("Error","匯率讀取失敗","OK");

        QVariantMap d;
        for(int i=0;i<m_listKey.length();i++)
        {
            setCell(i,0,0);

            d[m_listKey.at(i)]=0.0;
        }

        m_listRate.append(d);

        return ;
    }

    DataExchange data(m_listRate);

    setCell(0,0,data.last().NTD);
    setCell(1,0,data.last().HKD);
    setCell(2,0,data.last().RMB);
    setCell(3,0,data.last().MYR);
    setCell(4,0,data.last().SGD);

    //



    ui->tbHistory->setRowCount(0);

    DataExchange history(m_listRate);

    for(int i=0;i<history.m_listData.length();i++)
    {
        ui->tbHistory->setRowCount(i+1);

        DataExchange::Rate rate = history.m_listData.at(i);

        setHistoryCell(i,0,rate.Sid);
        setHistoryCell(i,1,QString::number(rate.NTD));
        setHistoryCell(i,2,QString::number(rate.HKD));
        setHistoryCell(i,3,QString::number(rate.RMB));
        setHistoryCell(i,4,QString::number(rate.MYR));
        setHistoryCell(i,5,QString::number(rate.SGD));
        QString sData = QDateTime::fromString(rate.UpdateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd hh:mm");
        setHistoryCell(i,6,sData);


    }




}



void LayerExchangeRate::on_btnSave_clicked()
{
    DataExchange tmpClass;

    QVariantMap data;

    QVariantList sendData;


    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        double d = getCell(i);

        data[m_listKey[i]] =d;
        QVariantMap tmp;
        tmp[m_listKey[i]] = d;
        sendData.append(tmp);
    }

    bool bIsDiff = GLOBAL.isDiff(m_listKey,m_listRate.last().toMap(),data);

    if(!bIsDiff)
    {
        DMSG.showMsg("","資料無變更","OK");
        return;
    }

    QString sError;

    bool bOk =ACTION.action(ACT::SAVE_EXCHANGE,sendData,sError);

    if(bOk)
        DMSG.showMsg("","匯率修改完成","OK");
    else
        DMSG.showMsg("Error","資料庫錯誤","OK");

    refresh();
}

void LayerExchangeRate::showEvent(QShowEvent *)
{
    refresh();
}

void LayerExchangeRate::setCell(int iRow,int iCol, double value)
{
    QDoubleSpinBox *w = new QDoubleSpinBox(this);
    w->setDecimals(3);
    w->setRange(0,999);
    w->setValue(0);
    w->setAlignment(Qt::AlignmentFlag::AlignCenter);

    w->setValue(value);

    if(iRow>= ui->tableWidget->rowCount())
        ui->tableWidget->setRowCount(iRow+1);

    if(iCol>= ui->tableWidget->columnCount())
        ui->tableWidget->setColumnCount(iCol+1);


    ui->tableWidget->setCellWidget(iRow,iCol,w);
}

void LayerExchangeRate::setHistoryCell(int iRow, int iCol, QString value)
{
    QTableWidgetItem *item = new QTableWidgetItem(value);
    item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
    ui->tbHistory->setItem(iRow,iCol,item);
}

double LayerExchangeRate::getCell(int iRow)
{
    double re = 0.00;

    if(iRow>= ui->tableWidget->rowCount())
        return re;

    QDoubleSpinBox *item = dynamic_cast<QDoubleSpinBox*>(ui->tableWidget->cellWidget(iRow,0));

    re =item ->value();

    return re;
}




void LayerExchangeRate::on_lineEdit_textChanged(const QString &arg1)
{
    return;
    //    QString sTemp = arg1;



    //    double d = sTemp.replace(",","").toDouble();

    //    const QLocale & cLocale = QLocale::c();

    //    QString ss = cLocale.toString(d, 'f');

    //    ss.replace(cLocale.groupSeparator(), ",");

    //    ss.replace(cLocale.decimalPoint(), ".");

    //    ui->lineEdit->setText(ss);

    //   return ;

    QString st =arg1;


    if(st.length()<1)
    {
        st="0";
    }

    if(!st.contains('.'))
    {
        st+=".00";
    }

    QString sNumber;

    QString sSub;


    sNumber = st.split('.').first();

    sSub = st.split('.').last();


    sNumber.replace(',',"");

    if(sNumber.length()>3)
    {
        sNumber = sNumber.insert(sNumber.length()-3,',');

        if(sNumber.length()>7)
        {
            sNumber = sNumber.insert(sNumber.length()-7,',');
        }

    }



    static QString sStrPre;
    sStrPre = sNumber;
    if(sSub!="")
        sStrPre+="."+sSub;

    ui->lineEdit->setText(sStrPre);
}



