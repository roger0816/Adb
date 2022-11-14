#include "DialogGameEdit.h"
#include "ui_DialogGameEdit.h"

DialogGameEdit::DialogGameEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGameEdit)
{
    ui->setupUi(this);

    ui->cbEnable->hide();

    setWindowTitle("遊戲清單設定");

    ui->btnDel->hide();

    setTabOrder(ui->cbEnable,ui->txId);

    setTabOrder(ui->txId,ui->txName);

    setTabOrder(ui->txName,ui->btnOk);

    ui->lbMsg->clear();


    QRegExp r("\\w{0,5}");

    ui->txId->setValidator(new QRegExpValidator(r,this));
}

DialogGameEdit::~DialogGameEdit()
{
    delete ui;
}

void DialogGameEdit::setData(QString sSid, bool bEnable, QString sId, QString sName, double iGameRate)
{
    m_bIsAddType = false;

    m_sSid = sSid;

    ui->btnDel->show();

    ui->lbTitle->setText("編輯遊戲");

    ui->txId->setReadOnly(true);

    ui->txId->setEnabled(false);

    ui->txId->setText(sId);

    ui->txName->setText(sName);

    ui->cbEnable->setChecked(bEnable);

    ui->dbGameRate->setValue(iGameRate);
}

void DialogGameEdit::on_btnCancel_clicked()
{
    reject();
}


void DialogGameEdit::on_btnOk_clicked()
{
    ui->lbMsg->clear();

    QVariantList listOut;

    bool b = ACTION.action(ACT::QUERY_GAME_LIST,QVariantMap(),listOut);

    if(!b)
    {
        ui->lbMsg->setText("錯誤代號401");
        return;
    }

    QString sId = ui->txId->text().trimmed();
    QString sName = ui->txName->text().trimmed();

    bool bHasOne = false;

    GameList gameList;
    gameList.setGameList(listOut);

    foreach(GameList::GameData data,gameList.listData)
    {
        if(data.Id.toUpper()==sId.toUpper() || data.Name.toUpper()==sName.toUpper())
        {
            bHasOne = true;
            break;
        }
    }

    if(bHasOne && m_bIsAddType)
    {
        ui->lbMsg->setText("代號或名稱，不能重復。");
        return;
    }


    if(sId=="" || sName=="")
    {
        ui->lbMsg->setText("代號與名稱，不能空白。");
        return;
    }

    m_sId = sId;

    m_sName = sName;

    m_bEnable = ui->cbEnable->isChecked();

    m_iGameRate = ui->dbGameRate->value();

    if(m_sSid=="")
    {
        //add
        done(1);

    }
    else
    {
        //edit
        done(2);
    }



}


void DialogGameEdit::on_btnDel_clicked()
{
    int iRet = DMSG.showMsg("","刪除遊戲時，對應的商品也會全刪除，確定是否刪除？",QStringList()<<"否"<<"是");

    if(iRet==1)
    {

        done(3);
    }
}

