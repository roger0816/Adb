#include "LayerGetOrder2.h"
#include "ui_LayerGetOrder2.h"

LayerGetOrder2::LayerGetOrder2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerGetOrder2)
{
    ui->setupUi(this);

    m_layerCost = new LayerSayCost;

    m_layerCost->m_bOrderMode = true;
    m_layerCost->setReadOnly();
    m_layerCost->hide();

    ui->wBottom->setCurrentIndex(0);
}

LayerGetOrder2::~LayerGetOrder2()
{
    delete ui;
}

void LayerGetOrder2::showEvent(QShowEvent *)
{
    ui->wBottom->setCurrentIndex(0);
    ACTION.getUser(true);

    ACTION.getOrder(true);

    m_listFactory.clear();


    DataFactory tmp;

    tmp.Id="ABD";

    tmp.Name="艾比代";

    m_listFactory.append(tmp);

    m_listFactory.append(ACTION.getFactoryClass("",true));

    ui->tbOrder->setRowCount(0);

    //ui->cbAddValueType->clear();

    QVariantList list;

    QVariantMap d;

    QString sError;

    ACTION.action(ACT::QUERY_ADDVALUE_TYPE,d,list,sError);

    QStringList listCb;

    for(int i=0;i<list.length();i++)
    {
        listCb.append(list.at(i).toMap()["Name"].toString());
    }

    // ui->cbAddValueType->addItems(listCb);

    refreshUser();
}

void LayerGetOrder2::refreshUser(bool bRe)
{
    ui->wBottom->setCurrentIndex(0);
    QList<UserData> list =ACTION.getUser(bRe);

    m_listOwner.clear();

    m_data.clear();

    QList<DataFactory> listFac = m_listFactory;

    for(int i=0;i<listFac.length();i++)
    {
        m_data[listFac.at(i).Name] = QVariantList();
    }


    for(int i=0;i<list.length();i++)
    {
        UserData data = list.at(i);
        if(data.Lv==USER_LV::_LV2)
        {
            m_listOwner.append(data);

            // m_data[data.Sid]=QVariantList();
        }
    }

    QList<OrderData> listOrder = ACTION.getOrder(bRe);

    for(int i=0;i<listOrder.length();i++)
    {
        QStringList listKeyUser = m_data.keys();

        OrderData order = listOrder.at(i);

        if(listKeyUser.indexOf(order.Owner)<0)
            continue;

        if(order.Step=="3")// || (order.Step=="3" && order.PaddingUser.trimmed()!=""))
        {

            QVariantList list =m_data[order.Owner].toList();

            list.append(order.data());

            m_data[order.Owner] = list;
        }

    }

    ui->tbOrder->setRowCount(0);

    ui->tbUser->setRowCount(0);

    ui->tbUser->setColumnCount(0);
    int row=0,col=0;

    for(int i=0;i<listFac.length();i++)
    {
        if(row>=ui->tbUser->rowCount())
            ui->tbUser->setRowCount(row+1);

        DataFactory fac = listFac.at(i);

        QString sCount = QString::number(m_data[fac.Name].toList().length());

        QString st = fac.Id+"    "+fac.Name+"  ("+sCount+")";

        if(ui->tbUser->columnCount()<=col)
            ui->tbUser->setColumnCount(ui->tbUser->columnCount()+1);

        ui->tbUser->setItem(row,col,UI.tbItem(st));

        col++;

        if(col>=3)
        {
            col=0;

            row++;
        }
    }


}

QVariantMap LayerGetOrder2::gameItem(QString sSid)
{
    QString sError;
    QVariantMap re;
    QVariantMap d1;
    QVariantList listOut;
    d1["Sid"] = sSid;
    ACTION.action(ACT::QUERY_GAME_ITEM,d1,listOut,sError);

    if(listOut.length()>0)
        re = listOut.first().toMap();

    return re;
}

void LayerGetOrder2::on_tbUser_cellPressed(int row, int column)
{
    int iIdx = row*ui->tbUser->columnCount()+column;
    QString sKey= m_listFactory.at(iIdx).Name;
    m_currentOwnerSid = sKey;
    QVariantList listItem = m_data[sKey].toList();

    ui->tbOrder->setRowCount(0);

    for(int i=0;i<listItem.length();i++)
    {
        ui->tbOrder->setRowCount(i+1);

        OrderData order(listItem.at(i).toMap());

        /*
          QStringList tmp=order.User;

          QString sUser = "";
          while(tmp.length()>0 && tmp.last()=="" )
          {
              tmp.pop_back();
          }


          if(tmp.length()>0)
          {
           sUser = ACTION.getUser(order.User.last(),true).Name ;
          }

          ui->tbOrder->setItem(i,0,UI.tbItem(sUser));
          */
        ui->tbOrder->setItem(i,0,UI.tbItem(sKey));

        ui->tbOrder->setItem(i,1,UI.tbItem(order.Name));
        ui->tbOrder->setItem(i,2,UI.tbItem(order.Id,true));

        QVariantMap d;
        QVariantList tmpOut;

        d["Sid"]=order.CustomerSid;

        QString sError;

        ACTION.action(ACT::QUERY_CUSTOMER,d,tmpOut,sError);


        QVariantMap customer;

        if(tmpOut.length()>0)
            customer = tmpOut.first().toMap();

        ui->tbOrder->setItem(i,3,UI.tbItem(customer["Id"]));
        ui->tbOrder->setItem(i,4,UI.tbItem(customer["Name"]));

        QString sGameItemSid= order.Item.split(";").first().split(",").first();
        QVariantMap item=gameItem(sGameItemSid);

        ui->tbOrder->setItem(i,5,UI.tbItem(ACTION.getGameName(item["GameSid"].toString())));


        if(order.Step=="3" )
        {
            if(order.PaddingUser.trimmed()=="")
            {
                ui->tbOrder->setItem(i,6,UI.tbItem("待處理"));
                ui->tbOrder->setItem(i,7,UI.tbItem("確認接單",true));
            }

            else
            {

                ui->tbOrder->setItem(i,6,UI.tbItem(ACTION.getUser(order.PaddingUser,true).Name+" 處理中"));
                ui->tbOrder->setItem(i,7,UI.tbItem(""));
            }
        }



    }


}


void LayerGetOrder2::on_tbOrder_cellPressed(int row, int column)
{

    QVariantList listData =m_data[m_currentOwnerSid].toList();

    if(row<0 || row>=listData.length())
        return;

    ui->wBottom->setCurrentIndex(0);
    OrderData order(listData.at(row).toMap());

    if(column==2)
    {

        QVariantMap d;
        d["Sid"] = order.CustomerSid;
        m_layerCost->setCustomer(d,order.Sid);

        m_layerCost->show();

        return ;
    }


    if(column==7 && ui->tbOrder->item(row,7)->text()=="確認接單")
    {
        if(1==UI.showMsg("",QString("請再次確認是否接單處理編號:%1？").arg(order.Id),QStringList()<<"否"<<"是"))
        {
            QString sError;
            order.PaddingUser=ACTION.m_currentUser.Sid;
            order.Step="3";
            ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);

            UI.showMsg("",sError,"OK");

            refreshUser();
        }

        return;
    }


    if(order.PaddingUser==ACTION.m_currentUser.Sid)
    {
        QVariantMap tmp;
        tmp["CustomerSid"]=order.CustomerSid;
        QVariantList listOut;
        QString sError;
        ACTION.action(ACT::QUERY_CUSTOMER_COST,tmp,listOut,sError);

        if(listOut.length()>0)
        {
            QString sValue = listOut.last().toMap()["Value"].toString();

            ui->lbOri->setText(sValue);

            ui->lbCost->setText(order.Cost);

            double d = sValue.toDouble()-order.Cost.toDouble();

            ui->lbFinal->setText(QString::number(d));

        }


        ui->wBottom->setCurrentIndex(1);

    }

}


void LayerGetOrder2::on_btnBackOrder_clicked()
{
    QVariantList listData =m_data[m_currentOwnerSid].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    int iRet= UI.showMsg("",QString("確定要將此訂單(%1) \n解除處理中的狀態？").arg(order.Id),QStringList()<<"否"<<"是");

    if(iRet==1)
    {

        QString sError;

        order.PaddingUser="";

        order.Step="3";

        ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);

        UI.showMsg("",sError,"OK");

        refreshUser();

        return;
    }

}


void LayerGetOrder2::on_btnFinish_clicked()
{
    QVariantList listData =m_data[m_currentOwnerSid].toList();

    QVariantMap data =listData.at(qBound(0,ui->tbOrder->currentRow(),listData.length()-1)).toMap();

    OrderData order(data);

    int iRet= UI.showMsg("",QString("請再確認訂單(%1) \n已完成回報處理？").arg(order.Id),QStringList()<<"否"<<"是");

    if(iRet==1)
    {

        QString sError;

        order.PaddingUser="";

        // order.AddValueType=ui->cbAddValueType->currentText();

        order.Step="4";

        ACTION.action(ACT::REPLACE_ORDER,order.data(),sError);

        UI.showMsg("",sError,"OK");

        refreshUser();

        return;
    }
}

