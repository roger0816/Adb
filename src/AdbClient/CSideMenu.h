#ifndef CSIDEMENU_H
#define CSIDEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>


namespace Ui {
class CSideMenu;
}

class CSideMenu : public QWidget
{
    Q_OBJECT

public:
    explicit CSideMenu(QWidget *parent = nullptr);
    ~CSideMenu();

    void setBtns(QStringList listBtnName,bool bIsVBoxLayout = true , int baseSize=48);

    void setSubBtns(int iIdx,QStringList listBtnName);
private:
    QList<QPushButton*> m_listBtn;

    QList< QList<QPushButton*>> m_listSubBtn;
    QGridLayout* layoutBtns(QStringList listBtnName, QList<QPushButton*> &listBtn, bool bIsVBoxLayout = true );


    void setButtonStyle(int iPoint);



    QGridLayout *gridLayout;

QWidget *m_wBg;

    Ui::CSideMenu *ui;


};

#endif // CSIDEMENU_H
