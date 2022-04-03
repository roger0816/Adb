#ifndef STAGECUSTOMER_H
#define STAGECUSTOMER_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class StageCustomer;
}

class StageCustomer : public QWidget
{
    Q_OBJECT

public:
    explicit StageCustomer(QWidget *parent = nullptr);
    ~StageCustomer();

private:
    Ui::StageCustomer *ui;

    QButtonGroup m_btns;
};

#endif // STAGECUSTOMER_H
