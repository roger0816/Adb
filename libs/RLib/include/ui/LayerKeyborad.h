#ifndef LAYERKEYBORAD_H
#define LAYERKEYBORAD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>

#include <QPropertyAnimation>

namespace Ui {
class LayerKeyborad;
}

class LayerKeyborad : public QWidget
{
    Q_OBJECT

public:
    explicit LayerKeyborad(QWidget *parent = 0);
    ~LayerKeyborad();

    static LayerKeyborad* Instance(QWidget *parent = 0);

    //setShow 跟 setBinding 都一樣，只差在 前者需用signals /slot去接輸入後的值
    void setBinding(QLineEdit *lineEdit);

    void setBinding(QLabel *lb);

    void setShow(QString sText);

private slots:

    void slotWordPressed();

    void slotWordReleased();

    void slotAniFinish();

    void callToolTip(bool bShow, QPushButton *target=0);

    void on_btnChange_clicked(bool checked);

    void on_btnSpace_clicked();



    void on_btnReturn_clicked();


    void on_btnSpChange_clicked(bool checked);

    void on_btnShift_clicked(bool checked);

    void on_btnSub2_clicked();

    void on_btnSub_clicked();

    void slotClear();


    void on_btnCancel_clicked();

private:
    Ui::LayerKeyborad *ui;

    QWidget *m_wBlockUi;

    static LayerKeyborad* m_kb;

    QPropertyAnimation m_ani;


    QLabel *m_lbTooltip;

    QList<QPushButton*> m_listBtnWord;

    QList<QPushButton*> m_listBtnSpWord;

    QStringList m_listTextSp[2];

    QPushButton *m_btnClear;
    void iniWord();

    void iniSpWord();


    void resizeEvent(QResizeEvent *);

    void showEvent(QShowEvent *);

    void aniShow();

    void aniHide();

signals:
    void signalText(QString sText);
};

#endif // LAYERKEYBORAD_H
