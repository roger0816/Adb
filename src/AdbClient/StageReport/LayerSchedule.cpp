#include "LayerSchedule.h"
#include "ui_LayerSchedule.h"

LayerSchedule::LayerSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSchedule)
{
    ui->setupUi(this);

    ui->tb0->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽

    //    ui->tb->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽



    m_listVHeader<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"<<"白班11-19"<<"備註"
                <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚班19-02"<<"夜班20-03"<<"夜班20-03"<<"夜班20-03"<<"備註";




    ui->tbUserList->setColumnCount(1);

    m_group.addButton(ui->btnCost,0);

    m_group.addButton(ui->btnName,1);

    m_group.addButton(ui->btnStatus,2);

    m_listBtn<<ui->btn0<<ui->btn1<<ui->btn2<<ui->btn3<<ui->btn4<<ui->btn5
            <<ui->btn6<<ui->btn7<<ui->btn8<<ui->btn9;



    QRegExp ex("[0-9.]{1,6}");
    ui->txt->setValidator(new QRegExpValidator(ex,this));


    for(int i=0;i<m_listBtn.length();i++)
    {
        connect(m_listBtn[i],SIGNAL(clicked()),this,SLOT(btnsClicked()));
    }

    connect(ui->itemStatus,&ItemScheduleStatus::sendClicked,this,[=](QString sText,QString sColor)
    {
        int iRow = ui->tb0->currentRow();

        int iCol = ui->tb0->currentColumn();

        if(iRow<0 ||iCol<0)
            return ;


        m_data[iRow][iCol].sStatus = sText;
        m_data[iRow][iCol].sStatusColor = sColor;

        refresh();

        ui->tb0->setFocus();
    });


    setEditMode(false);

}

LayerSchedule::~LayerSchedule()
{
    delete ui;
}

void LayerSchedule::setEditMode(bool b)
{
    m_bEditMode = b;


    ui->wKind->setVisible(m_bEditMode);


    ui->itemStatus->setEditMode(m_bEditMode);
    if(!m_bEditMode)
    {
        ui->stackRight->setCurrentWidget(ui->rPageStatus);
        ui->btnSave->setText("班表確認");
        ui->btnSave->setDisabled(true);
    }
    else
    {
        int iIdx = m_group.checkedId();

        ui->stackRight->setCurrentIndex(iIdx);
        ui->btnSave->setText("儲存本月修改");
        ui->btnSave->setDisabled(false);

    }

}



void LayerSchedule::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(delayRefresh()));
}


void LayerSchedule::refresh()
{
    //color: rgb(0, 85, 255);

    checkUserList();



    int iDays =  QDate::fromString(m_sYear+m_sMonth,"yyyyMM").daysInMonth();

    int iDay=1;

    int iFirstDayInWeek = checkDayOfWeek(m_sYear,m_sMonth,"01");

    int iNeedWeek = 5;

    if(iNeedWeek*7-iDays-iFirstDayInWeek<0)
        iNeedWeek=6;

    int iRowCount = 6*m_listVHeader.length();

    QStringList listV;

    for(int iRow=0;iRow<iRowCount;iRow++)
    {
        if(ui->tb0->rowCount()<=iRow)
            ui->tb0->setRowCount(iRow+1);
        QString sHeaderName = m_listVHeader.at(iRow%m_listVHeader.length());
        listV.append(sHeaderName);
        for(int iCol=0;iCol<7;iCol++)
        {

            Layer_Schedule::Data data = m_data[iRow][iCol];

            if(iRow%m_listVHeader.length()==0)
            {
                // ui->tb0->setItem(iRow,iCol,UI.tbItem(m_sMonth+"/"+QString::number(iDay++)));


                QLineEdit *d0 = new QLineEdit(ui->tb0);
                d0->setStyleSheet("background-color:white");
                d0->setAlignment(Qt::AlignmentFlag::AlignCenter);


                if(iDay==1 && iFirstDayInWeek!= iCol+1)
                    d0->setText("");
                else if(iDay>iDays)
                    d0->setText("");
                else
                    d0->setText(m_sMonth+"/"+QString::number(iDay++));
                d0->setReadOnly(true);
                // d0->setStyleSheet("background-color:rgb(222,222,222);");

                ui->tb0->setCellWidget(iRow,iCol,d0);
            }

            else if(sHeaderName=="備註" || sHeaderName=="")
            {
                QLineEdit *d0 = new QLineEdit(ui->tb0);
                d0->setAlignment(Qt::AlignmentFlag::AlignCenter);
                d0->setReadOnly(!m_bEditMode);

                d0->setText(data.sText);
                d0->setStyleSheet("background-color:rgb(222,222,222);");

                ui->tb0->setCellWidget(iRow,iCol,d0);
            }

            else
            {
                Label3 *l = new Label3(ui->tb0);

                l->setCurrentIdx(m_group.checkedId());

                bool bCheck=false;
                if(data.sCheck=="1")
                    bCheck=true;
                l->setFlag(bCheck);

                if(m_bEditMode)
                {

                }
                else
                {

                    l->setVisable(false,true,true);

                    if(ACTION.m_currentUser.Name==data.sUserSid)
                    {
                        l->setVisable(true,true,true);
                        l->setBorder(data.sCheck=="0");
                    }


                }

                l->setText(data.sCost,data.sUserSid,data.sStatus);

                l->setText(2,data.sStatus,data.sStatusColor);

                ui->tb0->setCellWidget(iRow,iCol,l);
            }

        }
    }

    ui->tb0->setVerticalHeaderLabels(listV);



}



void LayerSchedule::on_btnSave_clicked()
{

    qDebug()<<"btn save clicked ";

    if(m_bEditMode)
    {
        int ret = DMSG.showMsg("","是否儲存？",QStringList()<<"否"<<"是");

        if(ret==1)
            write();
    }
    else
    {
        int ret =DMSG.showMsg("","是否送出班表確認",QStringList()<<"OK");
        if(ret==1)
            sendUserCheck(ui->tb0->currentRow(),ui->tb0->currentColumn());
    }
}


void LayerSchedule::on_btnName_clicked()
{
    changeTb();
}


void LayerSchedule::on_btnCost_clicked()
{
    changeTb();
}

void LayerSchedule::on_btnStatus_clicked()
{
    changeTb();
}

void LayerSchedule::changeTb()
{

    int iIdx = m_group.checkedId();

    ui->stackRight->setCurrentIndex(iIdx);

    refresh();

    ui->tb0->setFocus();
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

    qDebug()<<"write : ";

    QStringList listData;

    QStringList listCheck;

    for(int i=0;i<ui->tb0->rowCount();i++)
    {

        QStringList listRow ;
        QStringList check;
        for(int j=0;j<ui->tb0->columnCount();j++)
        {

            if(i%m_listVHeader.length()==0)
            {

                //QLineEdit *t = dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,j));
                // qDebug()<<"note : "<<t->text();

            }
            else if(ui->tb0->verticalHeaderItem(i)->text()=="備註"
                    || ui->tb0->verticalHeaderItem(i)->text()=="")
            {

                QLineEdit *t = dynamic_cast<QLineEdit*>(ui->tb0->cellWidget(i,j));

                QString sTmp = t->text();

                sTmp=sTmp.replace(",,",",");

                sTmp=sTmp.replace(";;",";");

                sTmp=sTmp.replace("::",":");


                listRow.append(t->text());
            }
            else
            {
                listRow.append(m_data[i][j].s3TextData());

                QString c = m_data[i][j].sCheck;

                if(c=="")
                    c="0";

                check.append(c);

            }


        }

        listData.append(listRow.join(",,"));

        listCheck.append(check.join(",,"));

    }


    QVariantMap dStatus;

    dStatus["Data"] = ui->itemStatus->data();

    dStatus["Id"]=SCHEDULE_STATUS_ID;

    QString sError;

    ACTION.action(ACT::ADD_SCHEDULE,dStatus,sError);




    QVariantMap d;

    d["Header"] = m_listVHeader.join(",,");

    d["Data"] = listData.join(";;");

    d["UserCheck"] = listCheck.join(";;");

    d["Id"]=m_sYear+m_sMonth;


    ACTION.action(ACT::ADD_SCHEDULE,d,sError);

}

void LayerSchedule::read()
{


    QVariantMap in;

    QVariantList out;

    QString sError;

    ACTION.action(ACT::QUERY_SCHEDULE,in,out,sError);

    if(out.length()<1)
    {
        ui->itemStatus->setData("");
        return;
    }


    auto getData=[=](QString sId)
    {
        QVariantMap re;
        for(int i=0;i<out.length();i++)
        {
            if(out.at(i).toMap()["Id"]==sId)
                re = out.at(i).toMap();
        }

        return re;
    };


    ui->itemStatus->setData(getData(SCHEDULE_STATUS_ID)["Data"].toString());


    for(int i=0;i<128;i++)
    {
        for(int j=0;j<7;j++)
            m_data[i][j].clear();
    }

    QVariantMap data = getData(m_sYear+m_sMonth);

    QStringList listData = data["Data"].toString().split(";;");
    QStringList listCheck = data["UserCheck"].toString().split(";;");

    for(int i=0;i<128 && i<listData.length();i++)
    {
        QStringList data=listData.at(i).split(",,");

        QStringList check = listCheck.at(i).split(",,");

        while(check.length()<7)
            check.append("0");

        for(int j=0;j<7 && j<data.length();j++)
        {
            QString sTmp = data.at(j);

            m_data[i][j].set3TextData(sTmp);

            QString c= check.at(j);

            if(c=="")
                c="0";

            m_data[i][j].sCheck=c;

        }
    }
}




int LayerSchedule::checkDayOfWeek(QString yyyy, QString MM, QString dd)
{
    QDate date=QDateTime::fromString(yyyy+MM+dd,"yyyyMMdd").date();


    return date.dayOfWeek();
}

void LayerSchedule::checkUserList()
{
    ui->tbUserList->setRowCount(0);

    QList<UserData> list = ACTION.getUser(false);

    int iRow=0;

    for(int i=0;i<list.length();i++)
    {
        iRow = ui->tbUserList->rowCount();
        ui->tbUserList->setRowCount(iRow+1);

        QString sName = list.at(i).Name;

        ui->tbUserList->setItem(iRow,0,UI.tbItem(sName));


    }
}

void LayerSchedule::sendUserCheck(int iRow, int iCol)
{
    read();

    m_data[iRow][iCol].sCheck="1";

    write();

    refresh();
}


void LayerSchedule::on_tbUserList_itemClicked(QTableWidgetItem *item)
{
    if(ui->tb0->currentRow()<0 || ui->tb0->currentRow()>= ui->tb0->rowCount())
        return;

    if(ui->tb0->currentColumn()<0 || ui->tb0->currentColumn()>= ui->tb0->columnCount())
        return;


    QString st = item->text();

    int iRow=0;
    int iCol=0;

    iRow = ui->tb0->currentRow();

    iCol = ui->tb0->currentColumn();

    m_data[iRow][iCol].sUserSid = st;

    m_data[iRow][iCol].sCheck="0";

    refresh();
    //    ui->tb0->setItem(iRow,iCol,UI.tbItem(st));

    ui->tb0->setFocus();

}




void LayerSchedule::on_tb0_itemChanged(QTableWidgetItem *item)
{
    //    int iRow = item->row();

    //    int iCol = item->column();


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


    int iRow= ui->tb0->currentRow();
    int iCol = ui->tb0->currentColumn();
    if(iRow%m_listVHeader.length()!=0 && iRow>=0 && iRow< ui->tb0->rowCount()
            && iCol>=0 && iCol< ui->tb0->columnCount())
    {


        m_data[iRow][iCol].sCost = btn->text();
        m_data[iRow][iCol].sCheck="0";

        refresh();


    }
    ui->tb0->setFocus();
}



void LayerSchedule::delayRefresh()
{

    m_sYear = QDateTime::currentDateTimeUtc().toString("yyyy");
    m_sMonth = QDateTime::currentDateTimeUtc().toString("MM");

    ui->lbTitle->setText(m_sYear+" / "+m_sMonth);

    ACTION.getUser(true);

    read();

    refreshCb();

    refresh();

}






void LayerSchedule::on_btnNext_clicked()
{

    ui->btnPre->setEnabled(true);

    int iYear = m_sYear.toInt();

    int iMonth = m_sMonth.toInt();

    iMonth++;

    if(iMonth>12)
    {
        iMonth=1;

        iYear++;
    }

    m_sMonth = QString::number(iMonth);

    if(iMonth<10)
        m_sMonth="0"+m_sMonth;

    m_sYear=QString::number(iYear);

    if(QDate::currentDate().toString("MM")!=m_sMonth)
        ui->btnNext->setDisabled(true);


    ui->lbTitle->setText(m_sYear+" / "+m_sMonth);

    read();

    refresh();

}


void LayerSchedule::on_btnPre_clicked()
{
    ui->btnNext->setEnabled(true);


    int iYear = m_sYear.toInt();

    int iMonth = m_sMonth.toInt();

    iMonth--;

    if(iMonth==0)
    {
        iMonth=12;

        iYear--;
    }

    m_sMonth = QString::number(iMonth);

    if(iMonth<10)
        m_sMonth="0"+m_sMonth;

    m_sYear=QString::number(iYear);


    if(QDate::currentDate().toString("MM")!=m_sMonth)
        ui->btnPre->setDisabled(true);

    ui->lbTitle->setText(m_sYear+" / "+m_sMonth);

    read();

    refresh();
}




void LayerSchedule::on_tb0_cellClicked(int row, int column)
{
    if(!m_bEditMode)
    {
        if(row<0 || column<0)
        {
            ui->btnSave->setDisabled(true);
            return ;
        }

        if(m_data[row][column].sUserSid== ACTION.m_currentUser.Name)
        {
            ui->btnSave->setDisabled(false);
        }
        else
        {
            ui->btnSave->setDisabled(true);
        }

    }
}

