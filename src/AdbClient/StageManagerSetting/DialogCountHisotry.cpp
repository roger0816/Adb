#include "DialogCountHisotry.h"
#include "ui_DialogCountHisotry.h"

DialogCountHisotry::DialogCountHisotry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCountHisotry)
{
    ui->setupUi(this);

    setWindowTitle("商品數量-詳細");
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        hide();
    });

    ui->tb->hideColumn(2);
}

DialogCountHisotry::~DialogCountHisotry()
{
    delete ui;
}

void DialogCountHisotry::setTitle(QString sItemSid, QString sGameName, QString sItemName, QString sCount)
{

    m_sItemSid = sItemSid;
    ui->lbGameName->setText(sGameName);
    ui->lbItemName->setText(sItemName);
    ui->lbCount->setText(sCount);


    QVariantMap in;
    in["GameItemSid"]=m_sItemSid;
    in["DESC"]="Sid";
    in["LIMIT"]="1000";
    QVariantList listOut;

    QString sError;
    ACTION.action(ACT::QUERY_ITEM_COUNT,in,listOut,sError);

    m_listData.clear();
    foreach(QVariant v,listOut)
    {
        DataItemCount d(v.toMap());

        m_listData.append(d);
    }

    refresh();
}

void DialogCountHisotry::refresh()
{
    ui->tb->setRowCount(0);
    int iRow=0;

    for(int i=0;i<m_listData.length();i++)
    {
        ui->tb->setRowCount(iRow+1);

        DataItemCount data = m_listData.at(i);

        QString sType="增加庫存";

        int iChange = data.ChangeValue;


        if(data.ChangeValue<0)
            sType ="下單";
        else if(data.ChangeValue>0)
            sType ="取消訂單";
        else
        {
            sType="增加庫存";

            if(i<m_listData.length()-1)
            {
                int iPreCount = m_listData.at(i+1).TotalCount;

                iChange = data.TotalCount - iPreCount;
            }

        }

        ui->tb->setItem(iRow,0, UI.tbItem(m_listData.length()-iRow));
        ui->tb->setItem(iRow,1, UI.tbItem(sType));



        ui->tb->setItem(iRow,3, UI.tbItem(iChange));

         ui->tb->setItem(iRow,4, UI.tbItem(data.TotalCount-data.TotalSell));

         ui->tb->setItem(iRow,5,UI.tbItem(DATA.getUser(data.UserSid).Name));

         ui->tb->setItem(iRow,6,UI.tbItem(QDateTime::fromString(data.UpdateTime,"yyyyMMddhhmmss")));



        iRow++;
    }

}
