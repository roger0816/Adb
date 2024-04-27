#include "LayerFactory.h"
#include "ui_LayerFactory.h"

LayerFactory::LayerFactory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerFactory)
{
    ui->setupUi(this);

    ui->tbFactory->setMouseTracking(true);
    ui->tbFactory->hideColumn(0);
    connect(ui->btnSortUp,&QPushButton::clicked,this,&LayerFactory::slotBtnSortUp);
    connect(ui->btnSortDown,&QPushButton::clicked,this,&LayerFactory::slotBtnSortDown);
    connect(ui->btnSortTop,&QPushButton::clicked,this,&LayerFactory::slotBtnSortTop);
    connect(ui->btnSortSave,&QPushButton::clicked,this,&LayerFactory::slotBtnSortSave);


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

    QVariantMap data = m_listFactory[iRow].data();



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

//    m_listFactory.clear();

//    QString sError;

//    ACTION.action(ACT::QUERY_FACTORY_CLASS,tmp,m_listFactory,sError);

    m_listFactory = DATA.getFactoryClassList();

    if(m_listFactory.length()>1)
    {
        DataFactory fac =m_listFactory.last();

        if(fac.Id=="未" && fac.Name=="未分配")
            m_listFactory.pop_back();

    }


    ui->tbFactory->setRowCount(0);

    CListPair listPay = DATA.getAddValueType();

    for(int i=0;i<m_listFactory.length();i++)
    {
        ui->tbFactory->setRowCount(i+1);
        ui->tbFactory->setItem(i,0,UI.tbItem(m_listFactory.at(i).Sid));

        ui->tbFactory->setItem(i,1,UI.tbItem(m_listFactory.at(i).Id));

        ui->tbFactory->setItem(i,2,UI.tbItem(m_listFactory.at(i).Name));



        QStringList listSid = m_listFactory.at(i).PayTypeSid;


        QStringList listPayType = GLOBAL.mapping(listPay,listSid);



        ui->tbFactory->setItem(i,3,UI.tbItem(listPayType.join(","),GlobalUi::_TOOLTIP));


    }

}

void LayerFactory::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}

void LayerFactory::on_tbFactory_itemEntered(QTableWidgetItem *item)
{
    if(item->column()==3)
    {
        QString st = item->text().replace(",","\n");

        QToolTip::showText(QCursor::pos(),st);

    }
    else
    {
       // QToolTip::hideText();
    }

}

void LayerFactory::slotBtnSortUp()
{
    int iRow = ui->tbFactory->currentRow();

    if(iRow==0)
        return ;

    if(iRow<0 || iRow>=ui->tbFactory->rowCount())
    {
        UI.showMsg("","請先選擇目標","OK");
        return ;
    }

    QTableWidgetItem *current=ui->tbFactory->currentItem();
    int columnCount = ui->tbFactory->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbFactory->takeItem(iRow, col));
    }

    ui->tbFactory->removeRow(iRow);
    ui->tbFactory->insertRow(iRow - 1);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbFactory->setItem(iRow - 1, col, items.at(col));
    }

    ui->tbFactory->setCurrentItem(current);

}

void LayerFactory::slotBtnSortDown()
{
    int iRow = ui->tbFactory->currentRow();

    if(iRow==ui->tbFactory->rowCount()-1)
        return ;

    if(iRow<0 || iRow>=ui->tbFactory->rowCount())
    {
        UI.showMsg("","請先選擇目標","OK");
        return ;
    }

    QTableWidgetItem *current=ui->tbFactory->currentItem();
    int columnCount = ui->tbFactory->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbFactory->takeItem(iRow, col));
    }

    ui->tbFactory->removeRow(iRow);
    ui->tbFactory->insertRow(iRow + 1);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbFactory->setItem(iRow + 1, col, items.at(col));
    }

    ui->tbFactory->setCurrentItem(current);
}

void LayerFactory::slotBtnSortTop()
{
    int iRow = ui->tbFactory->currentRow();

    if(iRow==0)
        return ;

    if(iRow<0 || iRow>=ui->tbFactory->rowCount())
    {
        UI.showMsg("","請先選擇商品","OK");
        return ;
    }




    QTableWidgetItem *current=ui->tbFactory->currentItem();
    int columnCount = ui->tbFactory->columnCount();
    QList<QTableWidgetItem*> items;

    for (int col = 0; col < columnCount; ++col) {
        items.append(ui->tbFactory->takeItem(iRow, col));
    }

    ui->tbFactory->removeRow(iRow);
    ui->tbFactory->insertRow(0);

    for (int col = 0; col < columnCount; ++col) {
        ui->tbFactory->setItem(0, col, items.at(col));
    }

    ui->tbFactory->setCurrentItem(current);

}

void LayerFactory::slotBtnSortSave()
{

    QVariantMap data;

    data["Table"]="FactoryClass";

    QVariantMap item;

    for(int i=0;i<ui->tbFactory->rowCount();i++)
    {
        if(i>=0 && i<m_listFactory.length())
        {
            DataFactory data= m_listFactory.at(i);

            qDebug()<<"sid : "<<data.Sid<<" ,sort : "<<data.Sort<<" ,name : "<<data.Name;

            QString sSid = ui->tbFactory->item(i,0)->text();
            QString sSort = QString::number(i+1);

            item[sSid]=sSort;

        }
    }

    data["Data"]=item;

    QString sError;

    bool bOk=ACTION.action(ACT::EDIT_SORT,data,sError);

    if(bOk)
        UI.showMsg("","排序已修改","OK");
    else
        UI.showMsg("",sError,"OK");






  //  qDebug
}



