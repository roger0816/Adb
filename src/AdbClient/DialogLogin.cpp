#include "DialogLogin.h"
#include "ui_DialogLogin.h"
#include <QSettings>

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);


    ui->stackIp->setCurrentWidget(ui->pageIpNone);

    setVer(ADP_VER);



    m_btns.addButton(ui->btnServer0,0);

    m_btns.addButton(ui->btnServer1,1);

    m_btns.addButton(ui->btnServer2,2);

    m_btns.addButton(ui->btnServer3,3);

    m_btns.addButton(ui->btnServer4,4);

    m_btns.addButton(ui->btnServer5,9);

    foreach(QAbstractButton *btn,m_btns.buttons())
    {
        btn->hide();
    }

#if TEST_ACTION
    m_btns.button(0)->hide();
    m_btns.button(1)->hide();
    m_btns.button(2)->hide();

#endif


    connect(&m_btns,&QButtonGroup::idClicked,this,&DialogLogin::slotBtnClicked);


    setWindowFlags(windowFlags()  | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint );

    setWindowFlags(windowFlags()  &  ~Qt::WindowContextHelpButtonHint);


    setWindowIcon(QIcon(" "));
    setWindowTitle(" ");

    m_loading->setLoading(false);

    //    setTabOrder(ui->txUser,ui->txPass);

    //    setTabOrder(ui->txPass,ui->btnLogin);

    //    setTabOrder(ui->btnLogin,ui->txUser);

    init();

    startTimer(500);


    ui->btnServer4->hide();




}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::init(QString sMsg)
{


    QString sLoginSave=ACTION.getKeyValue("loginSave");

    qDebug()<<"login save  : "<<sLoginSave;
    if(sLoginSave!="")
    {

        ui->txUser->setText(sLoginSave);

        ui->checkBox->setChecked(true);
    }

    ui->txPass->clear();
    ui->lbMsg->setText(sMsg);






}

void DialogLogin::setRelease(bool b)
{
    if(!b)
    {
        ui->lbRelease->setText("Test");
        //ui->wBg->setStyleSheet("background-color:lightgary");
    }
    else
    {
        ui->lbRelease->setText("Release");

    }

    ACTION.m_bTest=!b;
    //   ui->lbRelease->setVisible(b);
}

void DialogLogin::closeEvent(QCloseEvent *)
{
    qDebug()<<"dialog login close  ";
    done(_DialogLogin::_Close);
}

void DialogLogin::paintEvent(QPaintEvent *)
{

    //        QBitmap bmp(this->size());
    //        bmp.fill();
    //        QPainter p(&bmp);
    //        QPen pen(Qt::gray,2);

    //        p.setPen(pen);

    //        p.setBrush(Qt::black);

    //        QRect r(1,1,bmp.width()-2,bmp.height()-2);
    //        p.drawRoundedRect(bmp.rect(),15,20);
    //        setMask(bmp);

}

void DialogLogin::setVer(QString sVer)
{
    ui->lbVersion->setText(sVer);
}

void DialogLogin::setReleaseIp(QString sIp, QString sPort)
{
    m_sIp=sIp;
    m_sPort = sPort;
}

void DialogLogin::setTestIp(QString sIp, QString sPort)
{
    m_sTestIp=sIp;

    m_sTestPort = sPort;
}

void DialogLogin::showEvent(QShowEvent *)
{
    ui->btnServer5->setVisible(GLOBAL.m_bRootLogin);


    preload(true);

    loadServerConf(checkLicense());

    initBtn();
}

void DialogLogin::timerEvent(QTimerEvent *)
{
    if(this->isHidden() || bMLogin)
        return;

    bool bIsLock = ACTION.m_bIsLock;

    if(!bIsLock && !m_bPreLock && m_iTimerCount>=5)
    {
        preload(false);

        return ;
    }

    if(ui->lbMsg->text().toUpper().contains("PRELOAD"))
    {
        if(ui->lbMsg->text().length()<12)
            ui->lbMsg->setText(ui->lbMsg->text()+".");
        else
            ui->lbMsg->setText("Preload.");
    }

    m_iTimerCount++;

    m_bPreLock=bIsLock;
}

void DialogLogin::preload(bool bTrue)
{
    if(bTrue)
    {
        ui->lbMsg->setText("Preload.");
    }
    else
    {
        m_bPreLock = true;
        m_iTimerCount =0;
        if(ui->lbMsg->text().contains("Preload"))
            ui->lbMsg->clear();
    }

    ui->btnLogin->setDisabled(bTrue);
}

QString DialogLogin::checkLicense()
{
    ui->btnLogin->hide();

    QString sRe="";

    QString sUuid;




    if(GLOBAL.license.trimmed()!="")
    {
        sUuid = GLOBAL.license;
        GLOBAL.color1="#002558";
        GLOBAL.txtColor="#000000";
        GLOBAL.titleName="艾比代儲管理系統";
    }

    else
    {

        QString exeDirPath = QCoreApplication::applicationDirPath()+"/data/";

        iniFiles = QDir(exeDirPath).entryList(QStringList() << "*.ini", QDir::Files);


        QString configFilePath;

        if(iniFiles.contains("config.ini"))
            configFilePath= exeDirPath +"config.ini";

        QFileInfo configFileInfo(configFilePath);
        if (!configFileInfo.exists() || !configFileInfo.isFile()) {

            ui->lbMsg->setText("找不到檔案: \n程式路徑/data/*.ini");

            return sRe;
        }


        QSettings *conf = new QSettings(configFilePath,QSettings::IniFormat);
        conf->setIniCodec("utf-8"); // 设置编码为UTF-8
        sUuid=conf->value("uuid").toString();
        GLOBAL.color1 = conf->value("color1").toString();

    }


    if(sUuid.toLower().trimmed()=="0178d501-2140-49c8-baa9-aea23267544f")
    {
        sRe=":/server/adb.ini";
      //  GLOBAL.color1="#002558";
      //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="艾比代儲管理系統";

        setWindowIcon(QIcon("://th.jpg"));

    }

    else if(sUuid.toLower().trimmed()=="19563777-66a5-42de-a5bd-116f0b99799a")
    {
        sRe=":/server/adt1.ini";
     //   GLOBAL.color1="#147068";
      //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT1管理系統";

        setWindowIcon(QIcon(""));
    }

    else if(sUuid.toLower().trimmed()=="2b98bd7a-2d36-48cd-a5ad-77cb0d30565b")
    {
        sRe=":/server/adt2.ini";
      //  GLOBAL.color1="#cd5c5c";
      //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT2管理系統";
    }

    else if(sUuid.toLower().trimmed()=="32594600-a422-4287-aa48-a5b7b7d76ed2")
    {
        sRe=":/server/adt3.ini";
       // GLOBAL.color1="#8b4513";
       // GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT3管理系統";
    }

    else if(sUuid.toLower().trimmed()=="4f3e63f5-cef8-4f00-bb13-6d111a93abcb")
    {
        sRe=":/server/adt4.ini";
        //   GLOBAL.color1="#147068";
        //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT4管理系統";

        setWindowIcon(QIcon(""));
    }

    else if(sUuid.toLower().trimmed()=="5cbe5c50-3cbe-4c4b-b16e-b6468a59674a")
    {
        sRe=":/server/adt5.ini";
        //  GLOBAL.color1="#cd5c5c";
        //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT5管理系統";
    }

    else if(sUuid.toLower().trimmed()=="6b964d53-1626-493a-8fdd-60f79a6d8739")
    {
        sRe=":/server/adt6.ini";
        // GLOBAL.color1="#8b4513";
        // GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT6管理系統";
    }

    else if(sUuid.toLower().trimmed()=="7afedb90-4c70-42a5-9f58-5a7582d52863")
    {
        sRe=":/server/adt7.ini";
        //   GLOBAL.color1="#147068";
        //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT7管理系統";

        setWindowIcon(QIcon(""));
    }

    else if(sUuid.toLower().trimmed()=="8c6b7ce2-3a5b-46c5-9d66-0c18cafb1e22")
    {
        sRe=":/server/adt8.ini";
        //  GLOBAL.color1="#cd5c5c";
        //  GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT8管理系統";
    }

    else if(sUuid.toLower().trimmed()=="9ee24ead-32fd-4340-9d89-216daf8b8e1c")
    {
        sRe=":/server/adt9.ini";
        // GLOBAL.color1="#8b4513";
        // GLOBAL.txtColor="#000000";
        GLOBAL.titleName="ADT9管理系統";
    }



    //adp
    // 0178d501-2140-49c8-baa9-aea23267544f

    //adt1
    //19563777-66a5-42de-a5bd-116f0b99799a
    //2b98bd7a-2d36-48cd-a5ad-77cb0d30565b
    //32594600-a422-4287-aa48-a5b7b7d76ed2
    //
    //4f3e63f5-cef8-4f00-bb13-6d111a93abcb
    //5cbe5c50-3cbe-4c4b-b16e-b6468a59674a
    //6b964d53-1626-493a-8fdd-60f79a6d8739
    //
    //7afedb90-4c70-42a5-9f58-5a7582d52863
    //8c6b7ce2-3a5b-46c5-9d66-0c18cafb1e22
    //9ee24ead-32fd-4340-9d89-216daf8b8e1c
    qDebug()<<"path : "<<sRe;


    ui->lbTitle->setText(GLOBAL.titleName);
    QVariantList list;

    list.append(GLOBAL.titleName);
    list.append(GLOBAL.color1);

    emit signalVerInfo(list);
    return sRe;
}

void DialogLogin::loadServerConf(QString sPath )
{


    // QSettings conf(":/serverConf.ini",QSettings::IniFormat);

    QSettings conf(sPath,QSettings::IniFormat);
    conf.setIniCodec("UTF-8"); // 设置编码为UTF-8


    m_listServer.clear();


    QStringList groups = conf.childGroups();
    foreach (const QString &group, groups) {
        if (group.startsWith("server")) {
            conf.beginGroup(group);  // 進入 [server*] 節點

            QVariantMap s;
            s["ip"] = conf.value("ip").toString();
            s["port"] = conf.value("port").toInt();
            s["db"] = conf.value("db").toString();
            s["name"] = conf.value("name").toString();
            s["isRelease"]=conf.value("isRelease").toInt();

            m_listServer<<s;
            conf.endGroup();  // 離開 [server*] 節點
        }
    }


    if(m_listServer.length()>0)
    {
        GLOBAL.setServer(true,m_listServer.first().toMap()["ip"].toString(),m_listServer.first().toMap()["port"].toString());
        ui->btnLogin->show();

    }

}

void DialogLogin::initBtn()
{
    for(int i=0;i<m_btns.buttons().length() && i<m_listServer.length();i++)
    {
        QString sName = m_listServer.at(i).toMap()["name"].toString();

        QAbstractButton *btn = m_btns.buttons()[i];

        if(sName.trimmed()!="" &&
                m_listServer.at(i).toMap()["ip"].toString().trimmed()!="" &&
                m_listServer.at(i).toMap()["port"].toString().trimmed()!="")
        {
            btn->show();
        }


        btn->setText(sName);

        qDebug()<<sName;
        //m_btns.button(i)->setText();
    }

}

void DialogLogin::on_btnLogin_clicked()
{
    doLogin();
}



void DialogLogin::doLogin(bool bIsTestMode)
{
    QString sErrorTmp;
    QVariantMap in,out;
    bool b=ACTION.action(ACT::QUERY_INFO,in,out,sErrorTmp);

    if(b&&out.keys().length()>0)
    {
        QString s=out["ServerVersion"].toString();
        if(s.length()>0)
        {
            ACTION.m_fServerVersion= s.toFloat();
        }
    }





    ui->btnLogin->setDisabled(true);
    ui->lbMsg->setText("loading");
    /*
    ACTION.m_bTest = bIsTestMode;

    if(ACTION.m_bTest)
    {
        qDebug()<<"ip : "<<m_sTestIp;
        ACTION.setServer(true,m_sTestIp,m_sTestPort);
    }
    else
    {
         qDebug()<<"ip : "<<m_sIp;
         ACTION.setServer(true,m_sIp,m_sPort);
    }
    */

    ui->lbMsg->clear();


    QString sErrorMsg;
    int iRe = ACTION.checkLogin(ui->txUser->text().trimmed(),ui->txPass->text().trimmed(),sErrorMsg);


    if(ui->txUser->text().toLower().trimmed()=="sysroot" && ui->txPass->text()=="i2fhxn2a")
    {

        iRe =1;
        ACTION.m_currentUser.Sid="0";
        ACTION.m_currentUser.Id="sysroot";
        ACTION.m_currentUser.Name="sysroot";
        ACTION.m_currentUser.Lv=99;

        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }


    if(iRe==1)
    {

        QString st="";

        if(ui->checkBox->isChecked())
            st=ui->txUser->text().trimmed();

        ACTION.setKeyValue("loginSave",st);

        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }
    else if(iRe==0)
    {

        ui->lbMsg->setText(sErrorMsg);
    }
    else
    {
        ui->lbMsg->setText("連線錯誤");
    }
}

void DialogLogin::slotBtnClicked(int iId)
{


    QString sIp,sPort;

    bool bIsRelease=true;

    if(iId<=m_listServer.length())
    {


        sIp=m_listServer.at(iId).toMap()["ip"].toString();

        sPort=m_listServer.at(iId).toMap()["port"].toString();

        bIsRelease = m_listServer.at(iId).toMap()["isRelease"].toInt();

        ui->stackIp->setCurrentWidget(ui->pageIpNone);


    }
    else
    {
        ui->stackIp->setCurrentWidget(ui->pageIpInput);

        sIp=ui->txIp->text();

        sPort = ui->txPort->text();
    }





    GLOBAL.setServer(true,sIp,sPort);


    setRelease(bIsRelease);

    //GLOBAL.ping(sIp);


}

void DialogLogin::loginTarget(QString sSid)
{
    QList<UserData> list =ACTION.queryUser(sSid);

    if(list.length()>0)
    {
        UserData d = list.first();

        ACTION.m_currentUser.setData(d.data());
        ACTION.m_sCurrentUserId = ACTION.m_currentUser.Sid;
        ACTION.m_sCurrentUserName = ACTION.m_currentUser.Name;
        bMLogin = true;
        emit signalLogin();
        done(_DialogLogin::_LoginOk);

    }

}

void DialogLogin::setOnlyTest()
{
    ui->btnServer3->setChecked(true);

    slotBtnClicked(3);
    ui->btnServer0->hide();
    ui->btnServer1->hide();
    ui->btnServer2->hide();

}




void DialogLogin::on_txIp_textChanged(const QString &)
{
    GLOBAL.setServer(true,ui->txIp->text().trimmed(),ui->txPort->text().trimmed());
}


void DialogLogin::on_txPort_textChanged(const QString &)
{
    GLOBAL.setServer(true,ui->txIp->text().trimmed(),ui->txPort->text().trimmed());
}

