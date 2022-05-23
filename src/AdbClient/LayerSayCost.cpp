#include "LayerSayCost.h"
#include "ui_LayerSayCost.h"

LayerSayCost::LayerSayCost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSayCost)
{
    ui->setupUi(this);

    ui->tbGameItem->setColumnWidth(0,60);
    ui->tbInfo->setColumnWidth(0,60);
    ui->tbInfo->setColumnWidth(1,200);
    ui->tbInfo->setColumnWidth(2,60);

    //        label->setText(
    //                                       QObject::tr("<font color = red>%1</font>").arg("abc"))+
    //                                       QObject::tr("<font color = blue>%1</font>").arg("efg")+
    //                                       "hij"
    //                                       );

}

LayerSayCost::~LayerSayCost()
{
    delete ui;
}

void LayerSayCost::orderMode()
{
    ui->lbTitle->setText("訂單");

    ui->btnOk->setText("送出訂單");
}

void LayerSayCost::setCustomer(QVariantMap data)
{
    m_dataCustomer = data;

    qDebug()<<"customer : "<<m_dataCustomer;

    ui->lbId->setText(m_dataCustomer["Id"].toString());

    ui->lbName->setText(m_dataCustomer["Name"].toString());

    QString sCurrency = "新台幣";
    if(m_dataCustomer["Currency"]=="HKD")
        sCurrency = "港幣";
    else if(m_dataCustomer["Currency"]=="RMB")
        sCurrency = "人民幣";
    else if(m_dataCustomer["Currency"]=="MYR")
        sCurrency = "林吉特";
    else if(m_dataCustomer["Currency"]=="SGD")
        sCurrency = "新加坡元";

    ui->lbCurrency->setText(sCurrency);

    QVariantMap d;

    d["CustomerId"] = m_dataCustomer["Id"];

    QString sError;

    ACTION.action(ACT::QUERY_GAME_INFO,d,m_listGameInfo,sError);

    QStringList cbName;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap tmp = m_listGameInfo.at(i).toMap();

        QString sName= DATA.getGameName(tmp["GameSid"].toString());

        if(cbName.indexOf(sName)<0)
            cbName.append(sName);
    }

    ui->cbGame->clear();

    ui->cbGame->addItems(cbName);


}

void LayerSayCost::showEvent(QShowEvent *)
{
    QString sDate = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");
    ui->lbTime->setText(sDate);

    QString sError;

    QVariantMap v;
    ACTION.action(ACT::QUERY_GAME_ITEM,v,m_listGameItem,sError);

    refreshInfo();
}

void LayerSayCost::refreshInfo()
{
    ui->tbInfo->setRowCount(0);

    for(int i=0;i<m_listInto.length();i++)
    {
        int iIdx = ui->tbInfo->rowCount();

        ui->tbInfo->setRowCount(iIdx+1);

        QVariantMap data = m_listInto.at(i).toMap();

        ui->tbInfo->setItem(iIdx,0,UI.tbItem("移除",true));

        ui->tbInfo->setItem(iIdx,1,UI.tbItem(data["Name"],false));


        QSpinBox *sp = new QSpinBox(this);

        sp->setRange(1,99);

        sp->setAlignment(Qt::AlignCenter);

        sp->setFont(UI.font());

        sp->setValue(data["Count"].toInt());

        QObject::connect(sp,SIGNAL(valueChanged(int)),this,SLOT(spValue(int)));
        ui->tbInfo->setCellWidget(iIdx,2,sp);
    }

    checkTotal();
}

double LayerSayCost::checkTotal()
{
    double re = 0;

     DataExchange::Rate rate = DATA.rate();



    for(int i=0;i<ui->tbInfo->rowCount();i++)
    {
        QSpinBox *sp =dynamic_cast<QSpinBox*>(ui->tbInfo->cellWidget(i,2));

        double iPrice =sp->value();

        double r = m_listInto.at(i).toMap()["NTD"].toDouble();


        if(m_dataCustomer["Currency"]=="HKD")
        {
            r = r/rate.NTD*rate.HKD;

        }

        else if(m_dataCustomer["Currency"]=="RMB")
             r = r/rate.NTD*rate.RMB;
        else if(m_dataCustomer["Currency"]=="MYR")
             r = r/rate.NTD*rate.MYR;
        else if(m_dataCustomer["Currency"]=="SGD")
             r = r/rate.NTD*rate.SGD;


        double cost = r* iPrice;


        re=re+cost;
        ui->tbInfo->setItem(i,3,UI.tbItem(cost));
    }

    ui->lbTotal->setText(QString::number(re,'f',2));
    //    DATA.rate()


    return re;
}



void LayerSayCost::on_btnSayCostBack_clicked()
{
    emit back();
}

void LayerSayCost::spValue(int i)
{
    qDebug()<<"tb row "<<ui->tbInfo->currentRow()<<" , sp : "<<i;
    checkTotal();

}


void LayerSayCost::on_cbGame_currentTextChanged(const QString &arg1)
{
    m_sCurrentGameSid = DATA.getGameId(arg1);

    ui->lbGameName->setText(arg1);

    QStringList cbAcc;

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap d = m_listGameInfo.at(i).toMap();

        if(d["GameSid"].toString() == m_sCurrentGameSid
                &&cbAcc.indexOf(d["LoginAccount"].toString())<0)
        {
            cbAcc.append(d["LoginAccount"].toString());
        }
    }

    ui->cbAccount->clear();

    ui->cbAccount->addItems(cbAcc);

    QVariantMap v;

    v["GameSid"] = m_sCurrentGameSid;

    v["Enable"] =1;


    QString sError;

    ACTION.action(ACT::QUERY_GAME_ITEM,v,m_listGameItem,sError);

    ui->tbGameItem->setRowCount(0);

    for(int i=0;i<m_listGameItem.length();i++)
    {
        int iRow = ui->tbGameItem->rowCount();

        ui->tbGameItem->setRowCount(iRow+1);

        QVariantMap dItem = m_listGameItem.at(i).toMap();

        ui->tbGameItem->setItem(iRow,1,UI.tbItem(dItem["Name"]));

        ui->tbGameItem->setItem(iRow,0,UI.tbItem("加入",true));

    }

}


void LayerSayCost::on_cbAccount_currentTextChanged(const QString &arg1)
{
    ui->lbGameAccount->setText(arg1);

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap d = m_listGameInfo.at(i).toMap();

        if(d["GameSid"].toString() == m_sCurrentGameSid &&
                d["LoginAccount"].toString() == arg1)
        {
            ui->lbLoginType->setText(d["LoginType"].toString());

            ui->lbServer->setText(d["ServerName"].toString());

            ui->lbChr->setText(d["Character"].toString());


        }
    }
}


void LayerSayCost::on_tbGameItem_cellClicked(int row, int column)
{
    if(column!=0)
        return;


    QString sItemName = ui->tbGameItem->item(row,1)->text();

    for(int i=0;i<m_listGameItem.length();i++)
    {
        QVariantMap data = m_listGameItem.at(i).toMap();

        if(data["Name"] != sItemName)
            continue;

        if(DATA.mapping(m_listInto,"Sid",data["Sid"].toString())<0)
        {
            data["Count"] = 1;
            m_listInto.append(data);

        }
        else
        {
            int iCurrentCount = m_listInto.at(row).toMap()["Count"].toInt();
            data["Count"] =iCurrentCount+1;
            m_listInto[row] = data;

        }


        refreshInfo();
    }


    return;
    if(row>=0 && row<m_listGameItem.length())
    {

        QVariantMap data = m_listGameItem.at(row).toMap();

        qDebug()<<"data : "<<data;

        if(DATA.mapping(m_listInto,"Sid",data["Sid"].toString())<0)
        {
            data["Count"] = 1;
            m_listInto.append(data);

        }
        else
        {
            int iCurrentCount = m_listInto.at(row).toMap()["Count"].toInt();
            data["Count"] =iCurrentCount+1;
            m_listInto[row] = data;

        }


        refreshInfo();
    }



}


void LayerSayCost::on_tbInfo_cellPressed(int row, int column)
{
    qDebug()<<row<<" , "<<column;
    if(column==0 && row>=0 && row<m_listInto.length())
    {
        m_listInto.removeAt(row);

        refreshInfo();
    }
}

