#include "LayerSchedule.h"
#include "ui_LayerSchedule.h"

LayerSchedule::LayerSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerSchedule)
{
    ui->setupUi(this);

    m_editHeader = new EditScheduleHeader(ui->wBg);

    m_editHeader->hide();

    connect(m_editHeader,&EditScheduleHeader::done,this,[=](QStringList list0,QStringList list1){
        QStringList listF;
        listF.append("");
        listF.append(list0);
        listF.append("備註");
        listF.append(list1);
        listF.append("備註");
        m_listVHeader = listF;

        refresh();

    });

    ui->tb0->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽

    //    ui->tb->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽



    m_listVHeader<<""<<"白領11-19"<<"白儲11-19"<<"早班10-18"<<"早班10-18"<<"白班11-19"<<"白班11-19"<<"白班11-19"<<"備註"
                <<"晚班18-0130"<<"晚班18-0130"<<"晚領19-03"<<"晚班19-02"<<"夜班20-03"<<"夜班20-03"<<"夜班20-03"<<"備註";




    // ui->tbUserList->setColumnCount(1);

    ui->tbUserList->hideColumn(0);
    ui->tbUserList->setColumnWidth(2,60);

    m_group.addButton(ui->btnCost,0);

    m_group.addButton(ui->btnName,1);

    m_group.addButton(ui->btnStatus,2);

    m_listBtn<<ui->btn0<<ui->btn1<<ui->btn2<<ui->btn3<<ui->btn4<<ui->btn5
            <<ui->btn6<<ui->btn7<<ui->btn8<<ui->btn9;


    // ^(-?\d+)(\.\d+)?$
    QRegExp ex("[0-9.]{1,6}");
    ui->txt->setValidator(new QRegExpValidator(ex,this));


    for(int i=0;i<m_listBtn.length();i++)
    {
        connect(m_listBtn[i],SIGNAL(clicked()),this,SLOT(btnsClicked()));
    }

    connect(ui->itemStatus,&ItemScheduleStatus::sendClicked,this,[=](QString sText,QString sColor)
    {


        QItemSelectionModel *selectionModel = ui->tb0->selectionModel();

        QModelIndexList indexes = selectionModel->selectedIndexes();

        QModelIndex index;

        QStringList userString;

        foreach(index, indexes) {
            m_data[index.row()][index.column()].sStatus = sText;
            m_data[index.row()][index.column()].sStatusColor = sColor;
            m_data[index.row()][index.column()].sCheck="0";
        }


        /*
        int iRow = ui->tb0->currentRow();

        int iCol = ui->tb0->currentColumn();

        if(iRow<0 ||iCol<0)
            return ;


        m_data[iRow][iCol].sStatus = sText;
        m_data[iRow][iCol].sStatusColor = sColor;
        */

        refresh();

        ui->tb0->setFocus();
    });



    ui->btnSchedulCheck->setDisabled(true);

    setEditMode(false);


}

LayerSchedule::~LayerSchedule()
{
    delete ui;
}

void LayerSchedule::setEditMode(bool b)
{
    m_bEditMode = b;

    ui->btnHeader->setVisible(m_bEditMode);

    ui->wFn->setVisible(m_bEditMode);

    ui->wKind->setVisible(m_bEditMode);

    ui->btnSave->hide();

    ui->btnSchedulCheck->hide();

    ui->itemStatus->setEditMode(m_bEditMode);
    if(!m_bEditMode)
    {
        ui->stackRight->setCurrentWidget(ui->rPageStatus);

        ui->btnSchedulCheck->show();

    }
    else
    {
        int iIdx = m_group.checkedId();

        ui->stackRight->setCurrentIndex(iIdx);

        ui->btnSave->show();

    }

}

void LayerSchedule::setOpenEditStatus(bool b)
{

    ui->itemStatus->setEditMode(b);
    ui->btnSave->setVisible(b);

}



void LayerSchedule::showEvent(QShowEvent *)
{
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(delayRefresh()));
}


void LayerSchedule::refresh()
{
    //color: rgb(0, 85, 255);


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

                    if(ACTION.m_currentUser.Sid==data.sUserSid)
                    {
                        l->setVisable(true,true,true);
                        l->setBorder(data.sCheck=="0");
                    }


                }

                QString sUserName= DATA.getUser(data.sUserSid).Name;

                l->setText(data.sCost,sUserName,data.sStatus);

                l->setText(2,data.sStatus,data.sStatusColor);

                ui->tb0->setCellWidget(iRow,iCol,l);
            }

        }
    }

    ui->tb0->setVerticalHeaderLabels(listV);

    checkUserList();


    checkTotal();
}

void LayerSchedule::keyPressEvent(QKeyEvent *e)
{
    int iRow = ui->tb0->currentRow();
    int iCol =ui->tb0->currentColumn();

    if(m_bEditMode && checkGrid(iRow,iCol))
    {

        if(e->key()==Qt::Key_Space || e->key()==Qt::Key_Backspace)
        {

            m_data[iRow][iCol].sCheck="0";

            if(m_group.checkedButton()==ui->btnCost)
                m_data[iRow][iCol].sCost ="";
            else  if(m_group.checkedButton()==ui->btnStatus)
                m_data[iRow][iCol].sStatus ="";
            else
                m_data[iRow][iCol].sUserSid ="";
            refresh();



        }

        else if (e->key()==Qt::Key_Escape)
        {

            m_data[iRow][iCol].sCheck="0";

            m_data[iRow][iCol].sCost ="";

            m_data[iRow][iCol].sStatus ="";

            m_data[iRow][iCol].sUserSid ="";

            refresh();


        }

        else if (e->key()==Qt::Key_PageDown)
        {
            int iIdx =m_group.checkedId();

            if(iIdx==0)
                iIdx=1;
            else
                iIdx=0;

            m_group.button(iIdx)->click();



        }
    }
}

bool LayerSchedule::checkGrid(int iRow, int iCol)
{
    if(iRow==-1)
        iRow = ui->tb0->currentRow();

    if(iCol==-1)
        iCol = ui->tb0->currentColumn();

    bool b=false;

    if(iRow%m_listVHeader.length()!=0 && iRow>=0
            && iRow< ui->tb0->rowCount()
            && iCol>=0 && iCol< ui->tb0->columnCount())
        b=true;


    return b;
}



void LayerSchedule::on_btnSave_clicked()
{

    qDebug()<<"btn save clicked ";


    int ret = DMSG.showMsg("","是否儲存？",QStringList()<<"否"<<"是");

    if(ret==1)
    {
        write();

        DMSG.showMsg("","儲存完成",QStringList()<<"OK");
    }

}

void LayerSchedule::on_btnSchedulCheck_clicked()
{
    int ret =DMSG.showMsg("","是否送出班表確認",QStringList()<<"OK");
    if(ret==1)
        sendUserCheck(ui->tb0->currentRow(),ui->tb0->currentColumn());

    DMSG.showMsg("","班表確認完成",QStringList()<<"OK");
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


                listRow.append(sTmp);
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
  QStringList listHeader = data["Header"].toString().split(",,");

  if(listHeader.length()>2)
      m_listVHeader= listHeader;


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

    QList<UserData> list = DATA.getUserList();

    int iRow=0;

    for(int i=0;i<list.length();i++)
    {
        iRow = ui->tbUserList->rowCount();
        ui->tbUserList->setRowCount(iRow+1);

        QString sName = list.at(i).Name;
        ui->tbUserList->setItem(iRow,0,UI.tbItem( list.at(i).Sid));
        ui->tbUserList->setItem(iRow,1,UI.tbItem(sName));


    }
}

void LayerSchedule::checkTotal()
{
    if(ui->tb0->rowCount()<0 || ui->tb0->columnCount()<0)
        return;

    QVariantMap dTotal;
    QVariantMap dUserCheck;

    for(int iRow=0;iRow<ui->tb0->rowCount() && iRow<128;iRow++)
    {
        for(int iCol=0;iCol<ui->tb0->columnCount()&&iCol<7;iCol++)
        {
            QString sUserSid = m_data[iRow][iCol].sUserSid;
            QString sCost = m_data[iRow][iCol].sCost;

            if(sUserSid.trimmed()=="")
                continue;

            //user check


            if(!dUserCheck.keys().contains(m_data[iRow][iCol].sUserSid))
                dUserCheck[sUserSid]="1";

            if(m_data[iRow][iCol].sCheck=="0")
                dUserCheck[sUserSid]="0";



            //money

            if(sCost.trimmed()=="")
                continue;

            if(!dTotal.keys().contains(m_data[iRow][iCol].sUserSid))
                dTotal[sUserSid]=0;


            int iTotalCost = dTotal[sUserSid].toInt();
            int iCurrentCost = sCost.toInt();

            if(m_data[iRow][iCol].sStatus.trimmed()!="")
            {
                QStringList statuRate=ui->itemStatus->getCost(m_data[iRow][iCol].sStatus,m_data[iRow][iCol].sStatusColor).split("+");

                if(statuRate.length()>1)
                {
                    double dTmp = iCurrentCost*statuRate.first().toDouble()+statuRate.last().toInt();

                    iCurrentCost=dTmp;

                }

            }

            dTotal[sUserSid]=iTotalCost+iCurrentCost;


        }

    }


    for(int i=0;i<ui->tbUserList->rowCount();i++)
    {
        QString sUserSid = ui->tbUserList->item(i,0)->text();

        QTableWidgetItem *item = UI.tbItem(ui->tbUserList->item(i,1)->text());


        item->setForeground(Qt::black);

        if(dUserCheck[sUserSid]=="1")
            item->setForeground(QColor(85,170,255));

        ui->tbUserList->setItem(i,1,item);

        ui->tbUserList->setItem(i,2,UI.tbItem(dTotal[sUserSid],GlobalUi::_AUTO,14));
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

    if(item->column()!=1)
        return;

    QString st = ui->tbUserList->item(item->row(),0)->text();

    QItemSelectionModel *selectionModel = ui->tb0->selectionModel();

    QModelIndexList indexes = selectionModel->selectedIndexes();

    QModelIndex index;

    QStringList userString;

    foreach(index, indexes)
    {
        QString sOriginUserSid =   m_data[index.row()][index.column()].sUserSid;
        m_data[index.row()][index.column()].sUserSid = st;
        if(sOriginUserSid!=st)
            m_data[index.row()][index.column()].sCheck="0";
    }

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
    QString sCost=btn->text();

#if 1
    QItemSelectionModel *selectionModel = ui->tb0->selectionModel();

    QModelIndexList indexes = selectionModel->selectedIndexes();

    QModelIndex index;

    QStringList userString;

    foreach(index, indexes) {
        m_data[index.row()][index.column()].sCost = btn->text();
        m_data[index.row()][index.column()].sCheck="0";
    }

    refresh();

    ui->tb0->setFocus();

#else
    int iRow= ui->tb0->currentRow();
    int iCol = ui->tb0->currentColumn();
    if(checkGrid(iRow,iCol))
    {

        m_data[iRow][iCol].sCost = btn->text();
        m_data[iRow][iCol].sCheck="0";
        refresh();

    }
    ui->tb0->setFocus();
#endif
}



void LayerSchedule::delayRefresh()
{

    if(!m_bEditMode)
    {
        setOpenEditStatus(ACTION.m_currentUser.Lv>=USER_LV::_LV3);

    }

    ui->btnNext->setEnabled(true);
    ui->btnPre->setEnabled(true);

    m_sYear = GLOBAL.dateTimeUtc8().toString("yyyy");
    m_sMonth = GLOBAL.dateTimeUtc8().toString("MM");

    ui->lbTitle->setText(m_sYear+" / "+m_sMonth);

    //ACTION.getUser(true);

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
    else
        ui->btnNext->setDisabled(false);


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
    else
         ui->btnPre->setDisabled(false);

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
            //ui->btnSave->setDisabled(true);
            ui->btnSchedulCheck->setDisabled(true);
            return ;
        }

        if(m_data[row][column].sUserSid== ACTION.m_currentUser.Sid)
        {
            ui->btnSchedulCheck->setDisabled(false);
        }
        else
        {
            ui->btnSchedulCheck->setDisabled(true);
        }

    }
}




void LayerSchedule::on_btnScheduleClear_clicked()
{

    int iRet = DMSG.showMsg("","清除後按下'儲存本月修改'，才會生效，\n確定要清除目前頁面資料嗎？",QStringList()<<"否"<<"是");

    if(iRet!=1)
        return;

    for(int iRow=0;iRow<128;iRow++)
    {
        for(int iCol=0;iCol<7;iCol++)
        {
            m_data[iRow][iCol].sCost = "";

            m_data[iRow][iCol].sStatus = "";

            m_data[iRow][iCol].sUserSid = "";
            m_data[iRow][iCol].sCheck="0";
        }

    }

    refresh();
}


void LayerSchedule::on_btnHeader_clicked()
{

    QStringList list = m_listVHeader;
    QStringList reHeader;

    if(list.length()>0 && list.first().trimmed()=="")
        list.pop_front();

    // 找到第一个 "A" 的位置
    int indexA = list.indexOf("備註");

    // 创建两个子列表
    QStringList a = list.mid(0, indexA); // 获取第一个 "A" 之前的元素

    // 获取第一个 "A" 之后的部分，直到第二个 "A" 或列表末尾
    QStringList b = list.mid(indexA + 1);
    int nextAIndex = b.indexOf("備註"); // 在子列表 b 中查找下一个 "A"
    if (nextAIndex != -1) {
        b = b.mid(0, nextAIndex); // 如果找到了第二个 "A"，只保留之前的元素
    }

    m_editHeader->setData(a,b);
    m_editHeader->setWindowModality(Qt::ApplicationModal); // 設置模態窗口
    m_editHeader->setGeometry(0,0,width(),height());
    m_editHeader->show();

    m_editHeader->raise();


}

