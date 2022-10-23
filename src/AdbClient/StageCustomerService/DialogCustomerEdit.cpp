#include "DialogCustomerEdit.h"
#include "ui_DialogCustomerEdit.h"

DialogCustomerEdit::DialogCustomerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCustomerEdit)
{
    ui->setupUi(this);

    this->setWindowTitle("客戶資料設定");

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
    m_listRateKey.clear();
    m_listRateKey = ACTION.listRate("",true).last().listKey();
    m_listRateKey.push_front("新台幣(NTD)");
    ui->cbCost->clear();

    ui->cbCost->addItems(m_listRateKey);
}

void DialogCustomerEdit::setData(QVariantList listClass, QVariantList listGame,QVariantList listGameInfo,QVariantMap data)
{


    setCb(listClass,listGame);

    m_data = data;

    QStringList tmpClass = mapToList(m_listClass,"Sid");

    int iCbClassIdx =qBound(0,tmpClass.indexOf(m_data["Class"].toString()),ui->cbClass->count()-1);
    ui->cbClass->setCurrentIndex(iCbClassIdx);

    ui->cbClass->setEnabled(false);

    ui->lbId->setText(m_data["Id"].toString());

    ui->txName->setText(m_data["Name"].toString());

    QString sCurrency = m_data["Currency"].toString();

    int iCbIdx =qBound(0,m_listRateKey.indexOf(sCurrency),ui->cbCost->count()-1);

    ui->cbCost->setCurrentIndex(iCbIdx);

//    ui->txPayType->setText(m_data["PayType"].toString());

//    ui->txPayInfo->setText(m_data["PayInfo"].toString());

    ui->txNote1->setText(m_data["Note1"].toString());

    ui->btnDel->show();

    m_listGameInfo = listGameInfo;




    refresh();

}

QVariantMap DialogCustomerEdit::data()
{
    QVariantMap re;

    m_data["Id"] = ui->lbId->text().trimmed();

    m_data["Name"] = ui->txName->text().trimmed();

//    m_data["PayType"] = ui->txPayType->text().trimmed();

//    m_data["PayInfo"] = ui->txPayInfo->text().trimmed();

    int iClassIdx =qBound(0,ui->cbClass->currentIndex(),m_listClass.length()-1);

    m_data["Class"] = mapToList(m_listClass,"Sid").at(iClassIdx);

    QString sCurrency = ui->cbCost->currentText();

    m_data["Currency"] = sCurrency;

    m_data["Note1"] = ui->txNote1->toPlainText();

    re = m_data;


    return re;
}

QVariantList DialogCustomerEdit::dataGameInfo()
{
    return m_listGameInfo;
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

    if(sLastId.length()>=4)
    {
        QString sTmp = sLastId.mid(sLastId.length()-4,4);

        QString sSecond = sTmp.mid(1,3);

        QString sFirst = sTmp.mid(0,1);

        if(sSecond.toInt()<999)
        {
            QString sNum = QString("%1").arg(sSecond.toInt()+1,3,10,QLatin1Char('0'));

            sId = sClassId+"-"+sFirst+sNum;
        }
        else
        {


            sFirst=QChar::fromLatin1(sFirst.at(0).toLatin1()+1);

            sId = sClassId+"-"+sFirst+"001";
        }

    }

    return sId;
}

void DialogCustomerEdit::refresh()
{
    ui->tbGameList->setRowCount(0);

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap data = m_listGameInfo.at(i).toMap();

        if(data["CustomerId"]!="" && data["CustomerId"]!=ui->lbId->text().trimmed())
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

        ui->tbGameList->setItem(iIdx,4,UI.tbItem(data["ServerName"].toString()));

        ui->tbGameList->setItem(iIdx,5,UI.tbItem(data["LoginType"].toString()));


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

    data["GameSid"] = gameToSid(ui->cbGame->currentText().trimmed());

    data["LoginType"] = ui->txLoginType->text().trimmed();

    data["LoginAccount"] = ui->txGameAccount->text().trimmed();

    data["ServerName"] =ui->txServer->text().trimmed();

    data["Characters"] = ui->txChr->text().trimmed();

    m_listGameInfo.append(data);

    refresh();


    return;

    /*
    int iIdx = ui->cbGame->currentIndex();

    if(iIdx<0 || iIdx>=m_listGame.length())
        return;

    QVariantMap dataGame = m_listGame.at(iIdx).toMap();

    QString sName = dataGame["Name"].toString();



    QVariantMap data;

    data["GameSid"] = dataGame["Sid"];

    m_listGameInfo.append(data);

    int iRowCount = ui->tbGameList->rowCount();
    ui->tbGameList->setRowCount(iRowCount+1);

    QPushButton *btn = new QPushButton(this);
    btn->setMaximumWidth(52);
    btn->setText("移除");

    m_btns.addButton(btn);

    ui->tbGameList->setItem(iRowCount,0,UI.tbItem(sName));

     ui->tbGameList->setCellWidget(iRowCount,1,btn);
     */
}



void DialogCustomerEdit::on_tbGameList_cellClicked(int row, int col)
{
    if(row >=m_listGameInfo.length() || row<0 )
    {
        return;
    }

    if(col==0)
    {
        QVariantMap d = m_listGameInfo.at(row).toMap();

        if(d["Sid"]!="")
            m_listDeleteInfo.append(d);

        m_listGameInfo.removeAt(row);

        refresh();

    }
    else
    {


        ui->cbGame->setCurrentText(ui->tbGameList->item(row,1)->text());
        ui->txGameAccount->setText(ui->tbGameList->item(row,2)->text());
        ui->txChr->setText(ui->tbGameList->item(row,3)->text());
        ui->txServer->setText(ui->tbGameList->item(row,4)->text());
        ui->txLoginType->setText(ui->tbGameList->item(row,5)->text());


    }
}


void DialogCustomerEdit::on_cbClass_currentIndexChanged(int index)
{
    if(index<0 || index>=m_listClass.length())
    {
        return;
    }

    ui->lbId->setText(checkId(index));

}


void DialogCustomerEdit::on_btnOk_clicked()
{

    for(int i=0;i<m_listGameInfo.length();i++)
    {
        QVariantMap d = m_listGameInfo.at(i).toMap();

        if(d["CustomerId"]=="")
        {
            d["CustomerId"] =ui->lbId->text().trimmed();

            m_listGameInfo[i] = d;
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
        m_listDeleteInfo = m_listGameInfo;
        done(3);
    }
}

