#ifndef LAYERADDVALUETYPE_H
#define LAYERADDVALUETYPE_H

#include <QWidget>
#include "Global.h"
#include "DialogAddValueTypeEdit.h"
#include "GlobalUi.h"

namespace Ui {
class LayerAddValueType;
}

class LayerAddValueType : public QWidget
{
    Q_OBJECT

public:
    explicit LayerAddValueType(QWidget *parent = nullptr);
    ~LayerAddValueType();
    void showEvent(QShowEvent *) override;


    QVariantList m_listData;
private slots:
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void refresh();

private:
    Ui::LayerAddValueType *ui;
};

#endif // LAYERADDVALUETYPE_H
