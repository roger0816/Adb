#include "LayerAccountManager.h"
#include "ui_LayerAccountManager.h"

LayerAccountManager::LayerAccountManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAccountManager)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

}

LayerAccountManager::~LayerAccountManager()
{
    delete ui;
}

void LayerAccountManager::showEvent(QShowEvent *)
{
    ui->tabWidget->setCurrentIndex(0);
    ui->txAddId->clear();
    ui->txAddCid->clear();
    ui->txAddName->clear();
     ui->txAddPass->clear();
      ui->txAddPass2->clear();
    QTimer::singleShot(30,Qt::PreciseTimer,this,SLOT(refresh()));
}

void LayerAccountManager::refresh()
{
    m_listUser = ACTION.queryUser();


    ui->tb->setRowCount(0);

    for(int i=0;i<m_listUser.length();i++)
    {
        UserData user = m_listUser.at(i);

        ui->tb->setRowCount(i+1);

        ui->tb->setItem(i,0, UI.tbItem(user.Id));

        ui->tb->setItem(i,1, UI.tbItem(user.Name));

        ui->tb->setItem(i,2, UI.tbItem(user.Cid));

        int iLv =user.Lv;
        QString sLv = GLOBAL.userLvToStr(iLv);



        ui->tb->setItem(i,3, UI.tbItem(sLv));
        QString sDate = QDate::fromString(user.StartDay,"yyyyMMdd").toString("yyyy/MM/dd");
        ui->tb->setItem(i,4, UI.tbItem(sDate));
        sDate = QDate::fromString(user.BirthDay,"yyyyMMdd").toString("yyyy/MM/dd");
        ui->tb->setItem(i,5, UI.tbItem(sDate));
        ui->tb->setItem(i,6, UI.tbItem(user.Tel));
        ui->tb->setItem(i,7, UI.tbItem(user.Email));

        sDate = QDateTime::fromString(user.CreateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd");
        ui->tb->setItem(i,8, UI.tbItem(sDate));
        sDate = QDateTime::fromString(user.UpdateTime,"yyyyMMddhhmmss").toString("yyyy/MM/dd");
        ui->tb->setItem(i,9, UI.tbItem(sDate));


    }
}

bool LayerAccountManager::checkRule(QString &sErrorMsg)
{
    bool bRe = false;

    if(ui->txAddId->text().length()<6)
    {
        sErrorMsg="帳號不能少於6個字母";
    }
    else if(ui->txAddPass->text().length()<6)
    {
        sErrorMsg ="密碼不能少於6個字母";
    }

    else if(ui->txAddPass->text().trimmed() != ui->txAddPass2->text().trimmed())
    {
        sErrorMsg ="密碼再確認錯誤";
    }
    else
        bRe = true;


    return bRe;
}

void LayerAccountManager::on_btnAdd_clicked()
{


    int iRet = DMSG.showMsg("","是否新增使用者 : "+ui->txAddId->text().trimmed(),QStringList()<<"否"<<"是");

    if(iRet==1)
    {
        bool bOk = false;

        QString sError="新增失敗";

        int iLv =1;

        if(ui->cbAddLv->currentIndex()==ui->cbAddLv->count()-1)
            iLv =99;
        else
            iLv = ui->cbAddLv->currentIndex()+1;


        if(checkRule(sError))
        {
            bOk = ACTION.addUser(ui->txAddId->text().trimmed(),ui->txAddPass->text().trimmed(),
                                ui->txAddCid->text().trimmed(), ui->txAddName->text(),
                                iLv,ui->caAddDate->selectedDate(),sError);
        }

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



void LayerAccountManager::on_btnEdit_clicked()
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
            refresh();

            DMSG.showMsg("","資料已修改",QStringList()<<"OK");
        }
        else
        {

            DMSG.showMsg("",sError,QStringList()<<"OK");
        }
    }



}

void LayerAccountManager::on_tabWidget_currentChanged(int index)
{
    if(index==1)
        refresh();
}

void LayerAccountManager::on_btnDel_clicked()
{
    DialogMsg dialog;


    int iRow =ui->tb->currentRow();

    if(ui->tb->currentRow()<0 || iRow>=ui->tb->rowCount()
            || iRow>=m_listUser.length())
    {

        dialog.setDialogInfo("請選擇要刪除的帳號!",QStringList()<<"確定");

        dialog.exec();

        return;
    }
    else
    {

        UserData user = m_listUser.at(iRow);

        QString sTemp =user.Id+"("+user.Name+")";

        dialog.setDialogInfo("確定要刪除 "+sTemp+" ? ",QStringList()<<"否"<<"是");

        if(dialog.exec()==1)
        {
            QString sError;
            bool bOk = ACTION.delUser(user.Sid,sError);

            if(bOk)
            {
                dialog.setDialogInfo(sTemp+" 刪除成功! ",QStringList()<<"OK");
            }
            else
            {
                dialog.setDialogInfo(" 刪除失敗! 錯誤:"+sError,QStringList()<<"OK");
            }

            dialog.exec();

            refresh();
        }
    }


}
