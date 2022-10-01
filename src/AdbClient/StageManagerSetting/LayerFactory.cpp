#include "LayerFactory.h"
#include "ui_LayerFactory.h"

LayerFactory::LayerFactory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerFactory)
{
    ui->setupUi(this);

    ui->tbFactory->setMouseTracking(true);
}

LayerFactory::~LayerFactory()
{
    delete ui;
}

void LayerFactory::on_btnFactoryEdit_clicked()
{
    int iRow = ui->tbFactory->currentRow();

    if(iRow<0 || iRow>= m_listFactory.length() )
    {
        UI.showMsg("","請先選擇要編輯的目標","OK");
        return;
    }

    QString sError;

    QVariantMap data = m_listFactory.at(iRow).toMap();

    DialogEditFactory factory;

    factory.setData(data);

    int iRet = factory.exec();

    if(iRet==1)
    {
        QVariantList list;
        QString sError;

        ACTION.action(ACT::EDIT_FACTORY_CLASS,factory.data(),sError);

        DMSG.showMsg("",sError,"OK");
        refresh();


    }

    else if(iRet==3)
    {
        QVariantMap input;
        input["Sid"] = data["Sid"];
        ACTION.action(ACT::DEL_FACTORY_CLASS,input,sError);

        UI.showMsg("",sError,"OK");

        refresh();
    }




}


void LayerFactory::on_btnFactoryAdd_clicked()
{

    DialogEditFactory factory;

    QVariantMap data;

    data["Sid"]="";

    factory.setData(data);

    int iRet = factory.exec();

    if(iRet==1)
    {
        QVariantList list;
        QString sError;

        ACTION.action(ACT::ADD_FACTORY_CLASS,factory.data(),sError);

        DMSG.showMsg("",sError,"OK");

        refresh();
        return ;

    }


}


void LayerFactory::refresh()
{
    QVariantMap tmp;

    m_listFactory.clear();

    QString sError;

    ACTION.action(ACT::QUERY_FACTORY_CLASS,tmp,m_listFactory,sError);

    ui->tbFactory->setRowCount(0);

    CListPair listPay = ACTION.getAddValueType(true);

    for(int i=0;i<m_listFactory.length();i++)
    {
        ui->tbFactory->setRowCount(i+1);

        ui->tbFactory->setItem(i,0,UI.tbItem(m_listFactory.at(i).toMap()["Id"]));

        ui->tbFactory->setItem(i,1,UI.tbItem(m_listFactory.at(i).toMap()["Name"]));

        QStringList listSid = GLOBAL.toList(m_listFactory.at(i).toMap()["PayTypeSid"].toString());

        QStringList listPayType = GLOBAL.mapping(listPay,listSid);

        ui->tbFactory->setItem(i,2,UI.tbItem(listPayType.join(","),GlobalUi::_TOOLTIP));


    }

}

void LayerFactory::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}



void LayerFactory::on_tbFactory_itemEntered(QTableWidgetItem *item)
{
    if(item->column()==2)
    {
        QString st = item->text().replace(",","\n");

        QToolTip::showText(QCursor::pos(),st);

    }
    else
    {
        QToolTip::hideText();
    }

}

