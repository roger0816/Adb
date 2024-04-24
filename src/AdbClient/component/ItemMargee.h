#ifndef ITEMMARGEE_H
#define ITEMMARGEE_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QResizeEvent>
#include <QTimer>
namespace Ui {
class ItemMargee;
}


struct DataMargee
{
    DataMargee() {}
    QString sName;
    QString sTitle;
    QString sText;
};

class ItemMargee : public QWidget
{
    Q_OBJECT

public:
    explicit ItemMargee(QWidget *parent = nullptr);
    ~ItemMargee();

    void appendText(QString sTitle, QString sName, QString st);
private:
    void reStart();


    QLabel *label;
    QTimer m_timer;

    int iX=0;

    void resizeEvent(QResizeEvent *) override;

    QList<DataMargee> m_list;

signals:
    void marqueeFinished();
private slots:
    void slotMove();
private:
    Ui::ItemMargee *ui;
};

#endif // ITEMMARGEE_H
