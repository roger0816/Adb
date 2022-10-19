#ifndef LAYERSCHEDULE_H
#define LAYERSCHEDULE_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QShowEvent>
#include <QButtonGroup>
#include <QSpinBox>
#include <QMouseEvent>
#include "Label3.h"

#define SCHEDULE_STATUS_ID "999999"

namespace Ui {
class LayerSchedule;
}


namespace  Layer_Schedule{

struct Data
{

    QString sUserSid;
    QString sCost;
    QString sStatus;
    QString sStatusColor;
    QString sCheck="0";
    //if sText is not "" , it's normal text
    QString sText="";


    QString s3TextData()
    {
        return sUserSid+"::"+sCost+"::"+sStatus+"::"+sStatusColor;
    }

    void set3TextData(QString sTmp)
    {
        QStringList list = sTmp.split("::");

        if(list.length()>3)
        {
            sUserSid= list.first();
            sCost= list.at(1);
            sStatus= list.at(2);
            sStatusColor = list.at(3);

        }
        else if(list.length()>=1)
        {
            sText = list.first();
        }

    }

    void clear()
    {
        sUserSid="";
        sCost="";
        sStatus="";
        sStatusColor="";
        sCheck="0";
        sText="";
    }

};

}


class CLineEditClick : public QLineEdit
{
    Q_OBJECT
public:
    void mousePressEvent(QMouseEvent *) override
    {
        emit clicked();
    }

 signals:
    void clicked();

};



class LayerSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit LayerSchedule(QWidget *parent = nullptr);
    ~LayerSchedule();

    void setEditMode(bool b);

private:
    void showEvent(QShowEvent*) override;

    void refresh();


    QButtonGroup m_group;

    Layer_Schedule::Data m_data[128][7];



private slots:
    void on_btnSave_clicked();

    void on_btnName_clicked();

    void on_btnCost_clicked();

    void on_btnStatus_clicked();

    void on_tbUserList_itemClicked(QTableWidgetItem *item);


    void on_tb0_itemChanged(QTableWidgetItem *item);

    void on_btnChangeBtn_clicked();

    void btnsClicked();


    void delayRefresh();

    void on_btnNext_clicked();

    void on_btnPre_clicked();

    void on_tb0_cellClicked(int row, int column);

public slots:

private:
    Ui::LayerSchedule *ui;

    void changeTb();

    QList<QPushButton*> m_listBtn;

    void refreshCb();


    void write();

    void read();



     QStringList m_listVHeader;


     int checkDayOfWeek(QString yyyy,QString MM,QString dd);

     QString m_sYear="2022";
     QString m_sMonth="10";



     bool m_bEditMode= false;

     void checkUserList();

     void sendUserCheck(int iRow,int iCol);
};

#endif // LAYERSCHEDULE_H
