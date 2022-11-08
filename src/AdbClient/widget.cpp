#include "widget.h"
#include "ui_widget.h"

#define varName(x) #x



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);




    QFile file(":/style.qss");

    if(file.open(QIODevice::ReadOnly))
    {

        QString style= QLatin1String(file.readAll());

        qApp->setStyleSheet(style);
        file.close();
    }
    this->setWindowTitle("艾比代管理系統");

    connect(&ACTION,SIGNAL(lockLoading(bool)),&UI,SLOT(slotLockLoading(bool)));

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


    ui->stackedWidget->setCurrentWidget(ui->pagePreLoad);

    UI.m_loading = new ItemMiniLoadbar(this);


    UI.m_loading->hide();
}

Widget::~Widget()
{
    delete ui;
}



void Widget::slotPage(int iIdx)
{

    ui->stackedWidget->setCurrentIndex(iIdx);

    if(ui->stackedWidget->currentWidget()==ui->pageService)
    {
        ui->pageService->changePage(0);
    }


}





void Widget::on_btnTest_clicked()
{

    ui->stackedWidget->setCurrentIndex(6);
    return ;
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



}

void Widget::showEvent(QShowEvent *)
{


}

void Widget::resizeEvent(QResizeEvent *)
{
    UI.m_loading->resize(this->size());
}

void Widget::checkUserLv()
{
    ui->lbName->setText(ACTION.m_currentUser.Name);

    int iLv = ACTION.m_currentUser.Lv;

    qDebug()<<"USER LV :"<<iLv;

    ui->btnTest->hide();


    foreach(QAbstractButton *btn,m_btns.buttons())
    {
        btn->setEnabled(false);
    }

    ui->btn0->setEnabled(true);

    ui->btn1->setEnabled(true);

    ui->btnAccount->setEnabled(true);



    if(iLv>=USER_LV::_LV2)
    {
        ui->btn2->setEnabled(true);

    }

    if(iLv>=USER_LV::_LV3)
    {
        ui->btn4->setEnabled(true);
    }

    if(iLv>=USER_LV::_LV4)
    {

        ui->btn3->setEnabled(true);
    }

    // if(iLv>=USER_LV::_ROOT)
    {
        ui->btnTest->setEnabled(true);
        ui->btnTest->show();
    }

    UI.m_loading->resize(this->size());


}




void Widget::on_btnLogout_clicked()
{
    this->hide();

    UI.m_dialogLogin->init();

    UI.m_dialogLogin->exec();
}

void Widget::slotLogin()
{
    qDebug()<<"login ";


    ACTION.setStartSyanc(true);

    QTimer::singleShot(1100,[=]()
    {
        ACTION.reQuerty();
        qDebug()<<"preload ok";
        show();
        qDebug()<<"main ui show";

        ui->stackedWidget->setCurrentIndex(0);
          checkUserLv();
    });


}

