#ifndef LAYERGETORDER1_H
#define LAYERGETORDER1_H

#include <QWidget>
#include "Global.h"
#include "GlobalUi.h"
#include "DialogNote.h"
#include <QCompleter>
#include <QStringListModel>
#include "LayerOrder.h"
#include <QStandardItemModel>
#include <QAbstractItemDelegate>

namespace Ui {
class LayerGetOrder1;
}

class LayerGetOrder1 : public QWidget
{
    Q_OBJECT

public:
    explicit LayerGetOrder1(QWidget *parent = nullptr);
    ~LayerGetOrder1();

    void init();

private slots:
    void on_tbUser_cellPressed(int row, int column);

    void on_tbOrder_cellPressed(int row, int column);

    void on_btnBackOrder_clicked();

    void on_btnFinish_clicked();

    void refresh();

    void on_btnChangeNote_clicked();

    void slotCancel();



    void on_btnDelayOrder_clicked();

    void on_btnFacChange_clicked();

    void on_btnFacCancel_clicked();

private:
    Ui::LayerGetOrder1 *ui;

   // QStandardItemModel m_model;
    enum _tbHeader{
        _User=0,
        _Name,
        _Id,
        _CustomerId,
        _CustomerName,
        _GameName,
        _Bouns,
        _Status,
        _Action,
        _Note1,
        _Note2

    };

    void refreshUser();

    QList<UserData> m_listOwner;

    QList<DataFactory> m_listFactory;

    CListPair m_listPayType;

    QVariantMap m_data;


    QString  m_currentDataKey="";

    LayerOrder *m_layerCost  = nullptr;

private:


    QString m_sPreSid="";

    bool m_bLockLoading = false;

};


//===============

class TaskD :public QThread
{
    Q_OBJECT
public:
    TaskD(QObject *parent=nullptr):QThread(parent)
    {

    }

    void fn()
    {


        qSort(listOrder->begin(),listOrder->end(),[=](const OrderData &v1, const OrderData &v2)
        {
            QString st1 =v1.OrderDate+v1.OrderTime;
            QString st2 =v2.OrderDate+v2.OrderTime;

            return st1<st2;

        });



        for(int i=0;i<listOrder->length();i++)
        {
            QStringList listKeyUser = m_data->keys();

            OrderData order = (*listOrder)[i];

            if(listKeyUser.indexOf(order.Owner)<0 &&order.Owner!="")
                continue;

            if(order.Step=="1" || (order.Step=="2" && order.PaddingUser.trimmed()!=""))
            {

                QVariantList list =(*m_data)[order.Owner].toList();

                list.append(order.data());

                (*m_data)[order.Owner] = list;
            }

        }


    }


    QVariantMap *m_data;
      QVariantList list;
    QList<OrderData> *listOrder;
    bool m_bStop = false;
private:
    void run()override
    {
        if(!m_bStop)
        {
            if(list.length()>0)
            {

                fn();


                list.pop_front();

                emit finished();
            }



           this->msleep(100);
        }

    }



signals:
    void finished();
};

#endif // LAYERGETORDER1_H
