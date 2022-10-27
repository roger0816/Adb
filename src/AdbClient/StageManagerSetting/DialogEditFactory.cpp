#include "DialogEditFactory.h"
#include "ui_DialogEditFactory.h"

DialogEditFactory::DialogEditFactory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditFactory)
{
    ui->setupUi(this);

    setWindowTitle(" ");
}

DialogEditFactory::~DialogEditFactory()
{
    delete ui;
}

void DialogEditFactory::setData(QVariantMap data)
{

    m_rate = ACTION.listRate("",true).last();

    m_data = data;

    ui->txId->setText(m_data["Id"].toString());
    ui->txName->setText(m_data["Name"].toString());

    QStringList listPaySid = GLOBAL.toList(data["PayTypeSid"].toString());

    CListPair listPaydata =ACTION.getAddValueType(true);

    m_listCbData = listPaydata.listSecond();

    ui->tb->setRowCount(0);

    for(int i=0;i<listPaySid.length();i++)
    {
        int idx = listPaydata.listFirst().indexOf(listPaySid.at(i));
        if(idx<0)
            continue;

        addCb(idx,listPaydata.listSecond());

    }


    if(data["Sid"]=="")
    {
        ui->lbTitle->setText("新增廠商");
    }

}

QVariantMap DialogEditFactory::data()
{

    m_data["Id"] = ui->txId->text();

    m_data["Name"]= ui->txName->text();


    CListPair listPaydata =ACTION.getAddValueType(true);
    QStringList listSid = listPaydata.listFirst();
    QStringList listName = listPaydata.listSecond();

    QStringList listData;

    for(int i=0;i<ui->tb->rowCount();i++)
    {
        QComboBox *cb = dynamic_cast<QComboBox*>(ui->tb->cellWidget(i,0));

        int iIdxKey = listName.indexOf(cb->currentText());

        if(iIdxKey<0)
            continue;

        QString sId =listSid.at(iIdxKey);

        if(listData.indexOf(sId)<0)
            listData.append(sId);
    }

    m_data["PayTypeSid"] = GLOBAL.toString(listData);

    return m_data;
}

void DialogEditFactory::on_btnCancel_clicked()
{
    reject();
}


void DialogEditFactory::on_btnOk_clicked()
{
    bool bOk = true;

    QString sError = "欄位不能為空白";

    if(ui->txId->text().trimmed()=="")
    {
        sError = "代號欄位不能為空白";
        bOk = false;
    }
    if(ui->txName->text().trimmed()=="")
    {
        sError = "名稱欄位不能為空白";
        bOk = false;
    }
    if(ui->tb->rowCount()<1)
    {
        sError ="支付方式不能空白";
        bOk = false;
    }


    if(!bOk)
    {
        DMSG.showMsg("",sError,"OK");
        return;
    }
    done(1);
}


void DialogEditFactory::on_btnDel_clicked()
{
    int iRet = DMSG.showMsg("","確定是否刪除？",QStringList()<<"否"<<"是");

    if(iRet==1)
    {
        done(3);
    }
}


void DialogEditFactory::on_tb_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->tb->item(row,0);

    bool b = item->checkState()==Qt::Checked;

    if(b)
        item->setCheckState(Qt::Unchecked);
    else
        item->setCheckState(Qt::Checked);
}

void DialogEditFactory::addCb(int iIdx, QStringList listData)
{
    if(listData.length()<1)
        return;

    int iRow = ui->tb->rowCount();

    ui->tb->setRowCount(iRow+1);

    QComboBox *cb = new QComboBox(ui->tb);

    cb->addItems(listData);

    int index = qBound(0,iIdx,listData.length()-1);

    cb->setCurrentIndex(index);

    ui->tb->setCellWidget(iRow,0,cb);


}


void DialogEditFactory::on_btnAdd_clicked()
{
    addCb(0,m_listCbData);
}


void DialogEditFactory::on_btnSub_clicked()
{
    if(ui->tb->rowCount()>0)
        ui->tb->setRowCount(ui->tb->rowCount()-1);
}

