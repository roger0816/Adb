#ifndef CLINKTABLE_H
#define CLINKTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QShowEvent>
#include <QResizeEvent>



namespace _CLinkTable {
enum _CELL_TYPE
{
    _TEXT,
    _TEXT_INPUT,
    _INT_INPUT,
    _DOUBLE_INPUT,
    _BTN_INPUT
};

}

class CLinkTable : public QWidget
{
    Q_OBJECT
public:
    explicit CLinkTable(QWidget *parent = nullptr);

    void setData(QVariantList data);

    void setEnableColKey(QStringList list);

    void setHeaderNameH(QStringList list);

    QTableWidgetItem *tbItem(QVariant dData, int iType=0);


 private:
    QVariantList m_listData;

    QStringList m_listColKey;

    QTableWidget *m_tb;

    void showEvent(QShowEvent *) override;

    void resizeEvent(QResizeEvent *) override;

    void reSetSize();

    void refresh();
signals:

};

#endif // CLINKTABLE_H
