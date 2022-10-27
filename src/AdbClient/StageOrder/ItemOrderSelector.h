#ifndef ITEMORDERSELECTOR_H
#define ITEMORDERSELECTOR_H

#include <QWidget>
#include "GlobalUi.h"
#include "Global.h"
#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
namespace Ui {
class ItemOrderSelector;
}

class ItemOrderSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ItemOrderSelector(QWidget *parent = nullptr);
    ~ItemOrderSelector();

    void setBtns(QStringList list);

    QVariantList m_listFactoryClass;


private slots:
    void on_pushButton_clicked();
    void refresh();

    void slotClickedFactory(int id);
private:
    Ui::ItemOrderSelector *ui;

    void showEvent(QShowEvent *) override;



    QButtonGroup m_btns;

    QGridLayout *m_lay;



};

#endif // ITEMORDERSELECTOR_H
