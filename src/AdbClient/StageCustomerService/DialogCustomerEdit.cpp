#include "DialogCustomerEdit.h"
#include "ui_DialogCustomerEdit.h"

DialogCustomerEdit::DialogCustomerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomerEdit)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);

    this->setWindowTitle(" ");

    ui->tbGameList->setColumnWidth(0,56);


    ui->btnDel->hide();
}

DialogCustomerEdit::~DialogCustomerEdit()
{
    delete ui;
}

void DialogCustomerEdit::setCb(QVariantList listClass, QVariantList listGame)
{

    m_listClass = listClass;

    m_listGame = listGame;

    ui->cbClass->clear();

    ui->cbClass->addItems(mapToList(m_listClass,"Name"));

    ui->cbGame->clear();

    ui->cbGame->addItems(mapToList(m_listGame,"Name"));

    m_lastPrimeRate=ACTION.primeRate("");

    ui->cbCurrency->clear();

    ui->cbCurrency->addItems(m_lastPrimeRate.listKey());
}

void DialogCustomerEdit::setData(QVariantList listClass, QVariantList listGame,QVariantList listCustomerInfo,QVariantMap data)
{


    setCb(listClass,listGame);

    m_data = data;

    QStringList tmpClass = mapToList(m_listClass,"Sid");

    int iCbClassIdx =qBound(0,tmpClass.indexOf(m_data["Class"].toString()),ui->cbClass->count()-1);
    ui->cbClass->setCurrentIndex(iCbClassIdx);

    ui->cbClass->setEnabled(false);

    ui->lbId->setText(m_data["Id"].toString());
    int vip = 0;
    if(m_data["Vip"]=="1")
        vip=1;
    ui->cbVip->setCurrentIndex(vip);
    ui->txName->setText(m_data["Name"].toString());

    ui->txNum5->setText(m_data["Num5"].toString());

    QString sCurrency = m_data["Currency"].toString();

    m_sOriginCurrency=sCurrency;

    int iCbIdx =qBound(0,m_lastPrimeRate.listKey().indexOf(sCurrency),ui->cbCurrency->count()-1);

    ui->cbCurrency->setCurrentIndex(iCbIdx);

    ui->cbCurrency->setEnabled(false);

    //    ui->txPayType->setText(m_data["PayType"].toString());

    //    ui->txPayInfo->setText(m_data["PayInfo"].toString());

    ui->txNote1->setText(m_data["Note1"].toString());

    ui->btnDel->show();

    m_listCustomerInfo =listCustomerInfo;

    refresh();

    if(ui->tbGameList->rowCount()>0)
    {

        ui->tbGameList->setCurrentCell(0,1);
        on_tbGameList_cellClicked(0,1);
    }

}

void DialogCustomerEdit::setData(QString sCustomerSid)
{
    m_sCustomerSid = sCustomerSid;

    QVariantMap tmp,outCustomer;
    tmp["Sid"] = sCustomerSid;
    QString sError;
    ACTION.action(ACT::QUERY_CUSTOMER,tmp,outCustomer,sError);


    QVariantMap in;
    QVariantList outClass,outGame,outCustomerInfo;



    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    in["CustomerSid"] = m_sCustomerSid;

    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,outCustomerInfo,sError);

    setData(outClass,outGame,outCustomerInfo,outCustomer);


}

void DialogCustomerEdit::setReadOnly(bool bReadOnly)
{
    bool bEnable =!bReadOnly;

    ui->wBottom->setVisible(bEnable);

    ui->wGameItemArea->setVisible(bEnable);

    ui->cbClass->setEnabled(bEnable);
    ui->cbCurrency->setEnabled(bEnable);
    ui->cbGame->setEnabled(bEnable);

    ui->cbVip->setEnabled(bEnable);
    ui->txName->setReadOnly(!bEnable);
    ui->txNote1->setReadOnly(!bEnable);

    ui->txLoginType->setReadOnly(!bEnable);
    ui->txGameAccount->setReadOnly(!bEnable);
    ui->txPassword->setReadOnly(!bEnable);
    ui->txChr->setReadOnly(!bEnable);
    ui->txServer->setReadOnly(!bEnable);
    ui->txNum5->setReadOnly(!bEnable);

    ui->tbGameList->hideColumn(0);

    ui->lbTitle->setText("客戶詳細資料");


}

QVariantMap DialogCustomerEdit::data()
{
    QVariantMap re;

    m_data["Id"] = ui->lbId->text().trimmed();

    m_data["Name"] = ui->txName->text().trimmed();

    m_data["Num5"] = ui->txNum5->text().trimmed();

    m_data["Vip"]="0";

    if(ui->cbVip->currentIndex()==1)
        m_data["Vip"]="1";


    //    m_data["PayType"] = ui->txPayType->text().trimmed();

    //    m_data["PayInfo"] = ui->txPayInfo->text().trimmed();

    int iClassIdx =qBound(0,ui->cbClass->currentIndex(),m_listClass.length()-1);

    m_data["Class"] = mapToList(m_listClass,"Sid").at(iClassIdx);

    QString sCurrency = ui->cbCurrency->currentText();

    m_data["Currency"] = sCurrency;

    m_data["Note1"] = ui->txNote1->toPlainText();

    re = m_data;


    return re;
}

QVariantList DialogCustomerEdit::dataGameInfo(QString sCustomerSid)
{

    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        QVariantMap d =m_listCustomerInfo[i].toMap();

        d["CustomerSid"]=sCustomerSid;

        m_listCustomerInfo[i] = d;

    }


    return m_listCustomerInfo;
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
/*
QString DialogCustomerEdit::checkId(int cbIdx)
{
    QString sId="";

    QString sClassSid = m_listClass.at(cbIdx).toMap()["Sid"].toString();
    QString sClassId  = m_listClass.at(cbIdx).toMap()["Id"].toString();

    QVariantMap in,out;

    in["Class"] = sClassSid;
    in["ClassId"] = sClassId;

    QString sError;

    ACTION.action(ACT::LAST_CUSTOMER_ID,in,out,sError);

    QString sLastId  = out["Id"].toString();

    QString sTargetWord="EA";
    QString sTargetNum="01";


    if(sLastId.length()>=4)
    {


        QString sTmp = sLastId.mid(sLastId.length()-4,4);


        QString sWord = sTmp.mid(0,2);

        QString sNum=sTmp.mid(2,2);

        if(sNum=="99")
        {
            sTargetNum="01";

            sTargetWord = strAdd1(sWord);

        }
        else
        {
            sTargetWord = sWord;
            sTargetNum=QString("%1").arg(sNum.toInt()+1,2,10,QLatin1Char('0'));
        }
    }
    sId = sClassId.toUpper()+"-"+sTargetWord.toUpper()+sTargetNum;


    return sId;



}

QString DialogCustomerEdit::strAdd1(QString st)
{

    if(st.length()!=2)
        return st;

    QString sRe0,sRe1;


    QString sFirst=st.at(0);
    QString sSecond =st.at(1);
    if(sSecond.toUpper()=="Z")
    {
        sRe1="A";

        int iTmp = (int)sFirst.toUtf8().at(0)+1;

        QByteArray d;
        d.append(iTmp);

        sRe0=QString(d);


    }
    else
    {
        sRe0=sFirst;

        int iTmp = (int)sSecond.toUtf8().at(0)+1;

        QByteArray d;
        d.append(iTmp);

        sRe1=QString(d);

    }


    return sRe0+sRe1;
}
*/
void DialogCustomerEdit::refresh()
{
    ui->tbGameList->setRowCount(0);

    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        QVariantMap data = m_listCustomerInfo.at(i).toMap();

        //        if(data["CustomerId"]!="" && data["CustomerId"]!=ui->lbId->text().trimmed())
        //        {
        //            continue;
        //        }

        if( data["CustomerSid"].toString()!="" && data["CustomerSid"].toString()!=m_sCustomerSid)
        {
            continue;
        }
        int iIdx = ui->tbGameList->rowCount();

        ui->tbGameList->setRowCount(ui->tbGameList->rowCount()+1);


        QString sGameName =gameToName(data["GameSid"].toString());
        ui->tbGameList->setItem(iIdx,0,UI.tbItem("移除"));

        ui->tbGameList->setItem(iIdx,1,UI.tbItem(sGameName));

        ui->tbGameList->setItem(iIdx,2,UI.tbItem(data["LoginAccount"].toString()));

        ui->tbGameList->setItem(iIdx,3,UI.tbItem(data["Characters"].toString()));

        ui->tbGameList->setItem(iIdx,4,UI.tbItem(data["LoginPassword"].toString()));

        ui->tbGameList->setItem(iIdx,5,UI.tbItem(data["ServerName"].toString()));

        ui->tbGameList->setItem(iIdx,6,UI.tbItem(data["LoginType"].toString()));


    }


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





void DialogCustomerEdit::on_btnAddGame_clicked()
{
    QVariantMap data;

    data["CustomerId"]="";

    data["CustomerSid"]=m_sCustomerSid;

    data["GameSid"] = gameToSid(ui->cbGame->currentText().trimmed());

    data["LoginType"] = ui->txLoginType->text().trimmed();

    data["LoginAccount"] = ui->txGameAccount->text().trimmed();

    data["LoginPassword"] = ui->txPassword->text().trimmed();

    data["ServerName"] =ui->txServer->text().trimmed();

    data["Characters"] = ui->txChr->text().trimmed();

    m_listCustomerInfo.append(data);

    refresh();


    return;


}



void DialogCustomerEdit::on_tbGameList_cellClicked(int row, int col)
{

    qDebug()<<"irow : "<<row;

    if(row >=m_listCustomerInfo.length() || row<0 )
    {
        return;
    }

    if(col==0)
    {
        QVariantMap d = m_listCustomerInfo.at(row).toMap();

        if(d["Sid"]!="")
            m_listDeleteInfo.append(d);

        m_listCustomerInfo.removeAt(row);
        qDebug()<<m_listCustomerInfo.length();
        refresh();

    }
    else
    {


        ui->cbGame->setCurrentText(ui->tbGameList->item(row,1)->text());
        ui->txGameAccount->setText(ui->tbGameList->item(row,2)->text());
        ui->txChr->setText(ui->tbGameList->item(row,3)->text());
        ui->txPassword->setText(ui->tbGameList->item(row,4)->text());
        ui->txServer->setText(ui->tbGameList->item(row,5)->text());
        ui->txLoginType->setText(ui->tbGameList->item(row,6)->text());


    }
}


void DialogCustomerEdit::on_cbClass_currentIndexChanged(int index)
{
    if(index<0 || index>=m_listClass.length())
    {
        return;
    }

    QString sId;

    bool bOk = ACTION.getNewCustomerId(sId);

    if(!bOk)
        return;

    QString sClassId  = m_listClass.at(index).toMap()["Id"].toString();

    ui->lbId->setText(sClassId+"-"+sId);
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


    QString customerId= ui->lbId->text();

    if(m_sCustomerSid=="")
    {
        QVariantMap in;

        in["Id"]=customerId;

        QVariantList out;
        QString sError;
        bool bOk = ACTION.action(ACT::QUERY_CUSTOMER,in,out,sError);


        if(!bOk)
        {
            DMSG.showMsg("","讀取資料錯誤。","OK");
            return;
        }
        else
        {
            if(out.length()>0)
            {
                DMSG.showMsg("","編號: "+customerId.split("_").last()+"已經被使用,\n已更新編號，請再試一次","OK");

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
            d["CustomerId"] =ui->lbId->text().trimmed();

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

