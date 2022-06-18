#ifndef LAYEREXCHANGERATE_H
#define LAYEREXCHANGERATE_H

#include <QWidget>
#include <QShowEvent>
#include "Global.h"
#include "DialogMsg.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDoubleValidator>
#include <QDoubleSpinBox>

namespace Ui {
class LayerExchangeRate;
}

class LayerExchangeRate : public QWidget
{
    Q_OBJECT

public:
    explicit LayerExchangeRate(QWidget *parent = nullptr);
    ~LayerExchangeRate();

    void refresh();

public slots:

    void on_btnSave_clicked();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::LayerExchangeRate *ui;

    void showEvent(QShowEvent *) override;

    void setCell(int iRow, int iCol, double value);

    void setHistoryCell(int iRow,int iCol,QString value);

    double getCell(int iRow);
    QVariantList m_listRate;

    QStringList m_listKey;
    QStringList m_listHeaderName;
};

#endif // LAYEREXCHANGERATE_H
