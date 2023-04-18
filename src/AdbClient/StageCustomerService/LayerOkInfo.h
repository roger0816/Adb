#ifndef LAYEROKINFO_H
#define LAYEROKINFO_H

#include <QWidget>
#include "GlobalUi.h"
#include "Global.h"
#include <QVariantMap>

namespace Ui {
class LayerOkInfo;
}

class LayerOkInfo : public QWidget
{
    Q_OBJECT

public:
    explicit LayerOkInfo(QWidget *parent = nullptr);
    ~LayerOkInfo();
    bool m_bOrderMode=false;
    void setData(QVariantMap data);
signals:
    void back(int iIdx=1);
private slots:
    void on_btnCopy_clicked();

private:
    Ui::LayerOkInfo *ui;
    QVariantMap m_dData;
};

#endif // LAYEROKINFO_H
