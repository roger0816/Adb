#include "widget.h"
#include "ui_widget.h"

#define varName(x) #x



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("艾比代管理系統");

    m_btns.addButton(ui->btn0,0);
    m_btns.addButton(ui->btn1,1);
    m_btns.addButton(ui->btn2,2);
    m_btns.addButton(ui->btn3,3);
    m_btns.addButton(ui->btn4,4);
    m_btns.addButton(ui->btnAccount,5);
    m_btns.addButton(ui->btnTest,6);

    for(int i=0;i<m_btns.buttons().length();i++)
    {
        m_btns.button(i)->setEnabled(false);
    }


    connect(&m_btns,SIGNAL(buttonClicked(int)),this,SLOT(slotPage(int)));


    ui->stackedWidget->setCurrentIndex(0);

    QString sAA="aa";

    auto fn = [=](QString *st)
    {
        qDebug()<<varName(st);
    };

    fn(&sAA);


    //    QString key="sAA";

    //    if(key.compare(sAA) ==0)
    //    {

    //    }




}

Widget::~Widget()
{
    delete ui;
}



void Widget::slotPage(int iIdx)
{
    ui->stackedWidget->setCurrentIndex(iIdx);
}





void Widget::on_btnTest_clicked()
{
    CData data;

    data.iAciton=ACT::LOGIN;

    data.sUser="root";

    data.sMsg="msgA";

    data.listData<<"listA"<<"listB"<<"listC";

    data.listName<<"listNameA"<<"listNameB"<<"listNameC";

    data.dData["A"]="a";

    data.dData["B"]="b";

    data.dData["C"]="c";

    CData outData;

    QByteArray out;

    RPKCORE.network.connectHost("127.0.0.1","6000",data.enCodeJson(),out);

    outData.deCodeJson(out);

    qDebug()<<outData.iAciton;

    qDebug()<<outData.sUser;
    qDebug()<<outData.sMsg;
    qDebug()<<outData.listData;
    qDebug()<<outData.listName;

    qDebug()<<outData.dData;

}

void Widget::showEvent(QShowEvent *)
{
    ui->lbName->setText(ACTION.m_currentUser.Name);
    setLv(ACTION.m_currentUser.Lv);
}

void Widget::setLv(int iLv)
{
    ui->btn0->setEnabled(true);

    ui->btn1->setEnabled(true);

    ui->btnAccount->setEnabled(true);

    if(iLv>=USER_LV::_LV2)
    {
        ui->btn2->setEnabled(true);

    }

    if(iLv>=USER_LV::_LV3)
    {
        ui->btn3->setEnabled(true);
    }

    if(iLv>=USER_LV::_LV4)
    {
        ui->btn4->setEnabled(true);
    }

    if(iLv>=USER_LV::_ROOT)
    {
        ui->btnTest->setEnabled(true);
    }

}




void Widget::on_btnLogout_clicked()
{
    this->hide();

    UI.m_dialogLogin->init();

    UI.m_dialogLogin->exec();
}

