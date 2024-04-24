#include "LayerCustomerGameEdit.h"
#include "ui_LayerCustomerGameEdit.h"

LayerCustomerGameEdit::LayerCustomerGameEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomerGameEdit)
{
    ui->setupUi(this);

    ui->tbCusGameInfo->setColumnWidth(0,56);


    connect(ui->btnAdd,&QPushButton::clicked,this,&LayerCustomerGameEdit::slotAdd);
    connect(ui->btnChange,&QPushButton::clicked,this,&LayerCustomerGameEdit::slotChange);
}

LayerCustomerGameEdit::~LayerCustomerGameEdit()
{
    delete ui;
}

void LayerCustomerGameEdit::setCustomer(QString sSid, QString sId)
{
    m_sCustomerSid = sSid;

    m_sCustomerId = sId;

    QVariantMap in;

    QString sError;

    QVariantList outGame,outCustomerInfo;

    //    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    //    setCb(outGame);
    in["CustomerSid"] = m_sCustomerSid;
    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,outCustomerInfo,sError);
    m_listCustomerInfo =outCustomerInfo;

    refresh();
}

void LayerCustomerGameEdit::setReadOnly(bool bReadOnly)
{
    bool bEnable =!bReadOnly;

    ui->wGameItemArea->setVisible(bEnable);
    ui->cbGame->setEnabled(bEnable);
    ui->txLoginType->setReadOnly(!bEnable);
    ui->txGameAccount->setReadOnly(!bEnable);
    ui->txPassword->setReadOnly(!bEnable);
    ui->txChr->setReadOnly(!bEnable);
    ui->txServer->setReadOnly(!bEnable);
    ui->tbCusGameInfo->hideColumn(0);

}


void LayerCustomerGameEdit::refresh()
{
    ui->tbCusGameInfo->setRowCount(0);

    for(int i=0;i<m_listCustomerInfo.length();i++)
    {
        CustomerGameInfo data(m_listCustomerInfo.at(i).toMap());


        if( data.CustomerSid!="" &&  data.CustomerSid!=m_sCustomerSid)
        {
            continue;
        }
        int iIdx = ui->tbCusGameInfo->rowCount();

        ui->tbCusGameInfo->setRowCount(ui->tbCusGameInfo->rowCount()+1);

        QString sGameName =DATA.getGameName(data.GameSid);


        ui->tbCusGameInfo->setItem(iIdx,0,UI.tbItem("移除"));

        ui->tbCusGameInfo->setItem(iIdx,1,UI.tbItem(sGameName));

        ui->tbCusGameInfo->setItem(iIdx,2,UI.tbItem(data.LoginAccount));

        ui->tbCusGameInfo->setItem(iIdx,3,UI.tbItem(data.Characters));

        ui->tbCusGameInfo->setItem(iIdx,4,UI.tbItem(data.LoginPassword));

        ui->tbCusGameInfo->setItem(iIdx,5,UI.tbItem(data.ServerName));

        ui->tbCusGameInfo->setItem(iIdx,6,UI.tbItem(data.LoginType));


    }
}

QVariantList LayerCustomerGameEdit::queeList(QString sCustomerSid)
{

    for( int i=0;i<m_listCustomerInfo.length();i++)
    {
        CustomerGameInfo d(m_listCustomerInfo.at(i).toMap());
        d.CustomerSid=sCustomerSid;

        m_listCustomerInfo[i] =d.data();
    }


    return m_listCustomerInfo;
}

void LayerCustomerGameEdit::setCb(QVariantList outGame)
{
    m_listGame = outGame;

    auto listGameName=[=](QString sKey)
    {
        QStringList listRe;

        foreach(QVariant v ,m_listGame)
        {
            listRe.append(v.toMap()[sKey].toString());

        }

        return listRe;
    };

    ui->cbGame->clear();


    ui->cbGame->addItems(listGameName("Name"));


}

void LayerCustomerGameEdit::on_tbCusGameInfo_cellClicked(int row, int col)
{
    qDebug()<<"irow : "<<row;

    if(row >=m_listCustomerInfo.length() || row<0 )
    {
        return;
    }

    if(col==0 && ui->tbCusGameInfo->item(row,0)->text()=="移除")
    {


        CustomerGameInfo data(m_listCustomerInfo.at(row).toMap());
        QString sGameName=ui->tbCusGameInfo->item(row,1)->text();
        int iRect =DMSG.showMsg("","請確認是否刪除客戶遊戲資料 : "+sGameName+" ？ ",QStringList()<<"否"<<"是");

        if(iRect!=1)
            return;

        QString sError;
        QVariantMap in;
        in["Sid"] =data.Sid;

        bool bOk;

        if(!m_bAddMode)
            bOk= ACTION.action(ACT::DEL_GAME_INFO,QVariantList()<<in,sError);
        else
            bOk=true;

        if(bOk)
        {
            m_listCustomerInfo.removeAt(row);

            refresh();
        }
        else
        {
            DMSG.showMsg("","刪除失敗","OK");
            return;
        }


    }
    else
    {


        ui->cbGame->setCurrentText(ui->tbCusGameInfo->item(row,1)->text());
        ui->txGameAccount->setText(ui->tbCusGameInfo->item(row,2)->text());
        ui->txChr->setText(ui->tbCusGameInfo->item(row,3)->text());
        ui->txPassword->setText(ui->tbCusGameInfo->item(row,4)->text());
        ui->txServer->setText(ui->tbCusGameInfo->item(row,5)->text());
        ui->txLoginType->setText(ui->tbCusGameInfo->item(row,6)->text());


    }
}

void LayerCustomerGameEdit::slotAdd()
{

    DataGameList select(m_listGame.at(ui->cbGame->currentIndex()).toMap());
    CustomerGameInfo data;

    data.CustomerSid = m_sCustomerSid;
    data.CustomerId = m_sCustomerId;
    data.GameSid=select.Sid;
    data.LoginType=ui->txLoginType->text();
    data.LoginAccount=ui->txGameAccount->text();
    data.LoginPassword=ui->txPassword->text();
    data.ServerName=ui->txServer->text();
    data.Characters=ui->txChr->text();

    QString sError;

    QVariantList listIn;
    listIn.append(data.data());

    bool bOk=false;

    if(!m_bAddMode)
    {
        bool b= ACTION.action(ACT::REPLACE_GAME_INFO,listIn,sError);

        if(b)
        {
            QVariantList out;
            QVariantMap in;
            in["CustomerSid"] = m_sCustomerSid;
            bOk= ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,out,sError);

            data.Sid=out.last().toMap()["Sid"].toString();
        }


    }
    else
        bOk=true;

    if(bOk)
    {
        m_listCustomerInfo.append(data.data());
        refresh();
    }
    else
    {
        DMSG.showMsg("","新增失敗","OK");
        return;
    }
}

void LayerCustomerGameEdit::slotChange()
{
    int row = ui->tbCusGameInfo->currentRow();

    if(row >=m_listCustomerInfo.length() || row<0 )
    {
        DMSG.showMsg("","請先選擇要修改的資料","OK");
        return;
    }
    DataGameList select(m_listGame.at(ui->cbGame->currentIndex()).toMap());
    CustomerGameInfo data(m_listCustomerInfo.at(row).toMap());



    //    if(data.GameSid != select.Sid)
    //    {
    //        DMSG.showMsg("錯誤","不能變更遊戲","OK");
    //        return;
    //    }


    data.GameSid=select.Sid;
    data.LoginType=ui->txLoginType->text();
    data.LoginAccount=ui->txGameAccount->text();
    data.LoginPassword=ui->txPassword->text();
    data.ServerName=ui->txServer->text();
    data.Characters=ui->txChr->text();


    QString sError;

    QVariantList listIn;
    listIn.append(data.data());

    bool bOk;

    if(!m_bAddMode)
    {
        bOk= ACTION.action(ACT::REPLACE_GAME_INFO,listIn,sError);
    }
    else
        bOk =true;

    if(bOk)
    {
        m_listCustomerInfo[row]=data.data();
        refresh();
    }
    else
    {
        DMSG.showMsg("","修改失敗","OK");
        return;
    }


}

