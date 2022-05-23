#include "StageManagerSetting.h"
#include "ui_StageManagerSetting.h"

StageManagerSetting::StageManagerSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageManagerSetting)
{
    ui->setupUi(this);


    m_btns.addButton(ui->btn0,0);

    m_btns.addButton(ui->btn1,1);

    m_btns.addButton(ui->btn2,2);

    m_btns.addButton(ui->btn3,3);
    m_btns.addButton(ui->btn4,4);

    m_btns.addButton(ui->btn5,5);


    connect(&m_btns,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    ui->tabWidget->setCurrentIndex(0);

    ui->stackedWidget->setCurrentIndex(0);


}

StageManagerSetting::~StageManagerSetting()
{
    delete ui;
}

void StageManagerSetting::on_btnAdd_clicked()
{


    int iRet = DMSG.showMsg("","是否新增使用者 : "+ui->txAddId->text().trimmed(),QStringList()<<"否"<<"是");

    if(iRet==1)
    {
        QString sError;

        int iLv =1;

        if(ui->cbAddLv->currentIndex()==ui->cbAddLv->count()-1)
            iLv =99;
        else
            iLv = ui->cbAddLv->currentIndex()+1;

        bool bOk = ACTION.addUser(ui->txAddId->text().trimmed(),ui->txAddPass->text().trimmed(),
                                  ui->txAddCid->text().trimmed(), ui->txAddName->text(),
                                  iLv,ui->caAddDate->selectedDate(),sError);

        if(bOk)
        {
            DMSG.showMsg("",ui->txAddId->text().trimmed()+" 新增成功!",QStringList()<<"OK");

        }
        else
        {

            ui->lbAddMsg->setText("");

            DMSG.showMsg("",sError,QStringList()<<"OK");


        }



    }
}


void StageManagerSetting::on_btnEdit_clicked()
{

    if(ui->tb->currentRow()<0)
    {

        DMSG.showMsg("","請先選擇編輯的目標 !",QStringList()<<"OK");

        return ;
    }

    DialogEditUser edit;

    int idx =qBound(0,ui->tb->currentRow(),m_listUser.length()-1);

    edit.setData(m_listUser[idx].data());

    QString sError;

    if(edit.exec()==1)
    {
        bool bOk = ACTION.editUser(edit.data(),sError);

        if(bOk)
        {
            refreshTb();

            DMSG.showMsg("","資料已修改",QStringList()<<"OK");
        }
        else
        {

            DMSG.showMsg("",sError,QStringList()<<"OK");
        }
    }


}

void StageManagerSetting::showEvent(QShowEvent *)
{
      refreshTb();
}

void StageManagerSetting::refreshTb()
{
    m_listUser = ACTION.queryUser();


    ui->tb->setRowCount(0);

    for(int i=0;i<m_listUser.length();i++)
    {
        UserData user = m_listUser.at(i);

        ui->tb->setRowCount(i+1);

        ui->tb->setItem(i,0, tbItem(0,user.Id));

        ui->tb->setItem(i,1, tbItem(1,user.Name));

        ui->tb->setItem(i,2, tbItem(2,user.Cid));

        int iLv =user.Lv;
        QString sLv = "客服專員";
        if(iLv==99)
            sLv = "系統管理員";
        else if(iLv==USER_LV::_LV2)
            sLv = "儲值專員";
        else if(iLv==USER_LV::_LV3)
            sLv = "主管";
        else if(iLv==USER_LV::_LV4)
            sLv = "會計";

        ui->tb->setItem(i,3, tbItem(3,sLv));
        QString sDate = QDate::fromString(user.StartDay,"yyyyMMdd").toString("yyyy/MM/dd");
        ui->tb->setItem(i,4, tbItem(4,sDate));
        sDate = QDate::fromString(user.BirthDay,"yyyyMMdd").toString("yyyy/MM/dd");
        ui->tb->setItem(i,5, tbItem(5,sDate));
        ui->tb->setItem(i,6, tbItem(6,user.Tel));
        ui->tb->setItem(i,7, tbItem(7,user.Email));

        sDate = QDateTime::fromString(user.CreateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd");
        ui->tb->setItem(i,8, tbItem(8,sDate));
        sDate = QDateTime::fromString(user.UpdateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd");
        ui->tb->setItem(i,9, tbItem(9,sDate));


    }
}

QTableWidgetItem *StageManagerSetting::tbItem(int , QString st)
{
    QTableWidgetItem *item = new QTableWidgetItem(st);
    item->setTextAlignment(Qt::AlignCenter);

    return item;
}


void StageManagerSetting::on_tabWidget_currentChanged(int index)
{
    if(index==1)
        refreshTb();
}


void StageManagerSetting::on_btnDel_clicked()
{
    DialogMsg dialog;


    if(ui->tb->currentRow()<0 || ui->tb->currentRow()>=ui->tb->rowCount())
    {

        dialog.setDialogInfo("請選擇要刪除的帳號!",QStringList()<<"確定");

        dialog.exec();

        return;
    }
    else
    {
        QString sUser= ui->tb->item(ui->tb->currentRow(),0)->text();
        QString sName = ui->tb->item(ui->tb->currentRow(),1)->text();

        QString sTemp =sUser+"("+sName+")";

        dialog.setDialogInfo("確定要刪除 "+sTemp+" ? ",QStringList()<<"否"<<"是");

        if(dialog.exec()==1)
        {
            QString sError;
            bool bOk = ACTION.delUser(sUser,sError);

            if(bOk)
            {
                dialog.setDialogInfo(sTemp+" 刪除成功! ",QStringList()<<"OK");
            }
            else
            {
                dialog.setDialogInfo(" 刪除失敗! 錯誤:"+sError,QStringList()<<"OK");
            }

            dialog.exec();

            refreshTb();
        }
    }


}

