#include "DialogCustomerEdit.h"
#include "ui_DialogCustomerEdit.h"

DialogCustomerEdit::DialogCustomerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomerEdit)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

    this->setWindowTitle(" ");


    ui->btnDel->hide();

    ui->txId->setReadOnly(true);

    ui->stackedWidget_2->setCurrentWidget(ui->page);
}

DialogCustomerEdit::~DialogCustomerEdit()
{
    delete ui;
}

void DialogCustomerEdit::setCb(QVariantList listClass, QVariantList listGame)
{

    ui->page->setCb(listGame);

    m_listClass = listClass;

    m_listGame = listGame;

    ui->cbClass->clear();

    ui->cbClass->addItems(mapToList(m_listClass,"Name"));

    m_lastPrimeRate=DATA.primeRate("");

    ui->cbCurrency->clear();

    ui->cbCurrency->addItems(m_lastPrimeRate.listKey());
}

bool DialogCustomerEdit::checkHasChange()
{
    bool bRe = false;
    QVariantMap d =data();

    QStringList listKey = d.keys();


    for(int i=0;i<listKey.length();i++)
    {
        QString sKey=listKey.at(i);

        if(d[sKey].toString().trimmed()!=m_originData[sKey].toString().trimmed())
        {

            bRe = true;
        }
    }

    return bRe;
}

void DialogCustomerEdit::setRoot(bool b)
{
    m_bIsRoot = b;

    ui->txId->setReadOnly(!b);
}

void DialogCustomerEdit::setData(QVariantList listClass, QVariantList listGame,QVariantList listCustomerInfo,QVariantMap data)
{


    setCb(listClass,listGame);

    m_data = data;

    QStringList tmpClass = mapToList(m_listClass,"Sid");

    int iCbClassIdx =qBound(0,tmpClass.indexOf(m_data["Class"].toString()),ui->cbClass->count()-1);
    ui->cbClass->setCurrentIndex(iCbClassIdx);

    ui->cbClass->setEnabled(false);

    ui->txId->setText(m_data["Id"].toString());
    int vip = 0;
    if(m_data["Vip"]=="1")
        vip=1;
    ui->cbVip->setCurrentIndex(vip);
    ui->txName->setText(m_data["Name"].toString());

    ui->txLine->setText(m_data["Line"].toString());

    ui->txNum5->setText(m_data["Num5"].toString());

    QString sCurrency = m_data["Currency"].toString();

    m_sOriginCurrency=sCurrency;

    int iCbIdx =qBound(0,m_lastPrimeRate.listKey().indexOf(sCurrency),ui->cbCurrency->count()-1);

    ui->cbCurrency->setCurrentIndex(iCbIdx);

    ui->cbCurrency->setEnabled(false);

    //    ui->txPayType->setText(m_data["PayType"].toString());

    //    ui->txPayInfo->setText(m_data["PayInfo"].toString());

    QString sNote = m_data["Note1"].toString();

    if(sNote=="_")
        sNote="";

    ui->txNote1->setText(sNote);


    ui->btnDel->setVisible(m_bIsRoot);

    m_listCustomerInfo =listCustomerInfo;

    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        QVariantMap d = m_listCustomerInfo[i].toMap();
        if(d["LastTime"].toString().trimmed()=="")
        {
            d["LastTime"]="20230227000000";  //for old version
        }
          d["UpdateTime"] = d["LastTime"];
        m_listCustomerInfo[i] = d;
    }



    if(m_sCustomerSid!="")
    {
        QVariantMap in;
        QVariantList out;
        QString sError;
        in["CustomerSid"]=m_sCustomerSid;

        QString sDate=GLOBAL.dateTimeUtc8().addDays(-3).toString("yyyyMMdd");
        in["OrderDate >"]=sDate;
        in["ASC"]="OrderDate";

        ACTION.action(ACT::QUERY_ORDER,in,out,sError,true);

        if(out.length()>0)
        {
            m_bHasHistoryOrder = true;
            OrderData order(out.last().toMap());
            m_lastOrderDate=order.OrderDate+order.OrderTime;
        }

    }

}

void DialogCustomerEdit::setData(QString sCustomerSid)
{
    m_sCustomerSid = sCustomerSid;

    QVariantMap tmp,outCustomer;
    tmp["Sid"] = sCustomerSid;
    QString sError;
    ACTION.action(ACT::QUERY_CUSTOMER,tmp,outCustomer,sError);
    m_originData = outCustomer;

    QVariantMap in;
    QVariantList outClass,outGame,outCustomerInfo;



    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    in["CustomerSid"] = m_sCustomerSid;

    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,outCustomerInfo,sError);


    CustomerData cus(outCustomer);

    ui->page->setCustomer(m_sCustomerSid,cus.Id);

    ui->page->m_bAddMode = false;
    setData(outClass,outGame,outCustomerInfo,outCustomer);


}

void DialogCustomerEdit::setAddMode()
{
    m_bIsAdd = true;
//    ui->lbId->hide();
//    ui->txId->hide();
}

void DialogCustomerEdit::setReadOnly(bool bReadOnly)
{
    bool bEnable =!bReadOnly;

    ui->wBottom->setVisible(bEnable);


    ui->cbClass->setEnabled(bEnable);
    ui->cbCurrency->setEnabled(bEnable);

    ui->cbVip->setEnabled(bEnable);
    ui->txName->setReadOnly(!bEnable);
    ui->txNote1->setReadOnly(!bEnable);


    ui->txNum5->setReadOnly(!bEnable);
    ui->txLine->setReadOnly(!bEnable);

    ui->lbTitle->setText("客戶詳細資料");

    ui->page->setReadOnly(bReadOnly);
}

QVariantMap DialogCustomerEdit::data()
{
    QVariantMap re;

    m_data["Id"] = ui->txId->text().trimmed();

//    if(m_bIsAdd)
//        m_data["Id"]="";


    m_data["Name"] = ui->txName->text().trimmed();

    m_data["Num5"] = ui->txNum5->text().trimmed();
    m_data["Line"] = ui->txLine->text().trimmed();
    m_data["Vip"]="0";

    if(ui->cbVip->currentIndex()==1)
        m_data["Vip"]="1";


    //    m_data["PayType"] = ui->txPayType->text().trimmed();

    //    m_data["PayInfo"] = ui->txPayInfo->text().trimmed();

    int iClassIdx =qBound(0,ui->cbClass->currentIndex(),m_listClass.length()-1);

    m_data["Class"] = mapToList(m_listClass,"Sid").at(iClassIdx);

    QString sCurrency = ui->cbCurrency->currentText();

    m_data["Currency"] = sCurrency;
    QString sTmp=ui->txNote1->toPlainText();

    if(sTmp.trimmed().length()<1)
        sTmp="_";

    m_data["Note1"] = sTmp;

    re = m_data;


    return re;
}

QVariantList DialogCustomerEdit::dataGameInfo(QString sCustomerSid)
{
   return ui->page->queeList(sCustomerSid);
    /*
    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        QVariantMap d =m_listCustomerInfo[i].toMap();

        d["CustomerSid"]=sCustomerSid;

        if(d["UpdateTime"].toString().trimmed()=="")
            d["LastTime"] = GLOBAL.dateTimeUtc8().toString("yyyyMMddhhmmss");

        m_listCustomerInfo[i] = d;

    }


    return m_listCustomerInfo;
    */
}

QVariantList DialogCustomerEdit::deleteGameInfo()
{
    return m_listDeleteInfo;
}

QStringList DialogCustomerEdit::mapToList(QVariantList list, QString sKey)
{
    QStringList listRe;

    foreach(QVariant v ,list)
    {
        listRe.append(v.toMap()[sKey].toString());


    }

    return listRe;
}



QString DialogCustomerEdit::gameToName(QString sSid)
{
    QString sRe="";

    for(int i=0;i<m_listGame.length();i++)
    {
        QVariantMap data = m_listGame.at(i).toMap();
        if(sSid == data["Sid"].toString())
        {
            sRe = data["Name"].toString();

            break;
        }
    }

    return sRe;

}

QString DialogCustomerEdit::gameToSid(QString sName)
{
    QString sRe="";

    for(int i=0;i<m_listGame.length();i++)
    {
        QVariantMap data = m_listGame.at(i).toMap();
        if(sName == data["Name"].toString())
        {
            sRe = data["Sid"].toString();

            break;
        }
    }

    return sRe;

}





void DialogCustomerEdit::on_cbClass_currentIndexChanged(int index)
{

    qDebug()<<"aaaddd:"<<index;

    if(index<0 || index>=m_listClass.length())
    {
        return;
    }

    QString sId;

    bool bOk = ACTION.getNewCustomerId(sId);


    if(!bOk)
        return;

    QString sClassId  = m_listClass.at(index).toMap()["Id"].toString();

    ui->txId->setText(sClassId+"-"+sId);
    qDebug()<<sClassId+"-"+sId;
}


void DialogCustomerEdit::on_btnOk_clicked()
{


    if(!ui->txName->isReadOnly() && ui->txName->text().trimmed()=="")
    {
        DMSG.showMsg("","客户名稱不能空白","OK");
        return;
    }


    if(m_sOriginCurrency!=ui->cbCurrency->currentText())
    {

        // todo
        /*
        int iRet =DMSG.showMsg("","確定要轉換幣別，餘額將以當前成本匯率轉換，是否繼續？",QStringList()<<"否"<<"是");

        if(iRet!=1)
            return;

        int iIdx =qBound(0,ui->cbCurrency->currentIndex(),m_lastPrimeRate.listValue().length()-1);

        double iOriginRate = m_lastPrimeRate.listValue().at(iIdx).toDouble();

        double money =CustomerData(m_data).Money.toDouble();

        m_data["Money"] = money/iOriginRate;
        */

    }


    QString customerId= ui->txId->text();

    if(m_sCustomerSid=="" && !m_bIsRoot)
    {
        QVariantMap in;

        in["Id"]=customerId;

        QVariantList out;
        QString sError;
        bool bOk;
        bOk= ACTION.action(ACT::QUERY_CUSTOMER,in,out,sError);


        if(!bOk)
        {
            DMSG.showMsg("","讀取資料錯誤。","OK");
            return;
        }
        else
        {
            if(out.length()>0)
            {
                DMSG.showMsg("","編號: "+customerId.split("-").last()+"已經被使用,\n已更新編號，請再試一次","OK");

                on_cbClass_currentIndexChanged(ui->cbClass->currentIndex());

                return;
            }

        }
    }



    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        QVariantMap d = m_listCustomerInfo.at(i).toMap();

        if(d["CustomerId"]=="")
        {
            d["CustomerId"] =ui->txId->text().trimmed();

            m_listCustomerInfo[i] = d;
        }
    }

    done(1);
}


void DialogCustomerEdit::on_btnCancel_clicked()
{
    reject();
}


void DialogCustomerEdit::on_btnDel_clicked()
{
    if(1==UI.showMsg("","確定要刪除此客戶資料嗎？",QStringList()<<"否"<<"是"))
    {
        m_listDeleteInfo = m_listCustomerInfo;
        done(3);
    }
}

