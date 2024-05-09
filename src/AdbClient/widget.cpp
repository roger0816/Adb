#include "widget.h"
#include "ui_widget.h"

#define varName(x) #x


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
/*
    connect(&DATA,&UpdateData::callUpdate,this,[=](QByteArray data){
            bool bOk = RPKCORE.network.sendData("",data);

         //   qDebug()<<"send data is :"<<bOk;
            if(!bOk)
            {
                QTimer::singleShot(500,this,[=]{
                    RPKCORE.network.sendData("",data);
                });
            }
    });

    connect(&RPKCORE.network,&Network::singalLongConnect,&DATA,&UpdateData::slotRead);
*/
    m_networkUpdate = new Network(this);

    connect(&DATA,&UpdateData::callUpdate,this,[=](QByteArray data){
            bool bOk = m_networkUpdate->sendData("",data);

         //   qDebug()<<"send data is :"<<bOk;
            if(!bOk)
            {
                QTimer::singleShot(500,this,[=]{
                    m_networkUpdate->sendData("",data);
                });
            }
    });

    connect(m_networkUpdate,&Network::singalLongConnect,&DATA,&UpdateData::slotRead);

    connect(&DATA,&UpdateData::firstFinished,this,[=](){
        UI.slotLockLoading(false);
    });

    m_wMargee= new ItemMargee(ui->wTopLeft);
    m_wMargee->move(0,0);

    ui->lbTestName->hide();

    QFile file(":/style.qss");

    if(file.open(QIODevice::ReadOnly))
    {

        QString style= QLatin1String(file.readAll());

        qApp->setStyleSheet(style);
        file.close();
    }
    this->setWindowTitle("艾比代管理系統      "+QString(ADP_VER));

    connect(&ACTION,SIGNAL(lockLoading(bool)),&UI,SLOT(slotLockLoading(bool)));


    connect(&ACTION,SIGNAL(sessionError()),this,SLOT(slotSessionError()));


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


    m_touchCheck = new LayerTouchCheck(this);

    m_touchCheck->hide();

    ui->btnTest->hide();
    ui->btnTest2->hide();

    connect(&DATA,&UpdateData::updateNotify,[=](int iType,QStringList listSid){
        if( iType == BULLETIN_DATA)
        {
            qDebug()<<"update BULLETIN_DATA UIdata ";
            QVariantList list = DATA.getBulletin();

            for(int i=0;i<list.length();i++)
            {
                 qDebug()<<"update BULLETIN_DATA UIdata 1";
                QVariantMap data = list.at(i).toMap();

                 qDebug()<<"update BULLETIN_DATA UIdata 2";
                QDateTime End=QDateTime::fromString(data["EndTime"].toString(),"yyyyMMddhhmmss");

                if(!listSid.contains(data["Sid"].toString()) ||  End.toSecsSinceEpoch()<=GLOBAL.dateTimeUtc8().toSecsSinceEpoch())
                    continue;

                 qDebug()<<"update BULLETIN_DATA UIdata 3";
                if(data["Type"].toString() =="0")
                {
                    QString sUserName = DATA.getUser(data["UserSid"].toString()).Name+" : ";
                   // QString st=data["Title"].toString()+" : "+data["Content"].toString();
                    m_wMargee->appendText(data["Title"].toString(),sUserName,data["Content"].toString().replace("\n","  "));
                }

            }


             qDebug()<<"update BULLETIN_DATA UIdata : OK";
        }
    });

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

    else if(ui->stackedWidget->currentWidget()== ui->pageOrder)
    {
        ui->pageOrder->init();
    }

}





void Widget::on_btnTest_clicked()
{




}

void Widget::showEvent(QShowEvent *)
{



    ui->lbTestName->setVisible(ACTION.m_bTest);
    ui->btnTest->setVisible(ACTION.m_bTest);
    if(ACTION.m_bTest)
    {



        ui->wTop->setStyleSheet("QWidget#wTop{background-color:lightgray;}");

        //  ui->wMenu->setStyleSheet("QWidget#wMenu{background-color:;}");


    }
    else
    {

        //    ui->wMenu->setStyleSheet("QWidget#wMenu{background-color:rgb(0, 37, 88);}");

        ui->wTop->setStyleSheet("QWidget#wTop{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));}");
    }
    m_wMargee->resize(ui->wTopLeft->size());
}

void Widget::resizeEvent(QResizeEvent *)
{
    UI.m_loading->resize(this->size());

    m_touchCheck->resize(size());

    m_wMargee->resize(ui->wTopLeft->size());
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

    if(iLv>=USER_LV::_ROOT)
    {
        ui->btnTest->setEnabled(true);
        // ui->btnTest->show();
    }

    UI.m_loading->resize(this->size());


}




void Widget::on_btnLogout_clicked()
{
    ACTION.setStartSyanc(false);

    this->hide();

    UI.m_dialogLogin->init();

    UI.m_dialogLogin->exec();
}

void Widget::slotLogin()
{


    ACTION.setStartSyanc(true);

//    QEventLoop *loop=new QEventLoop(this);

//    //   loop.connect(&timer,&QTimer::timeout,&loop,&QEventLoop::quit);

//    QTimer::singleShot(1000,[=]()
//    {
//        loop->quit();

//        delete loop;
//    });

//    loop->exec();

    /*
    if(ACTION.isNewVersion())
        ACTION.reQuerty();
    else
        ACTION.reQuertyOld();
        */

  //  ui->pageHome->setBulletinData(ACTION.m_listBulletin);

    show();

    qDebug()<<"main ui show "<<size();
    checkUserLv();
    ui->stackedWidget->setCurrentIndex(0);


    int iTmp = ACTION.m_port.toInt()+10;

   // DATA.connectIp(ACTION.m_ip,QString::number(iTmp));

      //RPKCORE.network.openConnect(ACTION.m_ip,QString::number(iTmp));

    m_networkUpdate->openConnect(ACTION.m_ip,QString::number(iTmp));


      DATA.m_sUserSid = ACTION.m_sCurrentUserId;
    DATA.setRun(true);
     UI.slotLockLoading(true);

}

void Widget::slotSessionError()
{

    ACTION.setStartSyanc(false);

    this->hide();

    UI.m_dialogLogin->init("登入失敗，網路異常或帳號重複登入");

    UI.m_dialogLogin->exec();

    // DMSG.showMsg("","連線失敗，網路狀態異常或帳密重複登入","OK");
}






void Widget::on_btnTest2_clicked()
{
    UI.m_loading->setLoading(true);
}

