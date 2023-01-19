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

    //ui->btnInport->hide();

    connect(ui->btnSearch,&QPushButton::clicked,this,&LayerCustomer::slotSearch);

}

LayerCustomer::~LayerCustomer()
{
    delete ui;
}

void LayerCustomer::init()
{
    qDebug()<<"layer customer init";
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

        ACTION.action(ACT::ADD_CUSTOMER,data,sError);
        QVariantMap tmp;
        tmp["Id"]=data["Id"];

        QVariantMap out;

        ACTION.action(ACT::QUERY_CUSTOMER,tmp,out,sError);

        data["Sid"] = out["Sid"];

        QString sCustomerSid = data["Sid"].toString();

        in=dialog.dataGameInfo(sCustomerSid);

        ACTION.action(ACT::REPLACE_GAME_INFO,in,sError);

        CustomerData cus(data);

        QVariantMap kValue;
        kValue["skey"]="CustomerId";
        kValue["svalue"]=cus.Id.split("-").last();

        QString sError2;
        ACTION.action(ACT::SET_VALUE,kValue,sError2);


        UI.showMsg("",sError,"OK");

        refresh();
    }
}

void LayerCustomer::refresh()
{
    if(m_bReLock)
        return;

    m_bReLock= true;

    ui->btnEdit->setEnabled(false);


 //   ACTION.reQuerty();

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
       // ui->tb->setItem(iRow,6,UI.tbItem(data.Money,GlobalUi::_BUTTON));

        ui->tb->setItem(iRow,6,UI.tbItem("詳細",GlobalUi::_BUTTON));

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



    m_bReLock = false;
}

void LayerCustomer::showEvent(QShowEvent *)
{
    //  init();
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
       slotSearch();
    }
}





void LayerCustomer::on_btnEdit_clicked()
{
    DialogCustomerEdit dialog;

    bool isRoot = ACTION.m_currentUser.Lv>=99;

    dialog.setRoot(isRoot);

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

    CustomerData customerData(m_listData.at(iIdx).toMap());

    dialog.setData(customerData.Sid);

#endif

    int iRet = dialog.exec();


    if(iRet==1)
    {
        QVariantMap data = dialog.data();

        data["UserSid"] =ACTION.m_currentUser.Sid;


        ACTION.action(ACT::REPLACE_GAME_INFO,dialog.dataGameInfo(customerData.Sid),sError);

        bool hasChangeCus = dialog.checkHasChange();
        qDebug()<<"CCCCCCCCC : "<<hasChangeCus;
        if(hasChangeCus)
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

        QVariantMap v;
        v["CustomerSid"] = customerData.Sid;
        ACTION.action(ACT::DEL_GAME_INFO,v,sError);

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

QString LayerCustomer::checkCurrency(QString sKey)
{
    if(sKey.trimmed()=="新")
    {
        return "新加坡元(SGD)";
    }


    QString sRe="";

    qDebug()<<"check key : "<<sKey;

    if(sKey.length()<1)
        return "";

    QString st=sKey.trimmed().mid(0,1);

    if(st=="马" || st=="馬")
    {
        st="林";
    }


    QStringList listCurrency;

    listCurrency<<"美金(USD)"<<"新台幣(NTD)"<<"港幣(HKD)"<<"人民幣(RMB)"<<"新加坡元(SGD)"<<"林吉特(MYR)";

    foreach(QString tmp,listCurrency)
    {
        if(tmp.contains(st))
        {
            sRe = tmp;

            break;
        }

    }

    qDebug()<<"re currency :"<<sRe;

    return sRe;
}


void LayerCustomer::exportXml(QString sFilePath)
{

    using namespace QXlsx;

    Document xlsx(sFilePath);



    //    qDebug() << xlsx.read("A1");
    //    qDebug() << xlsx.read("A2");
    //    qDebug() << xlsx.read("A3");
    //    qDebug() << xlsx.read("A4");
    //    qDebug() << xlsx.read("A5");
    //    qDebug() << xlsx.read("A6");
    //    qDebug() << xlsx.read("A7");

    ACTION.getCustomerClass(true);

    QString sDefaultClass=ACTION.getCustomerClass(true).first().Sid;

    int xxx=65014;

    QList<CustomerData> list;

    QString sErrorMsg="";

    for(int iRow=2;iRow<10000;iRow++)
    {
        CustomerData data;

        data.Class=sDefaultClass;

        data.Vip="0";

        bool bHasData=false;

        for(int iCol=1;iCol<10;iCol++)
        {
            Cell *cell = xlsx.cellAt(iRow, iCol);

            if(cell!=nullptr)
            {

                bHasData = true;

                QString cellData = cell->value().toString().trimmed();

                if(iCol==1)   //客戶分類
                {

                    QString sClassSid = ACTION.getCustomerClass(cellData).Sid;

                    if(sClassSid.trimmed()=="")
                        sClassSid =sDefaultClass;

                    data.Class=sClassSid;

                }
                else if(iCol==2)  //客戶編號
                {

                    if(cellData.length()<1)
                    {
                        break;

                    }


                    if(cellData.length()<3 || cellData.length()>4)
                    {
                        sErrorMsg="第"+QString::number(iRow-1)+"筆 客戶編號異常 : "+cellData;

                        break;
                    }
                    else
                    {
                        QString sId = cellData;

                        if(sId.length()<4)
                        {
                            sId="D"+sId;
                        }

                        data.Id="A-"+sId;
                    }


                }

                else if(iCol==3)  //客戶名稱
                {
                    if(cellData=="")
                    {
                        sErrorMsg="第"+QString::number(iRow-1)+"筆 客戶名稱空白 : "+cellData;

                        break;
                    }
                    else
                    {
                        data.Name=cellData;
                    }


                }

                else if(iCol==4)  //幣別
                {
                    if(cellData=="")
                    {
                        sErrorMsg="第"+QString::number(iRow-1)+"筆 幣別空白 : "+cellData;

                        break;
                    }
                    else
                    {
                        QString sCurrency= checkCurrency(cellData);

                        if(sCurrency=="")
                        {
                            sErrorMsg="第"+QString::number(iRow-1)+"筆 幣別無法分辨 : "+cellData;
                            break;
                        }

                        data.Currency=sCurrency;
                    }


                }

                else if(iCol==5)  //後五碼
                {
                    data.Num5=cellData;
                }

                else if(iCol==6)  //vip
                {
                    if(cellData.trimmed()=="1")
                    {
                        data.Vip="1";
                    }
                    else
                    {
                        data.Vip="0";
                    }
                }




            }

        }


        if(sErrorMsg!="")
        {
            DMSG.showMsg("資料錯誤，取消匯入",sErrorMsg,"OK");

            return;
        }

        if(bHasData && data.Name.trimmed()!="" && data.Id.trimmed()!="")
        {

            data.Sid=QString::number(xxx++);

            list.append(data);
        }

    }

    QString sError="";


    for(int i=0;i<list.length();i++)
    {

        CustomerData cus = list.at(i);

        ACTION.action(ACT::ADD_CUSTOMER,cus.data(),sError);
        qDebug()<<cus.Id<<" : "<<cus.Currency<<cus.Vip;
        qDebug()<<cus.data();


    }



    //    for (int row = 1; row < 10; ++row) {
    //        if (QXlsx::Cell *cell = xlsx.cellAt(row, 5))
    //            qDebug() << cell->value();
    //    }
}

void LayerCustomer::on_btnInport_clicked()
{
    QString sPath = QFileDialog::getOpenFileName(this,"請選擇檔案",".xls");
    if(sPath.trimmed()=="")
        return ;

    exportXml(sPath);
    qDebug()<<"AAAAA "<<sPath;



}

void LayerCustomer::slotSearch()
{
    refresh();
}

