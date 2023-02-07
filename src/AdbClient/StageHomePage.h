#ifndef STAGEHOMEPAGE_H
#define STAGEHOMEPAGE_H

#include <QWidget>
#include <QShowEvent>


#define HIDE_PIC 1

namespace Ui {
class StageHomePage;
}

class StageHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit StageHomePage(QWidget *parent = nullptr);
    ~StageHomePage();


    void showEvent(QShowEvent*) override;
private slots:
    void on_btnFn_clicked();

    void slotSavePic();

    void on_tabWidget_currentChanged(int);



private:
    Ui::StageHomePage *ui;

    bool m_bLock = false;
};

#endif // STAGEHOMEPAGE_H
