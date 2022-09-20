#include "LayerSchedule.h"
#include "ui_LayerSchedule.h"

LayerSchedule::LayerSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSchedule)
{
    ui->setupUi(this);

    ui->tb0->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
    ui->tb1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
    //    ui->tb->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽


    QStringList listV;
    listV<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"
        <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚儲19-02"<<"夜儲20-03"<<"夜班20-03";
    listV<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"
        <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚儲19-02"<<"夜儲20-03"<<"夜班20-03";
    listV<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"
        <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚儲19-02"<<"夜儲20-03"<<"夜班20-03";
    listV<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"
        <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚儲19-02"<<"夜儲20-03"<<"夜班20-03";



    ui->tb0->setRowCount(listV.length());

    ui->tb0->setVerticalHeaderLabels(listV);


    ui->tb1->setRowCount(listV.length());

    ui->tb1->setVerticalHeaderLabels(listV);

    ui->tb2->setColumnCount(1);

    m_group.addButton(ui->btnName);

    m_group.addButton(ui->btnCost);

    m_listBtn<<ui->btn0<<ui->btn1<<ui->btn2<<ui->btn3<<ui->btn4<<ui->btn5
            <<ui->btn6<<ui->btn7<<ui->btn8<<ui->btn9;



    QRegExp ex("[0-9.]{1,6}");
    ui->txt->setValidator(new QRegExpValidator(ex,this));


    for(int i=0;i<m_listBtn.length();i++)
    {
        connect(m_listBtn[i],SIGNAL(clicked()),this,SLOT(btnsClicked()));
    }

}

LayerSchedule::~LayerSchedule()
{
    delete ui;
}



void LayerSchedule::showEvent(QShowEvent *)
{
    ACTION.getUser(true);

    read();

    refreshCb();

    refresh();



}

void LayerSchedule::refresh()
{
    //color: rgb(0, 85, 255);

    ui->tb2->setRowCount(0);

    QList<UserData> list = ACTION.getUser(false);


    int iRow=0;

    for(int i=0;i<list.length();i++)
    {
        iRow = ui->tb2->rowCount();
        ui->tb2->setRowCount(iRow+1);

        QString sName = list.at(i).Name;

        ui->tb2->setItem(iRow,0,UI.tbItem(sName));


    }



    for(int i=0;i<52;i++)
    {


        for(int j=0;j<7;j++)
        {


            if(i%13==0)
            {
                QLineEdit *d0 = new QLineEdit(ui->tb0);
                d0->setAlignment(Qt::AlignmentFlag::AlignCenter);

                d0->setText(sDataUserSid[i][j]);
                d0->setStyleSheet("background-color:rgb(222,222,222);");

                ui->tb0->setCellWidget(i,j,d0);


                QLineEdit  *d1 = new QLineEdit(ui->tb1);

                d1->setReadOnly(true);

                d1->setText(sDataCost[i][j]);

                d1->setStyleSheet("background-color:rgb(222,222,222);");

                ui->tb1->setCellWidget(i,j,d1);



            }
            else
            {

                QTableWidgetItem *item = UI.tbItem(sDataUserSid[i][j]);

                ui->tb0->setItem(i,j,item);

                //

                QLineEdit* sp = new QLineEdit(ui->tb1);
                sp->setAlignment(Qt::AlignCenter);
                QRegExp ex("[0-9.]{1,6}");
                sp->setValidator(new QRegExpValidator(ex,ui->tb1));

                sp->setText(sDataCost[i][j]);
                ui->tb1->setCellWidget(i,j,sp);

            }




        }
    }





}



void LayerSchedule::on_btnSave_clicked()
{
    int ret = DMSG.showMsg("","是否儲存？",QStringList()<<"否"<<"是");

    if(ret==1)
        write();
}


void LayerSchedule::on_btnName_clicked()
{
    changeTb();
}


void LayerSchedule::on_btnCost_clicked()
{
    changeTb();
}

void LayerSchedule::changeTb()
{



    if(ui->btnName->isChecked())
    {
        ui->stack->setCurrentIndex(0);

        ui->stackRight->setCurrentIndex(0);

    }
    else
    {
        ui->stack->setCurrentIndex(1);

        ui->stackRight->setCurrentIndex(1);
    }
}

void LayerSchedule::refreshCb()
{
    ui->cb->clear();

    QStringList listBtnText;

    for(int i=0;i<m_listBtn.length();i++)
    {
        listBtnText.append(m_listBtn.at(i)->text());
    }

    ui->cb->addItems(listBtnText);

}

void LayerSchedule::write()
{

    QStringList listUser,listCost;

    for(int i=0;i<52;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(i%13==0)
            {
                sDataUserSid[i][j] = dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,j))->text();
                sDataCost[i][j] = dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,j))->text();
            }
            else
            {
                sDataUserSid[i][j]= ui->tb0->item(i,j)->text();
                sDataCost[i][j] = dynamic_cast<QLineEdit*>(ui->tb1->cellWidget(i,j))->text();
            }

            listUser.append(sDataUserSid[i][j]);
            listCost.append(sDataCost[i][j]);
        }
    }

    QVariantMap d;

    d["Id"] = listUser.join(",");
    d["Cost"] = listCost.join(",");

    QString sError;

    ACTION.action(ACT::ADD_SCHEDULE,d,sError);

}

void LayerSchedule::read()
{
    QVariantMap in;

    QVariantList out;

    QString sError;

    ACTION.action(ACT::QUERY_SCHEDULE,in,out,sError);

    if(out.length()<1)
        return;

    QVariantMap data = out.first().toMap();

    QStringList listUser = data["Id"].toString().split(",");

    QStringList listCost = data["Cost"].toString().split(",");

    int iIdx = 0;

    for(int i=0;i<52;i++)
    {
        for(int j=0;j<7;j++)
        {
            sDataUserSid[i][j] = listUser.at(iIdx);

            sDataCost[i][j] = listCost.at(iIdx);

            iIdx++;
        }
    }


}


void LayerSchedule::on_tb2_itemClicked(QTableWidgetItem *item)
{
    if(ui->tb0->currentRow()<0 || ui->tb0->currentRow()>= ui->tb0->rowCount())
        return;

    if(ui->tb0->currentColumn()<0 || ui->tb0->currentColumn()>= ui->tb0->columnCount())
        return;

    if(ui->stack->currentWidget()==ui->page0)
    {
        QString st = item->text();

        int iRow=0;
        int iCol=0;

        iRow = ui->tb0->currentRow();

        iCol = ui->tb0->currentColumn();

        ui->tb0->setItem(iRow,iCol,UI.tbItem(st));

        ui->tb0->setFocus();
    }
}


void LayerSchedule::on_tb1_itemChanged(QTableWidgetItem *item)
{
    int iRow = item->row();

    int iCol = item->column();

    qDebug()<<"tb1 : "<<iRow<<" , "<<iCol;
}


void LayerSchedule::on_tb0_itemChanged(QTableWidgetItem *item)
{
    int iRow = item->row();

    int iCol = item->column();

    qDebug()<<"tb0 : "<<iRow<<" , "<<iCol;
}


void LayerSchedule::on_btnChangeBtn_clicked()
{
    int iIdx = ui->cb->currentIndex();

    if(iIdx<0 || iIdx >= m_listBtn.length())
        return;

    m_listBtn[iIdx]->setText(ui->txt->text());

    ui->cb->setItemText(iIdx,ui->txt->text());
}

void LayerSchedule::btnsClicked()
{
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());

    if(ui->stack->currentWidget()==ui->page1)
    {
        int iRow= ui->tb1->currentRow();
        int iCol = ui->tb1->currentColumn();
        if(iRow%13!=0 && iRow>=0 && iRow< ui->tb1->rowCount()
                && iCol>=0 && iCol< ui->tb1->columnCount())
        {


            QLineEdit* sp = new QLineEdit(ui->tb1);
            sp->setAlignment(Qt::AlignCenter);
            sp->setText(btn->text());
            QRegExp ex("[0-9.]{1,6}");
            sp->setValidator(new QRegExpValidator(ex,ui->tb1));

            ui->tb1->setCellWidget(iRow,iCol,sp);

            ui->tb1->setFocus();
        }
    }
}


void LayerSchedule::on_tb1_cellChanged(int row, int column)
{
    qDebug()<<"tb1 : "<<"cell "<<row<<" , "<<column;
}

