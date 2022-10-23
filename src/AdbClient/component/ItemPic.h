#ifndef ITEMPIC_H
#define ITEMPIC_H

#include <QWidget>
#include <QLabel>
#include "Global.h"
#include <QFileDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QCryptographicHash>

namespace Ui {
class ItemPic;
}



class ItemPic : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPic(QWidget *parent = nullptr);
    ~ItemPic();

    QVariantMap data();

    void setData(QByteArray data);


private:
    QImage *m_img=nullptr;

    QString m_sFilePath="";

    QByteArray m_data=QByteArray();

    QDialog *m_dialogDetal=nullptr;

    QLabel *m_lbDetailPic ;


    void mousePressEvent(QMouseEvent *e) override;
private slots:
    void on_btnUpload_clicked(QString sFilePath="");

    void on_btnChip_clicked();

    void clear();

    void showDetail();

private:
    Ui::ItemPic *ui;
};

#endif // ITEMPIC_H
