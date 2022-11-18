#include "LayerCustomer.h"
#include "ui_LayerCustomer.h"

LayerCustomer::LayerCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerCustomer)
{
    ui->setupUi(this);

    ui->tb->setColumnWidth(0,60);

    ui->tb->hideColumn(7);

    ui->wEditArea->hide();

    connect(ui->btnClear,&QPushButton::clicked,this,&LayerCustomer::slotClearSearch);

}

LayerCustomer::~LayerCustomer()
{
    delete ui;
}

void LayerCustomer::init()
{
    ui->btnEdit->setEnabled(false);

    QTimer::singleShot(50,this,SLOT(refresh()));
}

void LayerCustomer::setEditType()
{
    ui->tb->hideColumn(0);

    ui->wEditArea->setVisible(true);
}

void LayerCustomer::on_btnAdd_clicked()
{
    DialogCustomerEdit dialog;

    QVariantList in,outClass,outGame;

    QString sError;

    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    dialog.setCb(outClass,outGame);


    int iRet = dialog.exec();



    if(iRet==1)
    {
        QVariantMap data = dialog.data();

        data["UserSid"] =ACTION.m_currentUser.Sid;


        in=dialog.dataGameInfo();

        ACTION.action(ACT::REPLACE_GAME_INFO,in,sError);




        ACTION.action(ACT::ADD_CUSTOMER,data,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}

void LayerCustomer::refresh()
{
    ui->btnEdit->setEnabled(false);


    ACTION.reQuerty();

    QString sError;

    QVariantList in;

    ACTION.action(ACT::QUERY_CUSTOMER,in,m_listData,sError);


    m_dIdxMapping.clear();

    ui->tb->setRowCount(0);



    for(int i=0;i<m_listData.length();i++)
    {
        QVariantMap v = m_listData.at(i).toMap();

        CustomerData data(v);

        bool bCheck = checkSearch(data);

        if(!bCheck)
            continue;

        int iRow = ui->tb->rowCount();

        ui->tb->setRowCount(iRow+1);

        ui->tb->setItem(iRow,0,UI.tbItem("進入",GlobalUi::_BUTTON));


        ui->tb->setItem(iRow,1,UI.tbItem(data.Id));

        QString sClassSid = ACTION.getCustomerClass(data.Class).Name;

        ui->tb->setItem(iRow,2,UI.tbItem(sClassSid));
        ui->tb->setItem(iRow,3,UI.tbItem(data.Name));

        QString sLv="一般";

        if(data.Vip=="1")
            sLv="VIP";

        ui->tb->setItem(iRow,4,UI.tbItem(sLv));

        ui->tb->setItem(iRow,5,UI.tbItem(data.Currency));
        ui->tb->setItem(iRow,6,UI.tbItem(data.Money,GlobalUi::_BUTTON));


        QVariantMap in;

        in["CustomerId"] = data.Sid;
        in["Desc"]="Sid";

        QVariantMap gameInfoV;

        //  ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,gameInfoV);


        QDateTime updatetime =QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss");

        QString sUserName = ACTION.getUser(data.UserSid).Name;

        ui->tb->setItem(iRow,7,UI.tbItem(updatetime));
        ui->tb->setItem(iRow,8,UI.tbItem(sUserName));
        ui->tb->setItem(iRow,9,UI.tbItem(data.Note1));


        m_dIdxMapping[iRow]=i;
    }



}

void LayerCustomer::showEvent(QShowEvent *)
{
    init();
}

bool LayerCustomer::checkSearch(CustomerData data)
{
    QString searchKey = ui->txSearch->text();

    if(searchKey.trimmed()=="")
        return true;

    QStringList listKey = searchKey.split("&");


    bool bRe = false;

    QList<int> listOk;

    foreach(QString v, listKey)
    {
        int iOk = 0;
        QString dateTime=QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd hh:mm:ss");

        QString Vip="一般";
        if(data.Vip=="1")
            Vip="VIP";

        QString sGroup=ACTION.getCustomerClass(data.Class).Name;

        QString sKey = v.toUpper().trimmed();
        //  if(data["Name"].toString().indexOf(m_sSearchKey,Qt::CaseInsensitive)>=0)
        //奇怪，Qt::CaseInsensitive 不起作用
        if(data.Name.toUpper().contains(sKey))
            iOk = 1;
        else if(data.Id.toUpper().contains(sKey))
            iOk =1;
        else if(data.Currency.toUpper().contains(sKey))
            iOk =1;
        else if(data.PayInfo.toUpper().contains(sKey))
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

void LayerCustomer::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
      //  on_btnCheck_clicked();
    }
}


void LayerCustomer::on_btnEdit_clicked()
{
    DialogCustomerEdit dialog;

    QString sError;
#if 0
    QVariantList in,outClass,outGame,outGameInfo;


    ACTION.action(ACT::QUERY_CUSTOM_CLASS,in,outClass,sError);

    ACTION.action(ACT::QUERY_GAME_LIST,in,outGame,sError);

    ACTION.action(ACT::QUERY_CUSTOMER_GAME_INFO,in,outGameInfo,sError);

    dialog.setData(outClass,outGame,outGameInfo,m_listData.at(ui->tb->currentRow()).toMap());
#else

    int iTmp = m_dIdxMapping.value(ui->tb->currentRow());
    int iIdx= qBound(0,iTmp,m_listData.length()-1);

    CustomerData data(m_listData.at(iIdx).toMap());

    dialog.setData(data.Sid);

#endif

    int iRet = dialog.exec();


    if(iRet==1)
    {
        QVariantMap data = dialog.data();

        data["UserSid"] =ACTION.m_currentUser.Sid;


        ACTION.action(ACT::REPLACE_GAME_INFO,dialog.dataGameInfo(),sError);
        ACTION.action(ACT::EDIT_CUSTOMER,data,sError);

        ACTION.action(ACT::DEL_GAME_INFO,dialog.deleteGameInfo(),sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
    else if(iRet==3)
    {
        QVariantMap data;

        data=dialog.data();


        ACTION.action(ACT::DEL_CUSTOMER,data,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }
}




void LayerCustomer::on_tb_cellClicked(int row, int column)
{
    int iTmp = m_dIdxMapping.value(row);

    if(row<0 || iTmp>=m_listData.length())
        return ;

    ui->btnEdit->setEnabled(true);


    CustomerData data(m_listData.at(iTmp).toMap());


    if(column==0)
    {

        emit into(iTmp);
    }

    else if(column==6)
    {

        DialogCustomerCostHistory dialog;

        dialog.setCustomer(data);

        dialog.exec();


    }
}


//void LayerCustomer::on_btnCheck_clicked()
//{
//    refresh();
//}

void LayerCustomer::slotClearSearch()
{
    ui->txSearch->clear();

    refresh();
}


void LayerCustomer::on_txSearch_textChanged(const QString &arg1)
{
    refresh();
}

CustomerData LayerCustomer::checkSelect(QString sSid)
{
    CustomerData re;

    foreach(QVariant v,m_listData)
    {
        CustomerData data(v.toMap());

        if(sSid==data.Sid)
            re = data;
    }



    return re;
}

