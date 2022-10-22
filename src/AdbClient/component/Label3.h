#ifndef LABEL3_H
#define LABEL3_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

namespace LABEL_3 {
enum _INDEX{_Left=0,_Cent,_Right};
}

class Label3 : public QWidget
{
    Q_OBJECT
public:

    explicit Label3(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override ;

    void setCurrentIdx(int idx);

    void setText(QString sCurrentText);

    void setText(int idx,QString sText,QString sColorName="");

    void setText(QString sTextL, QString sTextC, QString sTextR);

    QString text();

    QString text(int iIdx);


    void setData(QVariantList data);

    QVariantList data();


    void setVisable(bool bL,bool bC,bool bR);

    void setFlag(bool b);

    void setBorder(bool b);

signals:
private:
    QString m_sText[3]={"aaaa","bbbbbbb","cccccc"};
    QString m_sColor[3] = {"","",""};
    bool m_bVisable[3]={true,true,true};
    int m_iIdx=0;
    bool m_bBorder=false;

    bool m_bFlag=false;
};

#endif // LABEL3_H
